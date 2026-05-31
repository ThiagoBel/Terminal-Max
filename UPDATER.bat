@echo off

cd /d "%~dp0"
cd ..

configs\compiler\bin\g++.exe ^
TerminalMax.cpp ^
configs\icon.o ^
configs\discord\libdiscord-rpc.a ^
-lwinmm ^
-static ^
-static-libgcc ^
-static-libstdc++ ^
-o TerminalMax.exe

if %errorlevel% neq 0 (
    echo Erro ao compilar.
    pause
    exit /b
)

start TerminalMax.exe