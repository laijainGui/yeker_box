/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           cat  sample
*
*						        (c) Copyright 2006-2007, terry, China
*											All	Rights Reserved
*
* File    : cat.h
* By      : terry.zeng
* Version : V2.00
* Date	  : 2010-09-08
*********************************************************************************************************
*/

#ifndef __CAT_H__
#define __CAT_H__


#define CAT_MAX_FULL_PATH_LEN  1024


typedef unsigned int HEXPLR;
typedef unsigned int HCAT;


#define CAT_USB_DISK    "ExternalDisk1"
#define CAT_TF_CARD     "ExternalDisk0"
#define CAT_MEDIALIB    "media_lib_root"
#define CAT_LOCAL_DISK  "LocalDisk"
#define CAT_CDROM       "ExternalDisk2"


/*!
  * \brief
  *     AUDIO�ļ���ʽ
*/
typedef enum
{
    CAT_AUDIO_FORMAT_AAC = 0x00,
    CAT_AUDIO_FORMAT_AC3,
    CAT_AUDIO_FORMAT_AMR,
    CAT_AUDIO_FORMAT_APE,
    CAT_AUDIO_FORMAT_ATRC,
    CAT_AUDIO_FORMAT_DTS,
    CAT_AUDIO_FORMAT_FLAC,
    CAT_AUDIO_FORMAT_MID,    
    CAT_AUDIO_FORMAT_MP3, 
    CAT_AUDIO_FORMAT_OGG,   
    CAT_AUDIO_FORMAT_RA,
    CAT_AUDIO_FORMAT_WAV,
    CAT_AUDIO_FORMAT_WMA,    
    CAT_AUDIO_FORMAT_UNKNOWN,
}cat_audio_format_t;


/*!
  * \brief
  *     VIDEO�ļ���ʽ
*/
typedef enum
{
    CAT_VIDEO_FORMAT_3GP = 0x20,
    CAT_VIDEO_FORMAT_ASF,
    CAT_VIDEO_FORMAT_AVI,
    CAT_VIDEO_FORMAT_DAT,
    CAT_VIDEO_FORMAT_FLV,
    CAT_VIDEO_FORMAT_MKV,
    CAT_VIDEO_FORMAT_MOV,
    CAT_VIDEO_FORMAT_MP4,
    CAT_VIDEO_FORMAT_MPG,
    CAT_VIDEO_FORMAT_PMP,
    CAT_VIDEO_FORMAT_PSR,
    CAT_VIDEO_FORMAT_RM,
    CAT_VIDEO_FORMAT_RMVB,
    CAT_VIDEO_FORMAT_TP,
    CAT_VIDEO_FORMAT_TS,    
    CAT_VIDEO_FORMAT_VOB,    
    CAT_VIDEO_FORMAT_WMV,    
    CAT_VIDEO_FORMAT_UNKNOWN
}cat_video_format_t;


/*!
  * \brief
  *     ͼƬ�ļ���ʽ
*/
typedef enum
{
    CAT_PIC_FORMAT_BMP = 0x40,
    CAT_PIC_FORMAT_GIF,
    CAT_PIC_FORMAT_JPG,
    CAT_PIC_FORMAT_PNG,	
    CAT_PIC_FORMAT_UNKNOWN
}cat_pic_format_t;


/*!
  * \brief
  *     EBOOK�ļ���ʽ
*/
typedef enum
{
    CAT_EBOOK_FORMAT_TXT = 0x50,
    CAT_EBOOK_FORMAT_C,
    CAT_EBOOK_FORMAT_H,
    CAT_EBOOK_FORMAT_INI,
    CAT_EBOOK_FORMAT_LRC,
    CAT_EBOOK_FORMAT_SRT,
    CAT_EBOOK_FORMAT_PDF,
    CAT_EBOOK_FORMAT_EPUB,
    CAT_EBOOK_FORMAT_FB2,
    CAT_EBOOK_FORMAT_PDB,
    CAT_EBOOK_FORMAT_RTF,
    CAT_EBOOK_FORMAT_HTML,
    CAT_EBOOK_FORMAT_CHM,
    CAT_EBOOK_FORMAT_HTM,
    
    CAT_EBOOK_FORMAT_UNKNOWN
}cat_ebook_format_t;


/*!
  * \brief
  *     GAME�ļ���ʽ
*/
typedef enum
{
    CAT_GAME_FORMAT_EPOS = 0x70,
    CAT_GAME_FORMAT_UNKNOWN
}cat_game_format_t;


