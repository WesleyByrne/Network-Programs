@echo off
cls

set DRIVE_LETTER=%1:
set COMPILER_PATH=%DRIVE_LETTER%/TDM-GCC-64
set ZLIB_PATH=%COMPILER_PATH%/zlib-1.2.11
set PATH=%ZLIB_PATH%/lib;%COMPILER_PATH%/bin;%COMPILER_PATH%/wxWidgets-3.1.0/lib;c:/windows

Endeavor 1
