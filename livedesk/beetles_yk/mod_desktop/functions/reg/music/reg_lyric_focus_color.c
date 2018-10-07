/*
************************************************************************************************************************
*                                            lyric focus color in register table
*
*                                  Copyright(C), 2006-2010, AllWinner Technology Co., Ltd.
*											       All Rights Reserved
*
* File Name   : reg_lyric_focus_color.c
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
#ifndef  __REG_LYRIC_FOCUS_COLOR_C__
#define  __REG_LYRIC_FOCUS_COLOR_C__


#include "..\\reg_i.h"


#define REG_LYRIC_FOCUS_COLOR_REGNODE             "\\music\\lyric_focus_color"
#define REG_LYRIC_FOCUS_COLOR_SET                 "lyric_focus_color"
#define REG_LYRIC_FOCUS_COLOR_KEY_CURRENT         "current"
#define REG_LYRIC_FOCUS_COLOR_KEY_DEFAULT         "default"


static __u32  _lyric_focus_color_name2enm( const char *lyric_focus_color_name );
static __s32  _lyric_focus_color_enm2name( __u32 lyric_focus_color_enm, char *lyric_focus_color_name, __u32 size );


/*
****************************************************************************************************
*Name        : lion_reg_lyric_focus_color_get
*Prototype   : __u32 lion_reg_lyric_focus_color_get( void )
*Arguments   : void
*Return      : the current lyric focus color in register table. The color follows GUI's color format.
*Description : get the current lyric focus color in register table.
*Other       :
****************************************************************************************************
*/
__u32 lion_reg_lyric_focus_color_get( void )
{
    __hdle  h_node = NULL;
    char    key_value[ELIBS_KEY_VALUE_LEN+1];   
    __u32  ret;
    
    /* open reg node */
	h_node = eLIBs_RegOpenNode( REG_LYRIC_FOCUS_COLOR_REGNODE, ELIBS_REG_READONLY );
	if( h_node == NULL )
	{
		__wrn("Warning! Reg node %s cannot be opened!\n", REG_LYRIC_FOCUS_COLOR_REGNODE);
	    goto error;
	}
    
    /* get key value */
    eLIBs_RegGetKeyValue( h_node, REG_LYRIC_FOCUS_COLOR_SET, REG_LYRIC_FOCUS_COLOR_KEY_CURRENT, key_value );
    
    /* convert the format of the key value */
    ret = _lyric_focus_color_name2enm( key_value );
    
    /* close reg node */
    eLIBs_RegCloseNode( h_node );
    h_node = NULL;
    
    return ret;
    
error:
    if( h_node != NULL )
    {
        eLIBs_RegCloseNode( h_node );
        h_node = NULL;
    }
    return GUI_WHITE;
}



/*
****************************************************************************************************
*Name        : lion_reg_lyric_focus_color_set
*Prototype   : __s32 lion_reg_lyric_focus_color_set( __u32 lyric_focus_color )
*Arguments   : lyric_focus_color  input. lyric focus color. The color follows GUI's color format.
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : set the current lyric focus color in register table.
*Other       :
****************************************************************************************************
*/
__s32 lion_reg_lyric_focus_color_set( __u32 lyric_focus_color )
{
    __hdle  h_node = NULL;
    char    key_value[ELIBS_KEY_VALUE_LEN+1];   
    __s32   ret;
    
    /* open reg node */
	h_node = eLIBs_RegOpenNode( REG_LYRIC_FOCUS_COLOR_REGNODE, ELIBS_REG_READWRITE );
	if( h_node == NULL )
	{
		__wrn("Warning! Reg node %s cannot be opened!\n", REG_LYRIC_FOCUS_COLOR_REGNODE);
	    goto error;
	}
    
    /* convert the format of the key value */
    ret = _lyric_focus_color_enm2name( lyric_focus_color, key_value, ELIBS_KEY_VALUE_LEN );
    if( ret != 0 )
    {
        goto error;
    }
    
    /* set key value */
    eLIBs_RegSetKeyValue( h_node, REG_LYRIC_FOCUS_COLOR_SET, REG_LYRIC_FOCUS_COLOR_KEY_CURRENT, key_value );
    
    /* close reg node */
    eLIBs_RegCloseNode( h_node );
    h_node = NULL;
    
    return EPDK_OK;
    
error:
    if( h_node != NULL )
    {
        eLIBs_RegCloseNode( h_node );
        h_node = NULL;
    }
    return EPDK_FAIL;
}



