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
#ifndef __INIT_SERVER_H__
#define __INIT_SERVER_H__

typedef struct init_ctl_t
{
	/* �ػ� timer */	
	__s32 					 autooff_timeout;	/* �Զ��ػ�ʱ�� 	*/
	__s32					 auto_off_time_id;		/* �Զ��ػ�timer id */
	
	/* ���� timer */
	__s32 					 closescn_timeout;	/* �Զ�����ʱ�� 	*/	
	__bool					 closescn_gate_on;		/* �Ƿ��ֹ�Զ����� */	
	__s32					 close_scn_time_id;		/* �Զ�����timer id */
	
	/* �͵��ѯ */
	__s32 					 low_power_check_timeout;
	__s32					 low_power_check_time_id;
	
	/* �ź��� */
	__krnl_event_t			*state_sem;			/* ��ѯ״̬�ź���  */
	
	/* cursor */
	__s32					cursor_timeout;		/* cursor time out */
	__s32 					cursor_time_id;			/* cursor time id  */
	/* cursor ������Ϣ */
	__u8*					cursor_bmp;
	__gui_cursor_t   		cursor_info;
	
	/* �����¼�״̬��ʶλ*/
	__bool 					 usb_connect;		/* usb �Ƿ����ӵ� pc */
	__bool 					 screen_close_done;	/* ��Ļ�Ƿ��Ѿ��ر�  */
	
	/* msg enble */
	__bool					key_msg_enble;
	__bool 					tp_msg_enble;		

	__u8 					sys_msg_handle_tid;

    __bool                  autooff_timer_exist;
    __bool                  closescn_timer_exist;
    __bool                  usb_host_is_working_before_standy;
    __bool                  bdec_freq;
    __bool                  power_off;
    
}__init_ctl_t;

typedef enum
{
	POWEROFF_DIALOG,
	LOWPOWER_DIALOG,
	USBD_DIALOG,
	ORCHID_DIALOG,
	FW_UPDATA_DIALOG,
	NONE_DIALOG
}main_dialog_t;

typedef struct 
{
	/* ͼ���� */
	//H_LYR hbar_layer;			// ������ͼ��	
	H_LYR dialog_layer;			// ����ͼ��
		
	/* ���ھ�� */	
	H_WIN init_win;
	H_WIN headbar_win;			// ����������	
	H_WIN dialog_win;			// �Ի��򴰿�	
	H_WIN scnlock_win;
	H_WIN assistant_win;
	
	char app_title[32];			// headbar show app_name
	
	/* ��ǰheadbar �ֳ� */
	//__hbar_format_t hbar_format;
	//char hbar_title[32];
	
	/* ϵͳ״̬ dialog ��� */
	main_dialog_t cur_dialog;
    __bool usb_plug_in;//usb�ո����ӣ����ڷ�ֹ�͵��ػ��Ի���رպ󣬳��򱻹رա�
	__bool usb_connect;
 	__bool orchid_update;
 	__bool low_power;
 	__bool power_off;
 	__bool fw_update;
}init_scene_t;

void init_lock(__gui_msg_t *msg);

void init_unlock(__gui_msg_t *msg);

H_WIN init_mainwin_create(void);

#endif

