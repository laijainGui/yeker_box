/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           cat  sample
*
*						        (c) Copyright 2006-2007, terry, China
*											All	Rights Reserved
*
* File    : cat_db_interface.h
* By      : terry.zeng
* Version : V2.00
* date    :2010-09-06
*********************************************************************************************************
*/

#ifndef __CAT_ENGINE_H__
#define __CAT_ENGINE_H__

#include ".\\..\\cat_p.h"
#include ".\\..\\db\\cat_db.h"


typedef enum cat_engine_cmd_s
{
    READ_START = 0x01,      //��ʼ��ĳ�������Ϣ��������
    READ_PAUSE,             //��ͣ��ǰ������
    READ_STOP,              //ֹͣ��ǰ����
    READ_RESUME,            //�ָ���ǰ����
    UPDEATE_ROOT,
    GET_STATUS,             //��ȡ��ǰ����״̬
}cat_engine_cmd_t;


typedef enum cat_engine_status_s
{
    ENGINE_STOPPED,     //��ǰ���洦��ֹͣ״̬
    ENGINE_BUSY,        //��ǰ���洦��æµ״̬
    ENGINE_PAUSED,      //��ǰ���洦����ͣ״̬	
}cat_engine_status_t;


typedef struct cat_engine_s
{
    cat_db_t                *db;
    __u8                    thread_id;          /*�߳�ID*/	
    __krnl_event_t          *sem;               /*�ź���*/
    __s32                   cmd_pend_flag;      /*�̴߳����־λ*/
    __u32                   cmd;                /*�̴߳�������*/
    __s32                   param1;             /*�������1*/
    __s32                   param2;             /*�������2*/
    __s32                   result;             /*������õĽ��*/
    cat_engine_status_t     status;
    cat_list_handle_t       *list_handle;
}cat_engine_t;


/*
**********************************************************************************************************************
*                                               cat_engine_open
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      cat ��̨��������
*
* parameters:
*
* return:           if success return cat engine handle
*                   if fail return NULL
* modify history:
**********************************************************************************************************************
*/
void* cat_engine_open(cat_db_t *db);


/*
**********************************************************************************************************************
*                                               cat_engine_control
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      cat ��̨����������ƺ���
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_engine_control(void *hengine, __u32 cmd, __s32 param1, __s32 param2);


/*
**********************************************************************************************************************
*                                               cat_engine_close
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      cat ��̨��������ر�
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_engine_close(void *hengine); 


#endif

