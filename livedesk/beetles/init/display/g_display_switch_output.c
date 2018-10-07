/*
************************************************************************************************************************
*                                                     close screen
*
*                                  Copyright(C), 2006-2010, AllWinner Technology Co., Ltd.
*											       All Rights Reserved
*
* File Name   : g_display_switch_output.c
*
* Author      : Jackie.Chen
*
* Version     : 1.0
*
* Date        : 2010.10.28
*
* Description :
* 
* Others      : None at present.
*
*
* History     :
*
*  <Author>        <time>       <version>      <description>
*
* Jackie.Chen      2010.10.28        1.0         build the file
*
************************************************************************************************************************
*/

#include "..\\mod_init_i.h"

#define EVB 0

static void __board_config(ES_FILE *p_disp, __u32 epdkmode)
{
	__u32	arg[3];
#if EVB 
#else
	__here__
	switch(epdkmode)
	{
		case DISP_TV_MOD_PAL:
		case DISP_TV_MOD_NTSC:
		case DISP_TV_MOD_PAL_M:
		case DISP_TV_MOD_PAL_NC:
		{
			arg[0] = 0;		//DAC0
			arg[1] = DISP_TV_DAC_SRC_COMPOSITE;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);

			arg[0] = 1;		//DAC1
			arg[1] = DISP_TV_DAC_SRC_NONE;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);

			arg[0] = 2;		//DAC2
			arg[1] = DISP_TV_DAC_SRC_NONE;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);

			arg[0] = 3;		//DAC3
			arg[1] = DISP_TV_DAC_SRC_NONE;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);
		}
		case DISP_TV_MOD_PAL_SVIDEO:
		case DISP_TV_MOD_PAL_CVBS_SVIDEO:
		case DISP_TV_MOD_NTSC_SVIDEO:  
	    case DISP_TV_MOD_NTSC_CVBS_SVIDEO:
	    case DISP_TV_MOD_PAL_M_SVIDEO:      
	    case DISP_TV_MOD_PAL_M_CVBS_SVIDEO:
	    case DISP_TV_MOD_PAL_NC_SVIDEO:       
	    case DISP_TV_MOD_PAL_NC_CVBS_SVIDEO:  
		{
			break;
		}
		default:		
		{
			arg[0] = 0;		//DAC0
			arg[1] = DISP_TV_DAC_SRC_Y;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);
			
			arg[0] = 1;		//DAC1
			arg[1] = DISP_TV_DAC_SRC_PB;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);

			arg[0] = 2;		//DAC2
			arg[1] = DISP_TV_DAC_SRC_PR;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);

			arg[0] = 3;		//DAC3
			arg[1] = DISP_TV_DAC_SRC_NONE;
			arg[2] = 0;
			eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_DAC_SOURCE, 0, (void*)arg);	
			break;
		}
	}
#endif
}

static __hdle           pc11_hdl = 0;

static __s32 __app_pullup_tv_en(void)
{  
    __s32            ret;
    user_gpio_set_t  gpio_set[1];  

    if(!pc11_hdl)
    {
        /* ����tv_en */
        eLIBs_memset(gpio_set, 0, sizeof(user_gpio_set_t));
        ret = esCFG_GetKeyValue("tvout_para", "tv_en", (int *)gpio_set, sizeof(user_gpio_set_t)/4);
        if (!ret)
        {
            pc11_hdl = esPINS_PinGrpReq(gpio_set, 1);
            if (!pc11_hdl)
            {
                __msg("request output_col pin failed\n");
                return EPDK_FAIL;
            }
        }
        else
        {
            __msg("fetch para from script failed\n");
            return EPDK_FAIL;
        }
    }
		
	//ret = esPINS_SetPinPull(pc11_hdl, PIN_PULL_UP, NULL);

    ret = esPINS_WritePinData(pc11_hdl, 1, NULL);
	if (ret)
	{
		__msg("pull output_col failed\n");
		return EPDK_FAIL;
	}
    else
    {
        __msg("esPINS_SetPinPull success\n");
    }

    //esPINS_PinGrpRel(pc11_hdl, 0);//��Ҫ�ͷţ������������
}

static __s32 __app_pulldown_tv_en(void)
{  
    __s32            ret;
    user_gpio_set_t  gpio_set[1];
    
	if(!pc11_hdl)
    {
        /* ����tv_en */
        eLIBs_memset(gpio_set, 0, sizeof(user_gpio_set_t));
        ret = esCFG_GetKeyValue("tvout_para", "tv_en", (int *)gpio_set, sizeof(user_gpio_set_t)/4);
        if (!ret)
        {
            pc11_hdl = esPINS_PinGrpReq(gpio_set, 1);
            if (!pc11_hdl)
            {
                __msg("request output_col pin failed\n");
                return EPDK_FAIL;
            }
        }
        else
        {
            __msg("fetch para from script failed\n");
            return EPDK_FAIL;
        }
    }
		
	//ret = esPINS_SetPinPull(pc11_hdl, PIN_PULL_DOWN, NULL);

    ret = esPINS_WritePinData(pc11_hdl, 0, NULL);
	if (ret)
	{
		__msg("pull output_col failed\n");
		return EPDK_FAIL;
	}
    else
    {
        __msg("esPINS_SetPinPull success\n");
    }

    //esPINS_PinGrpRel(pc11_hdl, 0);//��Ҫ�ͷţ������������
}

