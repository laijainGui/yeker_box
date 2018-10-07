/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           home app sample
*
*						        	(c) Copyright 2006-2009, China
*											 All Rights Reserved
*
* File    : dv_uipara.h
* By      : lincoln
* Version : V1.00
*********************************************************************************************************
*/

#ifndef __DV_MSET_H__
#define __DV_MSET_H__

typedef enum dv_menu_id_e
{
    DV_MENU_ID_REC_SET,                        // ¼�񳡾�
    DV_MENU_ID_IMAGE_SET,                        // ���ճ���
    DV_MENU_ID_MAX
}dv_menu_id_e;

typedef enum
{
	CMD_DV_MSET_SET_RECORD_RESOLUTION,
	CMD_DV_MSET_EXIT,
}dv_mset_sub_cmd_t;


typedef struct dv_mset_para
{
	H_WIN win_hdl ;
	H_LYR lyr_hdl ;
	H_WIN h_parent ;
	__u32 focus_item_index ;	/*	����item ����*/
	__u32 tmp_focus_item ;		/*	�����������л�item������û�а�ȷ����֮ǰʹ��*/
	dv_menu_id_e dv_menu_id ;
	dv_uipara_para_t 	*uipara ;
	GUI_FONT* font ;
	__u32	txt_color ;

}dv_mset_para_t;

__s32 dv_mset_create(dv_mset_para_t *para);


#endif /* __DV_MSET_H__ */
