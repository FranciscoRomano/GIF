@echo off
call VsDevCmd.bat
call cmake -G"Visual Studio 16 2019" -A Win32 -B"./.vscode/cmake_bin" -H"."