@echo off
cd /d "%~dp0"
cd ..
color 02
echo Compilando...
configs\compiler\bin\g++.exe ^
TerminalMax.cpp ^
configs\icon.o ^
configs\discord\libdiscord-rpc.a ^
-lwinmm ^
-static ^
-static-libgcc ^
-static-libstdc++ ^
-o TerminalMax.exe
echo Iniciando...

if %errorlevel% neq 0 (
    color 04
    echo Erro ao compilar.
    pause
    exit /b
)

start TerminalMax.exe
echo TerminalMax atualizado com sucesso
timeout /t 1 /nobreak >nul