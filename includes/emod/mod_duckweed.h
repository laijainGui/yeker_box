/*
********************************************************************************
*                                    eMOD
*                   the Easy Portable/Player Develop Kits
*                               mod_duckweed sub-system
*
*          (c) Copyright 2009-2010, Allwinner Microelectronic Co., Ltd.
*                              All Rights Reserved
*
* File   : mod_duckweed.h
* Version: V1.0
* By     : Eric_wang
* Date   : 2010-10-14
* Description:
    ��ģ��ֻ��Դ���װ��ʽ����Ƶ�ļ�. ����Ƶ�ļ����ñ�ģ����Ч.
********************************************************************************
*/
#ifndef _MOD_DUCKWEED_H_
#define _MOD_DUCKWEED_H_

#define DUCKWEED_FPATH_SIZE        (1024*4)    /* ý���ļ�·�����������ֵ                                 */
#define DUCKWEED_MAX_LANG_CHAR_SIZE  (32)       // �洢�������Ƶ��������󳤶�,\0Ҳ��������
typedef enum __DUCKWEED_STATUS             /* the status os cedar                  */
{
    DUCKWEED_STAT_IDLE = 0,                 /* idle                                 */
    DUCKWEED_STAT_PLAY = 1,                 /* play����ʾΪ�õ�����ͼ�����ڽ��������;IO�ӿ�DUCKWEED_CMD_GET_PREVIEW_FB �ǲ���ͬʱ���õ� */

    DUCKWEED_STAT_NOT_EXIST = -1,            //��ʾduckweed������
} __duckweed_status_t;

typedef enum __DUCKWEED_RETURN_VAL
{
    DUCKWEED_ERR_NONE           = EPDK_OK,        //no error
    DUCKWEED_ERR_FAIL           = EPDK_FAIL,        //���󣬵��ǲ���ʾ�����������

    DUCKWEED_ERR_VBSBUF_FULL    = 1,        //VBS BUF���ˡ�
    DUCKWEED_ERR_FILE_READ_END  = 2,        //�ļ������ˡ�

    DUCKWEED_ERR_FILE_READ_FAIL      = -2,  //���ļ�ʧ��
} __duckweed_return_val_t;

/*******************************************************************************
Function name: __DUCKWEED_CMD_SET
Description: 
    DUCKWEED_CMD_GET_PREVIEW_FB��˵��:
    FB��Ҫ���Ǳ�����RGB��ʽ��Ҫ��APP��ı�����:
    pfb->size.width = PREVIEW_WIDTH;
    pfb->size.height = PREVIEW_HEIGHT;
    pfb->fmt.type = FB_TYPE_RGB;
    pfb->addr[0] = address;

    IO�ӿ���ɺ� duckweed��д�ı�����:
    pout->fmt.fmt.rgb.pixelfmt = PIXEL_COLOR_ARGB8888;
    pout->fmt.fmt.rgb.pixseq = RGB_SEQ_ARGB;
Parameters: 
    
Return: 
    
Time: 2010/11/22
*******************************************************************************/
typedef enum __DUCKWEED_CMD_SET             /* ý�岥���м�������б�(IOCtrol)                              */
{
    DUCKWEED_CMD_OPEN_MEDIAFILE = 0x0100,   /* ���ô����ŵ�ý���ļ�·����������Ϣ,���ļ�pbuffer = (__duckweed_media_file_inf *) */
    DUCKWEED_CMD_CLOSE_MEDIAFILE,           /* �رյ�ǰ��ý���ļ������ܻ�Ҫ�رս���� */

    DUCKWEED_CMD_GET_FILE_FORMAT  = 0x0200, /* �õ��ļ���Ϣ�������ļ���ʽ */
    DUCKWEED_CMD_GET_FILE_SIZE,             /* �õ��ļ�����ʵ��С, pbuffer = __s64*, ret = EPDK_OK,����odf�����ļ���ʵ�ʵ��ļ���С*/
    DUCKWEED_CMD_GET_TOTAL_TIME,            /* ��ȡ������ʱ��   return = total time(ms)                     */
    DUCKWEED_CMD_GET_VIDSTREAM_CNT,         /* �õ���Ƶ���������� ret = ����(-1����ʧ��) */
    DUCKWEED_CMD_GET_VIDSTREAM_PROFILE,     /* ��ȡ������Ƶ����˵����Ϣ: pbuffer = __duckweed_vidstream_profile_t, ����AudStrmListArrayҲ��app����. return = EPDK_OK or EPDK_FAIL */
    DUCKWEED_CMD_GET_AUDSTREAM_CNT,         /* �õ���Ƶ���������� ret = ����(-1����ʧ��)*/
    DUCKWEED_CMD_GET_AUDSTREAM_PROFILE,     /* ��ȡ������Ƶ����˵����Ϣ: pbuffer = __duckweed_audstream_profile_t, ����AudStrmListArrayҲ��app����. return = EPDK_OK or EPDK_FAIL */

    DUCKWEED_CMD_GET_PREVIEW_FB = 0x0300,       /* �õ�Ԥ��ͼ, pbuffer = FB*��FB�Ĳ�����Ҫ��,����ֻ֧���õ�һ֡��һ���ļ���һ֡������ٵ��ýӿڣ�ֱ�ӷ���ʧ�ܣ����������������Ͻ��� */
    DUCKWEED_CMD_GET_PREVIEW_FB_BY_PTS,         /* �õ�Ԥ��ͼ, pbuffer = FB*��FB�Ĳ�����Ҫ��,aux = pts(ms),��ʾ��Ҫ�ڸ�PTS�����Ĺؼ�֡���ýӿ�Ŀǰ��������������չ��     */

    DUCKWEED_CMD_SET_USER_FILEOP  = 0x05000,    // /* �����û���context,��ص�����,�ļ����ȵ�, (pbuffer = DuckweedUsrFileOp*, )������ֱ��ʹ��cedar�����ݽṹ__cedar_usr_file_op_t* */
    DUCKWEED_CMD_,
} __duckweed_cmd_set_t;

