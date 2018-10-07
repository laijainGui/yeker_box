/*
*********************************************************************************************************
*                                                    eMOD
*                                   the Easy Portable/Player Operation System
*                                               mod_mmp sub-system
*
*                                (c) Copyright 2007-2009, SoftWinners,
*                                               All Rights Reserved
*
* File   : eLIBs_GetAudioFmt.h
* Version: V1.0
* By     : lszhang
* Modify : kevin.z.m, 2009-11-26 19:45
*********************************************************************************************************
*/
#ifndef _ELIBS_AUDIO_FMT_H_
#define _ELIBS_AUDIO_FMT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum __ID3_IMG_FORMAT
{
    ID3_IMG_FORMAT_BMP = 0,
    ID3_IMG_FORMAT_JPG,
    ID3_IMG_FORMAT_GIF,
    ID3_IMG_FORMAT_PNG,
    ID3_IMG_FORMAT_UNSUPPORT = -1
}__id3_img_format_t;

typedef enum __A_AUDIO_FONTTYPE
{
	  A_AUDIO_FONTTYPE_ISOIEC8859_1  = 0,       //ISO/IEC 8859-1
	  A_AUDIO_FONTTYPE_UTF_16LE,//
	  A_AUDIO_FONTTYPE_UTF_16BE,
	  A_AUDIO_FONTTYPE_UTF_8,//
	  A_AUDIO_FONTTYPE_ISOIEC8859_2,//
	  A_AUDIO_FONTTYPE_ISOIEC8859_3,//
	  A_AUDIO_FONTTYPE_ISOIEC8859_4,//
	  A_AUDIO_FONTTYPE_ISOIEC8859_5,//
	  A_AUDIO_FONTTYPE_ISOIEC8859_6,
	  A_AUDIO_FONTTYPE_ISOIEC8859_7,
	  A_AUDIO_FONTTYPE_ISOIEC8859_8,
	  A_AUDIO_FONTTYPE_ISOIEC8859_9,
	  A_AUDIO_FONTTYPE_ISOIEC8859_10,
	  A_AUDIO_FONTTYPE_ISOIEC8859_11,
	  A_AUDIO_FONTTYPE_ISOIEC8859_12,
	  A_AUDIO_FONTTYPE_ISOIEC8859_13,
	  A_AUDIO_FONTTYPE_ISOIEC8859_14,
	  A_AUDIO_FONTTYPE_ISOIEC8859_15,
	  A_AUDIO_FONTTYPE_ISOIEC8859_16,
	  A_AUDIO_FONTTYPE_WINDOWS_1250,
	  A_AUDIO_FONTTYPE_WINDOWS_1251,//
	  A_AUDIO_FONTTYPE_WINDOWS_1252,
	  A_AUDIO_FONTTYPE_WINDOWS_1253,
	  A_AUDIO_FONTTYPE_WINDOWS_1254,
	  A_AUDIO_FONTTYPE_WINDOWS_1255,
	  A_AUDIO_FONTTYPE_WINDOWS_1256,
	  A_AUDIO_FONTTYPE_WINDOWS_1257,
	  A_AUDIO_FONTTYPE_WINDOWS_1258,
	  A_AUDIO_FONTTYPE_KOI8_R,
	  A_AUDIO_FONTTYPE_KOI8_U,
	  A_AUDIO_FONTTYPE_GB2312,
	  A_AUDIO_FONTTYPE_GBK,
	  A_AUDIO_FONTTYPE_BIG5,
		
	  
	  A_AUDIO_FONTTYPE_ = -1
}__a_audio_fonttype_e;

typedef struct __ID3_IMAGE_INFO
{
    __s32   length;         //���ݳ���
    __s32   FileLocation;   //�ļ�ƫ��λ��
    __id3_img_format_t  img_format; //ͼƬ��ʽ
    __s32   pic_type;       //picture type;
    __s32   img_high;       //Ԥ����ͼƬ�߶�
    __s32   img_width;      //Ԥ����ͼƬ���
    __s32   otherdata;      //Ԥ��

}__id3_image_info_t;

