@echo off
call "C:\BuildTools\Common7\Tools\VsDevCmd.bat"
cmake --build ./build --config Release -j 8
