/*
************************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						          (c) Copyright 2007-2010, Jackie, China
*										All Rights Reserved
*
* File    		: init_server.c
* By      		: Jackie.chen
* Func		: init server 
* Version	: v1.0
* ======================================================================================================================
* 2010-10-25  Jackie.chen  create this file, implements the fundemental interface;
************************************************************************************************************************
*/

//#include "apps.h"
#include "mod_init_i.h"
#include "init_server.h"
#include "live_init.h"
#include "dialog_scene\\dialog_scene.h"
#include "headbar\\headbar_com.h"
#include "assistant_scene\\assistant_scene.h"

#define OPEN_CURSOR				0
#define	AUTO_OFF_TIME_ID		1000
#define CLOSE_SCN_TIME_ID		1001
#define LOW_POWER_CHECK_TIME_ID	1002
#define CURSOR_TIME_ID			1003
#define SCREENSAVER_TIME_ID		1004

static __bool g_b_enable_standby = 1;

#define INIT_FW_UPDATE_MAX_ICON_RES_NUM 2

extern GUI_FONT    *SWFFont;

typedef struct  
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 res_id[INIT_FW_UPDATE_MAX_ICON_RES_NUM];
	HTHEME res_hdl[INIT_FW_UPDATE_MAX_ICON_RES_NUM];	
}init_fw_update_rect_t;

typedef enum
{		
    init_fw_update_prog_bg=0,
	init_fw_update_prog_left,
	init_fw_update_prog_mid,
	init_fw_update_prog_cursor,	
	init_fw_update_prog_icon_num
}init_fw_update_icon_t;

void init_lock(__gui_msg_t *msg)
{
	__u8 err;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);	
	esKRNL_SemPend(init_ctr->state_sem, 0, &err);	
	return;
}

void init_unlock(__gui_msg_t *msg)
{
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	esKRNL_SemPost(init_ctr->state_sem);
}

static void init_cursor_create(__init_ctl_t *m_ctl)
{
	HTHEME 	h_them_cursor;
	HTHEME 	h_them_pal;
	__pos_t	pos;
	int 	width, height;	
	
    __err("headbar");
	h_them_cursor = dsk_theme_open(0);	
	m_ctl->cursor_bmp = dsk_theme_hdl2buf(h_them_cursor);
	
	m_ctl->cursor_info.pat_mem = m_ctl->cursor_bmp + 54 + 1024;		
	
    h_them_pal = dsk_theme_open(0);	
	m_ctl->cursor_info.palette = dsk_theme_hdl2buf(h_them_pal);
	
	GUI_CursorCreate(&(m_ctl->cursor_info));
	
	dsk_display_get_size(&width, &height);
	
	pos.x = width/2;
	pos.y = height/2;
	
	GUI_CursorSetPos(&pos);
	GUI_CursorHide();	
}

static void init_cursor_delete(__init_ctl_t *m_ctl)
{
	eLIBs_free(m_ctl->cursor_info.palette);
	eLIBs_free(m_ctl->cursor_bmp);
	
	GUI_CursorDelete();
}

static void system_message_handle(void *arg)
{
	init_scene_t *p_scene;	
	H_WIN h_wnd = (H_WIN)arg;	
	
	while(1)
	{		
		if( esKRNL_TDelReq(OS_PRIO_SELF) == OS_TASK_DEL_REQ )
		{			
			esKRNL_TDel(OS_PRIO_SELF);			
			return;
		}
		
		//orchid update
		p_scene = (init_scene_t *)GUI_WinGetAddData(h_wnd);
		
		if(p_scene->orchid_update == EPDK_TRUE)
		{
			//dsk_orchid_update();			
			//NOTIFY_MSG(DSK_MSG_ORCHID_UPDATE_END, NULL, h_wnd, 0, 0);
		}

		esKRNL_TimeDly(1);
	}	
}

static __s32 sys_msg_handle_init(__gui_msg_t *msg)
{	
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);	
	
	/*����system_message_handle �߳� */
	init_ctr->sys_msg_handle_tid = esKRNL_TCreate( system_message_handle, (void*)msg->h_deswin, 0x800, KRNL_priolevel5 );
	
	return EPDK_OK;
}

static __s32 sys_msg_handle_exit(__gui_msg_t *msg)
{	
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	/* ɾ��system_message_handle �߳� */
	while( esKRNL_TDelReq(init_ctr->sys_msg_handle_tid) != OS_TASK_NOT_EXIST )
	{		
		esKRNL_TimeDly(1);		
	}
	
	init_ctr->sys_msg_handle_tid = 0;
	
	return EPDK_OK;
}

static __s32 init_low_power_proc(__gui_msg_t *msg)
{
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	if( !init_ctr->usb_connect )
	{		
		/* �˳�Ӧ�ó���*/
		//activity_return_home(NULL);			
		//activity_kill_all_backgrd();	
		__here__;
		activity_finish_all();
		/* low power dialog */		
		{
			init_scene_t *p_scene;
			p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
			p_scene->low_power = EPDK_TRUE;
			scene_on_dialog(msg);
		}		
	}
	
	return EPDK_OK;
}

static __s32 init_restart_close_scn(__gui_msg_t *msg)
{
	__bool exist;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);

	if( init_ctr->closescn_timeout == 0 )
		return EPDK_OK;

	exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);
	if( exist == EPDK_TRUE )
	{
		GUI_ResetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
	}
	else
	{
		GUI_SetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
	}
	return EPDK_OK;
}

static __s32 init_power_off_proc(__gui_msg_t * msg)
{	
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	if( !init_ctr->usb_connect )
	{	
		init_scene_t *p_scene;
		//activity_return_home(NULL);		
		//activity_kill_all_backgrd();		
		activity_finish_all();
		gscene_bgd_set_state(BGD_STATUS_SHOW);
		gscene_hbar_set_state(HBAR_ST_HIDE);
		/* poweroff dialog */		
		p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
		p_scene->power_off = EPDK_TRUE;
		__here__;
		scene_on_dialog(msg);		
		__here__;
        if(EPDK_FALSE == p_scene->usb_plug_in)//usb���ӵ����ѹػ��Ի���رպ󣬳���Ӧ������ִ�У�ֻ��usbδ���Ӳ��ܹػ�
        {
            __msg("NOTIFY_MSG(GUI_MSG_CLOSE\n");
		    //notify "init" to exit
		    NOTIFY_MSG(GUI_MSG_CLOSE, 0, msg->h_deswin, 0, 0);
        }
		__here__;	
	}

	return EPDK_OK;
}

static __s32 init_usb_device_plugin_proc(__gui_msg_t * msg)
{
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
    
	/* ֪ͨ��������������Ӧ�ó����˳� */	
	init_ctr->usb_connect = EPDK_TRUE;	

	
	//activity_return_home(NULL);	
	//activity_kill_all_backgrd();	
	//activity_suspend_top();
	activity_finish_all();
	if(dsk_wkm_is_open())
	{
		dsk_wkm_close();
	}
	gscene_bgd_set_state(BGD_STATUS_SHOW);
	gscene_hbar_set_state(HBAR_ST_HIDE);
	/* usb dialog */		
	{
		init_scene_t *p_scene;
		p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
		p_scene->usb_connect= EPDK_TRUE;
		scene_on_dialog(msg);
	}
	
	return EPDK_OK;
}

static __s32 init_usb_device_plugout_proc(__gui_msg_t *msg)
{
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	init_ctr->usb_connect = EPDK_FALSE;			
	{
		init_scene_t *p_scene;
		p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
		p_scene->usb_connect= EPDK_FALSE;
		scene_on_dialog(msg);
        p_scene->usb_plug_in = EPDK_FALSE;
	}
	
	return EPDK_OK;
}

