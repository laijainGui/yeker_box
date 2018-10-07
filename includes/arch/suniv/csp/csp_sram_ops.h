/*
*********************************************************************************************************
*											        eBase
*						                the Abstract of Hardware
*									           the OAL of CSP
*
*						        (c) Copyright 2006-2010, AW China
*											All	Rights Reserved
*
* File    	: 	csp_sram_ops.h
* Date    	:	2011-01-24
* By      	: 	holigun
* Version 	: 	V1.00
* Description :            just for aw1619
* History     :
*               <author>            <date>              <note>           
*               victor              2011-01-24          aw1619
*********************************************************************************************************
*/
#ifndef	_CSP_SRAM_OPS_H_
#define	_CSP_SRAM_OPS_H_


/*
****************************************************************************************************
*
*             SRAM_init
*
*  Description:
*       SRAM init,��boot��������Ϊnormalģ��ʹ�á�
*
*  Parameters:
*
*  Return value:
*		EBSP_TRUE/EBSP_FALSE
****************************************************************************************************
*/
s32 CSP_SRAM_init( void );

/*
****************************************************************************************************
*
*             SRAM_exit
*
*  Description:
*       SRAM exit����boot��������Ϊbootģ��ʹ�á�
*
*  Parameters:
*
*  Return value:
*		EBSP_TRUE/EBSP_FALSE
****************************************************************************************************
*/
s32 CSP_SRAM_exit(void);


/*
****************************************************************************************************
*
*             SRAM_get_virt_base
*
*  Description:
*       get virt base address��for extension
*
*  Parameters:
*
*  Return value:
*		EBSP_TRUE/EBSP_FALSE
****************************************************************************************************
*/
u32 CSP_SRAM_get_virt_base(void);



/*
****************************************************************************************************
*
*             CSP_SRAM_zone_number_get
*
*  Description:
*       get sram zone  number
*
*  Parameters:
*
*  Return value:
*		zone number
****************************************************************************************************
*/
s32 CSP_SRAM_zone_number_get( void );

/*
****************************************************************************************************
*
*             CSP_SRAM_zone_info_get
*
*  Description:
*       get sram zone info
*
*  Parameters:
*		zone_index		: 	base on 1
*		p_zone_info		:	Total zone number
*  Return value:
*		EBSP_TRUE/EBSP_FALSE
****************************************************************************************************
*/
s32 CSP_SRAM_zone_info_get(u32 zone_index ,struct sram_zone_info * p_zone_info);


/*
****************************************************************************************************
*
*             SRAM_switch_mapping
*
*  Description:
*       switch sram zone 
*          1. B1����CPU_DMA��USB�仯��
*
*          sram��ʼ���ӿ��Ѿ���boot��������Ϊnormalģ��ʹ�á�
*          
*          2. ������normal��:
*            2.1 C1����CPU_DMA��VE�仯;
*            2.2 C2ֻ������DE_FE;
*            3.3 C3ֻ������DE_BE.
*
*  Parameters:
*		zone_name			: 	such as CSP_SRAM_ZONE_NULL
*		mapping_to_module	:	such as	CSP_SRAM_MODULE_NULL
*  Return value:
*		EBSP_TRUE/EBSP_FALSE
****************************************************************************************************
*/
s32 CSP_SRAM_switch_mapping(csp_sram_zone_id_t zone_id , csp_sram_module_t mapping_to_module);

/*
****************************************************************************************************
*
*             get_chip_version
*
*  Description:
*       get chip version
*
*  Parameters:
*
*  Return value:
*		chip version
****************************************************************************************************
*/
u32 Misc_get_chip_version(void);



#endif	//_CSP_SRAM_OPS_H_

