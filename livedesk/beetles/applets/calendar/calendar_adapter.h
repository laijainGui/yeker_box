/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2011, CHIPHD, China
*											 All Rights Reserved
*
* File    	: calendar_adapter.h
* By      	: CQQ
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011/05/13 15:27  create this file, implements the fundamental interface;
**************************************************************************************************************
*/
#ifndef __CALENDAR_ADAPTER_H__328AE06C_DF8D_462D_B1AF_2984F4AD33F7__
#define __CALENDAR_ADAPTER_H__328AE06C_DF8D_462D_B1AF_2984F4AD33F7__

#include "beetles_app.h"

// #if (BEETLES_RTC_EXIST == 0)
// #ifndef ID_CALENDAR_COLOURTABLE_BMP
// #include "temp_res.h"
// #endif
// #endif
//////////////////////////////////////////////////////////////////////////
//opinion
/*
1.GUI_MSG_KEY_MENU���̰��˳����������������ز˵���
2.GUI_MSG_KEY_LEFT
3.GUI_MSG_KEY_RIGHT
4.GUI_MSG_KEY_ENTER
5.GUI_MSG_KEY_VADD(�̰��л��Ӳ˵����������������)
*/
////////////�����

//ʱ��/���ڽ��洦��
#define VK_CLD_SWITCH_TIME_DATE        VK_SUBMENU //�л�<ʱ��, ����>����
#define VK_CLD_POP_SETTING             VK_MENU    //�� / �� ʱ�����ý���
//���ý��洦��
#define VK_CLD_SETTING_ADD             VK_RIGHT   // ���� / ʱ�� �ȼ���ֵ
#define VK_CLD_SETTING_SUB             VK_LEFT    // ���� / ʱ�� �ȼ���ֵ
#define VK_CLD_SETTING_LOOPMENU        VK_SUBMENU // ���ò˵�ѭ��
#define VK_CLD_SETTING_ENTER           VK_ENTER   // ȷ�ϱ���
//////////////////////////////////////////////////////////////////////////
//macro const
#define CALENDAR_TIME_WND_NAME         Symbol2Str(calendar_time_wnd)

//for debug
#define DEBUG_CLD                      __msg

///////////////////for x, y / bmp / str
#if 0//re define GUI_BMP_Draw, GUI_DispStringAt, GUI_DispStringInRect

//re define GUI_BMP_Draw
#ifdef GUI_BMP_Draw
#define MY_GUI_BMP_DRAW                      (ORANGEMOD_FUNC_ENTRY->ptr_GUI_BMP_Draw         	)
#undef GUI_BMP_Draw
#define GUI_BMP_Draw(_p, _x, _y)             do \
{\
	{__msg("    GUI_BMP_Draw(%d, %d)\n", _x, _y);} \
	MY_GUI_BMP_DRAW(_p, _x, _y); \
}while(0)
#endif

//re define GUI_DispStringAt
#ifdef GUI_DispStringAt
#define MY_GUI_DispStringAt                  (ORANGEMOD_FUNC_ENTRY->ptr_GUI_DispStringAt       	)
#undef GUI_DispStringAt
#define GUI_DispStringAt(_p, _x, _y)         \
	do\
{ \
	{__msg("    GUI_DispStringAt(%d, %d) = %s\n", _x, _y, _p);} \
	MY_GUI_DispStringAt(_p, _x, _y); \
}while(0)
#endif

//re define GUI_DispStringInRect
#ifdef GUI_DispStringInRect
#define MY_GUI_DispStringInRect              (ORANGEMOD_FUNC_ENTRY->ptr_GUI_DispStringInRect   	)
#undef GUI_DispStringInRect
#define GUI_DispStringInRect(_p, _prt, _fmt)  \
	do \
{ \
	{__msg("    GUI_DispStringInRect(%d, %d, %d, %d)(%x) = %s\n", (_prt)->x0, (_prt)->y0, (_prt)->x1, (_prt)->y1, _fmt, _p);} \
	MY_GUI_DispStringInRect(_p, _prt, _fmt); \
} while (0)
#endif

#endif
//////////////////end of for x, y / bmp / str
#define TEST_TIME_FORMAT                0
#if TEST_TIME_FORMAT
extern __s32 g_time_format;

#define get_time_format()                            (g_time_format)
#define set_time_format(_d)                          (g_time_format = (_d))

#else

#define get_time_format                              _get_time_format
#define set_time_format                              _set_time_format

#endif
//////////////////////////////////////////////////////////////////////////

//ȡ��������
extern __u16 get_week_day(__u16 year, __u8 month, __u8 day);
extern __s32 _get_time_format(void);
extern __s32 _set_time_format(__s32 format);

#endif //__CALENDAR_ADAPTER_H__328AE06C_DF8D_462D_B1AF_2984F4AD33F7__
//End of this file

