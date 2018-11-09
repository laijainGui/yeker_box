#ifndef __PRESS_BUTTON_H__
#define __PRESS_BUTTON_H__

#include "beetles_app.h"

typedef struct press_button {
	//SCR_ScrollingWndInfo_ForHeader scrolling;
	__s32 item_id;
	__s32 page_id;
	__s32 jump_enable;
	__s32 jump_page_id;
	__s32 jump_delay_ms;
	__s32 item_type;
	__s32 relate_to_group;
	__s32 status;
	__s32 bmp_id[2];
	load_bmp_res_t bmp_res[2];
	__s32 text_id[2];
	__s32 text_size;
	__u32 text_color;
	__s32 text_x;
	__s32 text_y;
	ButtonCode_handle * code_handle;  //�������ݱ���
}press_button_t;

typedef struct push_button {
	//SCR_ScrollingWndInfo_ForHeader scrolling;
	__s32 item_id;
	__s32 page_id;
	__s32 item_type;
	__s32 status;
	__s32 bmp_id[3];
	load_bmp_res_t bmp_res[3];
	__s32 text_id[3];
	__s32 text_size;
	__u32 text_color;
	__s32 text_x;
	__s32 text_y;
	ButtonCode_handle * code_handle;  //�������ݱ���
}push_button_t;

typedef struct textview {
	//SCR_ScrollingWndInfo_ForHeader scrolling;
	__s32 item_id;
	__s32 page_id;
	__s32 item_type;
	__s32 text_id;
	__s32 text_size;
	__u32 text_color;
	__s32 x;
	__s32 y;
	__s32 width;
	__s32 height;
	//__gui_rect_t rect;
}textview_t;

typedef struct imageview {
	//SCR_ScrollingWndInfo_ForHeader scrolling;
	__s32 item_id;
	__s32 page_id;
	__s32 item_type;
	int    imageview_num;                  //ͼƬ�� ��ʾ��ͼƬ���
	int    imageview_tal;                  //ͼƬ��ͼƬ����
	Image_handle * image_date_handle;      //ͼƬ��ͼƬ���
}imageview_t;

typedef struct slider {
	//SCR_ScrollingWndInfo_ForHeader scrolling;
	__s32 item_id;
	__s32 page_id;
	__s32 item_type;
	int lampLimit;                         //������ �߶�/ ���
	int lampLimit_max;                     //���������ֵ
	int lampLimit_min;                     //��������Сֵ
	int lampLimit_height;                  //�������Ļ��� �߶�/ ���
	int lampValue;                         //����������λ��
	int old_lampValue;                     //��������һ������λ��
	int lampSlide;
	int lampStep;
	int value;                             //������ֵ
	int old_value;						   //��������һ�ε�ֵ
	int click_move;						   //�ܿ��ƶ�
}slider_t;

__s32 press_button_proc(__gui_msg_t * msg);

#endif
