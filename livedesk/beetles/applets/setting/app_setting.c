/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: app_settings.c
* By      	: Andy.zhang
* Func		: desk main thread
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#include "App_setting.h"
#include "app_setting_i.h"
#include "setting_para.h"
#include "setting_general.h"
#include "setting_power.h"
#include "setting_tips.h"
/***********************************************************************************************************
	����ͼ��
************************************************************************************************************/
static H_LYR setting_layer_create(RECT *rect)
{
	H_LYR layer = NULL;
	FB  fb =
	{
	    {0, 0},                                   		/* size      */
	    {0, 0, 0},                                      /* buffer    */
	    {FB_TYPE_RGB, {PIXEL_COLOR_ARGB8888, 0, (__rgb_seq_t)0}},    /* fmt       */
	};

	__disp_layer_para_t lstlyr =
	{
	    DISP_LAYER_WORK_MODE_NORMAL,                    /* mode      */
	    0,                                              /* ck_mode   */
	    0,                                              /* alpha_en  */
	    0,                                              /* alpha_val */
	    1,                                              /* pipe      */
	    0xff,                                           /* prio      */
	    {0, 0, 0, 0},                           		/* screen    */
	    {0, 0, 0, 0},                               	/* source    */
	    DISP_LAYER_OUTPUT_CHN_DE_CH1,                   /* channel   */
	    NULL                                            /* fb        */
	};

	__layerwincreate_para_t lyrcreate_info =
	{
	    "setting layer",
	    NULL,
	    GUI_LYRWIN_STA_SUSPEND,
	    GUI_LYRWIN_NORMAL
	};
	
	fb.size.width		= rect->width;
	fb.size.height		= rect->height;	
	
	lstlyr.src_win.x  		= 0;
	lstlyr.src_win.y  		= 0;
	lstlyr.src_win.width 	= rect->width;
	lstlyr.src_win.height 	= rect->height;
	
	lstlyr.scn_win.x		= rect->x;
	lstlyr.scn_win.y		= rect->y;
	lstlyr.scn_win.width  	= rect->width;
	lstlyr.scn_win.height 	= rect->height;
	
	lstlyr.pipe = 1;
	lstlyr.fb = &fb;
	lyrcreate_info.lyrpara = &lstlyr;
	
	layer = GUI_LyrWinCreate(&lyrcreate_info);
	if( !layer )
	{
		__err("app bar layer create error !\n");
	} 
		
	return layer;	
}

