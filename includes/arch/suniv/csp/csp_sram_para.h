/*
*********************************************************************************************************
*											        eBase
*						                the Abstract of Hardware
*									           the OAL of CSP
*
*						        (c) Copyright 2006-2010, AW China
*											All	Rights Reserved
*
* File    	: 	csp_sram_para.h
* Date    	:	2011-01-24
* By      	: 	holigun
* Version 	: 	V1.00
* Description :            just for aw1619
* History     :
*               <author>            <date>              <note>           
*               victor              2011-01-24          aw1619
*********************************************************************************************************
*/
#ifndef	_CSP_SRAM_PARA_H_
#define	_CSP_SRAM_PARA_H_


//------ZONE--------------------------------------
typedef	enum{
	CSP_SRAM_ZONE_NULL		=	0x00,
	
    CSP_SRAM_ZONE_BOOT              ,   /* ��ʹ�õ�ģ��Ϊ: BOOT��NORMAL. ע��:OS��ؽ������������ΪNORMAL  */
    
	CSP_SRAM_ZONE_B1		        ,   /* ��ʹ�õ�ģ��Ϊ: CPU_DMA��USB */
	CSP_SRAM_ZONE_C1		        ,   /* ��ʹ�õ�ģ��Ϊ: CPU_DMA��VE  */
	CSP_SRAM_ZONE_C2		        ,   /* ��ʹ�õ�ģ��Ϊ: DE_FE */
	CSP_SRAM_ZONE_C3		        ,   /* ��ʹ�õ�ģ��Ϊ: DE_BE */

	CSP_SRAM_ZONE_ICACHE	        ,   /* not used */
	CSP_SRAM_ZONE_DCACHE			,   /* not used */ 
	
	CSP_SRAM_ZONE_MAX_NR
}csp_sram_zone_id_t;

//------Module--------------------------------------
typedef enum{
	CSP_SRAM_MODULE_NULL	=	0x00,
	
	CSP_SRAM_MODULE_BOOT			, /* bootģ��  : zone c1,c2,c3��������   */
	CSP_SRAM_MODULE_NORMAL          , /* normalģ��: zone c1(CPU_DMA/VE),zone c2(DE_FE),zone c3(DE_BE) */
	
	CSP_SRAM_MODULE_CPU_DMA	        ,
	CSP_SRAM_MODULE_USB	            ,
	CSP_SRAM_MODULE_VE		        ,
	CSP_SRAM_MODULE_DE_FE	        ,
	CSP_SRAM_MODULE_DE_BE	        ,		
	
	CSP_SRAM_MODULE_MAX_NR
}csp_sram_module_t;


typedef struct  sram_zone_info{
	csp_sram_zone_id_t zone_id;
	u32 reserved;	//u32 zone_size;	
}sram_zone_info_t;


#endif	//_CSP_SRAM_OPS_H_

