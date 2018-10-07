/******************************************************************************
* file:GetAudio_format.h 2008-12-24 10:47:12
*
*author lszhang
*
*
*
*******************************************************************************/
#ifndef _GETAUFIO_FORMAT_H_
#define _GETAUFIO_FORMAT_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	IMG_FORMAT_BMP =0,
	IMG_FORMAT_JPG,
	IMG_FORMAT_GIF,
	IMG_FORMAT_PNG,
	IMG_FORMAT_UNSUPPORT = -1
}__w_img_format_t;

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
    __s32				length;         //���ݳ���
    __s32				FileLocation;   //�ļ�ƫ��λ��
    __w_img_format_t	img_format;     //ͼƬ��ʽ
    __s32				pic_type;       //picture type;
    __s32				img_high;       //Ԥ����ͼƬ�߶�
    __s32				img_width;      //Ԥ����ͼƬ���
    __s32				otherdata;      //Ԥ��

}__id3_image_info_t;


typedef struct __AUDIO_FILE_INFO
{
    __u32					ulSampleRate;   // ������ sample rate
    __u32					ulBitRate;      // ������ bit rate��λ��BPS
    __u32					ulChannels;     // ������ channel
    __u32					ulDuration;     // ����ʱ�� duration ��λ��ms
    __u32					ulBitsSample;   // ������λ�� sample 8/16/24/32
    __u32					ulCharEncode;   // 0:GB2312.1:UNICODE

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

    __s32					ulAPic_sz;             // attached picture
    __id3_image_info_t		*ulAPic;
    __a_audio_fonttype_e	ulAPicCharEncode;

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

/***************************************************
!!!!!!!!!!!!1����android��˵�Ѿ�����Ϊcdx_read�ȣ����Բ���ͨ���ļ������÷�ʽ������ͨ���ļ�ָ��ķ�ʽ��
***************************************************/
/*
function :GetAudioFormat
˵���������ļ���׺�ж��ļ���ʽ��
����˵����pFilename ���ļ���������ʵ���ļ�����.���治�ܳ���4λ������Χʧ�ܡ�ʶ���Сд��
			A_Audio_Format�������ļ���ʽ
����ֵ��1 :succed 0 :fail
*/
int GetAudioFormat(const char *pFilename,int *A_Audio_Format);//return 1 :succed 0 :fail
/*
function :GetAudioInfo
˵����ͨ���ļ�������ļ���Ϣ��
	���Ȼ����GetAudioFormat�������ļ���׺�����õ��ļ���ʽ��
	Ȼ������ļ��������ļ���ͨ���ļ�ָ��õ��ļ���Ϣ��
	������εõ���Ϣʧ�ܣ�������ļ�����ѭ���ж��ļ���ʽ��
	�ر��ļ�ָ�룬���˳�
����˵����pFilename ���ļ���������ʵ���ļ�����.���治�ܳ���4λ������Χʧ�ܡ�ʶ���Сд��
			AIF�������ļ���Ϣ
����ֵ��1 :succed 0 :fail
*/
int GetAudioInfo(const char *pFilename,__audio_file_info_t *AIF);  //return 1 :succed 0 :fail
/*
function :GetAudioFormatData
˵���������ļ�ǰ�����ֽڿ����ж��ļ����͡�
����˵����ptr ���ļ������׵�ַ��
			buflen�����ݳ��ȡ�
			A_Audio_Format�������ļ��ļ���ʽ
����ֵ��1 :succed 0 :fail
*/
//simple format from first 16bytes
int GetAudioFormatData(unsigned char *ptr,int buflen,int *A_Audio_Format);//return 1 :succed 0 :fail
/*
function :GetAudioDataInfo
˵����ͨ���ļ����ݻ���ļ���Ϣ��
	��������һ�������ļ�������Ϊ0��
	���Ȼ����GetAudioFormat�������ļ���׺�����õ��ļ���ʽ���ļ���׺������ȷ�����û���ļ�����֪�����ָ�ʽ���ɸ�ֵ.***,����.aac,.mp3�ȡ�
	�����֪����ʽ����ֵ�ļ���Ϊ0�������GetAudioFormatData���������ж��ļ���ʽ��
	Ȼ������ļ����ͣ�ͨ��������buffer�ͳ��ȣ�����ļ���Ϣ��
	������εõ���Ϣʧ�ܣ�ֱ�ӷ��أ���������ļ�����ѭ���ж��ļ���ʽ��
����˵����pFilename ���ļ���������ʵ���ļ����ͺ�׺��.���治�ܳ���4λ������Χʧ�ܡ�ʶ���Сд��
			AIF�������ļ���Ϣ
			buf�������׵�ַ
			datalen�����ݳ��ȡ�
����ֵ��1 :succed 0 :fail
*/
//*pFilename must get right audio_format suffix
int GetAudioDataInfo(const char *pFilename,__audio_file_info_t *AIF,__s8* buf,__s32 datalen);  //return 1 :succed 0 :fail
/*
function :GetAudioFileInfo
˵����ͨ���ļ�ָ�����ļ���Ϣ��
	���Ȼ�����id3��Ϣ��Ȼ�����GetAudioFormatData�������ļ�����ǰ�����ֽڵõ��ļ���ʽ��
	Ȼ��ͨ���ļ�ָ��õ��ļ���Ϣ��
	������εõ���Ϣʧ�ܣ�������ļ�����ѭ���ж��ļ���ʽ��
	�����������ļ�ָ��λ�ÿ��ܲ����ļ���ʼ����Ҫ�����걾��������ļ�ָ���Ƶ��ļ���ʼ����
����˵����Bitstream ���ļ�ָ�롣
			AIF�������ļ���Ϣ
����ֵ��1 :succed 0 :fail
*/
int GetAudioFileInfo(FILE *Bitstream,__audio_file_info_t *AIF);  //return 1 :succed 0 :fail 

/*
function :GetAudioFileInfoOffset
˵����ͨ���ļ�ָ�����ļ���Ϣ������֧��ƫ�����ͳ��Ƚ����жϣ�Ϊ��Ƶ����ֻ���ļ��м�ĳ���ط�ʹ�á�
offset:��Ч�������ļ��е�ƫ������length����Ч���ݳ��ȣ�����id3����Ч���ݣ�Ĭ��Ϊ0�����ļ�ʵ�ʳ��ȼ�Ϊlength
���offset =0,&& length =0;����GetAudioFileInfo��������˴˺�������������������
	���Ȼ�����id3��Ϣ��Ȼ�����GetAudioFormatData�������ļ�����ǰ�����ֽڵõ��ļ���ʽ��
	Ȼ��ͨ���ļ�ָ��õ��ļ���Ϣ��
	������εõ���Ϣʧ�ܣ�������ļ�����ѭ���ж��ļ���ʽ��
	�����������ļ�ָ��λ�ÿ��ܲ����ļ���ʼ����Ҫ�����걾��������ļ�ָ���Ƶ��ļ���ʼ����
����˵����Bitstream ���ļ�ָ�롣
			AIF�������ļ���Ϣ
����ֵ��1 :succed 0 :fail
*/
int GetAudioFileInfoOffset(FILE *Bitstream,int64_t offset,int64_t length,__audio_file_info_t *AIF);  //return 1 :succed 0 :fail 
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

#ifdef __cplusplus
}
#endif

#endif //_GETAUFIO_FORMAT_H_

