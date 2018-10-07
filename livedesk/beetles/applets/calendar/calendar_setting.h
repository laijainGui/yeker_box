/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2011, CHIPHD, China
*											 All Rights Reserved
*
* File    	: calendar_setting.h
* By      	: CQQ
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011/05/13 16:32  create this file, implements the fundamental interface;
**************************************************************************************************************
*/
#ifndef __CALENDAR_SETTING_H__FF741D68_0BBC_4EC7_A895_0FA3F3B1AAC2__
#define __CALENDAR_SETTING_H__FF741D68_0BBC_4EC7_A895_0FA3F3B1AAC2__

//��Դ
typedef struct tag_calendar_setting_res
{
	load_bmp_res_t bmp_bg;
}calendar_setting_wnd_res_t;

enum
{
	CLD_SET_LINE_DATE = 0,
	CLD_SET_LINE_FORMAT,
	CLD_SET_LINE_TIME,
	CLD_SET_LINE_MAX,
};
#define SET_OP_PARA_INVALIDATION       10000

//�û�����ʱ��ui���������
typedef struct tag_calendar_set_op_ui
{
	__s32    line;       //ѡ���е����
	__s32    pos;        //ѡ���еĽ������
}calendar_set_op_ui_t;

typedef __s8 TIME_FORAMT_T;
typedef struct tag_format_time_t
{
	__time_t      tm;  //���ڴ�ʱ�Ƶ�ʱ��, ��formatΪ0ʱ, Ϊ24ʱ��[00:00 - 23:59],
	                   //��formatΪ��0ʱ, Ϊ12ʱ��[12:00am - 11:59am, 12:00pm - 11:59pm],

	TIME_FORAMT_T fmt; //ʱ��(ע��:�ֽڶ�������, __time_t Ϊ24�ֽ�, �����Ϊ__s8)

}FORMAT_TIME_T;        //(�� __time_t��С �ı�, Ϊ���ֱ��ṹ��4�ֽڶ���, �ɼӱ����ֽڻ�ı�fmt��С)

#define Is24HourFormat(_format)        ((_format) == 0)
#define Set24HourFormat(_format)       ((_format) =  0)
#define Is12HourFormat(_format)        ((_format) &  0x3)
#define Set12HourFormat(_format)       ((_format) =  0x3)//�˺겻����ʹ�ã���������Ӧ�ÿ�ʹ_formatֵΪ��ȷ��am��pmֵ
#define SetFormatAm(_format)           ((_format) =  0x1)
#define SetFormatPm(_format)           ((_format) =  0x2)
#define IsFormatPm(_format)            ((_format) == 0x2)

// #define CSTR_AM                         "AM"
// #define CSTR_PM                         "PM"


//�����õ�����
typedef struct tag_calendar_setting_data 
{
	__date_t                date;
	FORMAT_TIME_T           f_time;
	calendar_set_op_ui_t    op_ui;

	//����Ϊ����ǰ���ݵ����ݣ��������õ����ݱȽϣ���û�仯�����õ�ϵͳ
	__date_t                old_date; 
	FORMAT_TIME_T           old_time;
}calendar_setting_data_t;

//��������
typedef struct tag_calendar_setting_para
{
	H_LYR                      layer;
	calendar_setting_wnd_res_t res;
	calendar_setting_data_t    data;
}calendar_setting_wnd_para_t;

//////////////////////////////////////////////////////////////////////////

//RTCʱ��ת��ʱ�Ƹ�ʽʱ�� 
/*ʹ�÷�ʽʾ��:
{
	__time_t rtc; 
	FORMAT_TIME_T f_time; 

	esTIME_GetTime(&rtc);
	f_time->fmt = get_time_format();//ȡϵͳʱ��,����0Ϊ24ʱ��,����1Ϊ12ʱ��
	//Set12HourFormat(f_time->fmt)  //�ֶ�����Ϊ12ʱ��
	//Set24HourFormat(f_time->fmt); //�ֶ�����Ϊ24ʱ��
	rtc_time_to_format_time(&rtc, &f_time); //�˵��û�ʹf_time->fmtΪ��ȷ��am,pmֵ
}
{//��һ��ʹ�÷�ʽ
	FORMAT_TIME_T f_time;
	esTIME_GetTime(&f_time.tm);
	rtc_time_to_format_time(&f_time.tm, f_time);//�˴ε���ʵ����f_time���ڲ�ת��(24ʱ��ת12ʱ��)
}
*/
extern void rtc_time_to_format_time(__time_t *rtc, FORMAT_TIME_T *f_time);

//��ʱ�Ƹ�ʽʱ��תRTCʱ��
/*ע�⣺
{
	//FORMAT_TIME_T f_time;
	format_time_to_rtc_time(&f_time, &f_time.tm);//�˴ε���ʵ����f_time���ڲ�ת�������ܻ��޸�f_time.fmt
}
*/
extern void format_time_to_rtc_time(FORMAT_TIME_T *f_time, __time_t *rtc);

//����ʱ�����ô���
extern H_WIN calendar_setting_frmwin_create(H_WIN h_parent, H_WIN layer);

#endif //__CALENDAR_SETTING_H__FF741D68_0BBC_4EC7_A895_0FA3F3B1AAC2__
//End of this file