typedef enum
{
    CAT_FLASH_FORMAT_SWF = 0x80,
    CAT_FLASH_FORMAT_UNKNOWN
}cat_flash_format_t;


typedef enum
{
    CAT_FIRMWARE_FORMAT_IMG = 0x90,
    CAT_FIRMWARE_FORMAT_UNKNOWN	
}cat_firmware_format_t;


/*!
  * \brief
  *     ���ɨ�������
*/
typedef enum
{
    CAT_SCAN_ALL_DEVICE,    //��ɨ�裬ɨ������CAT_USB_DISK��CAT_TF_CARD��CAT_MEDIALIB��CAT_LOCAL_DISK,CAT_CDROM
    CAT_SCAN_ALL_PATI,      //��ɨ�裬���Է���Ϊ����������CAT_MEDIALIB��e,f...�ȵ�
    CAT_SCAN_PARTI,         //����ɨ�裬ֻɨ��ĳ���豸�ķ���
    CAT_SCAN_DIR,           //��ͨĿ¼ɨ�裬ֻɨ�赱ǰ·�������ݹ�
    CAT_SCAN_MEIDA_ALL,     //Ŀ¼ȫɨ�裨ָ��·���������ļ�ɨ�裬������Ŀ¼�µ��ļ���
}cat_scan_type_t;


/*!
  * \brief
  *     �����ý������
*/
typedef enum
{
    CAT_MEDIA_TYPE_ALL,         //����ý������
    CAT_MEDIA_TYPE_PIC,         //����ͼƬ�ļ�
    CAT_MEDIA_TYPE_AUDIO,       //������Ƶ�ļ�
    CAT_MEDIA_TYPE_VIDEO,       //������Ƶ�ļ�
    CAT_MEDIA_TYPE_EBOOK,       //���е������ļ�
    CAT_MEDIA_TYPE_GAME,        //������Ϸ�ļ�
    CAT_MEDIA_TYPE_FLASH,       //����SWF�ļ�
    CAT_MEDIA_TYPE_FIRMWARE,    //���й̼��ļ�
    CAT_MEDIA_TYPE_UNKNOWN,     //����ϵͳ��֧�ֵ��ļ�
}cat_media_type_t;


/*!
  * \brief
  *     ����Ľ����ÿһ������ͣ��ļ���Ŀ¼��
*/
typedef enum
{
    CAT_SW_FILE = 0x01,     //�ļ�
    CAT_SW_DIR,             //Ŀ¼
    CAT_SW_PARTI,           //����
    CAT_SW_DEVICE,          //��
    CAT_SW_EMPTY            //�޷�ʶ��
}cat_item_type_t;



/*!
  * \brief
  *     ����ķ�ʽ
*/
typedef enum
{
    CAT_UNSORT,     //����
    CAT_ASCEND,     //����
    CAT_DESCEND     //����
}cat_sort_mode_t;


/*!
  * \brief
  *     ���������
*/
typedef enum
{
    CAT_SORT_NAME,      //������ֽ�������
    CAT_SORT_TIME,      //���ʱ���������
    CAT_SORT_SIZE,      //��Դ�С��������
    CAT_SORT_FORMAT     //��Ը�ʽ��������
}cat_sort_type_t;


/*!
  * \brief
  *     �������
*/
typedef struct
{
    cat_sort_mode_t     mode;       //����ʽ
    cat_sort_type_t     type;       //���������
}cat_sort_para_t;


/*!
  * \brief
  *     ����ͼ�������
*/
typedef struct
{
    char file[CAT_MAX_FULL_PATH_LEN];   //�ļ�ȫ·��
    __u8 format;                        //���ݸ�ʽ
    __u32 width;                        //���
    __u32 height;                       //�߶�
    __u32 mode;                         //����ģʽ��0�����죬1����
}cat_miniature_para_t;


/*!
  * \brief
  *     ���ص�����ͼ���ݲ���
*/
typedef struct
{
    __u32 len;      //���ݳ���
    char *buf;      //����
}cat_miniature_t;


/*!
  * \brief
  *     �����������ʱ�Ĵ������
*/
typedef struct
{
    char                path[CAT_MAX_FULL_PATH_LEN];    // �������·��
    cat_scan_type_t     scan_type;                      //���ɨ�������
    cat_media_type_t    media_type;                     //�����ý������
}cat_create_param_t;


/*!
  * \brief
  *     ���������Ϣ���cat״̬
*/
typedef enum
{
    CAT_CREATING = 0x01,    //������
    CAT_CREATE_OVER,        //�������
    CAT_CREATE_UNKONWN,
}cat_create_status_t;


