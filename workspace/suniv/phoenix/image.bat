::----------------------------------------------------------------
:: create by james at 2011-09-01
::----------------------------------------------------------------

@ECHO OFF

echo make image begin...

set BUILDTOOLPATH=..\..\..\..\eStudio\Softwares\mod_update
set DRAGONTOOLPATH=..\..\..\..\eStudio\Softwares\eDragonEx200

::----------------------------------------------------------------
:: ����ϵͳ�ļ�
::----------------------------------------------------------------
call update.bat > update.txt

::----------------------------------------------------------------
:: �������ýű�
::----------------------------------------------------------------
if exist ..\eFex\sys_config.bin del ..\eFex\sys_config.bin
%BUILDTOOLPATH%\script.exe ..\eFex\sys_config.fex

::----------------------------------------------------------------
:: ����BOOT0��BOOT1�ļ�ͷ��Ϣ
::----------------------------------------------------------------
copy ..\eGon\storage_media\sdcard\boot0.bin boot0.fex
copy ..\eGon\storage_media\sdcard\boot1.bin boot1.fex
%BUILDTOOLPATH%\update.exe ..\eFex\sys_config.bin boot0.fex boot1.fex SDMMC_CARD

::----------------------------------------------------------------
:: ����MBR
::----------------------------------------------------------------
%BUILDTOOLPATH%\script_old.exe part_config.fex
%BUILDTOOLPATH%\update_mbr.exe part_config.bin mbr.fex

::----------------------------------------------------------------
:: ��������ļ�
::----------------------------------------------------------------
call fsbuild.bat

::----------------------------------------------------------------
:: ������д�ļ�У���
::----------------------------------------------------------------
%DRAGONTOOLPATH%\FileAddSum.exe rootfs.fex ..\eFex\verify.fex

::----------------------------------------------------------------
:: ������д������ļ�
::----------------------------------------------------------------
if exist PHOENIXv100.img del PHOENIXv100.img
%DRAGONTOOLPATH%\compile -o image.bin image.cfg
%DRAGONTOOLPATH%\dragon image.cfg > image.txt

::----------------------------------------------------------------
:: ������ʱ�ļ�
::----------------------------------------------------------------
del rootfs.fex
del dlinfo.fex
del mbr.fex
del boot0.fex
del boot1.fex
del ..\eFex\sys_config.bin
del part_config.bin

echo make image finished...

PAUSE
