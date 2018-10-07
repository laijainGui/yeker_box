/*
*********************************************************************************************************
*											        ePOS
*						           the Easy Portable/Player Operation System
*									           epos headfile
*
*						        (c) Copyright 2006-2007, Steven.ZGJ China
*											All	Rights Reserved
*
* File    : epos_para.h
* By      : Steven.ZGJ
* Version : V0.1
*
* note�����е�ģ���ڲ������ȫ���Եĳ���������Ҫ���"ģ����_xxx", ����"MEMS_xxx", "EXEC_xxx"
************************************************************************************************************************
*/

#ifndef EPOS_PARA_H
#define EPOS_PARA_H

#include "typedef.h"
#include "cfgs.h"

#define   BOOT_MEDIA_NAND       0
#define   BOOT_MEDIA_CARD       1
#define   BOOT_MEDIA_NOR        2
/*
*****************
*   ����/����eposȫ�ֱ���
*****************
*/
typedef struct __TARGET_PARA
{
    __u32 debugenable;
}__target_para_t;

typedef struct
{
    __s32 boot_card_num;
}__ksrv_add_para;
typedef struct __RDSK_PARA
{
    __u32           base;           //ramdisk position address
    __u32           full_size;      //full ramdisk size
    __u32           use_size;       //usefull ramdisk size
    __u32           reserved0;      //reserved for align
}__rdsk_para_t;

typedef struct __LOGO_PIC_PARA
{
    __u32           base;           //logo picture position address
    __u32           size;           //size of the logo picture
    __u32           reserved0;      //reserved for align
    __u32           reserved1;
} __logo_pic_para_t;

typedef struct __P1_PARA
{
    __u32 Battery_cap;
    __u32 Discharge_current_rate;   //�ŵ�ʱ�����ⲿ������MOSFET
}__p1_para_t;

typedef struct __EPOS_PARA
{
    __target_para_t target;         // 0 debug, 1 release
    __dram_para_t   dram_para;      // dram init para    
    __rdsk_para_t   boot_para;      // ram disk init para????
    __rdsk_para_t   ramdisk_para;   // ram disk init para
    __u32           media;          // �����Ĵ洢����

}__epos_para_t;


typedef struct __EPOS_HEAD
{
	__u32			headjump;
	unsigned char	magic[8];       //'EPOS-IMG'
	__u32			version;
	__u8            reserved0[16];

	__epos_para_t   start_para;

    //ͷ�Ͱ���KRNL_INIT���볤�ȼ�����Ϊ16K
	unsigned char	reserved[(0x4000 - sizeof(__epos_para_t)) - 0x20 - 0x6C];

    //{sizeof(headjump + magic + version + rev.) = 0x20}

    //����KRNL_INIT����εĴ��룬Ϊ0x6C���ֽ�,
    //����޸���head.s�еİ��ƴ�������´���δ�С.
    //by sunny at 2011-04-13-13-47.
} __epos_head_t;
							                        

#endif						//EPOS_PARA_H