/*!
  * \brief
  *     ������Ӧ���豸
*/
typedef enum
{
    CAT_UNKNOWN,        //δ֪
    CAT_LOCAL,          //���ش���
    CAT_TF,             //TF��
    CAT_USB,            //USB�豸
    CAT_CD,             //CD-ROM
    CAT_MEDIA           //ý���
}cat_root_t;


/*!
  * \brief
  *     ��������
*/
typedef enum
{
    CAT_READONLY = 0x01,    //ֻ��
    CAT_READWRITE           //�ɶ�д
}cat_pati_attr_t;


/*!
  * \brief
  *     �����Ļ�����Ϣ
*/
typedef struct
{
    char                        fpath[CAT_MAX_FULL_PATH_LEN];           //��item��·��
    cat_item_type_t             type;                                   //���������
    char                        name[CAT_MAX_FULL_PATH_LEN];            //���������
    __epdk_charset_enm_e        char_encoding;                          //�����ʽ
    union
    {
        struct
        {
            cat_pati_attr_t     pati_attr;                          //�������ԣ�ֻ�����߿ɶ�д
            cat_root_t          root_type;                          //�����ͣ������̻���TF����������
        }pati;
        
        struct
        {
            ES_TIMESTAMP        m_time;                             //����ʱ��
        }dir;
        
        struct
        {
            __s64               size;
            ES_TIMESTAMP        m_time;                             //����ʱ��
            cat_media_type_t    media_type;                         //ý�����ͣ����֡���Ƶ��ͼƬ�ȵ�
            __u8                format;                             //��ʽ��MP3\WAV��
        }file;
    }item_pri_info;    
}cat_item_base_info_t;


/*!
  * \brief
  *     �����Ķ�����Ϣ
*/
typedef struct
{
    union
    {
        struct
        {
            __s64   size;
            __s64   space_left;     //������ʣ��ռ�
        }pati;
        
        struct
        {
            __s64   size;
            __u32   item_cnt;       //��������Ӧý�����͵��������
        }dir;
        
        struct
        {
            cat_miniature_t miniature;  //����ͼ��Ϣ
            union
            {
                struct
                {
                    __u32   bitrate;        //������
                    __u32   sample_rate;    //������
                    __u32   channel;        //������
                    __u32   duration;       //��ʱ��
                    __u32   bits;           //��������
                }audio;
                
                struct
                {
                    __u32   width;          //��
                    __u32   height;         //��
                }pic;
                
                struct
                {
                    __u32               width;      //��
                    __u32               height;     //��
                    __u32               frame_rate; //֡��
                    __cedar_video_fmt_t video_fmt;  //��Ƶ��ʽ
                    __cedar_audio_fmt_t audio_fmt;  //��Ƶ��ʽ
                    __u32               duration;   //��ʱ�� 
                }video;
                
                struct
                {
                    char    author[64];     //����
                    char    theme[256];     //����
                }ebook;
            }file_info;
        }file;
    }extra_info;
}cat_item_extra_info_t;


/*!
  * \brief
  *     ���������ÿһ��Ŀ����Ϣ
*/
typedef struct __cat_item_t
{
    cat_item_base_info_t    base_info;      //����Ļ�����Ϣ
    cat_item_extra_info_t   extra_info;     //����Ķ�����Ϣ
}__cat_item_t;


/*!
  * \brief
  *     ɾ��������Ϣ
*/
typedef struct
{
    cat_item_type_t     type;               //��Ŀ���ͣ��ļ�����Ŀ¼
    __u64               total_size;         //��Ҫ������������;
    __u64               finish_size;        //�ѿ�����������;
    __u32               total_num;          //Ŀ¼ʱ���追��/ɾ�����ļ�����
    __u32               finish_num;         //Ŀ¼ʱ������ɿ���/ɾ�����ļ���    
    __u32               percent;            //�ѿ���/ɾ�����ݵİٷֱȣ���ʽ=�ѿ�������/�追����������
}cat_file_op_info_t;


/*!
  * \brief
  *     ����ͼ��Ҫcacheʱ�Ĳ���
*/
typedef struct
{
    __u32 cache_num;    //��Ҫcache�ĸ���
    __u32 buf_size;     //cacheʱÿ��buffer�Ĵ�С
}cat_cache_para_t;


/*
**********************************************************************************************************************
*                                               cat_core_open
*
* author:        terry.zeng
*
* date:             2010-09-08
*
* Description:      cat core �򿪺���
*
* parameters:
*
* return:           if success return cat core handle
*                   if fail return NULL
* modify history:
**********************************************************************************************************************
*/
HCAT cat_core_open(void);