typedef struct __AUDIO_FILE_INFO
{
    __u32   ulSampleRate;   // ������ sample rate
    __u32   ulBitRate;      // ������ bit rate��λ��BPS
    __u32   ulChannels;     // ������ channel
    __u32   ulDuration;     // ����ʱ�� duration ��λ��ms
    __u32   ulBitsSample;   // ������λ�� sample 8/16/24/32
    __u32   ulCharEncode;   // 0:GB2312.1:UNICODE

    __s32					ulAudio_name_sz;        // ��Ƶ��ʽ˵��
    __s8					*ulAudio_name;          // mp3 /RealAudio Cook.sipo. / aac-lc....
    __a_audio_fonttype_e	ulAudio_nameCharEncode; // 

    __s32					ulGenre_sz;             // ����
    __s8					*ulGenre;               // pop soft...
    __a_audio_fonttype_e	ulGenreCharEncode;

    __s32					ultitle_sz;             // ������
    __s8					*ultitle;
   __a_audio_fonttype_e		ultitleCharEncode;

    __s32					ulauthor_sz;            // �ݳ���
    __s8					*ulauthor;
    __a_audio_fonttype_e	ulauthorCharEncode;

    __sw_audio_format_e		ulFormat;
    __s32					ulAlbum_sz;             // ר��
    __s8					*ulAlbum;
    __a_audio_fonttype_e	ulAlbumCharEncode;

    __s32					ulYear_sz;              // ��Ʒ���
    __s8					*ulYear;
    __a_audio_fonttype_e	ulYearCharEncode;

    __s32    ulAPic_sz;     // attached picture
    __id3_image_info_t      *ulAPic;
    __a_audio_fonttype_e    ulAPicCharEncode;

    __s32					ulUslt_sz;             // ��ͬ���ĸ��/�ı� ����
    __s8*					ulUslt;                // __s32 ulFileLocation��
    __a_audio_fonttype_e	ulUsltCharEncode;

    __s32					ulSylt_sz;             // ͬ���ĸ��/�ı�
    __s8*					ulSylt;                // __s32 ulFileLocation��
    __a_audio_fonttype_e	ulSyltCharEncode;

    __s32                   ulbufflag;				//0:���ļ����з����������buf��������ݽ��з���
	__s32                   ulbuf_length;			//buf length;
	char*					ulbuf;					//����buf���������.
//__s32					data[9];
	__s32         data[3];       //for  û���õ���ֻ��Ϊ��64λ����
	__s64       offset;        //audio data ���ļ��е�ƫ������id3Ҳ����audio data����������������Ϊ�˽���һ���ļ���ĳ��������audio��
	__s64       length;        //audio data lenth����Чaudio���ݵĳ��ȡ����Ը�ֵ0����˼������������Ч����
	__s64       readlen;       //��ǰ��ȡ���ٸ���Ч��audio ���ݣ��൱���ļ���ƫ��λ�ü�ȥaudio data���ļ��е�ƫ������


    __s8					*ulBSINFO;              // temporary buffer of read data
    __s32					InforBufLeftLength;
    __s8					*InforBuf;              // ���ڴ洢 ulAudio_name  ultitle ulauthor����Ϣ��buffer
    __s32                    stream_num;                       //�������� Ŀǰֻ��midi������Ч
}__audio_file_info_t;


/*
************************************************************************************************************************
*                       GET AUDIO FORMAT
*
*Description: get audio format.
*
*Arguments  : file      full path of audio file.
*             format    file format information.
*
*Return     : result.
*               1:get audio format succssed.
*               0:get audio format failed.
************************************************************************************************************************
*/
extern __bool eLIBs_GetAudioFormat(const char *file, int *format);


/*
************************************************************************************************************************
*                       GET AUDIO FILE INFORMATION
*
*Description: get audio file information.
*
*Arguments  : file      full path of audio file.
*             inf       file information.
*
*Return     : result.
*               1:get audio information succssed.
*               0:get audio information failed.
************************************************************************************************************************
*/
extern __bool eLIBs_GetAudioInfo(const char *file, __audio_file_info_t *inf);


/*
************************************************************************************************************************
*                       GET AUDIO DATA INFORMATION
*
*Description: get audio data information.
*
*Arguments  : file      full path of audio file.
*             inf       file information.
*
*Return     : result.
*               1:get audio information succssed.
*               0:get audio information failed.
************************************************************************************************************************
*/
extern __bool eLIBs_GetAudioDataInfo(const char *pFormat, __audio_file_info_t *AIF, __s8* buf, __s32 datalen);

#ifdef __cplusplus
}
#endif


#endif //_ELIBS_AUDIO_FMT_H_

