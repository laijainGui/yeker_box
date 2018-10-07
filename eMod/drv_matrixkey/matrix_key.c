/*
*********************************************************************************************************
*                                                    MELIS
*                                    the Easy Portable/Player Develop Kits
*                                           Matrix Key Driver Module
*
*                                    (c) Copyright 2006-2010, All winners Co,Ld.
*                                             All Rights Reserved
*
* File    : matrix_key.c
* By      : james deng <csjamesdeng@gmail.com>
* Version : 1.0.0
* Date    : 2011-04-25
* Descript:
* Update  : date              author         ver       notes
*           2011-04-25        james deng     1.0.0     build the file.
*********************************************************************************************************
*/
 
#include "drv_matrix_key_i.h"


#define MENU        0x00000001
#define VOL_ADD     0x00000002
#define VOL_DEC     0x00000004
#define LEFT        0x00000008
#define RIGHT       0x00000010
#define ENTER       0x00000020


static __u32 g_pw_off_support = 1;//Ϊ1�����ʹ��PA3�ڼ��ػ�����jtag�ڸ���

static __u32 input_row1 = 0;
static __u32 input_row2 = 0;
static __u32 output_col = 0;

static __u32 pw_off = 0;

/* ɨ������ */
static __s32 period;
/* �ػ�ʱ�� */
static __s32 pw_off_time;
/* ���������ӳٵ�ʱ�䣬��Ϊɨ�����ڵı���������û����� */
static __s32 key_down_delay;

static __s32 volatile is_power_off = EPDK_FALSE;
static __krnl_stmr_t *timer = NULL;

static __u8 matrix_key_tid = 0;

//���¶���Ϊ�˽������ϰ����������¿��ܳ��ֵİ���down��up��Ϣ����Ե����
static __u32 g_key_down_tbl[KEY_CNT] = {0};

/********************************************************************************************************
* Function:    matrix_key_read
* Description: read routine
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/

static __u32 matrix_key_read()
{
	__s32 d1 = 0, d2 = 0, d3 = 0;

	if(1 == g_pw_off_support)	/* ��Դ������ʱ���ȷ��� */
	{
		d1 = esPINS_ReadPinData(pw_off, 0);
		if (d1)
		{
			__msg("return KPAD_POWEROFF\n");
			return KPAD_POWEROFF;
		}
	}
    	
	esPINS_SetPinIO(input_row1, EPDK_FALSE, NULL);
	esPINS_SetPinIO(input_row2, EPDK_FALSE, NULL);
	esPINS_SetPinIO(output_col, EPDK_FALSE, NULL);

	esPINS_SetPinPull(input_row1, PIN_PULL_DOWN, NULL);//����ʱ��esPINS_SetPinPull
	esPINS_SetPinPull(input_row2, PIN_PULL_DOWN, NULL);
	esPINS_SetPinPull(output_col, PIN_PULL_DOWN, NULL);
	
	d1 = esPINS_ReadPinData(input_row1, NULL);
	if (d1)
	{
		return KPAD_VOICEUP;
	} 
    
	d2 = esPINS_ReadPinData(input_row2, 0);
	if (d2)
	{
		return KPAD_MENU;
	} 

    d3 = esPINS_ReadPinData(output_col, 0);
    if (d3)
    {
    	return KPAD_VOICEDOWN;
    } 

	esPINS_SetPinIO(output_col, EPDK_TRUE, NULL);
	esPINS_WritePinData(output_col, 1, NULL); 
	d1 = esPINS_ReadPinData(input_row1, NULL);
	if (d1)
	{
		return KPAD_LEFT;
	} 

	d2 = esPINS_ReadPinData(input_row2, 0);
	if (d2)
	{
		return KPAD_RIGHT;
	}

	esPINS_SetPinIO(input_row2, EPDK_TRUE, NULL);
	esPINS_WritePinData(input_row2, 1, NULL);
	d1 = esPINS_ReadPinData(input_row1, NULL);
	if (d1)
	{
		return KPAD_ENTER;
	}

    return 0;
}