/*
**********************************************************************************************************************
*                                               cat_create_explr
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ���������Ϣ��ֻ��ȡ������Ϣ��extra��Ϣ��Ҫ����Ľӿڵ��÷��ɵõ�
*
* parameters:		cat_handle:cat�����create_para�����б�Ĳ���
*
* return:           if success return explorer info handle
*                   if fail return NULL
* modify history:
**********************************************************************************************************************
*/
HEXPLR cat_create_explr(HCAT cat_handle, cat_create_param_t *create_para);


/*
**********************************************************************************************************************
*                                               cat_get_create_status
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡĿ¼��Ϣ������״̬
*
* parameters:		cat_handle:cat�����hexplr�������Ϣ���
*
* return:           ��
* modify history:
**********************************************************************************************************************
*/
cat_create_status_t cat_get_create_status(HCAT cat_handle, HEXPLR hexplr);


/*
**********************************************************************************************************************
*                                               cat_update_root
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ������Ϣ��������Ҫ���µ������Ϣ���;Ŀǰֻ�Է��������Ч
*
* parameters:		cat_handle:cat���;hexplr:�����Ϣ�����
*
* return:           if success return EPDK_OKt
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_update_root(HCAT cat_handle, HEXPLR hexplr, __s32 plug_in, char disk);


/*
**********************************************************************************************************************
*                                               cat_destroy_explr
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ���������Ϣ
*
* parameters:		core:cat���;hexplr:�����Ϣ�����
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_destroy_explr(HCAT cat_handle, HEXPLR hexplr);


/*
**********************************************************************************************************************
*                                               cat_get_explr_num
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡ�����Ϣ������
*
* parameters:		core:cat���;hexplr:�����Ϣ�����
*
* return:           if success return explorer info num
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_get_explr_num(HCAT cat_handle, HEXPLR hexplr);


/*
**********************************************************************************************************************
*                                               cat_get_explr_item
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡĳһ��������Ϣ
*
* parameters:		core:cat���;hexplr:�����Ϣ�����id:��Ҫ��ȡ����ID cat_item  ��ȡ���������Ϣ�����û�������Ӧ��Դ���ݸ�cat
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_get_explr_item(HCAT cat_handle, HEXPLR hexplr, __u32 id, __cat_item_t *cat_item);


/*
**********************************************************************************************************************
*                                               cat_sort_explr
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      �������Ϣ��������
*
* parameters:		core:cat���;hexplr:�����Ϣ�����sort_para	�������
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_sort_explr(HCAT cat_handle, HEXPLR hexplr, cat_sort_para_t sort_para);


/*
**********************************************************************************************************************
*                                               cat_get_explr_para
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡ�����Ϣ��������
*
* parameters:		core:cat���;hexplr:�����Ϣ�����
*
* return:           if success return create para
*                   if fail return NULL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_get_explr_para(HCAT cat_handle, HEXPLR hexplr, cat_create_param_t *create_para);


/*
**********************************************************************************************************************
*                                               cat_open_extra_dec
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ����ϸ��Ϣ�Ľ��빦�ܡ��˹�����Ҫ��ͼƬ����ͼ���롢����ר�����롢��Ƶ��ͼ������ߵ����������Ϣ����ʱ����
*
* parameters:		core:cat���;
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_open_extra_dec(HCAT cat_handle, cat_media_type_t type);


/*
**********************************************************************************************************************
*                                               cat_close_extra_dec
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      �ر���ϸ��Ϣ�Ľ��빦�ܡ�
*
* parameters:		core:cat���;
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_close_extra_dec(HCAT cat_handle);


/*
**********************************************************************************************************************
*                                               cat_cache_create
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ������ͼcache���ܣ�ÿһ�������Ϣ��Ӧһ��cache
*
* parameters:		core:cat���;hexplr:�����Ϣ�����cache_para
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_cache_create(HCAT cat_handle, HEXPLR hexplr, cat_cache_para_t cache_para);


/*
**********************************************************************************************************************
*                                               cat_cache_destroy
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ����cache���ܡ�
*
* parameters:		core:cat���;hexplr:�����Ϣ�����
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_cache_destroy(HCAT cat_handle, HEXPLR hexplr);


/*
**********************************************************************************************************************
*                                               cat_get_explr_extra
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡ������Ϣ
*
* parameters:		core:cat���;hexplr:�����Ϣ�����para������ͼ������id��������ţ�cat_item:�����
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_get_explr_extra(HCAT cat_handle, HEXPLR hexplr, cat_miniature_para_t *para, __u32 id, __cat_item_t *cat_item);


/*
**********************************************************************************************************************
*                                               cat_del_file
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ɾ��һ���ļ�
*
* parameters:		core:cat���;hexplr:�����Ϣ�����index:������Ӧ��id
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_del_file(HCAT cat_handle, HEXPLR hexplr, __u32 index);


/*
**********************************************************************************************************************
*                                               cat_del_dir
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ɾ��һ��Ŀ¼
*
* parameters:		core:cat���;hexplr:�����Ϣ�����dir:Ŀ¼��
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_del_dir(HCAT cat_handle, HEXPLR hexplr, __u32 index);


/*
**********************************************************************************************************************
*                                               cat_cancel_del
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ȡ��ճ��
*
* parameters:		core:cat���;hexplr:�����Ϣ�����
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_cancel_del(HCAT cat_handle, HEXPLR hexplr);
 
/*
**********************************************************************************************************************
*                                               cat_copy_file
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ����һ���ļ�
*
* parameters:		core:cat���;hexplr:�����Ϣ�����file:�ļ���
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_copy_file(HCAT cat_handle, HEXPLR hexplr, __u32 index);


/*
**********************************************************************************************************************
*                                               cat_paste_file
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ճ��һ���ļ�
*
* parameters:		core:cat���;hexplr:�����Ϣ�����des_path:Ŀ��·��
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_paste_file(HCAT cat_handle, HEXPLR hexplr, char *src, char *dst);


/*
**********************************************************************************************************************
*                                               cat_copy_dir
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ����һ��Ŀ¼
*
* parameters:		core:cat���;hexplr:�����Ϣ�����dir:Ŀ¼��
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_copy_dir(HCAT cat_handle, HEXPLR hexplr, __u32 index);


/*
**********************************************************************************************************************
*                                               cat_paste_dir
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ճ��һ��Ŀ¼
*
* parameters:		core:cat���;hexplr:�����Ϣ�����des_path:Ŀ��·��
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_paste_dir(HCAT cat_handle, HEXPLR hexplr, char *src, char *dst);


/*
**********************************************************************************************************************
*                                               cat_get_paste_del_info
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡ����ɾ������ϸ��Ϣ
*
* parameters:		core:cat���;hexplr:�����Ϣ�����info:����ɾ����Ϣ
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_get_file_operation_info(HCAT cat_handle, cat_file_op_info_t *info);


/*
**********************************************************************************************************************
*                                               cat_cancel_paste
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ȡ��ճ��
*
* parameters:		core:cat���;hexplr:�����Ϣ�����
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_cancel_paste(HCAT cat_handle, HEXPLR hexplr);


/*
**********************************************************************************************************************
*                                               cat_set_file_for_play
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ���õ�ǰ��Ҫ���ŵ��ļ�
*
* parameters:		core:cat���;hexplr:�����Ϣ�����cur_id����Ҫ���ŵ�item��media_type�����ŵ�ý�����ͣ����ں�����ȡ��ǰ����ʱʹ�á�
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_set_file_for_play(HCAT cat_handle, HEXPLR hexplr, cat_media_type_t *media_type, __u32 cur_id);


/*
**********************************************************************************************************************
*                                               cat_get_cur_playfile
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      ��ȡ��ǰ�������ID��
*
* parameters:		core:cat���;hexplr:�����Ϣ�����media_type����cat_set_file_for_play���ص�ý�����ͣ�cur_id����ǰ���ID��
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_get_cur_playfile(HCAT cat_handle, HEXPLR hexplr, cat_media_type_t media_type, __u32 *cur_id);


/*
**********************************************************************************************************************
*                                               cat_search
*
* author:           terry.zeng
*
* date:             2010-09-08
*
* Description:      �����ؼ��ֶ�Ӧ�������Ϣ�������������������Ϣ��Ӧ���б�
*
* parameters:		core:cat�����hexplr:��Ӧ�������Ϣ;keyword:�ؼ���
*
* return:           if success return explorer info handle
*                   if fail return NULL
* modify history:
**********************************************************************************************************************
*/
HEXPLR cat_search(HCAT cat_handle, HEXPLR hexplr, char* keyword);


/*
**********************************************************************************************************************
*                                               cat_core_close
*
* author:           terry.zeng
*
* date:             2009-09-29
*
* Description:      �ر�cat core���ͷ������Դ
*
* parameters:
*
* return:           if success return EPDK_OK
*                   if fail return EPDK_FAIL
* modify history:
**********************************************************************************************************************
*/
__s32 cat_core_close(HCAT cat_handle);



#endif