/* ֪ͨ��Ӧ�ó��� ����orchid��ʼ */
static __s32 init_orchid_update_start(__gui_msg_t * msg)
{	
	{
		init_scene_t *p_scene;
		p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
		p_scene->orchid_update= EPDK_TRUE;
		scene_on_dialog(msg);
	}

	return EPDK_OK;
}

/* ֪ͨ��Ӧ�ó��� ����orchid���� */
static __s32 init_orchid_update_end(__gui_msg_t * msg)
{
	{
		init_scene_t *p_scene;
		p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
		p_scene->orchid_update= EPDK_FALSE;		
	}

	return EPDK_OK;	
}

/** 
 * ���� 
 */
static __s32 init_close_screen(__gui_msg_t *msg)
{	
	__disp_output_type_t output;
	//__gui_msg_t msgex;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	output = dsk_display_get_output_type();
	if( output == DISP_OUTPUT_TYPE_LCD )
	{
		/* �ù���״̬λ */
		init_lock(msg);
		
		if( !init_ctr->screen_close_done )	/* δ���� */
		{
			init_ctr->screen_close_done = EPDK_TRUE;	
			init_unlock(msg);           
            
			/* ������ʾ����, ���� */
			dsk_display_lcd_off();	

            if( !(EPDK_TRUE == activity_all_able_standby() && !dsk_wkm_is_playing() && !dsk_radio_is_open()
                && g_is_enable_standby()))
            {
                //__init_decr_freq(msg);//112350               
            }
            
			/*{
				ES_FILE      		   	*p_disp;

				p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
				if(!p_disp)
				{
					__err("open display device fail!\n");
				}
				eLIBs_fioctrl(p_disp, DISP_CMD_CLK_OFF, 0, 0);
				eLIBs_fclose(p_disp);	
			}*/
			//notify top			
			/*msgex.id 			= DSK_MSG_SCREEN_CLOSE;
			msgex.h_srcwin 		= 0;
			msgex.h_deswin 		= 0;
			msgex.dwAddData1 	= 0;
			msgex.dwAddData2 	= 0;
			activity_notify_top(&msgex);	*/		
			
			/* ���� standby */			
			__here__;
			if( EPDK_TRUE == activity_all_able_standby() && !dsk_wkm_is_playing() && !dsk_radio_is_open()
                && g_is_enable_standby())
			{
				ES_FILE *pfile = NULL;

                //����standby֮ǰж��host��������ֹstandby���Ѻ��ϲ���host
                init_ctr->usb_host_is_working_before_standy = dsk_usbh_is_working();
                if(init_ctr->usb_host_is_working_before_standy)
                {                    
                    __s32 cnt = 0;
                    dsk_send_rmmod_usbh_cmd();
                    while(dsk_usbh_is_working())
                    {
                        esKRNL_TimeDly(20);
                        cnt++;
                        if(cnt > 50)
                        {
                            break;
                        }
                    }
                }
            	__here__;
	            pfile = eLIBs_fopen("b:\\AUDIO\\CTRL", "r+");
	            if(pfile)
	            {
	                //system will enter standby, set audio device to standby mode for power save	                
	                dsk_speaker_turnoff();	                
	                eLIBs_fioctrl(pfile, AUDIO_DEV_CMD_ENTER_STANDBY, 0, 0);
	            }				
	         	__here__;		
				esPWM_EnterStandby( init_ctr->autooff_timeout/100);	
                
                __here__;				
	            if(pfile)
	            {
	                //active audio device
	                eLIBs_fioctrl(pfile, AUDIO_DEV_CMD_EXIT_STANDBY, 0, 0);	                
	                esKRNL_TimeDly(10);
	                dsk_speaker_resume();	                
	                eLIBs_fclose(pfile);
	                pfile = NULL;
	            }
                
                __here__;
                init_open_screen(msg);
                init_close_screensaver(msg);

                //�˳�֮�����¼���host driver
                if(init_ctr->usb_host_is_working_before_standy)
                {
                    dsk_send_insmod_usbh_cmd();
                    init_ctr->usb_host_is_working_before_standy = 0;
                }
			}			
		}
		else									/* �Ѿ����� */
		{
			init_unlock(msg);
		}
	
	}
	return EPDK_OK;
}

static __u32 cpu_clk = 0;
static __u32 sdram_clk = 0;
  
static __s32 __init_decr_freq(__gui_msg_t *msg)
{   
    __s32 ret;
    __init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
    
    init_ctr->bdec_freq = 1;
    //__here__;
    //cpu_clk = esCLK_GetSrcFreq(CSP_CCM_SYS_CLK_CORE_PLL);
    __here__;
    sdram_clk = esCLK_GetSrcFreq(CSP_CCM_SYS_CLK_SDRAM_PLL);
    __msg("sdram_clk=%d\n", sdram_clk);
    //__here__;
    //esCLK_SetSrcFreq(CSP_CCM_SYS_CLK_CORE_PLL, 120*1000*1000);

    __here__;
    esCLK_SetSrcFreq(CSP_CCM_SYS_CLK_SDRAM_PLL, 180*1000*1000);   

    //ret = esCLK_GetSrcFreq(CSP_CCM_SYS_CLK_SDRAM_PLL);
    //__msg("ret=%d\n", ret);

    //__here__;
    //esPWM_LockCpuFreq();
    //__here__;
    
    return EPDK_OK;
}

static __s32 __init_incr_freq(__gui_msg_t *msg)
{
    __init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);

    if(1 == init_ctr->bdec_freq)
    {
        //__here__;
        //
        //esPWM_UnlockCpuFreq();  
        
        __msg("sdram_clk=%d\n", sdram_clk);
        esCLK_SetSrcFreq(CSP_CCM_SYS_CLK_SDRAM_PLL, sdram_clk);          
              
        //__msg("cpu_clk=%d\n", cpu_clk);
        //esCLK_SetSrcFreq(CSP_CCM_SYS_CLK_CORE_PLL, cpu_clk);
        //__here__;

        init_ctr->bdec_freq = 0;
    }           

    return EPDK_OK;
}


/**
 * ����
 */
static __s32 init_open_screen(__gui_msg_t *msg)
{	
	__bool exist;
	__disp_output_type_t output;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	init_scene_t * p_scene 	= (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
	/*{
		ES_FILE      		   	*p_disp;

		p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
		if(!p_disp)
		{
			__err("open display device fail!\n");
		}
		eLIBs_fioctrl(p_disp, DISP_CMD_CLK_ON, 0, 0);
		eLIBs_fclose(p_disp);	
	}*/   
            
    __here__;
	output = dsk_display_get_output_type();

    __here__;
	if( (output == DISP_OUTPUT_TYPE_NONE)||(output == DISP_OUTPUT_TYPE_LCD) )
	{		
        __here__;
		init_lock(msg);
        __here__;
		if( init_ctr->screen_close_done )	/* ��Ļ�Ѿ��ر� */
		{		
            __here__;
			init_unlock(msg); 

            __here__;
            //__init_incr_freq(msg);//112350
            
			dsk_display_lcd_on();				/* ������ʾ����, ����*/		           
			
			init_lock(msg);
			init_ctr->screen_close_done = EPDK_FALSE;/* 	�����״̬λ */
			init_unlock(msg);

			//��Ļ��
			//p_scene->scnlock_win = create_screen_lock(msg->h_deswin);
			//GUI_WinSetFocusChild(p_scene->scnlock_win);			
		}
		else									/* ��Ļ��û�ر� */
		{		
			init_unlock(msg);			
		}	
		
		exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);
		if( exist == EPDK_TRUE )
			GUI_ResetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);/* �������ö�ʱ��*/
	}
	return EPDK_OK;
}

