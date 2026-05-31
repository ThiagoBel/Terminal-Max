cd ..
color 02
curl -s --ssl-no-revoke "https://raw.githubusercontent.com/ThiagoBel/Terminal-Max/refs/heads/main/TerminalMax.cpp" -o TerminalMax_new.cpp

if exist TerminalMax_new.cpp (
    move /Y TerminalMax_new.cpp TerminalMax.cpp >nul
)