/********************************************************************************************************
* Function:    matrix_key_down
* Description: matrix key down
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/
static void matrix_key_down(__u32 key_value)
{
    __key_msg_t msg;
    
    msg.key_value = key_value;
    msg.flag = 1;
    
    dev_matrix_key_ioctrl(0, DRV_KEY_CMD_PUTKEY, 0, &msg);

    g_key_down_tbl[key_value]++;
}

/********************************************************************************************************
* Function:    matrix_key_up
* Description: matrix key up
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/
static void matrix_key_up(__u32 key_value)
{
    __key_msg_t msg;

    if(g_key_down_tbl[key_value] > 0)
    {
        g_key_down_tbl[key_value]--;
    }
    else
    {
        return ;
    }
    
    msg.key_value = key_value;
    msg.flag = 0;
    
    dev_matrix_key_ioctrl(0, DRV_KEY_CMD_PUTKEY, 0, &msg);
}

//ȫ�������ɿ������ڲ��䷢��δ���͵�key up��Ϣ
static void matrix_match_key_down(void)
{
    __s32 i;
    __s32 key_cnt;

    key_cnt = sizeof(g_key_down_tbl)/sizeof(g_key_down_tbl[0]);

    for(i = 0 ; i < key_cnt ; i++)
    {
        while(g_key_down_tbl[i] > 0)
        {
            matrix_key_up(i);
        }
    }
}

/********************************************************************************************************
* Function:    power_off_timer
* Description: 
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/
static void power_off_timer(void* arg)
{
    matrix_key_down(KPAD_POWEROFF);
    matrix_key_up(KPAD_POWEROFF);
	is_power_off = EPDK_TRUE;
}

/********************************************************************************************************
* Function:    matrix_key_thread
* Description: matrix key running thread
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/
static void matrix_key_thread(void *p_arg)
{    
    __u32 old_key, new_key, key = 0;
	__s32 delay;

    //���¶��������Զ�����
    static int auto_test_enable;
    
    {//�����debugģʽ�����Զ����ԣ������ϵͳ��������Ϣ
        if(EPDK_OK == esCFG_GetKeyValue("auto_test_para", "auto_test_enable", &auto_test_enable, 1))
        {
            __msg("***********auto_test_enable********=%d\n", auto_test_enable);
        }
        else
        {
            auto_test_enable = 0;
        }
        __msg("***********auto_test_enable********=%d\n", auto_test_enable);
    } 
    
    while (1)
    {
        if (esKRNL_TDelReq(OS_PRIO_SELF) == OS_TASK_DEL_REQ)
        {
            break;
        }              

		old_key = matrix_key_read();
        //enter�������ȼ�⣬����������enter����
        //˵��enter��û�����»����Ѿ�̧�������ö�ʱ��,��ֹ��ϼ���ʱ��ػ���������ȷ
        if(KPAD_POWEROFF != old_key && old_key)
        {
            __msg("stop pw-off timmer...\n");
            if (esKRNL_TmrStateGet(timer) == OS_TMR_STATE_RUNNING)
    		{
    			esKRNL_TmrStop(timer, OS_TMR_OPT_NONE, NULL);

    			if (is_power_off)
    			{
    				is_power_off = EPDK_FALSE;
    			}
            }
        }
        
        
		delay = 0;
        __here__;
		while (1)
		{
			esKRNL_TimeDly(period);
			new_key = matrix_key_read();
            //enter�������ȼ�⣬����������enter����
            //˵��enter��û�����»����Ѿ�̧�������ö�ʱ��,��ֹ��ϼ���ʱ��ػ���������ȷ        
            if(KPAD_POWEROFF != new_key && new_key)
            {
                __msg("stop pw-off timmer...\n");
                if (esKRNL_TmrStateGet(timer) == OS_TMR_STATE_RUNNING)
        		{
        			esKRNL_TmrStop(timer, OS_TMR_OPT_NONE, NULL);
        			if (is_power_off)
        			{
        				is_power_off = EPDK_FALSE;
        			}
                }
            }

			if (new_key) /* ����һ����Чֵ */
			{
                __here__;
				/* ǰ�����ζ�����ֵ��ͬ������ǰ�������ֵ��Ч */
				if ((new_key ^ old_key) && old_key)
				{
                    __msg("new_key=%d\n", new_key);
                    __msg("old_key=%d\n", old_key);
                    __here__;
					break;
				}
                __here__;

                if(KPAD_VOICEUP== new_key)//�簴����menu������ʼ�Զ�����
                {
                    __here__;
                    if(1 == auto_test_enable)
                    {
                        __here__;
                        while(1)
                        {        
                            __here__;
                            matrix_key_down(KPAD_RIGHT);

                            esKRNL_TimeDly(2);
                            matrix_key_up(KPAD_RIGHT);

                            esKRNL_TimeDly(10+eLIBs_ramdom(20));
                            continue;                    
                        }
                    }
                }
				
				delay += period;

				if (new_key == KPAD_POWEROFF)
				{
                    __msg("start pw-off timmer...\n");
					/* start timer if not start, otherwise do nothing */
					if (esKRNL_TmrStateGet(timer) == OS_TMR_STATE_STOPPED)
					{
					    key = new_key;
						esKRNL_TmrStart(timer);
					}
				}
				else if (!(delay ^ key_down_delay))
				{
                    __here__;
					/* ������Ϣǰ����Ƿ��ӳ��Ƿ�ﵽ�����趨����ֵ */
				    key = new_key;
				    matrix_key_down(key);
				}
                __here__;
			}
			else if (key) /* �������� */
			{
                __here__;
			    if (key == KPAD_POWEROFF)
			    {
                    __msg("stop pw-off timmer...\n");
                    if (esKRNL_TmrStateGet(timer) == OS_TMR_STATE_RUNNING)
    				{
    					esKRNL_TmrStop(timer, OS_TMR_OPT_NONE, NULL);
    
    					if (is_power_off)
    					{
    						is_power_off = EPDK_FALSE;
    					}
    					else
    					{
    						/* ������Ϣǰ����Ƿ��ӳ��Ƿ�ﵽ�����趨����ֵ */
    						if (delay >= key_down_delay)
    						{
    	                        matrix_key_down(KPAD_ENTER);
                                esKRNL_TimeDly(10);
    	                        matrix_key_up(KPAD_ENTER);
    						}
    					}
    				}
    			}
				else
				{
                    __here__;
				    matrix_key_up(key);
				}
				
				key = 0;
			    break; /* �˳���ѭ�� */
			}
			else /* ����һ����Чֵ */
			{
                __here__;
			    delay = 0;
                matrix_match_key_down();
			}
		}
    }
}