/** 
 * �����Զ�����ʱ��
 */
static __s32 init_set_close_scn(__gui_msg_t *msg)
{	
	__bool exist;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	if( msg->dwAddData1 == 0 )
	{        
        init_ctr->closescn_timeout = 0;//add by Kingvan
		exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);
		if( exist == EPDK_TRUE )
		{
			GUI_KillTimer(msg->h_deswin, init_ctr->close_scn_time_id);
		}				
	}	
	else if( msg->dwAddData1 >0 )
	{
		init_ctr->closescn_timeout = msg->dwAddData1/10;
		exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);		
		if( exist == EPDK_TRUE )
		{
			GUI_ResetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
		}
		else
		{
			GUI_SetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
		}		
	}
	else
	{
		__wrn(" close screen time < 0, set fail \n");
	}
		
	return EPDK_OK;
}

static __s32 init_set_screensaver(__gui_msg_t *msg)
{
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	if (init_ctr->screen_saver_on == 0)
	{
		__here__;
		init_ctr->screen_saver_on = 1;
		init_restart_close_scn(msg);

		{
			__gui_msg_t msgex;
			msgex.id 			= DSK_MSG_ENTER_SCREENSAVER;
	    	msgex.h_srcwin 		= NULL;
	    	msgex.h_deswin 		= msg->h_deswin;
	    	msgex.dwAddData1 	= 0;
	    	msgex.dwAddData2 	= 0;
	    	msgex.dwReserved 	= 0;
	    	msgex.p_arg	   		= NULL;
	    	
	    	activity_notify_top(&msgex);  
		}
	}
}


static __s32 init_close_screensaver(__gui_msg_t *msg)
{
	__bool exist;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
	

	if (init_ctr->screen_saver_on == 1)
	{
		__here__;
		init_ctr->screen_saver_on = 0;
		init_restart_close_scn(msg);

		{
			__gui_msg_t msgex;
			msgex.id 			= DSK_MSG_CLOSE_SCREENSAVER;
	    	msgex.h_srcwin 		= NULL;
	    	msgex.h_deswin 		= msg->h_deswin;
	    	msgex.dwAddData1 	= 0;
	    	msgex.dwAddData2 	= 0;
	    	msgex.dwReserved 	= 0;
	    	msgex.p_arg	   		= NULL;
	    	
	    	activity_notify_top(&msgex);  
		}
	}

	{
		reg_system_para_t *para;
		para = (reg_system_para_t *)dsk_reg_get_para_by_app(REG_APP_SYSTEM);
		dsk_display_set_lcd_bright(para->backlight);
	}

	exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->screen_saver_id);
	if (exist == EPDK_TRUE )
	{
		GUI_ResetTimer(msg->h_deswin, init_ctr->screen_saver_id, init_ctr->screen_saver_timeout, NULL);
	}
}

/**
 * �����Զ��ػ�ʱ��
 */
static __s32 init_set_auto_off(__gui_msg_t *msg)
{		
	__bool exist;
	__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);

    init_ctr->autooff_timeout = 0;
    
	if( msg->dwAddData1 == 0 )
	{
		exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id);
		if( exist == EPDK_TRUE )
		{
			GUI_KillTimer(msg->h_deswin, init_ctr->auto_off_time_id);
		}		
	}	
	else if( msg->dwAddData1 >0 )
	{			
		init_ctr->autooff_timeout = msg->dwAddData1/10;
		exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id);
		
		if( exist == EPDK_TRUE )
		{
			GUI_ResetTimer(msg->h_deswin, init_ctr->auto_off_time_id, init_ctr->autooff_timeout, NULL);
		}
		else
		{
			GUI_SetTimer(msg->h_deswin, init_ctr->auto_off_time_id, init_ctr->autooff_timeout, NULL);
		}		
	}		
	else
	{
		__wrn(" auto off time < 0, set fail \n");
	}
	
	return EPDK_OK;
}

static __s32 init_scene_create(__gui_msg_t *msg)
{
	SIZE	screen_size;
//	init_scene_t *p_scene;
//	p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);	
		
	init_screen_size();	

	//dialog		
	dialog_init(msg->h_deswin);	
	//headbar	
#ifndef  BOOT_FROM_SDMMC	  //������	
	gscene_hbar_create(msg->h_deswin, HBAR_FOARMAT_32BPP);
	//backgrd		
	screen_size.width	 = LCD_WIDTH;
	screen_size.height	 = LCD_HEIGHT;		
	gscene_bgd_init(&screen_size, BGD_STATUS_HIDE, FB_TYPE_YUV);	
#endif
	__here__
	return EPDK_OK;
}

static __s32 init_scene_destroy(__gui_msg_t *msg)
{
	init_scene_t * p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
	
	dialog_deinit(msg->h_deswin);
	__here__;
	gscene_hbar_delete();
	__here__;
	gscene_bgd_deinit();	
	
	return EPDK_OK;
}

static __s32 init_voltage_check(__gui_msg_t *msg)
{
    __gui_msg_t msgex;
    static power_level_e old_vol_level = DSK_POWER_LEVEL_;
    static __bool old_charge_state = 0;

    power_level_e	level;
    __bool charge_state;

    dsk_power_get_voltage_level(&level);		
    charge_state = dsk_get_charge_state();
    if(old_vol_level != level || 
        old_charge_state != charge_state)
    {
        msgex.id 			= DSK_MSG_VOLTAGE_CHANGE;
    	msgex.h_srcwin 		= NULL;
    	msgex.h_deswin 		= msg->h_deswin;
    	msgex.dwAddData1 	= (__u32)level;
    	msgex.dwAddData2 	= 0;
    	msgex.dwReserved 	= 0;
    	msgex.p_arg	   		= NULL;
    	
    	activity_notify_top(&msgex);          
    }

    __msg("level=%d\n", level);

    old_vol_level = level;
    old_charge_state = charge_state;
    
    return EPDK_OK;
}

