/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: app_main.c
* By      	: Andy.zhang
* Func		: desk main thread
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#include "beetles_app.h"
#include "app_home.h"
#include "main_menu.h"
#include "sub_menu.h"
#include "home_uipara.h"
#include "msgbox.h"
#include "app_home_i.h"

typedef struct tag_home_para
{
	H_WIN	h_app_main;
	H_WIN 	h_mmenu;
	H_WIN 	h_submenu;
	H_WIN	h_calendar;
	H_WIN	h_msgbox;

	H_WIN	lyr_mmenu;
	H_WIN	lyr_smenu;

	__s32	focus_id;
	__s32   first_item;
	GUI_FONT *main_font;

    __s32   focus_smenu_item;
	void		*core;
	__u32	root_type; 
}home_para_t;

/***********************************************************************************************************
	����ͼ��
************************************************************************************************************/
static H_LYR home_8bpp_layer_create(RECT *rect, __s32 pipe)
{
	H_LYR layer = NULL;
	FB  fb =
	{
	    {0, 0},                                   		/* size      */
	    {0, 0, 0},                                      /* buffer    */
	    {FB_TYPE_RGB, {PIXEL_MONO_8BPP, 0, (__rgb_seq_t)0}},    /* fmt       */
	};

	__disp_layer_para_t lstlyr =
	{
	    DISP_LAYER_WORK_MODE_PALETTE,                    /* mode      */
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
	    "sub menu layer",
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
	
	lstlyr.pipe = pipe;
	lstlyr.fb = &fb;
	lyrcreate_info.lyrpara = &lstlyr;
	
	layer = GUI_LyrWinCreate(&lyrcreate_info);
	if( !layer )
	{
		__err("app bar layer create error !\n");
	} 
		
	return layer;	
}

//Ӧ���˳�������ʱ���ûص�ǰ����
void __app_home_change_to_home_bg(void)
{
    reg_init_para_t* para;
    para = dsk_reg_get_para_by_app(REG_APP_INIT);
    if(para)
    {
        __s32 ret;

        ret = gscene_bgd_get_flag();
        if(ret != para->bgd_flag_in_main)
        {
            gscene_bgd_set_flag(para->bgd_flag_in_main);
            gscene_bgd_refresh();                                                      
        }   
        else
        {
            __msg("ret == para->bgd_flag_in_main, not need change bg...\n");
        }
    }
    else
    {
        __msg("dsk_reg_get_para_by_app fail...\n");
    }

    gscene_bgd_set_state(BGD_STATUS_SHOW);
    
}

void  main_cmd2parent(H_WIN hwin, __s32 id, __s32 data1, __s32 data2)
{
	__gui_msg_t msg;

	msg.h_deswin = GUI_WinGetParent(hwin);
	msg.h_srcwin = NULL;
	msg.id = GUI_MSG_COMMAND;
	msg.dwAddData1 = MAKELONG(GUI_WinGetItemId(hwin), id);
	msg.dwAddData2 = data1;
	msg.dwReserved = data2;

	GUI_SendNotifyMessage(&msg);
}

static void check_disk(home_para_t *home_para)
{
    __s32 i;
    __s32 ret;
    __s32 cnt;
    char diskname[RAT_MAX_PARTITION][4];

	if(0)
    {
        __target_para_t target;
        esKSRV_GetTargetPara(&target);
        if(target.debugenable == EPDK_TRUE)////����ǵ��ԣ���Ĭ��Ϊ������//112350
        {
            home_para->root_type = RAT_TF<<8;
            return ;        
        }
    }   

	__msg("**********check_disk**********\n");
    cnt = 0;
    home_para->root_type = RAT_UNKNOWN;    

    ret = rat_get_partition_name(RAT_USB_DISK, diskname);
    if(EPDK_OK == ret)
    {
    	i = 0;    
    	//while (i < RAT_MAX_PARTITION)
    	{
    		if (diskname[i][0])
    		{
    			__msg("SD : diskname[%d]=%s\n", i, diskname[i]);
                home_para->root_type += RAT_USB;
                cnt++;
    		}						
    		i++;
    	}
    }

    ret = rat_get_partition_name(RAT_SD_CARD, diskname);
    if(EPDK_OK == ret)
    {
    	i = 0;    
    	//while (i < RAT_MAX_PARTITION)
    	{
    		if (diskname[i][0])
    		{
    			__msg("SD : diskname[%d]=%s\n", i, diskname[i]);
                home_para->root_type += RAT_TF<<8;
                cnt++;
    		}						
    		i++;
    	}
    }
    
}

static void app_sub_menu_create(home_para_t *home_para)
{
	smenu_para_t smenu_para;
	RECT	rect;
	home_uipara_t * home_ui_para;

    home_ui_para = home_get_ui_para(GUI_GetScnDir());
    if(!home_ui_para)
    {
        __err("home_ui_para is null...\n");
        return ;
    }
		
	rect.x = (home_para->focus_id-home_para->first_item)*home_ui_para->item_width;
	rect.y = home_ui_para->lyr_sub_item.y;
	rect.width = home_ui_para->lyr_sub_item.w;
	rect.height = home_ui_para->lyr_sub_item.h;

	if (rect.x+rect.width >= home_ui_para->lyr_main_menu.w)
	{
		rect.x = home_ui_para->lyr_main_menu.w-rect.width;
	}
	
	home_para->lyr_smenu = home_8bpp_layer_create(&rect, 1);   
	
	smenu_para.layer = home_para->lyr_smenu;
	smenu_para.sub_menu_id = home_para->focus_id;
	smenu_para.smenu_font = home_para->main_font;
	smenu_para.root_type = home_para->root_type;
    smenu_para.focus_item = home_para->focus_smenu_item;
    __msg("home_para->focus_smenu_item=%d\n", home_para->focus_smenu_item);
	
	home_para->h_submenu = sub_menu_win_create(home_para->h_app_main, &smenu_para);	
    __msg("home_para->h_submenu=%x\n", home_para->h_submenu);
}

static void app_main_menu_create(home_para_t *home_para)
{
	RECT	rect;
    mmenu_para_t mmenu_para;
    home_uipara_t * home_ui_para;

    home_ui_para = home_get_ui_para(GUI_GetScnDir());
    if(!home_ui_para)
    {
        __err("home_ui_para is null...\n");
        return ;
    }
	
	rect.x = home_ui_para->lyr_main_menu.x;
	rect.y = home_ui_para->lyr_main_menu.y;
	rect.width = home_ui_para->lyr_main_menu.w;
	rect.height = home_ui_para->lyr_main_menu.h;

	home_para->lyr_mmenu = home_8bpp_layer_create(&rect, 1);

	mmenu_para.mmenu_font = home_para->main_font;
	mmenu_para.focus_id = home_para->focus_id;
	mmenu_para.layer = home_para->lyr_mmenu;
	home_para->h_mmenu = main_menu_win_create(home_para->h_app_main, &mmenu_para);
    __msg("home_para->h_mmenu=%x\n", home_para->h_mmenu);
	
	GUI_WinSetFocusChild(home_para->h_mmenu);
}

static __s32 app_home_proc(__gui_msg_t *msg)
{
    __msg("app_home_proc msg->id=%d, msg->h_deswin=%x, msg->dwAddData1=%d, msg->dwAddData2=%d\n"
        ,msg->id, msg->h_deswin, msg->dwAddData1, msg->dwAddData2);
	switch(msg->id)
	{
	case GUI_MSG_CREATE:
		{
			home_para_t *home_para;
			root_para_t *root_para;					

			root_para = (root_para_t *)GUI_WinGetAttr(msg->h_deswin);
			home_para = (home_para_t *)esMEMS_Balloc(sizeof(home_para_t));
            if(!home_para)
            {
                return EPDK_FAIL;
            }
			eLIBs_memset((void *)home_para, 0, sizeof(home_para_t));
			home_para->main_font = root_para->font;
			home_para->h_app_main = msg->h_deswin;
			home_para->focus_id = 2;			// 		
			home_para->first_item = 0;
		
			com_set_palette_by_id(ID_HOME_PAL_BMP);

            //background
            gscene_bgd_set_state(BGD_STATUS_SHOW);           
            
			//���˵�
			app_main_menu_create(home_para);

			//����һ���Ӳ˵�
			check_disk(home_para);
			app_sub_menu_create(home_para);
            
			GUI_LyrWinSetSta(home_para->lyr_mmenu, GUI_LYRWIN_STA_ON);
			GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_ON);

            gscene_hbar_set_state(HBAR_ST_SHOW);

            gscene_bgd_set_bottom();
            GUI_WinSetFocusChild(home_para->h_mmenu);
			GUI_WinSetAddData(msg->h_deswin, (__u32)home_para);                                 
            __here__;

            //test volume
            if(1){
                reg_system_para_t* para;
                __s32 vol;

                vol = dsk_volume_get();
                __msg("dsk_volume_get=%d\n", vol);

                para = dsk_reg_get_para_by_app(REG_APP_SYSTEM);
                if(para)
                {
                    __msg("para->volume=%d\n", para->volume);
                }
                else
                {
                    __msg("para is null...\n");
                }
            }           
		}
		return EPDK_OK;
	case GUI_MSG_CLOSE:
		GUI_ManWinDelete(msg->h_deswin);
		return EPDK_OK;
	case GUI_MSG_DESTROY:
		{
			home_para_t *home_para;

			home_para = (home_para_t *)GUI_WinGetAddData(msg->h_deswin);
			
			GUI_LyrWinDelete(home_para->lyr_mmenu);
			GUI_LyrWinDelete(home_para->lyr_smenu);

			home_para->lyr_mmenu = 0;
			home_para->lyr_smenu = 0;
            esMEMS_Bfree(home_para, sizeof(home_para_t));
		}
		return EPDK_OK;
	case GUI_MSG_KEY:
		__msg("******app_home_proc GUI_MSG_KEY*****\n");
		break;
	case GUI_MSG_TOUCH:
		break;
	case DSK_MSG_FS_PART_PLUGIN:
	case DSK_MSG_FS_PART_PLUGOUT:
		{					
			home_para_t *home_para;
			__s32 root_type;

            __msg("app_home_proc DSK_MSG_FS_PART_PLUGIN/OUT\n");

			home_para = (home_para_t *)GUI_WinGetAddData(msg->h_deswin);		

			root_type = home_para->root_type;
            __msg("home_para->root_type=%d\n", home_para->root_type);
			check_disk(home_para);
            __msg("home_para->root_type=%d\n", home_para->root_type);
            __here__;
            if (GUI_LYRWIN_STA_ON != GUI_LyrWinGetSta(home_para->lyr_mmenu))
				return EPDK_OK;
            __here__;
			if (1/*home_para->root_type != root_type*/)
			{
                __here__;
				if (home_para->focus_id == ID_HOME_MOVIE || home_para->focus_id == ID_HOME_PHOTO ||
					home_para->focus_id == ID_HOME_MUSIC || home_para->focus_id == ID_HOME_EBOOK
					|| home_para->focus_id == ID_HOME_RECORD)
				{
                    //�ȵ�ס�Ӳ˵�������Ӳ˵��л�ʱ�������⡣
                    //GUI_LyrWinSetTop(home_para->lyr_mmenu);//112357
                    //gscene_hbar_set_state(HBAR_ST_SHOW);//112357
                    
					if (home_para->lyr_smenu)
					{
						GUI_LyrWinDelete(home_para->lyr_smenu);
					}
					
					app_sub_menu_create(home_para);
					GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_ON);
                    GUI_LyrWinSetTop(home_para->lyr_smenu);
				}
			}
			
		}
		return EPDK_OK;
	case DSK_APP_RESTORE:
		{
			home_para_t *home_para;

			home_para = (home_para_t *)GUI_WinGetAddData(msg->h_deswin);

            com_set_palette_by_id(ID_HOME_PAL_BMP);

            __app_home_change_to_home_bg();
                       
			GUI_LyrWinSetSta(home_para->lyr_mmenu, GUI_LYRWIN_STA_ON);
			GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_ON);	
            gscene_hbar_set_state(HBAR_ST_SHOW);
            gscene_bgd_set_bottom();
            gscene_hbar_set_state(HBAR_ST_SHOW);
//            GUI_LyrWinSetSta(home_para->lyr_total_bg, GUI_LYRWIN_STA_ON);
//            GUI_LyrWinSetBottom(home_para->lyr_total_bg);

//            GUI_BMP_Draw(dsk_theme_hdl2buf(home_para->total_bg_hdl)
//               , main_uipara.lyr_total_bg.x, main_uipara.lyr_total_bg.y);

            GUI_WinSetFocusChild(home_para->h_mmenu);
		}
		return EPDK_OK;
	case GUI_MSG_COMMAND:
		{
			home_para_t *home_para;

			home_para = (home_para_t *)GUI_WinGetAddData(msg->h_deswin);
			
			switch(LOWORD(msg->dwAddData1))
			{
			case MAIN_MENU_ID:
			{
				switch(HIWORD(msg->dwAddData1))
				{
					case ID_SWITCH_ITEM:
					{	
                        //�ȵ�ס�Ӳ˵�������Ӳ˵��л�ʱ�������⡣
                        //GUI_LyrWinSetTop(home_para->lyr_mmenu);//112357
                        //gscene_hbar_set_state(HBAR_ST_SHOW);//112357
                        
						if (home_para->lyr_smenu)
						{
							GUI_LyrWinDelete(home_para->lyr_smenu);
						}
                        
						home_para->focus_id = msg->dwAddData2;
						home_para->first_item = msg->dwReserved;
						app_sub_menu_create(home_para);
						GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_ON);
                        GUI_LyrWinSetTop(home_para->lyr_smenu);
                        
                        
					}
					break;
					case ID_OP_SUB_UP:
					{
						__gui_msg_t mymsg;
						mymsg.h_deswin = home_para->h_submenu;
						mymsg.h_srcwin = NULL;
						mymsg.id = MSG_SUB_OP_UP;
						GUI_SendMessage(&mymsg);
					}
					break;
					case ID_OP_SUB_DOWN:
					{
						__gui_msg_t mymsg;
						mymsg.h_deswin = home_para->h_submenu;
						mymsg.h_srcwin = NULL;
						mymsg.id = MSG_SUB_OP_DOWN;
						GUI_SendMessage(&mymsg);
					}
					break;	
					case ID_OP_SUB_ENTER:
					{
						__gui_msg_t mymsg;
						mymsg.h_deswin = home_para->h_submenu;
						mymsg.h_srcwin = NULL;
						mymsg.id = MSG_SUB_OP_ENTER;
						GUI_SendMessage(&mymsg);
					}
					break;
					default:
					break;
				}
			}
			break;
			case SUB_MENU_ID:
			{
				if (HIWORD(msg->dwAddData1) == SMENU_APP_SWITCH)
				{
                    home_para->focus_smenu_item = msg->dwAddData2;
                    __msg("msg->dwAddData2=%d\n", msg->dwAddData2);
					__here__;
					
					//GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_SUSPEND);
					__here__;
					switch (home_para->focus_id)
					{						
						case ID_HOME_FM:						
						{   							
							GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_SUSPEND);
							GUI_LyrWinSetSta(home_para->lyr_mmenu, GUI_LYRWIN_STA_SUSPEND);
                            main_menu_res_uninit(home_para->h_mmenu);
                            sub_menu_uninit_res(home_para->h_submenu);
//                            GUI_LyrWinSetSta(home_para->lyr_total_bg, GUI_LYRWIN_STA_SUSPEND);
							main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP, home_para->focus_id, msg->dwAddData2);
						}
						break;
						case ID_HOME_MOVIE:
						case ID_HOME_PHOTO:
						case ID_HOME_MUSIC:
						case ID_HOME_EBOOK:
                        case ID_HOME_RECORD:
						{                                         
							__here__;
                            //if(ID_HOME_RECORD == home_para->focus_id)
                            //{
                            //    __msg("*************record not finish yet********\n");
                            //    break;
                            //}
                            
							if (home_para->root_type != 0)
							{
                                __s32 index;                                

                                index = msg->dwAddData2;
                                GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_SUSPEND);
								GUI_LyrWinSetSta(home_para->lyr_mmenu, GUI_LYRWIN_STA_SUSPEND);
                                main_menu_res_uninit(home_para->h_mmenu);
                                sub_menu_uninit_res(home_para->h_submenu);
//                                GUI_LyrWinSetSta(home_para->lyr_total_bg, GUI_LYRWIN_STA_SUSPEND);
								if ((home_para->root_type&0xff)//USB
                                    &&(home_para->root_type&0xff00))//SD
								{
                                    if(0 == index)
                                    {
                                        main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP
                                        , home_para->focus_id, RAT_USB);
                                    }
                                    else if(1 == index)
                                    {
                                        main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP
                                        , home_para->focus_id, RAT_TF);
                                    }									
                                    else
                                    {
                                        __err("wrong focus sub menu item\n");
                                    }
								}
								else if (home_para->root_type&0xff)//USB
								{
									 main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP
                                        , home_para->focus_id, RAT_USB);
								}
                                else if (home_para->root_type&0xff00)//TF
								{
									 main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP
                                        , home_para->focus_id, RAT_TF);
								}
                                else
                                {
                                    __err("wrong root type..\n");
                                }
							}
							__here__;
							break;
						}
						case ID_HOME_OTHERS:
						{
                            __msg("***********ID_HOME_OTHERS************\n");   
#if BEETLES_RTC_EXIST
                            if(3 == msg->dwAddData2)
                            {
                                if(0 == home_para->root_type)
                                {
                                    __msg("*************no disk insert, not load file manager************\n");
                                    break;
                                }
                            }
#else
                            if(2 == msg->dwAddData2)
                            {
                                if(0 == home_para->root_type)
                                {
                                    __msg("*************no disk insert, not load file manager************\n");
                                    break;
                                }
                            }

#endif
                            GUI_LyrWinSetSta(home_para->lyr_smenu, GUI_LYRWIN_STA_SUSPEND);
							GUI_LyrWinSetSta(home_para->lyr_mmenu, GUI_LYRWIN_STA_SUSPEND);
							//GUI_LyrWinSetSta(home_para->lyr_total_bg, GUI_LYRWIN_STA_SUSPEND);
							main_menu_res_uninit(home_para->h_mmenu);
                            sub_menu_uninit_res(home_para->h_submenu);
							main_cmd2parent(msg->h_deswin, SWITCH_TO_OTHER_APP, home_para->focus_id, msg->dwAddData2);
							break;
						}
					}
				}
			}
			break;
			case MSGBOX_ID:
			{
				if (HIWORD(msg->dwAddData1) == CMD_MSGBOX_CLOSE)
				{
					
				}
			}
			default:
				break;
			}
		}
		return EPDK_OK;
	}
	
	return GUI_ManWinDefaultProc(msg);	
}

/*******************************************************************************************************
*********************************************************************************************************/
H_WIN app_home_create(root_para_t *para)
{
	__gui_manwincreate_para_t create_info;

	__inf("****************************************************************************************\n");
	__inf("********  enter home app  **************\n");
	__inf("****************************************************************************************\n");

	//__wait__;
	
	eLIBs_memset(&create_info, 0, sizeof(__gui_manwincreate_para_t));
	
	create_info.name            = APP_HOME;
	create_info.hParent         = para->h_parent;
	create_info.ManWindowProc   = (__pGUI_WIN_CB)esKRNL_GetCallBack((__pCBK_t)app_home_proc); 
	create_info.attr            = (void*)para;
	create_info.id				= APP_HOME_ID;
	create_info.hHosting        = NULL;

	return(GUI_ManWinCreate(&create_info));
}
