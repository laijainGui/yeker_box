/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: gscene_headbar.h
* By      	: Andy.zhang
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2010-9-25 19:19:34 andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#ifndef __GSCENE_HEADBAR_H__
#define __GSCENE_HEADBAR_H__

typedef enum _HBarState
{
	HBAR_ST_SHOW,
	HBAR_ST_HIDE	
}HBarState;

typedef enum tag_HBAR_FORMAT
{
	HBAR_FOARMAT_8BPP,
	HBAR_FOARMAT_32BPP	
}__hbar_format_t;

typedef struct 
{
	char 			*name;		// ��������
	__u16 			sid;		// ����id	
	H_WIN 			parent;		// ������
	H_WIN 			layer;		// ͼ��	
	GUI_FONT    	*font;		// ������	
	__hbar_format_t format;		//format
}HBarCreatePara;

__s32 gscene_hbar_create(H_WIN parent, __hbar_format_t format);
__s32 gscene_hbar_set_state(HBarState state);
__s32 gscene_hbar_get_state(HBarState *p_state);
__s32 gscene_hbar_set_title(char *title, __u32 len);	/* title Ϊutf8�����ʽ�ַ�����len<=32 ,����hbar title �����ַ���*/
//__s32 gscene_hbar_set_volume(void);
__s32 gscene_hbar_set_format(__hbar_format_t format);
__s32 gscene_hbar_get_screen_rect(RECT *rect);
__s32 gscene_hbar_delete(void);


#endif /* __GSCENE_HEADBAR_H__ */