static __s32 app_setting_proc(__gui_msg_t *msg)
{
	switch(msg->id)
	{
		case GUI_MSG_CREATE:
		{
			setting_ctrl_t	*setting_ctrl;
			RECT rect;
			SIZE screen_size;

			setting_ctrl = (setting_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
			
			setting_ctrl->h_setting_main = setting_main_create(msg->h_deswin, SETTING_WIN_ID_MAIN);
		}
		return EPDK_OK;
		case GUI_MSG_CLOSE:
		{
			main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP, SETTING_SW_TO_MAIN, 0);
		}
		return EPDK_OK;
		case GUI_MSG_DESTROY:
		{
			setting_ctrl_t	*setting_ctrl;
			__msg( "setting destory begin ............\n");
			setting_ctrl	 = (setting_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
			if(!setting_ctrl)
			{
				__err("setting_ctrl is null ......\n");
				return EPDK_FAIL;
			}
			//�жϲ�Ʒ��Ϣ��ʾ���Ƿ���ڣ����ڵĻ�ɾ������ʾ��
			if(setting_ctrl->h_frm_tips)
			{
				H_LYR h_lyr ;
				h_lyr = GUI_WinGetLyrWin( setting_ctrl->h_frm_tips );
				if( !h_lyr )
				{
					__msg( "h_lyr is null \n");
					return EPDK_FAIL ;
				}
				GUI_LyrWinDelete( h_lyr );
				setting_ctrl->h_frm_tips = NULL ;
			}
			__here__;
			//�жϻָ�����������ʾ���Ƿ���ڣ����ڵĻ�ɾ������ʾ��
			if( setting_ctrl->h_dialoag_win )
			{
				app_dialog_destroy( setting_ctrl->h_dialoag_win );
				setting_ctrl->h_dialoag_win = NULL ;
			}
			if( setting_ctrl->lyr_setting)
			{
				__here__ ;
				__msg(" lyr_setting isn't null, delete it \n");
				GUI_LyrWinDelete(setting_ctrl->lyr_setting);
				__here__ ;
				setting_ctrl->lyr_setting = NULL ;
			}
			My_Bfree(setting_ctrl, sizeof(setting_ctrl_t));
		//	esKSRV_SysInfo();
		}
		return EPDK_OK;
		case GUI_MSG_KEY:
		{
		
			switch( msg->dwAddData1 )
			{			
				case GUI_MSG_KEY_ESCAPE:
				{
					__gui_msg_t my_msg;

					my_msg.id = GUI_MSG_CLOSE;
		    		my_msg.h_srcwin = msg->h_deswin;
		    		my_msg.h_deswin = msg->h_deswin;
		    		my_msg.dwAddData1 = 0;
		    		my_msg.dwAddData2 = 0;
		    		GUI_SendNotifyMessage(&my_msg);
					return EPDK_OK;
				}
			}
			
		}
		break;
		case DSK_MSG_FS_PART_PLUGIN:
		case DSK_MSG_FS_PART_PLUGOUT:
		{
			setting_ctrl_t *setting_ctrl;            
            
			setting_ctrl = (setting_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
			__here__;
			if(setting_ctrl->h_frm_tips)
			{				
                		__gui_msg_t set_msg;

                		eLIBs_memcpy(&set_msg, msg, sizeof(__gui_msg_t));
				set_msg.h_deswin = setting_ctrl->h_frm_tips;
				__here__;
				GUI_SendMessage(&set_msg);
				__here__;
			}
			return EPDK_OK;
		}
		case GUI_MSG_COMMAND:
		{
			setting_ctrl_t *setting_ctrl;

			setting_ctrl = (setting_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
			
			switch(LOWORD(msg->dwAddData1))
			{		
				case SETTING_WIN_ID_MAIN:
				{
					switch(HIWORD(msg->dwAddData1))
					{
						case ITEM_MSG_CLICKED:
						{
							if(setting_ctrl->h_setting_main != NULL) {
								GUI_ManWinDelete(setting_ctrl->h_setting_main);
								setting_ctrl->h_setting_main = setting_language_create(msg->h_deswin, SETTING_WIN_ID_LANGUAGE);
							}
						}
							break;
						case ID_OP_RIGHT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_RIGHT;
							GUI_SendMessage(&mymsg);
						}
							break;

						default:
							break;
					}
				}
					return EPDK_OK;
				
				case GENERAL_MENU_ID:
				{
					
					switch(HIWORD(msg->dwAddData1))
					{
						case ID_OP_LEFT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_LEFT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_RIGHT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_RIGHT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_UP:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_UP;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_DOWN:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_DOWN;
							GUI_SendMessage(&mymsg);
							
						}
						break;	
						case ID_OP_ENTER:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_ENTER;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_EXIT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_general;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_EXIT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_SWITCH_TO_TIPS:
						{
							if(msg->dwAddData2 ==TIPS_FACTORY_DEFAULT)	//�ָ���������
							{
								 __s32 lang_id[]={STRING_SET_CUE , STRING_SET_COMMON_RESTORE };
           							 default_dialog(setting_ctrl->h_dialoag_win , msg->h_deswin , SETTING_TIPS_ID, ADLG_YESNO, lang_id);
							}
							else
							{		// ��Ʒ��Ϣ��ʾ��
								setting_tip_para_t tips_para;
								RECT rect;						
								
								rect.x = 0;
								rect.y = 0;
								rect.width = SET_TIPS_W;
								rect.height = SET_TIPS_H;
								
								tips_para.msgbox_font = setting_ctrl->setting_font;
								tips_para.layer = setting_tips_layer_create(&rect);
								setting_ctrl->h_frm_tips = setting_tips_win_create(GUI_WinGetHandFromName(APP_SETTING),&tips_para);
								GUI_WinSetFocusChild(setting_ctrl->h_frm_tips);
							}
						}
						break;
					default:
						break;
					}
				}
					return EPDK_OK;

				case POWER_MANAGE_MENU_ID:
				{
					
					switch(HIWORD(msg->dwAddData1))
					{
						case ID_OP_LEFT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_power;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_LEFT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_RIGHT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_power;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_RIGHT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_UP:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_power;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_UP;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_DOWN:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_power;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_DOWN;
							GUI_SendMessage(&mymsg);
							
						}
						break;	
						case ID_OP_ENTER:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_power;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_ENTER;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_EXIT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_power;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_EXIT;
							GUI_SendMessage(&mymsg);
						}
						break;
						
					default:
						break;
					}
				}
				return EPDK_OK;
				case GENERAL_TIPS_ID:
				{
					switch(HIWORD(msg->dwAddData1))
					{
						case ID_OP_LEFT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_tips;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_LEFT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_RIGHT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_tips;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_RIGHT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_UP:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_tips;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_UP;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_DOWN:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_tips;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_DOWN;
							GUI_SendMessage(&mymsg);
							
						}
						break;	
						case ID_OP_ENTER:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_tips;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_ENTER;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_OP_EXIT:
						{
							__gui_msg_t mymsg;
							mymsg.h_deswin = setting_ctrl->h_frm_tips;
							mymsg.h_srcwin = NULL;
							mymsg.id = MSG_OP_EXIT;
							GUI_SendMessage(&mymsg);
						}
						break;
						case ID_SWITCH_TO_GENERAL:
						{
							H_LYR tips_win_layer;
							if(setting_ctrl==NULL)
							{
								__msg("setting_ctrl error.........\n");
								return EPDK_FAIL;
							}
							if( setting_ctrl->h_frm_tips == NULL )
							{
								__msg(" setting_ctrl->h_frm_tips is null \n");
								GUI_WinSetFocusChild(setting_ctrl->h_frm_general);
								return EPDK_FAIL ;
							}
							tips_win_layer = GUI_WinGetLyrWin(setting_ctrl->h_frm_tips);
							if(tips_win_layer == NULL )
							{
								__msg( " tips_win layer is null \n" );
								return EPDK_FAIL ;
							}
							GUI_LyrWinDelete(tips_win_layer);
							setting_ctrl->h_frm_tips = NULL ;
							GUI_WinSetFocusChild(setting_ctrl->h_frm_general);
						}
						break;
					default:
						break;
					}
				}
				return EPDK_OK;
				case SETTING_TIPS_ID:
				{	
					__here__;
					switch(HIWORD(msg->dwAddData1))
					{
						case ADLG_CMD_EXIT:
						{
							__here__ ;

							app_dialog_destroy( setting_ctrl->h_dialoag_win) ;
							setting_ctrl->h_dialoag_win = NULL ;

							if(ADLG_IDYES == msg->dwAddData2 )
							{
								__gui_msg_t mymsg;
								__msg("***********restore factory setting*******\n");
								mymsg.h_deswin = setting_ctrl->h_frm_general;
								mymsg.id = MSG_RESTORE_FACTORY;
								GUI_SendMessage(&mymsg);

							}
							return EPDK_OK ;
						}
						default:
						{
							break;
						}
					}
					break ;
				}
			default:
				break ; 
			}	
			return EPDK_OK;
		}
	default:
		break;
	}
	return GUI_ManWinDefaultProc(msg);	
}