static __s32 __init_prog_draw_progress(init_fw_update_rect_t* prog_bg, init_fw_update_rect_t* prog_left, 
    init_fw_update_rect_t* prog_mid, init_fw_update_rect_t* prog_cursor,
    __s32 min, __s32 max, __s32 cur)
{
    //������������
	{
		void* pbmp;

		if (!prog_bg->res_hdl[0])
		{
			__msg("prog_bg->res_hdl[0] is null...\n");
			return EPDK_FAIL;				
		}		
		pbmp = dsk_theme_hdl2buf(prog_bg->res_hdl[0]);
		if (!pbmp)
		{
			__msg("pbmp is null...\n");
			return EPDK_FAIL;
		}		
		GUI_BMP_Draw(pbmp, prog_bg->x, prog_bg->y);
	}

    //����������ߵ�ͼ��
	{
		void* pbmp;
        __s32 focus;

        focus = 0;
		
		if (!prog_left->res_hdl[focus])
		{
			__msg("prog_left->res_hdl[focus] is null...\n");			
			return EPDK_FAIL;				
		}		
		pbmp = dsk_theme_hdl2buf(prog_left->res_hdl[focus]);
		if (!pbmp)
		{
			__msg("pbmp is null...\n");			
			return EPDK_FAIL;
		}		
		GUI_BMP_Draw(pbmp, prog_left->x, prog_left->y);				
	}

	//����������cursor
	if(cur > max)//����һ��
    {
        cur = max;
    }
    
    if(cur < min)//����һ��
    {
        cur = min;
    }
    
	if(cur >= min
		&& cur <= max)
	{
		void* pbmp;
		
		if (!prog_mid->res_hdl[0])
		{
			__msg("prog_mid->res_hdl[0] is null...\n");			
			return EPDK_FAIL;				
		}		
		pbmp = dsk_theme_hdl2buf(prog_mid->res_hdl[0]);
		if (!pbmp)
		{
			__msg("pbmp is null...\n");			
			return EPDK_FAIL;
		}		

		{
			__s32 i;
			__s32 n;
            __s32 mid_w;
            __s32 max_mid_w;
            __s32 cursor_w;
            __s32 cursor_pos;
            __s32 bg_pos;
            __s32 bg_w;

			if (cur == min)
			{
				n = 0;
			}
			else
			{
				n = (prog_bg->w-prog_cursor->w)*(cur-min)
					/prog_mid->w/(max - min);
			}

            mid_w = prog_mid->w;
            max_mid_w = prog_bg->w-prog_cursor->w;
            cursor_w = prog_cursor->w;
            bg_pos = prog_bg->x;
            bg_w = prog_bg->w;
            //��ֹ��������ʱ������
            if(max_mid_w-n*mid_w < mid_w)
            {
                n++;
                cursor_pos = bg_pos + bg_w - cursor_w;
            }
            else
            {
                cursor_pos = bg_pos + n*mid_w;
            }
            
			for (i = 1 ; i < n ; i++)
			{
				GUI_BMP_Draw(pbmp, prog_mid->x+i*prog_mid->w
					, prog_mid->y);
			}

            //��cursor
            if (!prog_cursor->res_hdl[0])
    		{
    			__msg("prog_cursor->res_hdl[0] is null...\n");			
    			return EPDK_FAIL;				
    		}		
    		pbmp = dsk_theme_hdl2buf(prog_cursor->res_hdl[0]);
    		if (!pbmp)
    		{
    			__msg("pbmp is null...\n");			
    			return EPDK_FAIL;
    		}		
    		GUI_BMP_Draw(pbmp, cursor_pos, prog_cursor->y);				
		}		
	}   
    
    return EPDK_OK;
}

static void fw_update(__gui_msg_t *msg, char* fw_path)
{
    __s32 len;
	__u8 	mid_update;
	__mp* 	mod_update;
    __s32 progress;  
    RECT rect;
    char str_text[128];
    GUI_RECT gui_rect;
    init_scene_t * p_scene ;
    GUI_MEMDEV_Handle memdev_hdl = NULL;
    
    init_fw_update_rect_t prog_ui[init_fw_update_prog_icon_num];

    __msg("fw_path=%s\n", fw_path); 
    p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);	    

    GUI_LyrWinSetSta(p_scene->dialog_layer, GUI_LYRWIN_STA_ON);
    GUI_LyrWinSel(p_scene->dialog_layer);     
    GUI_LyrWinSetTop(p_scene->dialog_layer);
    GUI_LyrWinGetScnWindow(p_scene->dialog_layer, &rect);
    dsk_langres_get_menu_text(STRING_FW_UPDATE, str_text, sizeof(str_text));   
    
    gui_rect.x0 = 0;
    gui_rect.y0 = 32;
    gui_rect.x1 = rect.width-1;
    gui_rect.y1 = gui_rect.y0 + 32;
    GUI_SetFont(SWFFont);				
	GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
	GUI_SetColor(GUI_WHITE);														
	GUI_CharSetToEncode(EPDK_CHARSET_ENM_UTF8);	
    GUI_DispStringInRect(str_text, &gui_rect, GUI_TA_HCENTER|GUI_TA_VCENTER);

    prog_ui[init_fw_update_prog_bg].x = 61;
    prog_ui[init_fw_update_prog_bg].y = rect.height - 20;
    prog_ui[init_fw_update_prog_bg].w = 134;
    prog_ui[init_fw_update_prog_bg].h = 15;
    prog_ui[init_fw_update_prog_bg].res_id[0] = ID_INIT_PROG_BG_BMP;
    prog_ui[init_fw_update_prog_bg].res_id[1] = 0;
    
    prog_ui[init_fw_update_prog_left].x = 61;
    prog_ui[init_fw_update_prog_left].y = rect.height - 20;
    prog_ui[init_fw_update_prog_left].w = 7;
    prog_ui[init_fw_update_prog_left].h = 15;
    prog_ui[init_fw_update_prog_left].res_id[0] = ID_INIT_PROG_LEFT_BMP;
    prog_ui[init_fw_update_prog_left].res_id[1] = 0;

    prog_ui[init_fw_update_prog_mid].x = 61;
    prog_ui[init_fw_update_prog_mid].y = rect.height - 20;
    prog_ui[init_fw_update_prog_mid].w = 7;
    prog_ui[init_fw_update_prog_mid].h = 15;
    prog_ui[init_fw_update_prog_mid].res_id[0] = ID_INIT_PROG_MID_BMP;
    prog_ui[init_fw_update_prog_mid].res_id[1] = 0;

    prog_ui[init_fw_update_prog_cursor].x = 61;
    prog_ui[init_fw_update_prog_cursor].y = rect.height - 20;
    prog_ui[init_fw_update_prog_cursor].w = 20;
    prog_ui[init_fw_update_prog_cursor].h = 15;
    prog_ui[init_fw_update_prog_cursor].res_id[0] = ID_INIT_PROG_CURSOR_BMP;
    prog_ui[init_fw_update_prog_cursor].res_id[1] = 0;

    {
		int i;
		int j;
		
		for (i = 0 ; i < init_fw_update_prog_icon_num ; i++)
		{
			for (j = 0 ; j < INIT_FW_UPDATE_MAX_ICON_RES_NUM ; j++)
			{
				if (prog_ui[i].res_id[j])
				{
					prog_ui[i].res_hdl[j] = dsk_theme_open(prog_ui[i].res_id[j]);
					if (!prog_ui[i].res_hdl[j])
					{
						__msg("dsk_theme_open fail...\n");
					}
                    else//�ȶ�ȡnor����ռס���ڴ�
                    {
                        dsk_theme_hdl2buf(prog_ui[i].res_hdl[j]);
                    }
				}
                else
                {
                    prog_ui[i].res_hdl[j] = NULL;
                }
			}
		}
	}	     

    __init_prog_draw_progress(&prog_ui[init_fw_update_prog_bg],
                &prog_ui[init_fw_update_prog_left], 
                &prog_ui[init_fw_update_prog_mid],
                &prog_ui[init_fw_update_prog_cursor],
                0, 100, 0);

    mid_update = esMODS_MInstall(BEETLES_APP_ROOT"mod\\update.mod", 0);
	if( mid_update == 0 )
	{
		__err("update mod install error \n");
		goto err1;
	} 
	
	mod_update = esMODS_MOpen(mid_update, 0);
	if( mod_update == NULL)
	{
		__err("open update mode error \n");
		esMODS_MUninstall(mid_update);
		goto err1;
	}
	
	__msg("mod_update = %x,file=%s\n",mod_update, fw_path);
	
	esMODS_MIoctrl(mod_update, UPDATE_CMD_START, 0, (void *)fw_path);	
	
	__msg(" ioctrl mod update complete \n");
    
    while (1)
	{
	    esKRNL_TimeDly(50);
	    progress = esMODS_MIoctrl(mod_update, UPDATE_CMD_CHECK_PROG, 0, 0);
	    if (-1  == progress)
	    {
	        __err("error occur\n");
	        break;
	    }

        GUI_LyrWinSel(p_scene->dialog_layer);
        memdev_hdl = GUI_MEMDEV_Create(
            prog_ui[init_fw_update_prog_bg].x,
            prog_ui[init_fw_update_prog_bg].y,
            prog_ui[init_fw_update_prog_bg].w,
            prog_ui[init_fw_update_prog_bg].h);
    	if (!memdev_hdl)
    	{
            __msg("GUI_MEMDEV_Create fail...\n");
    		continue ;
    	}

        GUI_MEMDEV_Select(memdev_hdl);
        __init_prog_draw_progress(&prog_ui[init_fw_update_prog_bg],
            &prog_ui[init_fw_update_prog_left], 
            &prog_ui[init_fw_update_prog_mid],
            &prog_ui[init_fw_update_prog_cursor],
            0, 100, progress);

        GUI_MEMDEV_CopyToLCD(memdev_hdl); 
    	GUI_MEMDEV_Select( NULL );			
    	GUI_MEMDEV_Delete(memdev_hdl);
	    __msg("current progress is %d%%\n", progress); 
	    if (100 == progress)
	    {
	    	__u32 status=0;
			__u32 count=0;
            __msg("update complete\n");
			//��Ϊ���������Ϳ�����������������̣�������������֮���Ƿ��������û��Լ�����
			status = esMODS_MIoctrl(mod_update, UPDATE_CMD_STATUS, 0, 0);
			if(status != -1)
			{//�����ɹ�
				esMODS_MIoctrl(mod_update, UPDATE_CMD_STOP, 0, 0);
				eLIBs_printf("update finish..................................\n");
				eLIBs_printf("���ڴ�����LCD����ʾ�����ɹ���ʾ�û��忨����ϵͳ\n");
				while(1)
				{
					//do what you want to do here
					//�����⿨�Ƿ��Ѿ��γ�������������������С������Ա��Ҫ�ֻ��ػ��ص��鷳
					//����һֱ��⣬������һС��DEMO�������ο�
#if 0					
					if(get_gpio_status(1,3) == 1) //����pa3Ϊ�ߵ�ƽ��֤�����γ�����������
					{
						count++;
						
						if(count>=10)//��ֹ�������������μ��
						{
							__err("��������");
						}
											
					}
					else
					{
						count=0;
					}
#endif					
					esKRNL_TimeDly(1);
				}
			}
			else
			{//����ʧ��
				//������Ҫ���û������Ƿ�����
				__err("����ʧ��\n");
				__err("���ڴ�����LCD����ʾ����ʧ����ʾ�û�\n");
			}
            
	    }
	}
	
	esMODS_MClose(mod_update);
	
	esMODS_MUninstall(mid_update);   

