/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           calendar app sample
*
*						        	(c) Copyright 2006-2009, ANDY, China
*											 All Rights Reserved
*
* File    : .c
* By      :lyn
* Version : V1.00
*********************************************************************************************************
*/
#include "mod_init_i.h"
#include "scene_adjust_uipara.h"

static scene_adjust_para_t scene_uipara_800_480 =
{
	{PIXEL_COLOR_ARGB8888,0,0,800,480},
	{0,0,800,480},
	{
		{100,100,50,50},
		{700,100,50,50},
		{700,400,50,50},
		{100,400,50,50},	
		{400,250,50,50},	
	},
};

static scene_adjust_para_t scene_uipara_400_240 =
{
	{PIXEL_COLOR_ARGB8888,0,0,400,240},
	{0,0,400,240},
	{
		{60,60,30,30},
		{340,60,30,30},
		{340,180,30,30},
		{60,180,30,30},	
		{200,105,30,30},	
	},
};
static scene_adjust_para_t scene_uipara_480_272 =
{
	{PIXEL_COLOR_ARGB8888,0,0,480,272},
	{0,0,480,272},
	{
		{60,60,50,50},
		{420,60,50,50},
		{420,212,50,50},
		{60,212,50,50},	
		{240,130,50,50},	
	},
};
scene_adjust_para_t *scene_adjust_get_uipara(void)
{
	__u32 width;
	__u32 height;	
	
	dsk_display_get_size((__s32 *)&width,(__s32 *)&height);	
    __msg("width=%d, height=%d\n", width, height);
	
	if(width == 800 && height == 480)
	{
		return &scene_uipara_800_480;
	}
	else if(width == 480 && height == 272)
	{
		return &scene_uipara_480_272;
	}
	else if(width == 400 && height == 240)
	{
		return &scene_uipara_400_240;
	}
	else
	{
		return &scene_uipara_800_480;
	}
}

