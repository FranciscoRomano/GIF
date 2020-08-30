@echo off
call VsDevCmd.bat
call cmake --build "./.vscode/cmake_bin"