/*
****************************************************************************************************
*Name        : lion_reg_lyric_focus_color_get_default
*Prototype   : __u32 lion_reg_lyric_focus_color_get_default( void )
*Arguments   : void
*Return      : the default lyric focus color in register table. The color follows GUI's color format.
*Description : get the default lyric focus color in register table.
*Other       :
****************************************************************************************************
*/
__u32 lion_reg_lyric_focus_color_get_default( void )
{
    __hdle  h_node = NULL;
    char    key_value[ELIBS_KEY_VALUE_LEN+1];   
    __u32  ret;
    
    /* open reg node */
	h_node = eLIBs_RegOpenNode( REG_LYRIC_FOCUS_COLOR_REGNODE, ELIBS_REG_READONLY );
	if( h_node == NULL )
	{
		__wrn("Warning! Reg node %s cannot be opened!\n", REG_LYRIC_FOCUS_COLOR_REGNODE);
	    goto error;
	}
    
    /* get key value */
    eLIBs_RegGetKeyValue( h_node, REG_LYRIC_FOCUS_COLOR_SET, REG_LYRIC_FOCUS_COLOR_KEY_DEFAULT, key_value );
    
    /* convert the format of the key value */
    ret = _lyric_focus_color_name2enm( key_value );
    
    /* close reg node */
    eLIBs_RegCloseNode( h_node );
    h_node = NULL;
    
    return ret;
    
error:
    if( h_node != NULL )
    {
        eLIBs_RegCloseNode( h_node );
        h_node = NULL;
    }
    return GUI_WHITE;
}



/*
****************************************************************************************************
*Name        : lion_reg_lyric_focus_color_restore
*Prototype   : __s32 lion_reg_lyric_focus_color_restore( void )
*Arguments   : void
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : restore the default value of lyric focus color in register table.
*Other       :
****************************************************************************************************
*/
__s32 lion_reg_lyric_focus_color_restore( void )
{
    __hdle  h_node = NULL;
    char    key_value[ELIBS_KEY_VALUE_LEN+1];   
    
    /* open reg node */
	h_node = eLIBs_RegOpenNode( REG_LYRIC_FOCUS_COLOR_REGNODE, ELIBS_REG_READWRITE );
	if( h_node == NULL )
	{
		__wrn("Warning! Reg node %s cannot be opened!\n", REG_LYRIC_FOCUS_COLOR_REGNODE);
	    goto error;
	}

    /* get default value */
    eLIBs_RegGetKeyValue( h_node, REG_LYRIC_FOCUS_COLOR_SET, REG_LYRIC_FOCUS_COLOR_KEY_DEFAULT, key_value );

    /* set current value */
    eLIBs_RegSetKeyValue( h_node, REG_LYRIC_FOCUS_COLOR_SET, REG_LYRIC_FOCUS_COLOR_KEY_CURRENT, key_value );
    
    /* close reg node */
    eLIBs_RegCloseNode( h_node );
    h_node = NULL;
    
    return EPDK_OK;
    
error:
    if( h_node != NULL )
    {
        eLIBs_RegCloseNode( h_node );
        h_node = NULL;
    }
    return EPDK_FAIL;
}



#define LION_LYRIC_FOCUS_COLOR_NAME_RED                   "RED"
#define LION_LYRIC_FOCUS_COLOR_NAME_BLUE                  "BLUE"
#define LION_LYRIC_FOCUS_COLOR_NAME_GREEN                 "GREEN"
#define LION_LYRIC_FOCUS_COLOR_NAME_WHITE                 "WHITE"
#define LION_LYRIC_FOCUS_COLOR_NAME_BLACK                 "BLACK"
#define LION_LYRIC_FOCUS_COLOR_NAME_GRAY                  "GRAY"
#define LION_LYRIC_FOCUS_COLOR_NAME_CYAN                  "CYAN"
#define LION_LYRIC_FOCUS_COLOR_NAME_MAGENTA               "MAGENTA"
#define LION_LYRIC_FOCUS_COLOR_NAME_YELLOW                "YELLOW"