/*********************************************************************
* Method	 :    		set_hpCom_driver_mode
* Description: set driver mode of head phone
* Parameters : 
	@__bool isDcDriveMode : 1 if DC drive mode, 0 if AC drive mode
* Returns    :   __s32
* Note       :
*********************************************************************/
static __s32 set_hpCom_driver_mode(__bool isDcDriveMode)
{
    ES_FILE* pAuCtrl = eLIBs_fopen("b:\\AUDIO\\CTRL","r+");
    if(!pAuCtrl){
        __wrn("Fail to open Audio control dev.\n");
        return EPDK_FAIL;
    }
    eLIBs_fioctrl(pAuCtrl, AUDI_DEV_CMD_SET_HPCOM_DRIVE_MODE, isDcDriveMode, NULL);

    eLIBs_fclose(pAuCtrl);
    return EPDK_OK;
}

static __s32 __switch_output(__lion_disp_format_e mode)
{
	ES_FILE      		   	*p_disp;
	__u32                	epdkmode;
	__disp_output_type_t 	output;
	__u32					arg[3];
	//__u32					result;
	
	epdkmode = dsk_display_dskfmt2epdkfmt(mode, &output);	
	
	/*open display driver handle*/
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp)
	{
		__err("open display device fail!\n");
	}
	//dsk_volume_off();
    if(output == DISP_OUTPUT_TYPE_LCD)
    {    	 
        __app_pulldown_tv_en();
        set_hpCom_driver_mode(1);
		//dsk_set_audio_if(AUDIO_DEV_IF_CODEC);//112358
    }     
	else if(output == DISP_OUTPUT_TYPE_TV)
	{   		
        __app_pullup_tv_en();
        set_hpCom_driver_mode(0);
		//__board_config(p_disp, epdkmode);
		arg[0] = epdkmode;
		arg[1] = 0;
		arg[2] = 0;
	    eLIBs_fioctrl(p_disp, DISP_CMD_TV_SET_MODE, 0, (void *)arg);
	    //dsk_set_audio_if(AUDIO_DEV_IF_CODEC);//112358
	}
	else if(output == DISP_OUTPUT_TYPE_VGA)
	{     
		arg[0] = epdkmode;
		arg[1] = 0;
		arg[2] = 0;
	    eLIBs_fioctrl(p_disp, DISP_CMD_VGA_SET_MODE, 0, (void *)arg);	    
	    dsk_set_audio_if(AUDIO_DEV_IF_CODEC);
	}
	else if(output == DISP_OUTPUT_TYPE_HDMI)
	{     
		arg[0] = epdkmode;
		arg[1] = 0;
		arg[2] = 0;
	    eLIBs_fioctrl(p_disp, DISP_CMD_HDMI_SET_MODE, 0, (void *)arg);		
	    dsk_set_audio_if(AUDIO_DEV_IF_IIS);
	}     
	eLIBs_fclose(p_disp);	
	//������	
	dsk_volume_on();
	
	return  EPDK_OK;
}

__s32 g_display_switch_output(__lion_disp_format_e mode)
{	
	__disp_output_type_t 	output;

    {
        reg_system_para_t* para;
        para = (reg_system_para_t*)dsk_reg_get_para_by_app(REG_APP_SYSTEM);
        if(para)
        {
            if(para->output == mode)
            {
                return EPDK_OK;
            }
            para->output = mode;
            //dsk_reg_flush();
        }
    }    
	
	dsk_display_dskfmt2epdkfmt(mode, &output);

	if(output != DISP_OUTPUT_TYPE_TV)
	{
		SEND_MSG(DSK_MSG_ASSISTANT_SCENE_DELETE, 0, GUI_WinGetHandFromName("init"), 0, 0); 
	}
	if(dsk_wkm_is_open())
	{
		dsk_wkm_pause();
	}
	//�رյ�ǰ��ʾ
	dsk_display_off();
	
	//����	
	__switch_output(mode);	
	
	//֪ͨinit  ����	
	SEND_MSG(DSK_MSG_SCREEN_SWITCH, 0, GUI_WinGetHandFromName("init"), mode, 0); 
	
	//toplevel  ��activity  ���´���UI ����
	//activity_suspend_top();
	//activity_resume_top();
	
	//����ʾ
	dsk_display_on(output);	
	esKRNL_TimeDly(100);
	if(dsk_wkm_is_open())
	{
		dsk_wkm_resume_play();
	}
	if(output == DISP_OUTPUT_TYPE_TV)
	{
		//SEND_MSG(DSK_MSG_ASSISTANT_SCENE_CREATE, 0, GUI_WinGetHandFromName("init"), 0, 0); 
	}
	
	return  EPDK_OK;
}