/********************************************************************************************************
* Function:    matrix_key_init
* Description: initial matrix key
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/
__s32 matrix_key_init(void)
{
    __s32            ret;
    user_gpio_set_t  gpio_set[1];

    {//�����debugģʽ�����pw-off�ڸ�jtag��
        __target_para_t target;
        esKSRV_GetTargetPara(&target);
        __msg("target.debugenable=%d\n", target.debugenable);
        if(target.debugenable == EPDK_TRUE)
        {
            g_pw_off_support = 0;
        }
        else
        {
            g_pw_off_support = 1;
        }
    }   

	/* ����input_row1 */
    eLIBs_memset(gpio_set, 0, sizeof(user_gpio_set_t));
    ret = esCFG_GetKeyValue("matrixkey_para", "input_row1", (int *)gpio_set, sizeof(user_gpio_set_t)/4);
    if (!ret)
    {
        input_row1 = esPINS_PinGrpReq(gpio_set, 1);
        if (!input_row1)
        {
            __wrn("request input_row1 pin failed\n");
            return EPDK_FAIL;
        }
    }
    else
    {
        __wrn("fetch para from script failed\n");
        return EPDK_FAIL;
    }

	ret = esPINS_SetPinPull(input_row1, PIN_PULL_DOWN, NULL);
	if (ret)
	{
		__wrn("pull input_row1 failed\n");
		return EPDK_FAIL;
	}

	/* ����input_row2 */
    eLIBs_memset(gpio_set, 0, sizeof(user_gpio_set_t));
    ret = esCFG_GetKeyValue("matrixkey_para", "input_row2", (int *)gpio_set, sizeof(user_gpio_set_t)/4);
    if (!ret)
    {
        input_row2 = esPINS_PinGrpReq(gpio_set, 1);
        if (!input_row2)
        {
            __wrn("request input_row2 pin failed\n");
            return EPDK_FAIL;
        }
    }
    else
    {
        __wrn("fetch para from script failed\n");
        return EPDK_FAIL;
    }

	ret = esPINS_SetPinPull(input_row2, PIN_PULL_DOWN, NULL);
	if (ret)
	{
		__wrn("pull input_row2 failed\n");
		return EPDK_FAIL;
	}

	/* ����output_col */
    eLIBs_memset(gpio_set, 0, sizeof(user_gpio_set_t));
    ret = esCFG_GetKeyValue("matrixkey_para", "output_col", (int *)gpio_set, sizeof(user_gpio_set_t)/4);
    if (!ret)
    {
        output_col = esPINS_PinGrpReq(gpio_set, 1);
        if (!output_col)
        {
            __wrn("request output_col pin failed\n");
            return EPDK_FAIL;
        }
    }
    else
    {
        __wrn("fetch para from script failed\n");
        return EPDK_FAIL;
    }

	ret = esPINS_SetPinPull(output_col, PIN_PULL_UP, NULL);
	if (ret)
	{
		__wrn("pull output_col failed\n");
		return EPDK_FAIL;
	}
	
    if(1 == g_pw_off_support)
    {
    	/* ����Power Off */
    	eLIBs_memset(gpio_set, 0, sizeof(user_gpio_set_t));
    	ret = esCFG_GetKeyValue("matrixkey_para", "pw_off", (int *)gpio_set, sizeof(user_gpio_set_t)/4);
    	if (!ret)
    	{
    		pw_off = esPINS_PinGrpReq(gpio_set, 1);
    		if (!pw_off)
    		{
    			__wrn("request Power Off pin failed\n");
    			return EPDK_FAIL;
    		}
    	}
    	else
    	{
    		__wrn("fetch para from script failed\n");
    		return EPDK_FAIL;
    	}
    }

	/* ��ȡɨ������ */
	ret = esCFG_GetKeyValue("matrixkey_para", "period", &period, 1);
	if (ret)
	{
	    __wrn("fetch para: period from script failed\n");
	    period = 2;
	}
	__msg("matrix key update period: %d\n", period);
	
	/* ��ȡ�ػ�ʱ�� */
	ret = esCFG_GetKeyValue("matrixkey_para", "pw_off_time", &pw_off_time, 1);
	if (ret)
	{
	    __wrn("fetch para: pw_off_time from script failed\n");
		pw_off_time = 2000;
	}
	__msg("power off time: %d\n", pw_off_time);

	/* ��ȡ���������ӳٵ�ʱ�� */
	ret = esCFG_GetKeyValue("matrixkey_para", "key_down_delay", &key_down_delay, 1);
	if (ret)
	{
		__wrn("fetch para: key_down_delay from script failed\n");
		key_down_delay = 3 * period;
	}
	__msg("key down delay: %d\n", key_down_delay);

	/* ����timer */
	timer = esKRNL_TmrCreate(
				pw_off_time, 
				OS_TMR_OPT_PRIO_HIGH | OS_TMR_OPT_PERIODIC,
				(OS_TMR_CALLBACK)power_off_timer,
				NULL);
	if (!timer)
	{
		__wrn("create timer failed\n");
		esKRNL_TmrDel(timer);
		timer = NULL;
	}

    matrix_key_tid = esKRNL_TCreate(matrix_key_thread, 0, 0x800, KRNL_priolevel1);
    
    __msg("matrix key init finish\n");
    
    return EPDK_OK;
}

/********************************************************************************************************
* Function:    matrix_key_exit
* Description: exit matrix key
* Input��      
* Output��     
* Other��      
*********************************************************************************************************/
__s32 matrix_key_exit(void)
{
    esPINS_PinGrpRel(input_row1, 0);
    esPINS_PinGrpRel(input_row2, 0);
    esPINS_PinGrpRel(output_col, 0);
    if(1 == g_pw_off_support)
	{
        esPINS_PinGrpRel(pw_off, 0);
    }
    

    esKRNL_TDel(matrix_key_tid);

	if (!timer)
	{
		esKRNL_TmrDel(timer);
		timer = NULL;
	}

    __msg("matrix key exit finish\n");
    
    return EPDK_OK;
}