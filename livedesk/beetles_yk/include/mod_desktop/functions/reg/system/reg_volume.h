/*
************************************************************************************************************************
*                                              volume in register table
*
*                                  Copyright(C), 2006-2010, AllWinner Technology Co., Ltd.
*											       All Rights Reserved
*
* File Name   : reg_volume.h
*
* Author      : Gary.Wang
*
* Version     : 1.0
*
* Date        : 2010.08.31
*
* Description :
* 
* Others      : None at present.
*
*
* History     :
*
*  <Author>        <time>       <version>      <description>
*
* Gary.Wang      2010.08.31        1.0         build the file
*
************************************************************************************************************************
*/
#ifndef  __REG_VOLUME_H__
#define  __REG_VOLUME_H__

#ifdef __cplusplus
extern "C" {
#endif



/*
****************************************************************************************************
*Name        : lion_reg_volume_get
*Prototype   : __u32 lion_reg_volume_get( void )
*Arguments   : void
*Return      : the current volume in register table.
*Description : get the current volume in register table.
*Other       :
****************************************************************************************************
*/
extern __u32  lion_reg_volume_get( void );

/*
****************************************************************************************************
*Name        : lion_reg_volume_set
*Prototype   : __s32 lion_reg_volume_set( __u32 volume )
*Arguments   : volume         input. volume
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : set the current volume in register table.
*Other       :
****************************************************************************************************
*/
extern __s32 lion_reg_volume_set( __u32 volume );

/*
****************************************************************************************************
*Name        : lion_reg_volume_get_default
*Prototype   : __u32 lion_reg_volume_get_default( void )
*Arguments   : void
*Return      : the default volume in register table.
*Description : get the default volume in register table.
*Other       :
****************************************************************************************************
*/
extern __u32  lion_reg_volume_get_default( void );

/*
****************************************************************************************************
*Name        : lion_reg_volume_restore
*Prototype   : __s32 lion_reg_volume_restore( void )
*Arguments   : void
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : restore the default value of volume in register table.
*Other       :
****************************************************************************************************
*/
extern __s32 lion_reg_volume_restore( void );



#ifdef __cplusplus
}
#endif

#endif     //  ifndef __REG_VOLUME_H__

/* end of reg_volume.h */