err1:;    
    
	return ;
}


static __s32 init_mainwin_cb(__gui_msg_t *msg)
{
	switch( msg->id )
	{
		case GUI_MSG_CREATE:				
		{			
			__init_ctl_t * init_ctr;
			init_scene_t * p_scene;
			/////////////////////////////////////////////////////////////////
			init_ctr = (__init_ctl_t *)eLIBs_malloc(sizeof(__init_ctl_t));
			if(!init_ctr)
			{
				__err("init_ctr malloc error \n");
				return EPDK_FAIL;
			}
			eLIBs_memset( init_ctr, 0, sizeof(__init_ctl_t));
			GUI_WinSetAttr(msg->h_deswin, (void*)init_ctr);
			/////////////////////////////////////////////////////////////////
			p_scene = (init_scene_t *)eLIBs_malloc(sizeof(init_scene_t));
			if(!p_scene)
			{
				__err("p_scene malloc error \n");
				return EPDK_FAIL;
			}
			eLIBs_memset( p_scene, 0, sizeof(init_scene_t));
			GUI_WinSetAddData(msg->h_deswin, (__u32)p_scene);
			p_scene->init_win = msg->h_deswin;
			//p_scene->hbar_format = HBAR_FOARMAT_32BPP;
			/////////////////////////////////////////////////////////////////			
			init_ctr->low_power_check_time_id	= LOW_POWER_CHECK_TIME_ID;
			init_ctr->cursor_time_id		   	= CURSOR_TIME_ID;			
			init_ctr->close_scn_time_id	   		= CLOSE_SCN_TIME_ID;
			init_ctr->auto_off_time_id			= AUTO_OFF_TIME_ID;
			init_ctr->screen_saver_id            = SCREENSAVER_TIME_ID;
			/* �͵��ѯ��ʱ�� */
			init_ctr->low_power_check_timeout	= 100;							// 1s									
			/* cursor ���ض�ʱ�� */
			init_ctr->cursor_timeout   			= 500;							// 5s
			init_ctr->screen_saver_timeout		= 1500;	
			
			/* ���� timer */				
			GUI_SetTimer(msg->h_deswin, init_ctr->low_power_check_time_id, init_ctr->low_power_check_timeout, NULL);			
		#if OPEN_CURSOR
			GUI_SetTimer(msg->h_deswin, init_ctr->cursor_time_id, init_ctr->cursor_timeout, NULL);
		#endif
			if( init_ctr->closescn_timeout != 0 )
			{
				GUI_SetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
			}
			GUI_SetTimer(msg->h_deswin, init_ctr->screen_saver_id, init_ctr->screen_saver_timeout, NULL);
			/* �����ź��� */
			init_ctr->state_sem = esKRNL_SemCreate(1);
			init_ctr->closescn_gate_on 	= EPDK_TRUE;
			init_ctr->usb_connect 	   	= EPDK_FALSE;
			init_ctr->screen_close_done = EPDK_FALSE;	
			init_ctr->tp_msg_enble	   	= EPDK_TRUE;
			init_ctr->key_msg_enble	   	= EPDK_TRUE;

			//initialize res
			live_init();				
			//create cursor
		#if OPEN_CURSOR
			init_cursor_create(init_ctr);
		#endif
			//create hbar,bgd,dialog
			init_scene_create(msg);				
			//��̨�̴߳����ʱ����
			sys_msg_handle_init(msg);					
			
			break;
		}
		
		case GUI_MSG_DESTROY:
		{
			__u8 err;				
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			init_scene_t * p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);	
	
			if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->low_power_check_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->low_power_check_time_id);
			
			if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->cursor_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->cursor_time_id);

			if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->close_scn_time_id);

            if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->auto_off_time_id);

			if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->screen_saver_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->screen_saver_id);
				
			esKRNL_SemDel(init_ctr->state_sem, 0, &err);
											
			//ɾ����̨�߳�
			sys_msg_handle_exit(msg);		
			//delete hbar,bgd,dialog
			init_scene_destroy(msg);			
			//delete cursor
		#if OPEN_CURSOR
			init_cursor_delete(init_ctr);			
		#endif
			//deinit res
			live_exit();			
			
			eLIBs_free(init_ctr);			
			eLIBs_free(p_scene);

            __msg("init_mainwin destroyed...\n");
			
			break;
		}
		case GUI_MSG_CLOSE:		
			__here__
			GUI_ManWinDelete(msg->h_deswin);				
			break;		

		case GUI_MSG_TIMER:
		{
			init_scene_t *p_scene;
			__init_ctl_t * init_ctr;
			init_ctr= (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);			 
			p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);

			if( msg->dwAddData1 == init_ctr->cursor_time_id )//������ʱ��
			{
				GUI_CursorHide();	
			}
			else if( msg->dwAddData1 == init_ctr->screen_saver_id )
			{
				init_set_screensaver(msg);
			}
			else if( msg->dwAddData1 == init_ctr->low_power_check_time_id )//�͵���
			{				
				if( dsk_power_is_low() == EPDK_TRUE )//�͵�
				{	
                    __msg("****************low power...****************\n");
                    GUI_KillTimer(msg->h_deswin, init_ctr->low_power_check_time_id);
				    SEND_MSG(DSK_MSG_LOW_POWER, NULL, msg->h_deswin, 0, 0);
				}
                else
                {
                    __msg("**************not low power...*********\n");
                }
                
                init_voltage_check(msg);
                
			}	
			else if( msg->dwAddData1 == LOW_POWER_DIALOG_TIME_ID )//�͵�Ի������ʱ��
			{
				p_scene->low_power = EPDK_FALSE;
				GUI_KillTimer(msg->h_deswin, LOW_POWER_DIALOG_TIME_ID);
				scene_on_dialog(msg);
			}	
			else if( msg->dwAddData1 == POWER_OFF_DIALOG_TIME_ID )//�ػ��Ի������ʱ��
			{
				__here__;
				p_scene->power_off = EPDK_FALSE;
				GUI_KillTimer(msg->h_deswin, POWER_OFF_DIALOG_TIME_ID);
				scene_on_dialog(msg);
				__here__;			
			}	
			else if( msg->dwAddData1 == ORCHID_UPDATE_DIALOG_TIME_ID )//ý��������Ի������ʱ��
			{							
				if(p_scene->orchid_update == EPDK_FALSE)
				{					
					GUI_KillTimer(msg->h_deswin, ORCHID_UPDATE_DIALOG_TIME_ID);
					scene_on_dialog(msg);					
				}				
			}
			else if( msg->dwAddData1 == init_ctr->close_scn_time_id )//�Զ�����ʱ��
			{		
                __here__;
				SEND_MSG(DSK_MSG_SCREEN_CLOSE, NULL, msg->h_deswin, 0, 0);
                __here__;
			}	
			else if( msg->dwAddData1 == init_ctr->auto_off_time_id)//�Զ��ػ�ʱ��
			{                
                __here__;
				SEND_MSG(DSK_MSG_POWER_OFF, NULL, msg->h_deswin, 0, 0);
                __here__;
			}
			else
			{
				__wrn(" unknown msg timer id = %d \n", msg->dwAddData1);
			}
			break;
		}			

		case GUI_MSG_KEY:
		{		
			//__msg("key value = %d, key action = %d\n", msg->dwAddData1, msg->dwAddData2);
			__bool exist;
			__init_ctl_t * init_ctr;
			init_ctr= (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);	

			//�������ù�����ʱ��
			exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);
			if( exist == EPDK_TRUE )
			{
				GUI_ResetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
			}		

            //�������ùػ���ʱ��
			exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id);
			if( exist == EPDK_TRUE )
			{
				GUI_ResetTimer(msg->h_deswin, init_ctr->auto_off_time_id, init_ctr->autooff_timeout, NULL);
			}
			
			switch(msg->dwAddData1)
			{				
				case GUI_MSG_KEY_LONGVADD:
				case GUI_MSG_KEY_VADD:					
				{
					if(msg->dwAddData2 != KEY_UP_ACTION)
					{
						//dsk_volume_inc();
					}
					return GUI_ManWinDefaultProc(msg);
				}	
				case GUI_MSG_KEY_LONGVDEC:	
				case GUI_MSG_KEY_VDEC:				
				{
					if(msg->dwAddData2 != KEY_UP_ACTION)
					{
						//dsk_volume_dec();
					}
					return GUI_ManWinDefaultProc(msg);
				}	
				default:
					return GUI_ManWinDefaultProc(msg);
			}			
		}
			
		case GUI_MSG_TOUCH:			
		{
			__bool  exist;			
			__pos_t pos;					
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);

			//�������ù�����ʱ��
			exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);
			if( exist == EPDK_TRUE )
			{
				GUI_ResetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
			}
			if (msg->dwAddData1 == GUI_MSG_TOUCH_UP || msg->dwAddData1 == GUI_MSG_TOUCH_OVERUP)
			{
				init_close_screensaver(msg);
			}
            //�������ùػ���ʱ��
			exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id);
			if( exist == EPDK_TRUE )
			{
				GUI_ResetTimer(msg->h_deswin, init_ctr->auto_off_time_id, init_ctr->autooff_timeout, NULL);
			}
			
			pos.x = LOSWORD(msg->dwAddData2);
			pos.y = HISWORD(msg->dwAddData2);
			
			__msg(" pos.x =%d, pos.y =%d \n", pos.x, pos.y);	
		#if OPEN_CURSOR
			GUI_CursorSetPos(&pos);
			GUI_CursorShow();
		#endif	
			exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->cursor_time_id);
			if( exist == EPDK_TRUE )
			{
				GUI_ResetTimer(msg->h_deswin, init_ctr->cursor_time_id, init_ctr->cursor_timeout, NULL);
			}
			
			//return GUI_ManWinDefaultProc(msg);			
			return activity_notify_top(msg);
		}		

		case DSK_MSG_RESET_SCREENSAVER:
		{
			init_close_screensaver(msg);
			break;
		}
		case DSK_MSG_ENABLE_SCREENSAVER:
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			
			if(!GUI_IsTimerInstalled(msg->h_deswin, init_ctr->screen_saver_id))	 {
				GUI_SetTimer(msg->h_deswin, init_ctr->screen_saver_id, init_ctr->screen_saver_timeout, NULL);
			}
			break;
		}
		case DSK_MSG_DISABLE_SCREENSAVER:
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			
			if (init_ctr->screen_saver_on == 1)
			{
				init_ctr->screen_saver_on = 0;
				//init_restart_close_scn(msg);
			
				{
					__gui_msg_t msgex;
					msgex.id			= DSK_MSG_CLOSE_SCREENSAVER;
					msgex.h_srcwin		= NULL;
					msgex.h_deswin		= msg->h_deswin;
					msgex.dwAddData1	= 0;
					msgex.dwAddData2	= 0;
					msgex.dwReserved	= 0;
					msgex.p_arg 		= NULL;
					
					activity_notify_top(&msgex);  
				}
			}

			if(GUI_IsTimerInstalled(msg->h_deswin, init_ctr->screen_saver_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->screen_saver_id);
			break;
		}

		case HEADBAR_CMD_SET_FORMAT:
		{
			//init_scene_t * p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);
			//p_scene->hbar_format   = (__hbar_format_t)msg->dwAddData1;
			
			//gscene_hbar_delete();			
			//gscene_hbar_create(msg->h_deswin, (__hbar_format_t)msg->dwAddData1);				
			
			break;
		}
		/*case HEADBAR_CMD_GET_SCN_POS:
		{
			RECT hbar_rect;
			init_scene_t * p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);			
			GUI_LyrWinGetScnWindow(p_scene->hbar_layer, &hbar_rect);
			
			return ((hbar_rect.y<<16) + hbar_rect.x);
		}

		case HEADBAR_CMD_GET_SIZE:
		{
			RECT hbar_rect;
			init_scene_t * p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);			
			GUI_LyrWinGetScnWindow(p_scene->hbar_layer, &hbar_rect);
			
			return ((hbar_rect.height<<16) + hbar_rect.width);
		}*/
		case DSK_MSG_USBD_PLUG_IN:				/* usb device plug in */			
		{                       
            __init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
            init_scene_t *p_scene;
            __bool        other_dlg_exist;//����usbʱ���Ƿ��������ģʽ��
            
            p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);

            //��ǰ����usb���ӱ�־����ֹusb����ʱ���͵���߹ػ��Ի���ǿ�ƹرպ���������ܣ�����Ӧ�ñ�����
            p_scene->usb_plug_in = EPDK_TRUE;
            __here__;
            other_dlg_exist = EPDK_FALSE;

            //����usb��ʱ���ֹ�Զ������͹ػ�
            init_ctr->autooff_timer_exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id);
    		if(EPDK_TRUE == init_ctr->autooff_timer_exist)
    		{
    			GUI_KillTimer(msg->h_deswin, init_ctr->auto_off_time_id);
    		}
            init_ctr->closescn_timer_exist = GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id);
    		if(EPDK_TRUE == init_ctr->closescn_timer_exist )
    		{
    			GUI_KillTimer(msg->h_deswin, init_ctr->close_scn_time_id);
    		}

            // ��ֹ��Ϣ��Ӧ
            init_ctr->tp_msg_enble = EPDK_FALSE;

            __here__;
            //USB���ӵ�����ʱ����ܴ�ʱ��ʾ���ڹػ����ߵ͵�Ի����Ƚ���������
            //�������ñ�ǲ����������ܣ��Ӷ����ػ���
            __msg("p_scene->power_off=%d\n", p_scene->power_off);
            if (p_scene->power_off == EPDK_TRUE)
            {
                other_dlg_exist = EPDK_TRUE;
                __here__;
                p_scene->power_off = EPDK_FALSE;
                if(GUI_IsTimerInstalled(msg->h_deswin, POWER_OFF_DIALOG_TIME_ID))
                {
                    __here__;
                    GUI_KillTimer(msg->h_deswin, POWER_OFF_DIALOG_TIME_ID);
                    scene_on_dialog(msg);
                    __here__;
                }                
            }

            __here__;
            if (p_scene->low_power == EPDK_TRUE)
            {
                other_dlg_exist = EPDK_TRUE;
                __here__;
                p_scene->low_power = EPDK_FALSE;
                if(GUI_IsTimerInstalled(msg->h_deswin, LOW_POWER_DIALOG_TIME_ID))
                {
                    __here__;
                    GUI_KillTimer(msg->h_deswin, LOW_POWER_DIALOG_TIME_ID);
                    scene_on_dialog(msg);
                }
            }

            //�������usbʱ����������ģʽ�������Ͷ����Ϣ�ķ�ʽ֪ͨusb���ӣ�
            //����ر������Ի���󣬶Ի�����Ϣѭ��δ���������������
            if(EPDK_TRUE == other_dlg_exist)
            {
                __gui_msg_t set_msg;

                eLIBs_memcpy(&set_msg, msg, sizeof(__gui_msg_t));
                GUI_SendNotifyMessage(&set_msg);
            }
            else
            {
                __here__;
                init_usb_device_plugin_proc(msg);
                __here__;
                NOTIFY_MSG(DSK_MSG_ORCHID_UPDATE_START, NULL, msg->h_deswin, 0, 0);         
                __here__;                                   
            }
            			
			break;
		}		
		case DSK_MSG_USBD_PLUG_OUT:				/* usb devcie plug out */
         {
            __init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
            
			__here__;
			init_usb_device_plugout_proc(msg);
            init_ctr->tp_msg_enble = EPDK_TRUE;
			__here__;

            //usb���Ӱγ��������õ͵��ѯ��ʱ������Ϊ���ܵ͵�
            GUI_ResetTimer(msg->h_deswin, init_ctr->low_power_check_time_id, init_ctr->low_power_check_timeout, NULL);                

            //usb���Ӱγ��������Զ��ػ����Զ�������ʱ��            
    		if(EPDK_TRUE == init_ctr->autooff_timer_exist)
    		{
                if(GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id))
                {
                    GUI_ResetTimer(msg->h_deswin, init_ctr->auto_off_time_id, init_ctr->autooff_timeout, NULL);    			    			
                }
                else
                {
                    GUI_SetTimer(msg->h_deswin, init_ctr->auto_off_time_id, init_ctr->autooff_timeout, NULL);    			    			
                }
    		}
            
    		if(EPDK_TRUE == init_ctr->closescn_timer_exist )
    		{
                if(GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id))
                {
                    GUI_ResetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
                }
                else
                {
                    GUI_SetTimer(msg->h_deswin, init_ctr->close_scn_time_id, init_ctr->closescn_timeout, NULL);
                }
                
    		}

            //�͵���ʾ�򵯳������usb�����°γ���
            //�ö�ʱ���ѱ�ɾ����������һ��
            if(!GUI_IsTimerInstalled(msg->h_deswin, init_ctr->low_power_check_time_id))		
            {
                GUI_SetTimer(msg->h_deswin, init_ctr->low_power_check_time_id, init_ctr->low_power_check_timeout, NULL);			
            }
            
			break;		
		}
		case DSK_MSG_ORCHID_UPDATE_START:
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			__here__
			//init_orchid_update_start(msg);	
			__here__
			activity_load_app("application://app_root");
			__here__
			break;
		}

		case DSK_MSG_ORCHID_UPDATE_END:			
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			__here__
			init_orchid_update_end(msg);
			__here__
			if(dsk_display_get_output_type() == DISP_OUTPUT_TYPE_LCD)
			{
				init_ctr->tp_msg_enble = EPDK_TRUE;	
			}
			
			break;
		}
		case DSK_MSG_FS_PART_PLUGIN:
		{
			char diskname[4];
			__gui_msg_t msgex;			
			
			diskname[0] = msg->dwAddData2;
			diskname[1] = '\0';			
			DebugPrintf("disk %s (%c)plug in\n", diskname,msg->dwAddData2);
			
			if( (msg->dwAddData2 == 'D')||(msg->dwAddData2 == 'E')||(msg->dwAddData2 == 'Z') )
			{
				return 0;
			}
			
			msgex.id 			= DSK_MSG_FS_PART_PLUGIN;
			msgex.h_srcwin 		= 0;
			msgex.h_deswin 		= 0;
			msgex.dwAddData1 	= msg->dwAddData1;
			msgex.dwAddData2 	= msg->dwAddData2;
			activity_notify_top(&msgex);
			
			break;
		}
		case DSK_MSG_FS_PART_PLUGOUT:	
		{
			char diskname[4];
			__gui_msg_t msgex;
			
			diskname[0] = msg->dwAddData2;
			diskname[1] = '\0';			
			DebugPrintf("disk %s plug out\n", diskname);

			if( (msg->dwAddData2 == 'D')||(msg->dwAddData2 == 'E')||(msg->dwAddData2 == 'Z') )
			{
				return 0;
			}
			//notify top				
			msgex.id 			= DSK_MSG_FS_PART_PLUGOUT;
			msgex.h_srcwin 		= 0;
			msgex.h_deswin 		= 0;
			msgex.dwAddData1 	= msg->dwAddData1;
			msgex.dwAddData2 	= msg->dwAddData2;
			activity_notify_top(&msgex);	

			if(dsk_wkm_is_open())
			{				
				char filename[512];
				
				dsk_wkm_get_now_playing_file(filename);
				__msg("filename = %s\n", filename);
				if(0 == eLIBs_strnicmp(filename, diskname, 1))
				{
				__here__
					dsk_wkm_close();
				}
			}
			
			break;
		}
		case DSK_MSG_SCREEN_OPEN:				/* ���� */
			init_open_screen(msg);			
			break;				
	
		case DSK_MSG_LOW_POWER:				/* low power */          
        {
            __init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);

            if(init_ctr->power_off)
            {
                break;
            }
            init_ctr->power_off = 1;
            
			__here__;
			init_low_power_proc(msg);	
			__here__;
			init_power_off_proc(msg);
            init_ctr->power_off = 0;
            __here__;
			break;
		}
		case DSK_MSG_ENABLE_STANDBY:
            init_lock(msg);
            g_b_enable_standby = 1;
            init_unlock(msg);
            break;
        case DSK_MSG_DISABLE_STANDBY:
            init_lock(msg);
            g_b_enable_standby = 0;
            init_unlock(msg);
            break;
        case DSK_MSG_GET_STANDBY_FLAG:
        {
            __bool flag;
            init_lock(msg);
            flag = g_b_enable_standby;
            init_unlock(msg);
            return flag;
        }            
		case DSK_MSG_POWER_OFF: 			/* power off */ 	
		{            
			__here__;
			if(msg->dwAddData2 == KEY_UP_ACTION)
			{                
                //������ʱ��ʼ
                init_restart_close_scn(msg);
				__here__;
				init_power_off_proc(msg);	
                __here__;
			}
			break;
		}	
		/*case DSK_MSG_HOLD:
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			if(init_ctr->closescn_gate_on == EPDK_TRUE)
			{
				init_close_screen(msg);				
			}	
			break;
		}*/
		case DSK_MSG_STANDBY_WAKE_UP:
			__here__
			init_open_screen(msg);
			break;
			
		case DSK_MSG_TVDAC_PLUGIN:
            __msg("************DSK_MSG_TVDAC_PLUGIN*****************\n");
			break;
			
		case DSK_MSG_TVDAC_PLUGOUT:
		case DSK_MSG_HDMI_PLUGOUT:
		{		
            __msg("************DSK_MSG_TVDAC_PLUGOUT/DSK_MSG_HDMI_PLUGOUT*****************\n");

            //����
			if(dsk_display_get_output_type() != DISP_OUTPUT_TYPE_LCD)
			{               
				__gui_msg_t msgex;
			    			
                __here__;
    			
    			//notify top				
    			msgex.id 			= msg->id;
    			msgex.h_srcwin 		= 0;
    			msgex.h_deswin 		= 0;
    			msgex.dwAddData1 	= msg->dwAddData1;
    			msgex.dwAddData2 	= msg->dwAddData2;
    			activity_notify_top(&msgex);
			}
            __here__;
			
			break;		
		}

		case DSK_MSG_SCREEN_SWITCH:
		{			
			__init_ctl_t * init_ctr;
			init_ctr= (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);				
			
			if( msg->dwAddData1 == LION_DISP_LCD )		// �л���LCD���򿪴�������Ϣ
			{
				init_lock(msg);
				init_ctr->tp_msg_enble = EPDK_TRUE;				
				init_unlock(msg);
			}
			else											// �л���tv , �رմ�������Ϣ
			{				
				init_lock(msg);
				init_ctr->tp_msg_enble = EPDK_FALSE;				
				init_unlock(msg);				
			}
			
			//���´�������			
			init_scene_destroy(msg);			
			init_scene_create(msg);				
			
			break;
		}

		case DSK_MSG_ASSISTANT_SCENE_CREATE:
		{
			/*init_scene_t *p_scene;	
			ES_FILE 	 *p_disp = NULL;							 
			p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);	
			__here__
			if(!p_scene->assistant_win)
			{
				//������������
				GUI_SetScnNo(1);				
				p_scene->assistant_win = assistant_scene_create(msg->h_deswin);
				
				// open display driver
				p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
				if( p_disp == NULL )
				{
				    __err("Error in opening display driver.\n");
				    return EPDK_FAIL;
				}					
				eLIBs_fioctrl(p_disp, DISP_CMD_LCD_ON, 1, 0);  				
				eLIBs_fclose(p_disp);
				p_disp = NULL;
				
				GUI_SetScnNo(0);
			}*/
			break;
		}

		case DSK_MSG_ASSISTANT_SCENE_DELETE:
		{
			/*init_scene_t *p_scene;	
			ES_FILE 	 *p_disp = NULL;							 
			p_scene = (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);	
			__here__
			if(p_scene->assistant_win)
			{
				__here__
				GUI_SetScnNo(1);
				assistant_scene_delete(p_scene->assistant_win);
				p_scene->assistant_win = NULL;
				
				p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
				if( p_disp == NULL )
				{
				    __err("Error in opening display driver.\n");
				    return EPDK_FAIL;
				}					
				eLIBs_fioctrl(p_disp, DISP_CMD_LCD_OFF, 1, 0);  				
				eLIBs_fclose(p_disp);
				p_disp = NULL;
				
				GUI_SetScnNo(0);
			}*/
			break;
		}
		
		case DSK_MSG_SET_SCN_CLOSE:			
			init_set_close_scn(msg);
			break;

		case DSK_MSG_SCREEN_CLOSE:	
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			if(init_ctr->closescn_gate_on == EPDK_TRUE)
			{
				init_close_screen(msg);
			}
			break;
		}

		case DSK_MSG_CLOSE_SCN_GATE_OFF:
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			init_ctr->closescn_gate_on = EPDK_FALSE; 
			break;
		}

		case DSK_MSG_CLOSE_SCN_GATE_ON:
		{
			__init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);
			init_ctr->closescn_gate_on = EPDK_TRUE; 
			break;
		}

		case DSK_MSG_SET_AUTO_OFF:
		{
			init_set_auto_off(msg);
			break;
		}
        case DSK_MSG_FW_UPDATE:
        {
            __here__;
            /* delay */
			esKRNL_TimeDly(200);

            __msg("********dsk_fw_update*******\n");
            /* ִ���������� */
			dsk_fw_update();				

            __here__;
			esKRNL_TimeDly(200);					

            __here__;
            break;
        }
        case DSK_MSG_FW_START_UPDATE: //�����̼� 
		{
            __init_ctl_t * init_ctr = (__init_ctl_t *)GUI_WinGetAttr(msg->h_deswin);			

            __msg("msg->dwAddData1=%s\n", msg->dwAddData1);
            if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->low_power_check_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->low_power_check_time_id);
			
			if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->cursor_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->cursor_time_id);

			if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->close_scn_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->close_scn_time_id);

            if( GUI_IsTimerInstalled(msg->h_deswin, init_ctr->auto_off_time_id))		
				GUI_KillTimer(msg->h_deswin, init_ctr->auto_off_time_id);
            __here__;
			activity_finish_all();
			__here__;

