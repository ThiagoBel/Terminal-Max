@echo off
cd ..
color 02

echo Buscando atualizacoes...

curl -s --ssl-no-revoke "https://raw.githubusercontent.com/ThiagoBel/Terminal-Max/refs/heads/main/TerminalMax.cpp" -o TerminalMax_new.cpp

if errorlevel 1 (
    echo.
    echo Erro ao baixar atualização
    pause
    exit /b 1
)

timeout /t 1 /nobreak >nul

if exist TerminalMax_new.cpp (
    echo Atualizando arquivo principal...

    move /Y TerminalMax_new.cpp TerminalMax.cpp >nul

    if errorlevel 1 (
        echo.
        echo Erro ao atualizar arquivo principal
        pause
        exit /b 1
    )
) else (
    echo.
    echo Erro ao atualizar arquivo inexistente
    pause
    exit /b 1
)

echo Arquivo atualizado com sucesso
timeout /t 1 /nobreak >nul