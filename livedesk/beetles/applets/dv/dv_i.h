/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           home app sample
*
*						        	(c) Copyright 2006-2009, China
*											 All Rights Reserved
*
* File    : home_i.h
* By      : lyn
* Version : V1.00
*********************************************************************************************************
*/

#ifndef __DV_I_H__
#define __DV_I_H__


#include "beetles_app.h"
#include "core\\cvr_core.h"
#include "core\\cvr_show.h"
#include "core\\cvr_watermark.h"

#define     USER_DISK           "F:"                        // �ļ��洢��
#define     DISK_FULL_LEVEL     (1024 * 1024 * 100 * 2)      // 100M�ռ�(Ԥ���ռ䣬�����̼�ⷢ�ֲ���50M�ռ�ʱ����ʼɾ���ļ�)
#define     FILE_NAME_PRIX       "AW_"                       // �ļ�ǰ׺
#define     FILE_NAME_SUFFIX		".mov"
#define     CVR_HDMI_ENABLE         0                       // HDMI֧�ֿ���
#define     CVR_TVOUT_ENABLE        0                       // TVOUT֧�ֿ���

#define 	DV_FRM_WIN_ID				(APP_DV_ID+100)
#define 	DV_MENU_WIN_ID			(APP_DV_ID+110)
#define 	DV_DIALOAG_WIN_ID			(APP_DV_ID+120)


typedef enum dv_TIMER
{
    TIMER_STATUS_ID = 0x100,            // ״̬���TIMER
    TIMER_DIALOAG_TIMEOUT_ID ,
}dv_timer_e;

// ¼��ֱ���, vga�� ����HD(720P)
typedef enum dv_record_resuliton
{
	dv_record_resuliton_VGA,
	dv_record_resuliton_HD,
}dv_record_resuliton_e;

// ���շֱ���1M,2M,3M
typedef enum dv_image_resuliton
{
	dv_image_resuliton_1M,
	dv_image_resuliton_2M,
	dv_image_resuliton_3M,
}dv_image_resuliton_e;


typedef enum dv_PAINT
{
    DV_PAINT_FLASH_ICON1=100, 
    DV_PAINT_FLASH_ICON2, 
    DV_PAINT_MENUBAR_BG, 
    DV_CLEAR_MENUBAR_BG, 
}dv_paint_e;

typedef enum dv_STATE
{
    DV_ON_REC,                        // ¼�񳡾�
    DV_ON_CAM,                        // ���ճ���
    DV_ON_REC_SET,                    // ¼�����ó���
    DV_ON_CAM_SET,                    // �������ó���
}dv_state_e;


#endif /* __DV_I_H__ */