#ifndef  BOOT_FROM_SDMMC	   //������	
            gscene_bgd_set_flag(EPDK_TRUE);
		    gscene_bgd_refresh();
            __here__;
		    gscene_hbar_set_state(HBAR_ST_HIDE);
            __here__;            
#endif
            fw_update(msg, (char*)(msg->dwAddData1));
            __here__;
						
			break;
		}
		/*case GUI_MSG_COMMAND:
		{
			if(ID_SCREEN_LOCK == LOSWORD(msg->dwAddData1) && SCREEN_LOCK_EXIT == HISWORD(msg->dwAddData1))
			{
				__gui_msg_t msgex;
				init_scene_t * p_scene 	= (init_scene_t *)GUI_WinGetAddData(msg->h_deswin);				
				delete_screen_lock(p_scene->scnlock_win);
				
				msgex.id 			= DSK_MSG_SCREEN_OPEN;
				msgex.h_srcwin 		= 0;
				msgex.h_deswin 		= 0;
				msgex.dwAddData1 	= 0;
				msgex.dwAddData2 	= 0;
				activity_notify_top(&msgex);				
			}
			break;
		}*/
		default:			
			GUI_ManWinDefaultProc(msg);
			break;
	}

	return EPDK_OK;
}

H_WIN init_mainwin_create(void)
{
	H_WIN  						hManWin;	
	__gui_manwincreate_para_t  	create_info;	
			
	eLIBs_memset(&create_info, 0, sizeof(__gui_manwincreate_para_t));
	
	create_info.attr            = NULL; 
	create_info.hParent			= NULL;
	create_info.hHosting 		= NULL;   
    create_info.ManWindowProc   = init_mainwin_cb;
    create_info.name            = "init"; 	
	hManWin 					= GUI_ManWinCreate(&create_info);
	
	if(hManWin == NULL)
    {        
        __wrn("init: create main windows failed!\n");      
        return NULL;
    }	
		
	return hManWin;
}

