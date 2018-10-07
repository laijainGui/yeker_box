/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2011, CHIPHD, China
*											 All Rights Reserved
*
* File    	: calendar_uipara.h
* By      	: CQQ
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011/05/13 14:32  create this file, implements the fundamental interface;
**************************************************************************************************************
*/
#ifndef __CALENDAR_UIPARA_H__1C41C96B_8695_4CC3_AA1E_4B651F6A0725__
#define __CALENDAR_UIPARA_H__1C41C96B_8695_4CC3_AA1E_4B651F6A0725__

#include "beetles_app.h"

//////////////////////////////////////////////////////////////////////////
//����ʱ�ӵ�ͼƬ��Դ(���)��С
typedef struct tag_CLD_UI_SIZE_TIME
{
	__rectsz_t num;     //����ͼƬ��С
	__rectsz_t colon;   //ð��ͼƬ��С
	__rectsz_t format;  //am, pmͼƬ��С
}CLD_UI_SIZE_TIME_T;

//����ʱ��ui����
typedef struct tag_CLD_UI_TIME_PARA
{
	RECT               rt;            //ui��������(ͼ������)
	CLD_UI_SIZE_TIME_T bmp_size;      //ͼƬ��Դ(���)��С
	__pos_t            pos_first_num; //����ʱ�ӵ�һλ���ֵ�����
	__pos_t            pos_format;    //am, pmͼƬ������
}CLD_UI_TIME_PARA_T;

//////////////////////////////////////////////////////////////////////////
//����ui��(���)��С����
typedef struct tag_CLD_UI_SIZE_DATE
{
	__rectsz_t week_sp;   //���ڼ�ļ��
	__rectsz_t date_sp;   //���ڼ�ļ��
	__rectsz_t chs_dt_sp; //���� / ũ�� ��ļ��
	__rectsz_t date;      //���ڿ�(������ / ũ��)�Ĵ�С
	//	__rectsz_t reserve;   //prompt;
}CLD_UI_SIZE_DATE_T;

//����ui����ɫ����
typedef struct tag_CLD_UI_COLOUR_DATE
{
	GUI_COLOR  txt;       //һ��������ɫ
	GUI_COLOR  date_f;    //date focus colour
//	GUI_COLOR  holiday;   //holiday colour
//	GUI_COLOR  week;      //������ɫ
//	GUI_COLOR  date_n;    //date normal colour	
//	GUI_COLOR  dateinfo;  //������Ϣ��ɫ
//	GUI_COLOR  date_s;    //date select colour
}CLD_UI_COLOUR_DATE_T;

//����ui����
typedef struct tag_CLD_UI_DATE_PARA
{
	RECT                 rt;          //ui��������(ͼ������)
	CLD_UI_COLOUR_DATE_T colour;      //��ɫ����
	CLD_UI_SIZE_DATE_T   size;        //����ui��(���)��С����
	__pos_t              week_first;  //���ڿ�ʼ������
	__pos_t              date_first;  //���ڿ�ʼ������
	__pos_t              prompt;      //������Ϣ������
}CLD_UI_DATE_PARA_T;


typedef struct tag_CLD_UI_COLOUR_SETTING 
{
	GUI_COLOR  txt;                      //һ��������ɫ
	GUI_COLOR  focus_line;               //focus line text colour
//	GUI_COLOR  focus;                    //focus colour
}CLD_UI_COLOUR_SETTING_T;

typedef struct tag_CLD_UI_SIZE_SETTING
{
	__rectsz_t    line;                  //һ�����ֿ��
}CLD_UI_SIZE_SETTING_T;

//���ý������
typedef struct tag_CLD_UI_SETTING_PARA
{
	RECT                    rt;          //ui��������(ͼ������)
	CLD_UI_COLOUR_SETTING_T colour;      //��ɫ����
	CLD_UI_SIZE_SETTING_T   size;        //����ui��(���)��С����
	__pos_t                 date_tip;    //"����"������
	__pos_t                 format_tip;  //"ģʽ"������
	__pos_t                 time_tip;    //"ʱ��"������
}CLD_UI_SETTING_PARA_T;

//////////////////////////////////////////////////////////////////////////
//calendar ui para 
typedef struct tag_calendar_uipara 
{
//	RECT                    rt_lcd;         //LCD����
	CLD_UI_TIME_PARA_T      ui_time;        //����ʱ��ui����
	CLD_UI_DATE_PARA_T      ui_date;        //����ui����
	CLD_UI_SETTING_PARA_T   ui_setting;     //���ý���
}calendar_uipara_t;


//��ȡui����
calendar_uipara_t * get_calendar_uipara(void);

#endif //__CALENDAR_UIPARA_H__1C41C96B_8695_4CC3_AA1E_4B651F6A0725__
//End of this file

