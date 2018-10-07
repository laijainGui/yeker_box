/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: headbar_com.h
* By      	: Andy.zhang
* Func		: headbar manage
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#ifndef __HEADBAR_COM_H__
#define __HEADBAR_COM_H__

/* ֪ͨ�� */
#define HBAR_ADJUST_VOLUME			1

/* ������ */
#define HBAR_TIME_PAINT			(GUI_MSG_USER_DEF+1)	// ����ʱ��
#define HBAR_DATA_PAINT			(GUI_MSG_USER_DEF+2)	// ��������
#define HBAR_VOL_PAINT			(GUI_MSG_USER_DEF+3)	// ���Ƶ�ص���
#define HBAR_BRIGHT_PAINT		(GUI_MSG_USER_DEF+4)	// ��������
#define HBAR_VOLUME_PAINT		(GUI_MSG_USER_DEF+5)	// ��������
#define HBAR_MUSIC_BG_PAINT		(GUI_MSG_USER_DEF+6)	// ���Ʊ�������
#define HBAR_TITLE_PAINT		(GUI_MSG_USER_DEF+7)	// ���Ʊ���

typedef enum _headbar_cmd_id
{		
	HEADBAR_CMD_SET_VOLUME = GUI_MSG_USER_DEF,
	HEADBAR_CMD_SET_BRIGHT,	
	HEADBAR_CMD_SET_FORMAT,
	HEADBAR_CMD_GET_SCN_POS,
	HEADBAR_CMD_GET_SIZE
}headbar_cmd_id;


typedef struct
{
	char 		*name;		
	__u16 		id;	
	
	H_WIN   	parent;
	H_WIN   	layer;		
	RECT    	rect;
	GUI_FONT   *font;			// ������	
}__headbar_create_para;

H_WIN headbar_frm_create(H_WIN parent, H_LYR layer);
__s32 headbar_frm_delete(H_WIN frmwin); 

#endif /* __HEADBAR_COM_H__ */


