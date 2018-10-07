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

#ifndef __CAT_COMMON_H__
#define __CAT_COMMON_H__

#include ".\\..\\cat_p.h"
#include ".\\..\\engine\\cat_engine.h"

#define ORCHID_FILE_PATH                "b:\\module\\orchid"

/*
**********************************************************************************************************************
*                                               cat_create_root
*
* author:          terry.zeng 
*
* date:             2010-09-13
*
* Description:       �����������Ϣ 
*
* parameters:       param ����������� cat_listΪ����������Ϣ
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_create_root(cat_create_param_t *param, cat_list_t *cat_list);


/*
**********************************************************************************************************************
*                                               cat_destroy_root
*
* author:          terry.zeng 
*
* date:             2010-09-13
*
* Description:       ɾ����Ŀ¼��Ϣ
*
* parameters:       __cat_item_t *item
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_destroy_root(cat_list_t *cat_list);


/*
**********************************************************************************************************************
*                                               cat_create_partition_info
*
* author:          terry.zeng 
*
* date:             2010-09-13
*
* Description:       �������������Ϣ 
*
* parameters:       param �����������,����������Ϣ
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_create_partition_info(cat_create_param_t *param, cat_list_t *cat_list);


/*
**********************************************************************************************************************
*                                               cat_destroy_partition_info
*
* author:          terry.zeng 
*
* date:             2010-09-13
*
* Description:       ���ٷ��������Ϣ 
*
* parameters:       cat_list �����Ϣ
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_destroy_partition_info(cat_list_t *cat_list);


/*
**********************************************************************************************************************
*                                               cat_create_dir_info
*
* author:          terry.zeng 
*
* date:             2010-09-13
*
* Description:       ����Ŀ¼�����Ϣ 
*
* parameters:       param �����������,����������Ϣ
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_create_dir_info(cat_create_param_t *param, cat_list_t *cat_list, cat_engine_t *engine, __u32 start_pos);


/*
**********************************************************************************************************************
*                                               cat_destroy_playlist_info
*
* author:          terry.zeng 
*
* date:             2010-09-30
*
* Description:       ����Ŀ¼�����Ϣ
*
* parameters:       cat_list �����Ϣ
*
* return:           success: EPDK_OK;   failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_destroy_dir_info(cat_list_t *cat_list);


/*
**********************************************************************************************************************
*                                               cat_create_playlist
*
* author:          terry.zeng 
*
* date:             2010-09-30
*
* Description:       ����playlist�����Ϣ 
*
* parameters:       param �����������,����������Ϣ
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_create_playlist_info(cat_create_param_t *param, cat_list_t *cat_list, cat_engine_t *engine, __u32 start_pos);


/*
**********************************************************************************************************************
*                                               cat_destroy_playlist_info
*
* author:          terry.zeng 
*
* date:             2010-09-30
*
* Description:       ����playlist�����Ϣ 
*
* parameters:       cat_list �����Ϣ
*
* return:           success: EPDK_OK;	failed: EPDK_FAIL;
* modify history: 
**********************************************************************************************************************
*/
__s32 cat_destroy_playlist_info(cat_list_t *cat_list);


/*
**********************************************************************************************************************
*                                               cat_get_file_count_in_dir
*
* author:          terry.zeng 
*
* date:             2009-09-30
*
* Description:       ��ȡĿ¼���µķ���Ҫ���ʽ���ļ����� 
*
* parameters:       path Ŀ¼ȫ·����  media_type��ý������
*
* return:           �ļ�����
* modify history: 
**********************************************************************************************************************
*/
__u32 cat_get_file_count_in_dir(char *path, __u32 check_type);


#endif
