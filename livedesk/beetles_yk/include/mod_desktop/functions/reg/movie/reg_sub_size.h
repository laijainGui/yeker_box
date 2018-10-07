/*
************************************************************************************************************************
*                                           subtitle size in register table
*
*                                  Copyright(C), 2006-2010, AllWinner Technology Co., Ltd.
*											       All Rights Reserved
*
* File Name   : reg_sub_size.h
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
#ifndef  __REG_SUB_SIZE_H__
#define  __REG_SUB_SIZE_H__

#ifdef __cplusplus
extern "C" {
#endif



/*
****************************************************************************************************
*Name        : lion_reg_sub_size_get
*Prototype   : __u32 lion_reg_sub_size_get( void )
*Arguments   : void
*Return      : the current subtitle size in register table.
*Description : get the current subtitle size in register table.
*Other       :
****************************************************************************************************
*/
extern __u32  lion_reg_sub_size_get( void );

/*
****************************************************************************************************
*Name        : lion_reg_sub_size_set
*Prototype   : __s32 lion_reg_sub_size_set( __u32 value )
*Arguments   : value         input. subtitle size value.
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : set the current subtitle size in register table.
*Other       :
****************************************************************************************************
*/
extern __s32 lion_reg_sub_size_set( __u32 value );

/*
****************************************************************************************************
*Name        : lion_reg_sub_size_get_default
*Prototype   : __u32 lion_reg_sub_size_get_default( void )
*Arguments   : void
*Return      : the default subtitle size in register table.
*Description : get the default subtitle size in register table.
*Other       :
****************************************************************************************************
*/
extern __u32  lion_reg_sub_size_get_default( void );

/*
****************************************************************************************************
*Name        : lion_reg_sub_size_restore
*Prototype   : __s32 lion_reg_sub_size_restore( void )
*Arguments   : void
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : restore the default value of subtitle size in register table.
*Other       :
****************************************************************************************************
*/
extern __s32 lion_reg_sub_size_restore( void );



#ifdef __cplusplus
}
#endif

#endif     //  ifndef __REG_SUB_SIZE_H__

/* end of reg_sub_size.h */
