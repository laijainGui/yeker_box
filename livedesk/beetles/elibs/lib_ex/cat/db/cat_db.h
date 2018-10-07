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
#ifndef __CAT_DB_H__
#define __CAT_DB_H__

#include ".\\..\\cat_p.h"

#define DB_FILE_NAME   ":memory:"   //"d:\\apps\\db_cat.db"  


typedef struct cat_db_s
{
    HDBConn     hdb;
}cat_db_t;


/*
**********************************************************************************************************************
*                                               cat_db_open
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      cat ���ݿ�򿪺�����ִ��������ݿ�ĳ�ʼ������
*
* parameters:
*
* return:           if success return cat db handle
*                   if fail return NULL
* modify history:
**********************************************************************************************************************
*/
cat_db_t *cat_db_open(void);


/*
**********************************************************************************************************************
*                                               cat_db_close
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �ر� ���ݿ�
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_close(cat_db_t *db_handle);


/*
**********************************************************************************************************************
*                                               cat_db_table_create
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      ���������Ϣ���ݿ��ļ�
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_table_create(cat_db_t *db_handle, cat_list_handle_t *list_handle);


/*
**********************************************************************************************************************
*                                               cat_db_table_del
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      ɾ�������Ϣ���ݿ��ļ�
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_table_del(cat_db_t *db_handle, cat_list_handle_t *list_handle);


/*
**********************************************************************************************************************
*                                               cat_db_get_num
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      ��ȡ�����Ϣ������
*
* parameters:
*
* return:           return item number
*
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_get_num(cat_db_t *db_handle, cat_list_handle_t *list_handle);


/*
**********************************************************************************************************************
*                                               cat_db_add_base_info
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �����ݿ������������������Ϣ
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_add_base_info(cat_db_t *db_handle, cat_list_handle_t *list_handle);


/*
**********************************************************************************************************************
*                                               cat_db_get_base_info
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �����ݿ������ȡ����������Ϣ
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_get_base_info(cat_db_t *db_handle, cat_list_handle_t *list_handle, __u32 index, __cat_item_t *item);


/*
**********************************************************************************************************************
*                                               cat_db_add_extra_info
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �����ݿ������������������Ϣ
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_add_extra_info(cat_db_t *db_handle, cat_list_handle_t *list_handle, __u32 index, __cat_item_t *item);


/*
**********************************************************************************************************************
*                                               cat_db_get_extra_info
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �����ݿ������ȡ����������Ϣ
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_get_extra_info(cat_db_t *db_handle, cat_list_handle_t *list_handle, __u32 index, __cat_item_t *item);


/*
**********************************************************************************************************************
*                                               cat_db_disable_extra_info
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      ʹĳһ��Ķ�����Ϣ��Ч
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_disable_extra_info(cat_db_t *db_handle, cat_list_handle_t *list_handle, __u32 index);


/*
**********************************************************************************************************************
*                                               cat_db_sort
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �����ݿ����ݽ�������
*
* parameters:		type���������ͣ�����С�����֡�ʱ�䡢���͵ȣ� mode������ģʽ���������
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_sort(cat_db_t *db_handle, cat_list_handle_t *list_handle, cat_sort_type_t type, cat_sort_mode_t mode);


/*
**********************************************************************************************************************
*                                               cat_db_del_item
*
* author:        terry.zeng
*
* date:             2010-10-18
*
* Description:      ɾ�����ݿ�ĳһ��
*
* parameters:		
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_del_item(cat_db_t *db_handle, cat_list_handle_t *list_handle, __u32 index, __cat_item_t *cat_item);


/*
**********************************************************************************************************************
*                                               cat_db_add_item
*
* author:        terry.zeng
*
* date:             2010-10-18
*
* Description:      �����ݿ������ĳһ��
*
* parameters:		
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_add_item(cat_db_t *db_handle, cat_list_handle_t *list_handle, __cat_item_t *cat_item);


/*
**********************************************************************************************************************
*                                               cat_db_check_item_exist
*
* author:        terry.zeng
*
* date:             2010-10-18
*
* Description:      checkĳһ���Ƿ���������ݿ���
*
* parameters:		
*
* return:           if exist return EPDK_TRUE
*                   else return EPDK_FALSE
* modify history:
**********************************************************************************************************************
*/
__bool cat_db_check_item_exist(cat_db_t *db_handle, cat_list_handle_t *list_handle, __cat_item_t *item);


/*
**********************************************************************************************************************
*                                               cat_db_get_rowid
*
* author:        terry.zeng
*
* date:             2010-10-18
*
* Description:      ͨ�����ֻ�ȡID
*
* parameters:		
*
* return:           if success return ID
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_get_rowid(cat_db_t *db_handle, cat_list_handle_t *list_handle, char *filename);


/*
**********************************************************************************************************************
*                                               cat_db_search
*
* author:        terry.zeng
*
* date:             2010-09-06
*
* Description:      �����ݿ����������ļ�
*
* parameters:		keyword:�ؼ���
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_db_search(cat_db_t *db_handle, cat_list_handle_t *list_handle, char *keyword, cat_list_handle_t *search_handle);

#endif

