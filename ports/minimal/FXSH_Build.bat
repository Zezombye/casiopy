@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.

if exist debug\*.obj  del debug\*.obj
if exist CASIOPY.G1A  del CASIOPY.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"D:\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"D:\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "C:\cygwin64\home\Zezombye\micropython\micropython-master\ports\minimal"
if not exist CASIOPY.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

