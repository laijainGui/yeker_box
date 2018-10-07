/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           home app sample
*
*						        	(c) Copyright 2006-2009, China
*											 All Rights Reserved
*
* File    : home.c
* By      : lyn
* Version : V1.00
*********************************************************************************************************
*/

#include "dv_i.h"
#include "dv_uipara.h"
#include "dv_frm.h"
#include "dv_mset.h"

typedef struct tag_dv_ctrl
{
	GUI_FONT *font;
	__s32 root_type;
	
	H_WIN				win_hdl ;
	H_WIN				h_child_frm ;
	H_WIN				h_child_mset ;

	dv_uipara_para_t 	*uipara ;
	dv_frmwin_para_t*	pfrm_para ;
	dv_mset_para_t*		pmset_para ;
}dv_ctrl_t;

static __s32 __dv_on_create(__gui_msg_t * msg)
{
    dv_ctrl_t*        	dv_ctrl;
	dv_frmwin_para_t dv_frmwin_para ;
	
	dv_ctrl = (dv_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	// ��ʼ��ͼ����Դ
   	Dv_Uipara_Init();

	eLIBs_memset((void*)(&dv_frmwin_para), 0, sizeof(dv_frmwin_para_t));
	dv_frmwin_para.font = dv_ctrl->font ;
	dv_frmwin_para.txt_color = APP_COLOR_WHITE ;
	dv_ctrl->h_child_frm = dv_frm_create(&dv_frmwin_para);
	GUI_WinSetFocusChild(dv_ctrl->h_child_frm);
    
    return EPDK_OK;
}

static __s32 __dv_on_destroy(__gui_msg_t * msg)
{
    dv_ctrl_t*        	dv_ctrl;

	dv_ctrl = (dv_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);

	if( dv_ctrl->h_child_frm)
	{
		dv_frm_destroy(dv_ctrl->h_child_frm);
	}
	if( dv_ctrl->h_child_mset)
	{
		dv_mset_destroy(dv_ctrl->h_child_mset);
	}

    Dv_Uipara_UnInit();

    esMEMS_Mfree(0, dv_ctrl);
    
    return EPDK_OK;
}

static __s32 __dv_frm_command_proc(__gui_msg_t *msg)
{
	__gui_msg_t setmsg;
    dv_ctrl_t*        	dv_ctrl;

	dv_ctrl = (dv_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	switch(HIWORD(msg->dwAddData1))
	{
		case CMD_DV_FRM_POP_REC_SETTING_MENU:
		{
			dv_mset_para_t dv_mset_para ;
			eLIBs_memset((void*)(&dv_mset_para),0,sizeof(dv_mset_para_t));
			dv_mset_para.dv_menu_id = DV_MENU_ID_REC_SET ;
			dv_mset_para.txt_color = APP_COLOR_WHITE ;
			dv_mset_create(&dv_mset_para);
			break;
		}
		case CMD_DV_FRM_POP_IMAGE_SETTING_MENU:
		{
			dv_mset_para_t dv_mset_para ;
			eLIBs_memset((void*)(&dv_mset_para),0,sizeof(dv_mset_para_t));
			dv_mset_para.dv_menu_id = DV_MENU_ID_IMAGE_SET;
			dv_mset_para.txt_color = APP_COLOR_WHITE ;
			dv_mset_create(&dv_mset_para);
			break;
		}
		default:
			break;
	}

	return EPDK_OK ;
}

static __s32 __dv_mset_command_proc(__gui_msg_t *msg)
{
	__gui_msg_t setmsg;
    dv_ctrl_t*        	dv_ctrl;

	dv_ctrl = (dv_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);
	
	switch(HIWORD(msg->dwAddData1))
	{
		case CMD_DV_MSET_SET_RECORD_RESOLUTION:
		{
			__gui_msg_t new_msg ;

			new_msg.h_deswin = dv_ctrl->h_child_frm ;
			new_msg.h_srcwin = msg->h_deswin ;
			new_msg.id = CMD_DV_FRM_SET_RECORD_RESOLUTION ;
			new_msg.dwAddData1 = msg->dwAddData2 ;	// focus item index 
			GUI_SendMessage(&new_msg);
			break;
		}
		case CMD_DV_MSET_EXIT:
		{
			__gui_msg_t new_msg ;
			if( dv_ctrl->h_child_mset)
			{
				dv_mset_destroy(dv_ctrl->h_child_mset);
				dv_ctrl->h_child_mset = NULL ;
			}

			new_msg.h_deswin = dv_ctrl->h_child_frm ;
			new_msg.h_srcwin = msg->h_deswin ;
			new_msg.id = CMD_DV_FRM_SETTING_MENU_EXIT ;
			new_msg.dwAddData1 = msg->dwAddData2 ;	// focus item index 
			GUI_SendMessage(&new_msg);
			break;
		}	
		default:
			break;
	}

	return EPDK_OK ;
}
static __s32 _app_dv_main_proc(__gui_msg_t * msg)
{
    dv_ctrl_t*        	dv_ctrl;

	dv_ctrl = (dv_ctrl_t *)GUI_WinGetAttr(msg->h_deswin);

    switch(msg->id)
    {
		case GUI_MSG_CREATE:
		{
			__dv_on_create(msg);
		}
			return EPDK_OK;		
		case GUI_MSG_DESTROY:
		{ 
            __dv_on_destroy(msg);
		}
			return EPDK_OK;
		case GUI_MSG_COMMAND:
		{
			if(LOWORD(msg->dwAddData1) == DV_FRM_WIN_ID)
			{
				__dv_frm_command_proc(msg);
			}
			else if(LOWORD(msg->dwAddData1) == DV_MENU_WIN_ID)
			{
				__dv_mset_command_proc(msg);
			}
		}
			return EPDK_OK;
    	default:
    	    break;
    }
	return GUI_ManWinDefaultProc(msg);
}

__s32 app_dv_create(root_para_t *para)
{

	__gui_manwincreate_para_t create_info;
	dv_ctrl_t *dv_ctrl;

	__log("=======================================================================\n");
	__log("=============================| DV APP RUN |============================\n");
	__log("=======================================================================\n");

    dv_ctrl = (dv_ctrl_t *)esMEMS_Malloc(0, sizeof(dv_ctrl_t));
	if(dv_ctrl == NULL)
	{
		__wrn("malloc error \n");
		return NULL;
	}
	eLIBs_memset(dv_ctrl, 0, sizeof(dv_ctrl_t));

	dv_ctrl->font = para->font;
	dv_ctrl->root_type = para->root_type;
	eLIBs_memset(&create_info, 0, sizeof(__gui_manwincreate_para_t));
	
	create_info.name            = APP_DV;
	create_info.hParent			= para->h_parent ;
	create_info.ManWindowProc = (__pGUI_WIN_CB)esKRNL_GetCallBack((__pCBK_t)_app_dv_main_proc); 
	create_info.attr            = (void*)dv_ctrl;
	create_info.id			= APP_DV_ID;
	create_info.hHosting        = NULL;

	return(GUI_ManWinCreate(&create_info));

}



