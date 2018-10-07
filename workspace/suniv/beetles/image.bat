::/*
::*********************************************************************************************************
::*                                                    MELIS
::*                                    the Easy Portable/Player Develop Kits
::*                                                 make image
::*
::*                                    (c) Copyright 2011-2014, Sunny China
::*                                             All Rights Reserved
::*
::* File    : image.bat
::* By      : Sunny
::* Version : v1.0
::* Date    : 2011-4-19
::* Descript: make a melis100 sdk image file.
::* Update  : date                auther      ver     notes
::*           2011-4-19 13:11:43  Sunny       1.0     Create this file.
::*********************************************************************************************************
::*/

    @ECHO OFF
    
    echo make image begin......
    if exist ePDKv100.img del ePDKv100.img

    set BUILDTOOLPATH=.\..\..\..\tools\build_tools
    set DRAGONTOOLPATH=.\..\..\..\tools\build_tools\eDragonEx220
    
    ::----------------------------------------------------------------
    ::      ����ϵͳ�ļ�
    ::----------------------------------------------------------------
    echo ----------------------------------------------------------------
    echo                       update.bat
    echo ----------------------------------------------------------------
    call update.bat >update.txt
    
    ::----------------------------------------------------------------
    ::      �������ýű���ϵͳ
    ::----------------------------------------------------------------
    %BUILDTOOLPATH%\script.exe .\..\eFex\sys_config.fex
    %BUILDTOOLPATH%\script.exe .\..\eFex\sys_partition.fex

    ::----------------------------------------------------------------
    ::      �������ýű���Ӧ��
    ::----------------------------------------------------------------
    %BUILDTOOLPATH%\script.exe .\rootfs\app_config.fex    
    ::----------------------------------------------------------------
    ::      ����BOOT0��BOOT1�ļ�ͷ��Ϣ
    ::----------------------------------------------------------------
    ::%BUILDTOOLPATH%\update.exe  ..\eFex\sys_config.bin Boot0.bin Boot1.bin
    
    ::----------------------------------------------------------------
    ::      ����boot0��boot1�ļ�ͷ
    ::---------------------------------------------------------------- 
    echo ----------------------------------------------------------------
    echo                       update boot0\boot1
    echo ----------------------------------------------------------------
    %BUILDTOOLPATH%\update_boot0.exe Boot0.bin  ..\eFex\sys_config.bin  SPINOR_FLASH

    %BUILDTOOLPATH%\update_boot1.exe Boot1.bin  ..\eFex\sys_config.bin  

    ::----------------------------------------------------------------
    ::      ����MBR�ļ�
    ::----------------------------------------------------------------
    %BUILDTOOLPATH%\BurnMBR.exe ..\eFex\sys_config.bin  mbr.bin

    ::----------------------------------------------------------------
    ::      ������д��Ҫ��MBR�ļ� ,���������4����Ϊusbtool.fex�Ѿ�д��
    ::----------------------------------------------------------------
    %BUILDTOOLPATH%\update_mbr.exe ..\eFex\sys_partition.bin  4


    ::----------------------------------------------------------------
    ::      fes1��uboot������USB��¼
    ::----------------------------------------------------------------
    @copy ..\eFex\usb\fes1_sun63i.bin          fes1.fex   
    @copy ..\eFex\usb\u-boot-sun63i.bin        u-boot.fex
    ::----------------------------------------------------------------
    ::      ����fes1��uboot�ļ�ͷ
    ::---------------------------------------------------------------- 
    echo ----------------------------------------------------------------
    echo                       update fes1 uboot
    echo ----------------------------------------------------------------
    %BUILDTOOLPATH%\update_fes1.exe  fes1.fex  ..\eFex\sys_config.bin
    %BUILDTOOLPATH%\update_uboot.exe u-boot.fex  ..\eFex\sys_config.bin

    
    ::----------------------------------------------------------------
    ::      ���rootfs\ramfs\udiskĿ¼�ľ����ļ�
    ::----------------------------------------------------------------
    call fsbuild.bat

    ::----------------------------------------------------------------
    ::      BOOT0��BOOT1�ļ���С������
    ::----------------------------------------------------------------
    %BUILDTOOLPATH%\fix_file.exe boot0.bin  24
    %BUILDTOOLPATH%\fix_file.exe boot1.bin  120
    
    ::----------------------------------------------------------------
    ::      ����boot0+boo1+mbr+rootfs.iso+udisk.iso
    ::----------------------------------------------------------------
    type boot0.bin boot1.bin mbr.bin rootfs.iso udisk.iso > melis100.fex
    
    ::----------------------------------------------------------------
    ::      ������д�ļ�У���
    ::----------------------------------------------------------------
    %DRAGONTOOLPATH%\FileAddSum.exe melis100.fex verify.fex
    
    ::----------------------------------------------------------------
    ::      ������д������ļ�ePDKv100.img
    ::----------------------------------------------------------------
    
    %DRAGONTOOLPATH%\compile -o image.bin image.cfg
    %DRAGONTOOLPATH%\dragon  image.cfg > image.txt
    
    ::----------------------------------------------------------------
    ::      ������ʱ�ļ�
    ::----------------------------------------------------------------
    del boot0.bin
    del boot1.bin
    del mbr.bin
    del rootfs.iso
    del udisk.iso
    ::del melis100.fex
    del ..\eFex\sys_config.bin
    del sunxi_mbr.fex
    del u-boot.fex
    del ..\eFex\sys_partition.bin
    del fes1.fex
    del dlinfo.fex
    
    echo make image finished....
    
    PAUSE