//the information of the media file which will be input to play
typedef struct
{
    char    file_path[DUCKWEED_FPATH_SIZE];    /* ý���ļ��ľ���·����,��app��д                 */
    __s32   file_format; //__sw_file_format_t, ��duckweed��д
    __s64   file_size;  //ָ��������Ƶ�ļ��Ĵ�С����duckweed��д,(���������ODF���ܸ�ʽ�ļ���file_sizeָ�������ڲ�����������Ƶ�ļ��Ĵ�С������odf�ļ��Ĵ�С)
    __s32   ext[8];     //��չ��
} __duckweed_media_file_inf;

//#if 1
//typedef enum
//{
//    DUCKWEED_AUD_CTRL_CODEC_TYPE         = (1<<0),
//    DUCKWEED_AUD_CTRL_CHANNELS           = (1<<1),
//    DUCKWEED_AUD_CTRL_BITS_PER_SAMPLE    = (1<<2),
//    DUCKWEED_AUD_CTRL_SAMPLE_PER_SECOND  = (1<<3),
//    DUCKWEED_AUD_CTRL_AVG_BIT_RATE       = (1<<4),
//    DUCKWEED_AUD_CTRL_MAX_BIT_RATE       = (1<<5),
//    DUCKWEED_AUD_CTRL_CBR                = (1<<6),
//    DUCKWEED_AUD_CTRL_LANG               = (1<<7),
//} __duckweed_aud_ctrlbit_t;

//audio format information
typedef struct  __DUCKWEED_AUDIO_BS_INFO
{
    //__u32       ctrl_bits;      //__duckweed_aud_ctrlbit_t
    __s32       codec_type;     //����__sw_audio_format_e, ����__cedar_audio_fmt_t
    __s32       channels;
    __s32       bits_per_sample;
    __s32       sample_per_second;
    __s32       avg_bit_rate;
    __s32       max_bit_rate;
    __s32       cbr_flg;    //cbr����vbr
    __s32       lang_encode_type;    //����__epdk_charset_enm_e, ����__cedar_subtitle_encode_t���������Ƶ��ַ��ı����ʽ
    __u8        lang[DUCKWEED_MAX_LANG_CHAR_SIZE];  //��������:�������ģ�Ӣ�ĵ�
    __s32       ext[8];
} __duckweed_audio_bs_info_t;

typedef struct{
    __u8                        nAudStrmNum;    //audio number, <= nAudStrmMaxCnt
    __s32                       nAudStrmMaxCnt; //����AudStrmListArray��Ԫ�ظ���
    __duckweed_audio_bs_info_t  *AudStrmArray;
} __duckweed_audstream_profile_t;

//typedef enum
//{
//    DUCKWEED_VID_CTRL_CODEC_TYPE    = (1<<0),
//    DUCKWEED_VID_CTRL_PIC_SIZE      = (1<<1),
//    DUCKWEED_VID_CTRL_FRAME_RATE    = (1<<2),
//    DUCKWEED_VID_CTRL_AVG_BIT_RATE  = (1<<3),
//    DUCKWEED_VID_CTRL_MAX_BIT_RATE  = (1<<4),
//    DUCKWEED_VID_CTRL_CBR           = (1<<5),
//} __duckweed_vid_ctrlbit_t;

//video format inforamtion
typedef struct __DUCKWEED_VIDEO_BS_INFO
{
    //__u32       ctrl_bits;  //__duckweed_vid_ctrlbit_t
    __u16       codec_type; //__sw_codec_type_t
    __u16       width;
    __u16       height;
    __u16       frame_rate; //��ֵ����1000
    __s32       avg_bit_rate;
    __s32       max_bit_rate;
    __u8        cbr_flg;    //�ɱ�֡�ʻ��ǹ̶�֡��
    __s32       ext[8];
} __duckweed_video_bs_info_t;

typedef struct{
    __s32                        nVidStrmNum;    //video number, <= nVidStrmMaxCnt
    __s32                       nVidStrmMaxCnt; //����VidStrmListArray��Ԫ�ظ���
    __duckweed_video_bs_info_t  *VidStrmArray;
} __duckweed_vidstream_profile_t;
//#endif


typedef struct tag_DuckweedUsrFileOp
{
    __pCBK_t usr_fread;                               /*�ص�����(���ļ�)*/
    __u32 fp;                                         /*�ļ����*/
    __sw_file_format_t media_fmt;               /*��ý���ļ��ļ���ʽ*/
    __s32 file_size;                                  /*�ļ�����*/
    __u32 flag;
    __pCBK_t usr_fseek;
    __u32 reserved[4];                                /*����,������Ϊ0,*/
} DuckweedUsrFileOp;

#endif  /* _MOD_DUCKWEED_H_ */

