/*
************************************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Developent Kits
*									           ePDK interface
*
*                                   (c) Copyright 2007-2008, steven.zgj.china
*                                            All Rights Reserved
*
* File    : epdk.h
* By      : Steven.ZGJ
* Version : V0.1
*
*	����Ҫʹ��ePDK��������ֻ��Ҫ����ͷ�ļ���ӵ��Լ��Ĵ����У�ͬʱҪ��eslibc.o + epdk.o�ļ�Ҳ��ӵ������ļ��С�
*�������϶�������Ϳ��Ե���ePDK����������ϵͳ���ú�����
*
************************************************************************************************************************
*/

#ifndef EPDK_H
#define EPDK_H


#include    "cfgs.h"        /* ϵͳ����     */
#include    "typedef.h"     /* ���Ͷ���     */

#if(EPDK_OS == EPDK_OS_EPOS)
#include    "configs.h"
#include    "dbgs.h"    
#include    "ebios.h"       /* bios����     */
#include	"epos.h"        /* ϵͳ����     */
#include    "emod.h"        /* module����   */
#include    "elibs.h"       /* ��׼��      */
#include    "cplus.h"       /* c++��        */

#elif((EPDK_OS == EPDK_OS_WIN2K) || (EPDK_OS == EPDK_OS_WINXP))

#else
    #error please select os platform!
#endif

#define EPDK_AUDIO_READY 1
#define EPDK_SPI_READY 1
#define EPDK_AUTO_PLAY_MOVIE_ENABLE 	0
#define EPDK_PLAY_VIDEO_AUDIO_ENABLE 	0
#define EPDK_LOAD_FROM_SD 0
#define	EPDK_ROOTFS_PATH						"f:\\rootfs\\"
#define	EPDK_TRANS_KEY_LONGLEFT2LONGVADD		1				
#define EPDK_USE_ONLY_ONE_SD 1//��ý�忨���������Ƿ�ͬһ��
#define	EPDK_USE_EBOOK_TEST_TVIN				1
#define EPDK_PLAY_AUDIO_ENABLE			1
/**********************************************************************************************************************/
#endif		//#define EPDK_H