typedef struct _lyric_focus_color_map_t
{
	char   name[ELIBS_KEY_VALUE_LEN+1];
	__u32  code;
}lyric_focus_color_map_t;


const static lyric_focus_color_map_t lyric_focus_color_map_tbl[ ] =
{
    { LION_LYRIC_FOCUS_COLOR_NAME_RED    , GUI_RED     },
    { LION_LYRIC_FOCUS_COLOR_NAME_BLUE   , GUI_BLUE    },
    { LION_LYRIC_FOCUS_COLOR_NAME_GREEN  , GUI_GREEN   },
    { LION_LYRIC_FOCUS_COLOR_NAME_WHITE  , GUI_WHITE   },
    { LION_LYRIC_FOCUS_COLOR_NAME_BLACK  , GUI_BLACK   },
    { LION_LYRIC_FOCUS_COLOR_NAME_GRAY   , GUI_GRAY    },
    { LION_LYRIC_FOCUS_COLOR_NAME_CYAN   , GUI_CYAN    },
    { LION_LYRIC_FOCUS_COLOR_NAME_MAGENTA, GUI_MAGENTA },
    { LION_LYRIC_FOCUS_COLOR_NAME_YELLOW , GUI_YELLOW  }
};

#define LYRIC_FOCUS_COLOR_NR           ( sizeof(lyric_focus_color_map_tbl) / sizeof(lyric_focus_color_map_tbl[0]) )



/*
****************************************************************************************************
*Name        : _lyric_focus_color_name2enm
*Prototype   : __u32  _lyric_focus_color_name2enm( const char *lyric_focus_color_name )
*Arguments   : lyric_focus_color_name   input. the name of a lyric focus color
*Return      : the enum value of the lyric focus color. return GUI_WHITE, if fail.
*Description : get the enum value of the lyric focus color through its name
*Other       :
****************************************************************************************************
*/
static __u32  _lyric_focus_color_name2enm( const char *lyric_focus_color_name )
{
	__u32  i;

    if( lyric_focus_color_name == NULL )
    {
        return GUI_WHITE;
    }
    
    /* search in table */
	for( i = 0;  i < LYRIC_FOCUS_COLOR_NR;  i++ )
	{
		if( eLIBs_strcmp( lyric_focus_color_name, lyric_focus_color_map_tbl[i].name ) == 0 )
			return lyric_focus_color_map_tbl[i].code;
	}

	return GUI_WHITE;
}



/*
****************************************************************************************************
*Name        : _lyric_focus_color_enm2name
*Prototype   : __s32  _lyric_focus_color_enm2name( __u32 lyric_focus_color_enm, 
*                                              char *lyric_focus_color_name, __u32 size )
*Arguments   : lyric_focus_color_enm    input. the enum value of a lyric focus color
*              lyric_focus_color_name   output. a buffert to store the name of a lyric focus color
*              size                     input. the buffer's size.
*Return      : ==0      succeed
*              !=0      fail
*Description : get the name of the lyric focus color through its enum value
*Other       :
****************************************************************************************************
*/
static __s32  _lyric_focus_color_enm2name( __u32 lyric_focus_color_enm, char *lyric_focus_color_name, __u32 size )
{
	__u32  i;
	
	if( lyric_focus_color_name == NULL || size == 0 )
	{
		return -1;
    }
    
    /* search in table */
	for( i = 0;  i < LYRIC_FOCUS_COLOR_NR;  i++ )
	{
		if( lyric_focus_color_enm == lyric_focus_color_map_tbl[i].code )
		{
			eLIBs_strncpy( lyric_focus_color_name, lyric_focus_color_map_tbl[i].name, size );
			lyric_focus_color_name[size-1] = '\0';
			
			return 0;
		}
	}

	return -1;
}




#endif     //  ifndef __REG_LYRIC_FOCUS_COLOR_C__

/* end of reg_lyric_focus_color.c */
