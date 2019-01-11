@echo off
cls

set DRIVE_LETTER=%1:
set GAME_PATH=%DRIVE_LETTER%/Game_Engine
set COMPILER_PATH=%DRIVE_LETTER%/TDM-GCC-64
set PATH=%COMPILER_PATH%/bin;c:/windows
set ZLIB_PATH=%GAME_PATH%/zlib-1.2.11
set CSC1310_PATH=%DRIVE_LETTER%/Endeavor/Endeavor_Networked/CSC1310

g++ -I./ -I%ZLIB_PATH% -I%CSC1310_PATH%/include -c Zip.cpp
ar -r libzipp.a Zip.o
