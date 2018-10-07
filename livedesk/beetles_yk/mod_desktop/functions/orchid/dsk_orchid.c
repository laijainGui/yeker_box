/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: dsk_orchid.c
* By      	: Andy.zhang
* Func		: orchid op
* Version	: v1.0
* ============================================================================================================
* 2010-1-8 9:46:40  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#include "..\\functions_i.h"

#define ORCHID_DISK						"z:\\"
#define ORCHID_FILE_PATH                "b:\\module\\orchid"

__s32 dsk_orchid_createDisk(void)
{
	__s32  ret = 0;

	ret = eLIBs_IsPartFormated(ORCHID_DISK);

	if(ret == ELIBS_PART_FMT_NFORMATED)
	{
		ret = eLIBs_format(ORCHID_DISK, "fat", 0);
	}
	else if(ret == ELIBS_PART_FMT_FORMATED)
	{
		ret = EPDK_OK;
	}
	else
	{
		ret = EPDK_FAIL;
	}
	return ret;
}

static __s32 dsk_orchid_rebuild(void)
{
	ES_FILE  *horc    = 0;

    /* create a handle of orchid */
    horc = eLIBs_fopen( ORCHID_FILE_PATH, "r+");
    if( horc == 0)
    {
    	__wrn("Error in opening a handle of orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	goto error;
    }

    /* �ؽ�orchid ���ݿ� */
    if( eLIBs_fioctrl( horc, ORC_CMD_REBUILD_ORCHID, 0, 0 ) )
    {
    	__wrn("Error in updating orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	goto error;
    }
    eLIBs_fclose( horc );
	horc = 0;
	return EPDK_OK;

error:
	if( horc != 0 )
	{
		eLIBs_fclose( horc );
		horc = 0;
	}

	return EPDK_FAIL;
}

__s32 dsk_orchid_check(void)
{
	ES_FILE  *horc    = 0;
	__bool valid;

    /* create a handle of orchid */
    horc = eLIBs_fopen( ORCHID_FILE_PATH, "r+");
    if( horc == 0)
    {
    	__wrn("Error in opening a handle of orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	goto error;
    }
	
	/* orchid �Ƿ���Ч */
	valid = eLIBs_fioctrl( horc, ORC_CMD_ORCHID_IS_VALID, 0, 0 );
	eLIBs_fclose( horc );
	horc = 0;

    /* check orchid */
    if( !valid )
    {
    	dsk_orchid_rebuild();
    }

	return EPDK_OK;

error:
	if( horc != 0 )
	{
		eLIBs_fclose( horc );
		horc = 0;
	}

	return EPDK_FAIL;
}


//__s32 dsk_orchid_notify_update(void)
//{
//	__gui_msg_t msg;
//	
//	msg.id 			= DSK_MSG_ORCHID_UPDATA_START;
//	msg.h_srcwin 	= NULL;
//	msg.h_deswin	= GUI_WinGetHandFromName(APP_DESKTOP_MWIN);
//	msg.dwAddData1	= 0;
//	msg.dwAddData2  = 0;
//	msg.p_arg		= 0;
//	
//	return GUI_SendNotifyMessage(&msg);
//}

__s32 dsk_orchid_update(void)
{
	ES_FILE  *horc    = 0;

    /* create a handle of orchid */
    horc = eLIBs_fopen( ORCHID_FILE_PATH, "r+");
    if( horc == 0)
    {
    	__wrn("Error in opening a handle of orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	goto error;
    }

	/* check valid */
	eLIBs_fioctrl( horc, ORC_CMD_ORCHID_IS_VALID, 0, 0 );

    /* ˢ�����ݿ� */
    if( eLIBs_fioctrl( horc, ORC_CMD_UPDATE_ORCHID, 0, 0 ) )
    {
    	__wrn("Error in updating orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	goto error;
    }
    eLIBs_fclose( horc );
	horc = 0;
	return EPDK_OK;

error:
	if( horc != 0 )
	{
		eLIBs_fclose( horc );
		horc = 0;
	}

	return EPDK_FAIL;
}

__s32 dsk_orchid_save_npl(void)
{
	__s32	 ret;
	ES_FILE  *horc = 0;
	HNPL	  hNpl;
	orc_arg_npl_t  arg;

	
	horc = eLIBs_fopen( ORCHID_FILE_PATH, "r+");
	if( horc == 0)
    {
    	__wrn("Error in opening a handle of orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	return EPDK_FAIL;
    }
    
    eLIBs_fioctrl( horc, ORC_CMD_ORCHID_IS_VALID, 0, 0 );
    	
	arg.media_type = ORC_MEDIA_TYPE_AUDIO;
	arg.work_mode  = ORC_NPL_WORK_MODE_MANAGE;	
	hNpl	   	   = eLIBs_fioctrl( horc, ORC_CMD_CONSTRUCT_NOW_PLAYLIST, 0, (void *)&arg );
	if( NULL == hNpl )
	{
		__err("Error in creating now play list!\n");
		eLIBs_fclose(horc);
		return EPDK_FAIL;
	}
	
	ret = eLIBs_fioctrl(horc, ORC_CMD_SAVE_NPL, 0, (void *)hNpl);   
	
	eLIBs_fioctrl(horc, ORC_CMD_DESTROY_NOW_PLAYLIST, 0, (void *)hNpl);
	
	eLIBs_fclose( horc ); 
	
	return ret;
}

__s32 dsk_orchid_load_last_npl(void)
{
	ES_FILE  *horc = 0;
	HNPL	  hNpl;
	orc_arg_npl_t  arg;
	__s32 	  ret;
	__s32	  total_npl;
	
	horc = eLIBs_fopen( ORCHID_FILE_PATH, "r+");
	if( horc == 0)
    {
    	__wrn("Error in opening a handle of orchid! At line %u of file %s.\n", __LINE__, __FILE__);
    	return EPDK_FAIL;
    }
    
    eLIBs_fioctrl( horc, ORC_CMD_ORCHID_IS_VALID, 0, 0 );
    	
	arg.media_type = ORC_MEDIA_TYPE_AUDIO;
	arg.work_mode  = ORC_NPL_WORK_MODE_MANAGE;	
	hNpl	   	   = eLIBs_fioctrl( horc, ORC_CMD_CONSTRUCT_NOW_PLAYLIST, 0, (void *)&arg );
	if( NULL == hNpl )
	{
		__wrn("Error in creating now play list!\n");
		eLIBs_fclose(horc);
		return EPDK_FAIL;
	}
	
	total_npl = eLIBs_fioctrl(horc, ORC_CMD_GET_TOTAL_ITEM_COUNT_OF_NPL, 0, (void *)hNpl); 
	
	ret = EPDK_OK;
	
	if( total_npl == 0 )
	{			
		ret = eLIBs_fioctrl(horc, ORC_CMD_LOAD_LAST_NPL, 0, (void *)hNpl);  		
	} 	
	
	eLIBs_fioctrl(horc, ORC_CMD_DESTROY_NOW_PLAYLIST, 0, (void *)hNpl);	
	
	eLIBs_fclose( horc ); 
	
	return ret;
}


