@echo off
call "C:\BuildTools\Common7\Tools\VsDevCmd.bat"
cmake -S . -B ./build
