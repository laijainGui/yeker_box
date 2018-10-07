/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           willow app sample
*
*						        (c) Copyright 2006-2007, SoftWinners Microelectronic Co., Ltd.
*											All	Rights Reserved
*
* File    : miniplay_uipara.h
* By      : john.fu
* Version : V1.00
*********************************************************************************************************
*/

#ifndef _MINI_MUSIC_UIPARA_H_
#define _MINI_MUSIC_UIPARA_H_

typedef struct MINIPLAY_UI_PARA_ITEM
{
   	__u32   x;
    __u32   y;
    __u32   width;
    __u32   height;
	__u32   reserved[32];
}__miniplay_ui_para_item_t;

typedef struct LYRIC_UI_PARA_LAYER
{
    __pixel_rgbfmt_t    fb_fmt;             //ͼ���ʽ
    SIZE 	fb_size;					  	//framebuffer��С
    RECT    src_rect;					  	//scrwin����	
    RECT 	scn_rect;						//srcwin����
	__u32  	reserved[32];					//Ԥ��
}__miniplay_ui_para_layer_t;

typedef struct LYRIC_PARA
{
	__miniplay_ui_para_layer_t  para_lyrwin;		//lyrwin
    __miniplay_ui_para_item_t 	para_frmwin;   		//framewin
    __miniplay_ui_para_item_t	para_songname;		//�������ؼ�����
    __miniplay_ui_para_item_t	para_slide;			//�������ؼ�����
    __miniplay_ui_para_item_t	para_pre;			//ǰһ�׿ؼ�����
    __miniplay_ui_para_item_t	para_next;			//��һ�׿ؼ�����
    __miniplay_ui_para_item_t	para_play;			//���ſؼ�����
    __miniplay_ui_para_item_t	para_time;  		//����ʱ��ؼ�����              
    __miniplay_ui_para_item_t   para_exit;			//ֹͣ�ؼ���ֹͣ���ֲ���
    __miniplay_ui_para_item_t   para_quit;			//�Ƴ��ؼ���ת��ȫģʽ���Ž���
    __miniplay_ui_para_item_t	para_bg;			//����
}__miniplay_uipara_t;


__miniplay_uipara_t * miniplay_get_uipara(void);



#endif //_MINIPLAY_UIPARA_H_