H_WIN app_setting_create(root_para_t *para)

{
	__gui_manwincreate_para_t create_info;
	setting_ctrl_t *setting_ctrl;

	__inf("****************************************************************************************\n");
	__inf("********  enter setting app  **************\n");
	__inf("****************************************************************************************\n");

	//__wait__;
	setting_ctrl = (setting_ctrl_t *)My_Balloc(sizeof(setting_ctrl_t));
	if(!setting_ctrl)
	{
		__msg("memory balloc fail.........\n");
		return EPDK_FAIL;
	}
	eLIBs_memset(setting_ctrl, 0, sizeof(setting_ctrl_t));

	setting_ctrl->setting_font = para->font;
	setting_ctrl->root_type = para->setting_opt;
	eLIBs_memset(&create_info, 0, sizeof(__gui_manwincreate_para_t));
	
	create_info.name            = APP_SETTING;
	create_info.hParent         = para->h_parent;
	create_info.ManWindowProc   = (__pGUI_WIN_CB)esKRNL_GetCallBack((__pCBK_t)app_setting_proc); 
	create_info.attr            = (void*)setting_ctrl;
	
	create_info.id			= APP_SETTING_ID;
	create_info.hHosting        = NULL;
	
	return(GUI_ManWinCreate(&create_info));
}

