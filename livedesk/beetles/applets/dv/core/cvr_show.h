/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           home app sample
*
*						        	(c) Copyright 2006-2009, LYN, China
*											 All Rights Reserved
*
* File    : cvr_show.h
* By      : lyn
* Version : V1.00
*********************************************************************************************************
*/

#ifndef __CVR_SHOW_H__
#define __CVR_SHOW_H__

#include "..\\dv_i.h"

typedef enum tag_SHOW_MODE
{
    SHOW_WINDOW_BESTSHOW = 0x00,        /* ��ͼƬ����ı�����������������ʾ��ͼƬ������ */
    SHOW_WINDOW_ORIGINAL,               /* ��ͼƬԭʼ��С�ڴ�������ʾ�������������     */
    SHOW_WINDOW_FULLSCN,                /* �Դ��ڵı�������ͼƬ����������ʾ�����ܻ���� */
    SHOW_WINDOW_
}show_mode_e;

__s32   Cvr_ShowOpen(void);
__s32   Cvr_ShowClose(void);
__s32   Cvr_ShowStatus(__s32 enable);
__s32   Cvr_ShowSetData(void * buf, SIZE buf_size);
__s32   Cvr_ShowSetMode(show_mode_e mode);
__s32   Cvr_ShowGetSize(SIZE * size);

#endif  /* __CVR_SHOW_H__ */

