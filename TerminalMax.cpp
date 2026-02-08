//     _/\\\\____________/\\\\_____/\\\\\\\\\_____/\\\_______/\\\________
//     _\/\\\\\\________/\\\\\\___/\\\\\\\\\\\\\__\///\\\___/\\\/________
//     __\/\\\//\\\____/\\\//\\\__/\\\/////////\\\___\///\\\\\\/_________
//     ___\/\\\\///\\\/\\\/_\/\\\_\/\\\_______\/\\\_____\//\\\\__________
//     ____\/\\\__\///\\\/___\/\\\_\/\\\\\\\\\\\\\\\______\/\\\\_________
//     _____\/\\\____\///_____\/\\\_\/\\\/////////\\\______/\\\\\\_______
//     ______\/\\\_____________\/\\\_\/\\\_______\/\\\____/\\\////\\\____
//     _______\/\\\_____________\/\\\_\/\\\_______\/\\\__/\\\/___\///\\\_
//     ________\///______________\///__\///________\///__\///_______\///_
/*
Olá!!!!!!
Esse projeto foi criado por github.com/ThiagoBel
Esse projeto foi feito apenas para facilitar o uso do terminal, com comandos mais fáceis e curtos
Atualmente só poderá servir para Windows, mas tentaremos no futuro deixar para Linux também

06/02/2026
*/
#pragma comment(lib, "winmm.lib")
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#define _WIN32_WINNT 0x0A00
#define WIN32_LEAN_AND_MEAN
#define STB_IMAGE_IMPLEMENTATION
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <direct.h>
#include <windows.h>
#include <stack>
#include <mmsystem.h>
#include <cctype>
#include <cstring>
#include <sstream>
#include <fstream>
#include <locale>
#include <shlobj.h>
#include <random>
#include <string>
#include <cstdio>
#include <Lmcons.h>
#include <fcntl.h>
#include <io.h>

#include "configs/headers/notify.h"
#include "configs/headers/MOPTS.h"
#include "configs/headers/icolor.hpp"
#include "configs/headers/stb_image.h"
#include "configs/discord/discord_rpc.h"
std::string _DEFINE = "";            // negocio definido
std::string _VERSION = "1.1.3";      // versao do terminal
std::string AND_OPERATOR = "&&&&";   // adicione comandos
std::string DELAY_OPERATOR = "@@@@"; // adiciona comandos + delay
bool exited = false;                 // ve se o usuario quer sair
bool pularlinhaw = false;            // só pro prompt não ficar fei
bool IMAGE_CHAR_OPT = false;         // bagulho de otimização de imagens
bool discord_disponivel = false;     // ve se o discord tá aberto pra usar o RPC
bool _DISCORD_RPC_VALUE = true;      // ve o bagui do rpc do discord
bool _PROMPT_COLOR_VALUE = true;     // cores no prompt
bool _SOUNDS_VALUE = true;           // sons
std::string _APELIDO = "";           // apelido do usuario
std::string _APELIDO_WINDOWS = "";   // apelido do WINDOWS do usuario
DiscordEventHandlers handlers;
DiscordRichPresence presence;
std::random_device rd;
std::mt19937 gen(rd());
std::string GetExePath();

void PRINT_ERROR(const std::string &msg, const bool withendl)
{
    if (withendl == true)
    {
        std::cout << icolor::fatal() << msg << icolor::finished() << std::endl;
    }
    else if (withendl == false)
    {
        std::cout << icolor::fatal() << msg << icolor::finished();
    }
    else
    {
        std::cout << icolor::fatal() << "Erro no sinalizador" << icolor::finished() << std::endl;
    }
}

void PRINT_SYS(const std::string &msg, const bool withendl)
{
    if (withendl == true)
    {
        std::cout << msg << std::endl;
    }
    else if (withendl == false)
    {
        std::cout << msg;
    }
    else
    {
        std::cout << icolor::fatal() << "Erro no sinalizador" << icolor::finished() << std::endl;
    }
}

void PRINT_BLUE(const std::string &msg, const bool withendl)
{
    if (withendl == true)
    {
        std::cout << icolor::blue() << msg << icolor::finished() << std::endl;
    }
    else if (withendl == false)
    {
        std::cout << icolor::blue() << msg << icolor::finished();
    }
    else
    {
        std::cout << icolor::fatal() << "Erro no sinalizador" << icolor::finished() << std::endl;
    }
}

std::wstring UTF8ToWide(const std::string &s) // transforma UTF8 pra UTF16
{
    int size = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);

    std::wstring result(size, 0);

    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, &result[0], size);

    return result;
}

std::string TO_UPPER(std::string texto) // grita
{
    std::transform(texto.begin(), texto.end(), texto.begin(),
                   [](unsigned char c)
                   {
                       return std::toupper(c);
                   });
    return texto;
}

std::string TO_LOWER(std::string texto) // fala baixo
{
    std::transform(texto.begin(), texto.end(), texto.begin(),
                   [](unsigned char c)
                   {
                       return std::tolower(c);
                   });
    return texto;
}

std::string CAPITALIZE(std::string texto) // deixa mais formal
{
    bool novaPalavra = true;

    for (char &c : texto)
    {
        if (std::isspace((unsigned char)c))
        {
            novaPalavra = true;
        }
        else if (novaPalavra)
        {
            c = std::toupper((unsigned char)c);
            novaPalavra = false;
        }
        else
        {
            c = std::tolower((unsigned char)c);
        }
    }

    return texto;
}

int calcularExpressao(const std::string &expr) // matematica safada
{
    std::stack<int> numeros;
    std::stack<char> ops;

    auto aplicar = [](int a, int b, char op) -> int
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Erro, divisão por zero"); // animal
            return a / b;
        default:
            throw std::runtime_error("Erro, operador inválido"); // precisa ser extremamente burro pra acontecer isso, não é possivel
        }
    };

    auto prioridade = [](char op) -> int
    {
        if (op == '+' || op == '-')
        {
            return 1;
        }
        if (op == '*' || op == '/')
        {
            return 2;
        }
        return 0;
    };

    std::istringstream in(expr);
    char token;
    while (in >> token)
    {
        if (std::isdigit(token))
        {
            in.putback(token);
            int n;
            if (!(in >> n))
            {
                throw std::runtime_error("Erro, número inválido"); // quem faz isso deve cometer prisao perpetua
            }
            numeros.push(n);
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/')
        {
            while (!ops.empty() && prioridade(ops.top()) >= prioridade(token))
            {
                if (numeros.size() < 2)
                {
                    throw std::runtime_error("Erro, expressão inválida");
                }
                int b = numeros.top();
                numeros.pop();
                int a = numeros.top();
                numeros.pop();
                char op = ops.top();
                ops.pop();

                numeros.push(aplicar(a, b, op));
            }
            ops.push(token);
        }
        else
        {
            throw std::runtime_error("Erro, token inválido");
        }
    }

    while (!ops.empty())
    {
        if (numeros.size() < 2)
        {
            throw std::runtime_error("Expressão inválida");
        }
        int b = numeros.top();
        numeros.pop();
        int a = numeros.top();
        numeros.pop();
        char op = ops.top();
        ops.pop();

        numeros.push(aplicar(a, b, op));
    }

    if (numeros.size() != 1)
    {
        throw std::runtime_error("Expressão inválida");
    }
    return numeros.top();
}

void PLAY_SOUND(const std::string &nome) // toca um som ou musica
{
    if (_SOUNDS_VALUE == true)
    {
        std::string caminho = GetExePath() + "\\configs\\sounds\\" + nome + ".wav";

        PlaySoundA(caminho.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
}

void STOP_SOUND() // para a musica ou som (nunca usei isso)
{
    PlaySoundA(NULL, NULL, 0);
}

void REOPEN() // reabre o programa
{
    wchar_t caminho[MAX_PATH];

    GetModuleFileNameW(NULL, caminho, MAX_PATH);

    STARTUPINFOW si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    if (CreateProcessW(caminho, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        ExitProcess(0); // mata o processo atual
    }
}

void enableANSI()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

bool EhAdmin()
{
    BOOL isAdmin = FALSE;
    HANDLE token = NULL;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
    {
        TOKEN_ELEVATION elevation;
        DWORD size;
        if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &size))
        {
            isAdmin = elevation.TokenIsElevated;
        }
        CloseHandle(token);
    }

    return isAdmin != FALSE;
}
std::string GetExePath() // pega o lugar do .exe
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string full(path);
    size_t pos = full.find_last_of("\\/");
    return full.substr(0, pos);
}

std::string GetUserPath()
{
    HKEY hKey;
    char value[8192];
    DWORD size = sizeof(value);

    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Environment", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        return "";
    }
    RegQueryValueExA(hKey, "Path", NULL, NULL, (LPBYTE)value, &size);
    RegCloseKey(hKey);

    return std::string(value);
}

void SetUserPath(const std::string &newPath)
{
    HKEY hKey;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
    {
        return;
    }
    RegSetValueExA(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE *)newPath.c_str(), newPath.size() + 1);

    RegCloseKey(hKey);

    // avisa o Windows que o PATH mudou
    SendMessageTimeoutA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) "Environment", SMTO_ABORTIFHUNG, 100, NULL);
}

void iniciarDiscordRPC() // RPC do discord
{
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("1469464608749256805", &handlers, 1, NULL);

    memset(&presence, 0, sizeof(presence));

    std::string detalhes = "Terminal MAX v" + _VERSION;
    presence.details = detalhes.c_str();
    presence.largeImageKey = "maxlogo";
    presence.largeImageText = "Terminal MAX";
    presence.startTimestamp = time(NULL);

    Discord_UpdatePresence(&presence);

    discord_disponivel = true;
}

void HELP_CMD()
{
    std::cout << "TerminalMax v" << _VERSION << "\n\n";

    std::cout << "define <valor>            - define valor\n";
    std::cout << "#define <valor>           - define valor permanente\n";
    std::cout << "$define                   - mostra valor definido\n";
    std::cout << "&define                   - limpa os valores salvo\n";
    std::cout << "sayln                     - mostra algo no terminal pulando linha no final\n";
    std::cout << "say                       - mostra algo no terminal\n";
    std::cout << "terminalinfo              - informações do terminal\n";
    std::cout << "cmdinfo                   - alias de terminalinfo\n";
    std::cout << "version                   - mostra versão\n";
    std::cout << "help                      - mostra ajuda\n";
    std::cout << "cls / clear               - limpa a tela\n";
    std::cout << "calcc                     - calcula algo\n";
    std::cout << "run                       - executa script (.trmax)\n";
    std::cout << "exit                      - sai do terminal\n";
    std::cout << "exitf                     - saída forçada\n";
    std::cout << "reopen                    - reinicia o terminal\n";
    std::cout << "exec                      - executa programa definido\n";
    std::cout << "open                      - executa programa ou site definido\n";
    std::cout << ">                         - executa comando direto do sistema\n";
    std::cout << "mkfile / newfile          - cria arquivo\n";
    std::cout << "rmfile / delfile          - deleta arquivo\n";
    std::cout << "mkdir / newfolder         - cria pasta\n";
    std::cout << "rmdir / delfolder         - deleta pasta\n";
    std::cout << "ls / dir / $              - lista arquivos\n";
    std::cout << "local                     - muda para diretório definido\n";
    std::cout << "$local                    - mostra diretório atual\n";
    std::cout << "check_storage             - mostra armazenamento do disco\n";
    std::cout << "$storage                  - alias de check_storage\n";
    std::cout << "to_desktop                - vai para Desktop\n";
    std::cout << "time                      - mostra a hora\n";
    std::cout << "check_admin / $admin      - verifica se é administrador\n";
    std::cout << "image                     - converte imagem para ASCII\n";
    std::cout << "clear_cmd                 - apaga TODAS as configs\n";
    std::cout << "beep                      - toca som de beep\n";
    std::cout << "configs                   - abre menu de configurações\n";
    std::cout << "roll                      - escolhe um numero aleatorio\n";
    std::cout << "date                      - mostra a data\n";
    std::cout << "kill                      - mata uma tarefa\n";
    std::cout << "$tasks / tasks / tasklist - lista todas as tarefas\n";
    std::cout << "$apelido / $apelidos      - mostra apelido\n";
    std::cout << "credits                   - mostra créditos\n";
    std::cout << "notify                    - mostra uma notificação\n\n";
    std::cout << "upper                     - transforma o define tudo em maiusculo\n";
    std::cout << "lower                     - transforma o define tudo em minusculo\n";
    std::cout << "capitalize                - primeiro caractere de uma palavra fica maiusculo e o resto minusculo, deixando mais formal\n";
    std::cout << "len                       - mostra a quantidade de caracteres em uma frase/palavra\n";

    std::cout << "&&&&                      - executa múltiplos comandos\n";
    std::cout << "@@@@<valor>               - executa comando com delay\n\n";

    std::cout << "--version                 - mostra versão do TerminalMax\n";
    std::cout << "--exec <cmd>              - executa comando direto\n";
    std::cout << "--run <arquivo>           - executa script\n";
}

void ASCII_CALL()
{
    std::cout << icolor::blue() << R"( _/\\\\____________/\\\\_____/\\\\\\\\\_____/\\\_______/\\\________ )" << icolor::finished() << std::endl;
    std::cout << icolor::blue() << R"( _\/\\\\\\________/\\\\\\___/\\\\\\\\\\\\\__\///\\\___/\\\/__)" << _VERSION << "_" << icolor::finished() << std::endl;
    std::cout << icolor::blue() << R"( __\/\\\//\\\____/\\\//\\\__/\\\/////////\\\___\///\\\\\\/_________ )" << icolor::finished() << std::endl;
    std::cout << icolor::white() << R"( ___\/\\\\///\\\/\\\/_\/\\\_\/\\\_______\/\\\_____\//\\\\__________ )" << icolor::finished() << std::endl;
    std::cout << icolor::white() << R"( ____\/\\\__\///\\\/___\/\\\_\/\\\\\\\\\\\\\\\______\/\\\\_________ )" << icolor::finished() << std::endl;
    std::cout << icolor::white() << R"( _____\/\\\____\///_____\/\\\_\/\\\/////////\\\______/\\\\\\_______ )" << icolor::finished() << std::endl;
    std::cout << icolor::blue() << R"( ______\/\\\_____________\/\\\_\/\\\_______\/\\\____/\\\////\\\____ )" << icolor::finished() << std::endl;
    std::cout << icolor::blue() << R"( _______\/\\\_____________\/\\\_\/\\\_______\/\\\__/\\\/___\///\\\_ )" << icolor::finished() << std::endl;
    std::cout << icolor::blue() << R"( ________\///______________\///__\///________\///__\///_______\///_ )" << icolor::finished() << std::endl;
}

std::wstring ReadUnicodeLine()
{
    std::wstring input;
    std::getline(std::wcin, input);
    return input;
}

std::string toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return s;
}

void system_path_SET(const std::string &what)
{
    std::string exePath = GetExePath();
    std::string path = GetUserPath();

    if (what == "add")
    {
        if (path.find(exePath) != std::string::npos)
        {
            PRINT_SYS("Terminal já está no PATH", true);
            return;
        }

        if (!path.empty() && path.back() != ';')
        {
            path += ';';
        }

        path += exePath;
        SetUserPath(path);
    }
    else if (what == "remove")
    {
        size_t pos = path.find(exePath);
        if (pos == std::string::npos)
        {
            PRINT_SYS("Terminal não está no PATH", true);
            return;
        }

        // remove ; antes ou depois
        if (pos > 0 && path[pos - 1] == ';')
            path.erase(pos - 1, exePath.size() + 1);
        else
            path.erase(pos, exePath.size());

        SetUserPath(path);
    }
}

void CriarArquivo(const std::string &nome)
{
    std::ofstream file(nome);

    if (file)
    {
        PRINT_BLUE("Arquivo criado", true);
    }
    else
    {
        PRINT_ERROR("Erro ao criar arquivo", true);
    }
}

void DeletarArquivo(const std::string &nome)
{
    if (DeleteFileA(nome.c_str()))
    {
        PRINT_BLUE("Arquivo deletado", true);
    }
    else
    {
        PRINT_ERROR("Erro ao deletar arquivo", true);
    }
}

void DeletarPasta(const std::string &nome)
{
    if (_rmdir(nome.c_str()) == 0)
    {
        PRINT_BLUE("Pasta deletada", true);
    }
    else
    {
        PRINT_ERROR("Erro ao deletar pasta", true);
    }
}

void CriarPasta(const std::string &nome)
{
    if (_mkdir(nome.c_str()) == 0)
    {
        PRINT_BLUE("Pasta criada", true);
    }
    else
    {
        PRINT_ERROR("Erro ao criar pasta", true);
    }
}

void ListarArquivos(const std::string &dir)
{
    std::string caminho;

    if (dir.empty())
    {
        caminho = "*";
    }
    else
    {
        caminho = dir + "\\*";
    }

    WIN32_FIND_DATAA data;
    HANDLE hFind = FindFirstFileA(caminho.c_str(), &data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        PRINT_ERROR("Erro, diretório inválido ou vazio", true);
        return;
    }

    do
    {
        std::string nome = data.cFileName;

        if (nome == "." || nome == "..")
        {
            continue;
        }

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            PRINT_BLUE(nome + " [DIR]", true);
        }
        else
        {
            PRINT_SYS(nome, true);
        }

    } while (FindNextFileA(hFind, &data));

    FindClose(hFind);
}
std::string WideToUTF8(const std::wstring &w)
{
    int size = WideCharToMultiByte(
        CP_UTF8,
        0,
        w.c_str(),
        -1,
        nullptr,
        0,
        nullptr,
        nullptr);

    std::string result(size - 1, 0);

    WideCharToMultiByte(
        CP_UTF8,
        0,
        w.c_str(),
        -1,
        &result[0],
        size,
        nullptr,
        nullptr);

    return result;
}

bool DirectoryExists(const std::string &path)
{
    int size = MultiByteToWideChar(
        CP_UTF8,
        0,
        path.c_str(),
        -1,
        nullptr,
        0);

    std::wstring wpath(size, 0);

    MultiByteToWideChar(
        CP_UTF8,
        0,
        path.c_str(),
        -1,
        &wpath[0],
        size);

    DWORD attr = GetFileAttributesW(wpath.c_str());

    return (attr != INVALID_FILE_ATTRIBUTES &&
            (attr & FILE_ATTRIBUTE_DIRECTORY));
}

std::string GetCurrentPath()
{
    wchar_t wpath[MAX_PATH];

    GetCurrentDirectoryW(MAX_PATH, wpath);

    return WideToUTF8(wpath);
}

bool ChangeDirectory(const std::string &path, bool showError = true)
{
    if (path.empty())
    {
        return false;
    }

    int size = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, nullptr, 0); // Converte UTF-8 para UTF-16
    std::wstring wpath(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, &wpath[0], size);

    if (SetCurrentDirectoryW(wpath.c_str())) // Tenta mudar o diretório
    {
        return true;
    }

    if (showError)
    {
        PRINT_ERROR("Erro, diretório inválido: " + path, true);
    }

    return false;
}

void CLEAR_TERMINAL()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hConsole == INVALID_HANDLE_VALUE)
    {
        return;
    }

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);

    SetConsoleCursorPosition(hConsole, homeCoords);
}

std::string trim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](unsigned char ch)
                                    {
                                        return !std::isspace(ch);
                                    }));

    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch)
                         {
                             return !std::isspace(ch);
                         })
                .base(),
            s.end());

    return s;
}

std::string GetAppFolder()
{
    char path[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path);

    std::string pasta = std::string(path) + "\\TerminalMax";
    CreateDirectoryA(pasta.c_str(), NULL);

    return pasta;
}

void SalvarConfig(const std::string &nome, const std::string &conteudo)
{
    std::ofstream file(GetAppFolder() + "\\" + nome);
    file << conteudo;
}

std::string LerConfig(const std::string &nome)
{
    std::ifstream file(GetAppFolder() + "\\" + nome);

    if (!file)
    {
        return "";
    }

    std::string linha;
    std::string conteudo;

    while (getline(file, linha))
    {
        conteudo += linha;
    }

    return trim(conteudo);
}

bool DeletarConfig(const std::string &nome)
{
    std::string caminho = GetAppFolder() + "\\" + nome;
    return remove(caminho.c_str()) == 0;
}

void ImagemParaASCII(const std::string &caminhoImagem, int larguraASCII = 80)
{
    int w, h, c;
    unsigned char *img = stbi_load(caminhoImagem.c_str(), &w, &h, &c, 4);
    if (!img)
    {
        PRINT_ERROR("Erro ao carregar imagem", true);
        return;
    }

    float proporcao = (float)h / w;
    int alturaASCII = (int)(proporcao * larguraASCII * 0.55f);

    const char **escala;

    if (IMAGE_CHAR_OPT)
    {
        static const char *escalaA[] = {"#", "@", "%", "*", "&"};
        escala = escalaA;
    }
    else
    {
        static const char *escalaB[] = {"░", "░", "▒", "▓", "█"};
        escala = escalaB;
    }

    constexpr int escalaTam = 5;

    std::vector<int> mapX(larguraASCII);
    std::vector<int> mapY(alturaASCII);

    for (int x = 0; x < larguraASCII; x++)
    {
        mapX[x] = x * w / larguraASCII;
    }
    for (int y = 0; y < alturaASCII; y++)
    {
        mapY[y] = y * h / alturaASCII;
    }
    std::string buffer;
    buffer.reserve(larguraASCII * alturaASCII * 32); // pega tudo e lança tudo no mesmo tempo

    int lastR = -1, lastG = -1, lastB = -1;

    for (int y = 0; y < alturaASCII; y++)
    {
        int py = mapY[y];

        for (int x = 0; x < larguraASCII; x++)
        {
            int px = mapX[x];
            int i = (py * w + px) * 4;

            int r = img[i];
            int g = img[i + 1];
            int b = img[i + 2];
            int a = img[i + 3];

            if (a < 50)
            {
                buffer += ' ';
                continue;
            }

            if (r != lastR || g != lastG || b != lastB)
            {
                buffer += "\033[38;2;";
                buffer += std::to_string(r);
                buffer += ';';
                buffer += std::to_string(g);
                buffer += ';';
                buffer += std::to_string(b);
                buffer += 'm';

                lastR = r;
                lastG = g;
                lastB = b;
            }

            int gray = (r + g + b) / 3;
            int idx = (gray * (escalaTam - 1)) >> 8;

            buffer += escala[idx];
        }

        buffer += "\033[0m\n";
        lastR = lastG = lastB = -1;
    }

    std::cout << buffer;
    stbi_image_free(img);
}

void image_char_SET(const std::string &what)
{
    if (what == "true")
    {
        IMAGE_CHAR_OPT = true;
        SalvarConfig("image_char.cfg", "true");
    }
    else if (what == "false")
    {
        IMAGE_CHAR_OPT = false;
        SalvarConfig("image_char.cfg", "false");
    }
}

void image_char_CHECK()
{
    std::string val = LerConfig("image_char.cfg");

    if (val == "true")
    {
        IMAGE_CHAR_OPT = true;
    }
    else
    {
        IMAGE_CHAR_OPT = false;
    }
}

void apelido_SET(const std::string &what)
{
    if (what == "mudar")
    {
        std::string salvarapelido;
        PRINT_SYS("Novo apelido: ", false);
        getline(std::cin, salvarapelido);

        _APELIDO = salvarapelido;
        SalvarConfig("_APELIDO.cfg", salvarapelido);
    }
    else if (what == "reiniciar")
    {
        _APELIDO = _APELIDO_WINDOWS;
        SalvarConfig("_APELIDO.cfg", _APELIDO_WINDOWS);
    }
    else if (what == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro no sinalizador", true);
    }
}

void apelido_CHECK()
{
    _APELIDO = LerConfig("_APELIDO.cfg");
}

void startdir_SET(const std::string &what)
{
    if (what == "mudar")
    {
        std::string dir;

        PRINT_SYS("Digite o diretório inicial: ", false);
        getline(std::cin, dir);

        dir = trim(dir);

        if (!DirectoryExists(dir))
        {
            PRINT_ERROR("Erro, diretório não existe", true);
            return;
        }

        if (ChangeDirectory(dir))
        {
            SalvarConfig("start_dir.cfg", dir);
            PRINT_BLUE("Diretório inicial salvo!", true);
        }
    }
    else if (what == "reiniciar")
    {
        DeletarConfig("start_dir.cfg");
        PRINT_BLUE("Diretório inicial resetado para Desktop", true);
    }
    else if (what == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro no sinalizador", true);
    }
}

std::string startdir_CHECK()
{
    return LerConfig("start_dir.cfg");
}

void discord_rpc_SET(const std::string &what)
{
    if (what == "true")
    {
        _DISCORD_RPC_VALUE = true;
        SalvarConfig("_DISCORD_RPC.cfg", "true");
        iniciarDiscordRPC();
    }
    else if (what == "false")
    {
        _DISCORD_RPC_VALUE = false;
        SalvarConfig("_DISCORD_RPC.cfg", "false");
        if (discord_disponivel)
        {
            Discord_Shutdown();
            discord_disponivel = false;
        }
    }

    else if (what == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro no sinalizador", true);
    }
}

void discord_rpc_CHECK()
{
    std::string val = LerConfig("_DISCORD_RPC.cfg");

    if (val == "true")
    {
        _DISCORD_RPC_VALUE = true;
    }
    else if (val == "false")
    {
        _DISCORD_RPC_VALUE = false;
    }
    else
    {
        _DISCORD_RPC_VALUE = true;
    }
}

void prompt_color_SET(const std::string &what)
{
    if (what == "add")
    {
        _PROMPT_COLOR_VALUE = true;
        SalvarConfig("_PROMPT_COLOR.cfg", "true");
    }
    else if (what == "remove")
    {
        _PROMPT_COLOR_VALUE = false;
        SalvarConfig("_PROMPT_COLOR.cfg", "false");
    }
    else if (what == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro no sinalizador", true);
    }
}

void prompt_color_CHECK()
{
    std::string val = LerConfig("_PROMPT_COLOR.cfg");

    if (val == "true")
    {
        _PROMPT_COLOR_VALUE = true;
    }
    else if (val == "false")
    {
        _PROMPT_COLOR_VALUE = false;
    }
    else
    {
        _PROMPT_COLOR_VALUE = true;
    }
}

void sounds_SET(const std::string &what)
{
    if (what == "true")
    {
        _SOUNDS_VALUE = true;
        SalvarConfig("_SOUNDS.cfg", "true");
    }
    else if (what == "false")
    {
        _SOUNDS_VALUE = false;
        SalvarConfig("_SOUNDS.cfg", "false");
    }
    else if (what == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro no sinalizador", true);
    }
}

void sounds_CHECK()
{
    std::string val = LerConfig("_SOUNDS.cfg");

    if (val == "true")
    {
        _SOUNDS_VALUE = true;
    }
    else if (val == "false")
    {
        _SOUNDS_VALUE = false;
    }
    else
    {
        _SOUNDS_VALUE = true;
    }
}

void CONFIGS_ABA(const std::string &opt)
{
    if (opt == "image_char")
    {
        MOPTS::MenuOption image_char_opts[] = {
            {"Ativar Image char", "true", image_char_SET},
            {"Desativar image char", "false", image_char_SET},
            {"Voltar", "voltar", image_char_SET},
        };
        MOPTS::ShowMenu("Image char", image_char_opts, "> ", "");
    }
    else if (opt == "apelido")
    {
        MOPTS::MenuOption image_char_opts[] = {
            {"Mudar apelido", "mudar", apelido_SET},
            {"Reiniciar apelido", "reiniciar", apelido_SET},
            {"Voltar", "voltar", apelido_SET},
        };
        MOPTS::ShowMenu("Apelido", image_char_opts, "> ", "");
    }
    else if (opt == "start_dir")
    {
        MOPTS::MenuOption startdir_opts[] = {
            {"Definir diretório inicial", "mudar", startdir_SET},
            {"Resetar para Desktop", "reiniciar", startdir_SET},
            {"Voltar", "voltar", startdir_SET},
        };
        MOPTS::ShowMenu("Diretório inicial", startdir_opts, "> ", "");
    }
    else if (opt == "discord_rpc")
    {
        MOPTS::MenuOption discordrpc_opts[] = {
            {"Ativar Discord RPC", "true", discord_rpc_SET},
            {"Desativar Discord RPC", "false", discord_rpc_SET},
            {"Voltar", "voltar", discord_rpc_SET},
        };
        MOPTS::ShowMenu("Discord RPC", discordrpc_opts, "> ", "");
    }
    else if (opt == "system_path")
    {
        MOPTS::MenuOption path_opts[] = {
            {"Adicionar ao PATH do sistema", "add", system_path_SET},
            {"Remover do PATH do sistema", "remove", system_path_SET},
            {"Voltar", "voltar", system_path_SET},
        };

        MOPTS::ShowMenu("PATH do sistema", path_opts, "> ", "");
    }
    else if (opt == "prompt_color")
    {
        MOPTS::MenuOption path_opts[] = {
            {"Adicionar cor no prompt", "add", prompt_color_SET},
            {"Remover cor no prompt", "remove", prompt_color_SET},
            {"Voltar", "voltar", prompt_color_SET},
        };

        MOPTS::ShowMenu("PATH do sistema", path_opts, "> ", "");
    }
    else if (opt == "sounds")
    {
        MOPTS::MenuOption path_opts[] = {
            {"Ativar sons", "true", sounds_SET},
            {"Desativar sons", "false", sounds_SET},
            {"Voltar", "voltar", sounds_SET},
        };

        MOPTS::ShowMenu("PATH do sistema", path_opts, "> ", "");
    }

    else if (opt == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro na sinalização das configurações", true);
    }
}

std::wstring GetDesktopPath()
{
    wchar_t wpath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, wpath)))
    {
        return std::wstring(wpath);
    }
    return L"";
}

bool IrParaDesktop()
{
    std::wstring desktop = GetDesktopPath();
    if (desktop.empty()) 
    {
        PRINT_ERROR("Não foi possível localizar a área de trabalho", true);
        return false;
    }
    return SetCurrentDirectoryW(desktop.c_str());
}

void MostrarArmazenamento(const char *drive = "C:\\")
{
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalNumberOfBytes;
    ULARGE_INTEGER totalNumberOfFreeBytes;

    if (GetDiskFreeSpaceExA(
            drive,
            &freeBytesAvailable,
            &totalNumberOfBytes,
            &totalNumberOfFreeBytes))
    {
        double KB = 1024.0;
        double MB = KB * 1024.0;
        double GB = MB * 1024.0;

        PRINT_SYS("Total:", true);
        PRINT_SYS("KB: " + std::to_string(totalNumberOfBytes.QuadPart / KB), true);
        PRINT_SYS("MB: " + std::to_string(totalNumberOfBytes.QuadPart / MB), true);
        PRINT_SYS("GB: " + std::to_string(totalNumberOfBytes.QuadPart / GB), true);

        PRINT_SYS("", true);

        PRINT_SYS("Livre:", true);
        PRINT_SYS("KB: " + std::to_string(totalNumberOfFreeBytes.QuadPart / KB), true);
        PRINT_SYS("MB: " + std::to_string(totalNumberOfFreeBytes.QuadPart / MB), true);
        PRINT_SYS("GB: " + std::to_string(totalNumberOfFreeBytes.QuadPart / GB), true);
    }
    else
    {
        PRINT_ERROR("Erro ao obter informações do disco", true);
    }
}

std::string RemoverComentario(const std::string &linha)
{
    size_t pos = linha.find("#;");
    if (pos != std::string::npos)
    {
        return trim(linha.substr(0, pos));
    }
    return trim(linha);
}

bool RUN_SCRIPT_FILE(const std::string &arquivo);

void OPEN(const std::string &caminhoOuURL) // abre
{
    if (caminhoOuURL.empty())
    {
        PRINT_ERROR("Erro caminho ou URL vazio", true);
        return;
    }

    std::string pathFixed = caminhoOuURL;
    for (size_t i = 0; i < pathFixed.size(); ++i)
    {
        if (pathFixed[i] == '\\')
        {
            pathFixed.insert(i, "\\");
            ++i;
        }
    }

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, pathFixed.c_str(), -1, nullptr, 0);
    std::wstring wCaminho(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, pathFixed.c_str(), -1, &wCaminho[0], size_needed);

    HINSTANCE result = ShellExecuteW(
        NULL,
        L"open",
        wCaminho.c_str(),
        NULL,
        NULL,
        SW_SHOWNORMAL);

    if ((INT_PTR)result <= 32)
    {
        PRINT_ERROR("Erro ao abrir", true);
    }
}

void COMANDOS_EXEC(const std::string &comandoOriginal) // TODOS os comandos
{
    std::string comandoA = trim(comandoOriginal);

    // separa comando + argumento
    size_t space = comandoA.find(' ');

    std::string cmdWord;
    std::string cmdArg;

    if (space != std::string::npos)
    {
        cmdWord = comandoA.substr(0, space);
        cmdArg = comandoA.substr(space + 1);
    }
    else
    {
        cmdWord = comandoA;
    }

    std::string comando = toLower(cmdWord);
    if (comando == "define") // salva uma variavel
    {
        _DEFINE = cmdArg;
    }
    else if (comando == "#define") // salva uma variavel "permanente"
    {
        _DEFINE = cmdArg;
        SalvarConfig("H_DEFINE_.cfg", cmdArg);
    }
    else if (comando == "&define") // deleta o valor da variavel salva permanentemente e limpa o valor da variavel normal
    {
        _DEFINE = "";
        DeletarConfig("H_DEFINE_.cfg");
    }
    else if (comando == "$define") // mostra oque salvou na variavel
    {
        PRINT_BLUE(_DEFINE, true);
    }
    else if (comando == "terminalinfo" || comando == "cmdinfo") // mostra as informacoes do terminal
    {
        PRINT_BLUE("Versão: " + _VERSION, true);
    }
    else if (comando == "test") // so de teste msm
    {
        PRINT_BLUE("TEST", true);
    }
    else if (comando == "exit") // sai do terminal
    {
        exited = true;
    }
    else if (comando == "exitf") // sai do terminal FORÇADO
    {
        Discord_Shutdown();
        exit(0);
        exited = true;
    }
    else if (comando == "exec")
    {
        std::string caminho = _DEFINE;
        if (caminho.empty())
        {
            PRINT_ERROR("Nenhum arquivo especificado", true);
            return;
        }

        // Confirma se o arquivo existe
        int size = MultiByteToWideChar(CP_UTF8, 0, caminho.c_str(), -1, nullptr, 0);
        std::wstring wCaminho(size, 0);
        MultiByteToWideChar(CP_UTF8, 0, caminho.c_str(), -1, &wCaminho[0], size);

        DWORD attr = GetFileAttributesW(wCaminho.c_str());
        if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
        {
            PRINT_ERROR("Erro Arquivo não encontrado ou é uma pasta", true);
            return;
        }

        HINSTANCE result = ShellExecuteW(
            NULL,
            L"open",
            wCaminho.c_str(),
            NULL,
            NULL,
            SW_SHOWNORMAL);

        if ((INT_PTR)result <= 32)
        {
            PRINT_ERROR("Erro ao abrir arquivo (código " + std::to_string((INT_PTR)result) + ")", true);
        }
    }

    else if (comando == "configs") // coisa lina, bonita, cheirosa e maravilhosa
    {
        MOPTS::MenuOption configs_opts[] = {
            {"Images chars", "image_char", CONFIGS_ABA},
            {"Apelido", "apelido", CONFIGS_ABA},
            {"Diretório inicial", "start_dir", CONFIGS_ABA},
            {"Discord RPC", "discord_rpc", CONFIGS_ABA},
            {"Cor do prompt", "prompt_color", CONFIGS_ABA},
            {"PATH do sistema", "system_path", CONFIGS_ABA},
            {"Sons", "sounds", CONFIGS_ABA},
            {"Voltar", "voltar", CONFIGS_ABA},
        };

        MOPTS::ShowMenu("Configurações", configs_opts, "> ", "");
    }
    else if (comando == "image") // manda uma imagem, absurdo
    {
        ImagemParaASCII(_DEFINE, 100);
    }
    else if (comando == "clear_cmd") // limpa tudo oque o terminal fez de configuração
    {
        MOPTS::MenuOption formatar_cmd_opts[] = {
            "Sim", "lp", [](const std::string &)
            {
                PRINT_SYS("\nLimpando configurações...", true);

                system_path_SET("remove");

                Discord_Shutdown();
                discord_disponivel = false;
                _DISCORD_RPC_VALUE = false;

                std::string pasta = GetAppFolder();
                WIN32_FIND_DATAA data;
                HANDLE hFind = FindFirstFileA((pasta + "\\*").c_str(), &data);

                if (hFind != INVALID_HANDLE_VALUE)
                {
                    do
                    {
                        std::string nome = data.cFileName;
                        if (nome == "." || nome == "..")
                        {
                            continue;
                        }

                        std::string caminho = pasta + "\\" + nome;

                        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        {
                            RemoveDirectoryA(caminho.c_str());
                        }
                        else
                        {
                            DeleteFileA(caminho.c_str());
                        }

                    } while (FindNextFileA(hFind, &data));

                    FindClose(hFind);
                }

                _DEFINE.clear();
                IMAGE_CHAR_OPT = false;
                _APELIDO = _APELIDO_WINDOWS;
                _PROMPT_COLOR_VALUE = true;

                PRINT_BLUE("Tudo foi resetado com sucesso", true);
                Sleep(500);
                REOPEN();
            },
            {"Não", "nl", [](const std::string &)
             {
                 // nada
             }}};

        MOPTS::ShowMenu(
            "isso apagará TODAS as configs do TerminalMax\nTem certeza?",
            formatar_cmd_opts,
            "> ",
            "");
    }

    else if (comando == "$apelido" || comando == "$apelidos")
    {
        PRINT_SYS(_APELIDO, true);
    }
    else if (comando == "version")
    {
        PRINT_SYS(_VERSION, true);
    }
    else if (comando == "sayln")
    {
        pularlinhaw = false;
        std::cout << _DEFINE << std::endl;
    }
    else if (comando == "say")
    {
        pularlinhaw = true;
        std::cout << _DEFINE;
    }
    else if (comando == "cls" || comando == "clear")
    {
        CLEAR_TERMINAL();
    }
    else if (comando == "local")
    {
        if (!_DEFINE.empty())
        {
            ChangeDirectory(_DEFINE);
        }
    }
    else if (comando == "$local")
    {
        PRINT_SYS(GetCurrentPath(), true);
    }
    else if (comando == "mkfile" || comando == "newfile") // cria um arquivo
    {
        if (!_DEFINE.empty())
        {
            CriarArquivo(_DEFINE);
        }
    }
    else if (comando == "mkdir" || comando == "newfolder") // cria uma pasta
    {
        if (!_DEFINE.empty())
        {
            CriarPasta(_DEFINE);
        }
    }
    else if (comando == "rmfile" || comando == "delfile") // deleta um arquivo
    {
        if (!_DEFINE.empty())
        {
            DeletarArquivo(_DEFINE);
        }
    }
    else if (comando == "rmdir" || comando == "delfolder") // deleta uma pasta
    {
        if (!_DEFINE.empty())
        {
            DeletarPasta(_DEFINE);
        }
    }
    else if (comando == "ls" || comando == "dir" || comando == "$") // lista todos os bagui do diretorio
    {
        ListarArquivos(_DEFINE);
    }
    else if (comando == "to_desktop")
    {
        ChangeDirectory(WideToUTF8(GetDesktopPath()), false);
    }
    else if (comando == "check_storage" || comando == "$storage")
    {
        MostrarArmazenamento();
    }
    else if (comando == "help")
    {
        HELP_CMD();
    }
    else if (comando == "run")
    {
        if (!_DEFINE.empty())
        {
            RUN_SCRIPT_FILE(_DEFINE);
        }
        else
        {
            PRINT_ERROR("Erro, script não encontrado ou vazio", true);
        }
    }
    else if (comando == "credits")
    {
        PRINT_BLUE("Criador do terminal : ThiagoBel", true);
        PRINT_BLUE("Som da intro        : PixaBay - MagiaZ", true);
        PRINT_BLUE("Som do beep         : PixaBay - freesound_community", true);
    }
    else if (comando == ">")
    {
        system(_DEFINE.c_str());
    }
    else if (comando == "check_admin" || comando == "$admin")
    {
        if (EhAdmin())
        {
            PRINT_SYS("true", true);
        }
        else
        {
            PRINT_SYS("false", true);
        }
    }
    else if (comando == "reopen")
    {
        REOPEN();
    }
    else if (comando == "beep")
    {
        PLAY_SOUND("beep");
    }
    else if (comando == "time")
    {
        SYSTEMTIME st;
        GetLocalTime(&st);

        PRINT_SYS(
            (st.wHour < 10 ? "0" : "") + std::to_string(st.wHour) + ":" +
                (st.wMinute < 10 ? "0" : "") + std::to_string(st.wMinute) + ":" +
                (st.wSecond < 10 ? "0" : "") + std::to_string(st.wSecond),
            true);
    }
    else if (comando == "date")
    {
        SYSTEMTIME st;
        GetLocalTime(&st);

        PRINT_SYS(
            (st.wDay < 10 ? "0" : "") + std::to_string(st.wDay) + "/" +
                (st.wMonth < 10 ? "0" : "") + std::to_string(st.wMonth) + "/" +
                std::to_string(st.wYear),
            true);
    }

    else if (comando == "roll")
    {
        int max = 6;

        if (!_DEFINE.empty())
        {
            try
            {
                max = std::stoi(_DEFINE);
                if (max <= 0)
                    max = 6;
            }
            catch (...)
            {
                max = 6;
            }
        }

        srand((unsigned int)time(NULL));
        int result = (rand() % max) + 1;

        PRINT_BLUE(std::to_string(result), true);
    }
    else if (comando == "kill")
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Erro, defina um processo ou PID", true);
            return;
        }

        std::string cmd = "taskkill /F ";

        bool isPID = std::all_of(_DEFINE.begin(), _DEFINE.end(), ::isdigit);

        if (isPID)
            cmd += "/PID " + _DEFINE;
        else
            cmd += "/IM " + _DEFINE;

        system(cmd.c_str());
    }
    else if (comando == "tasklist" || comando == "tasks" || comando == "$tasks")
    {
        char buffer[128];
        std::string result = "";

        FILE *pipe = _popen("tasklist", "r");
        if (!pipe)
        {
            PRINT_ERROR("Erro ao listar tarefas", true);
            return;
        }

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }

        _pclose(pipe);

        PRINT_SYS(result, true);
    }
    else if (comando == "calcc") // calcula uma expressão
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Erro, defina uma expressão", true);
            return;
        }

        try
        {
            int resultado = calcularExpressao(_DEFINE);
            PRINT_BLUE(std::to_string(resultado), true);
        }
        catch (const std::exception &e)
        {
            PRINT_ERROR("Erro ao calcular a expressão", true);
        }
    }
    else if (comando == "notify")
    {
        if (_DEFINE.empty())
        {
            return;
        }
        std::vector<std::string> partes;
        std::string temp = _DEFINE;
        size_t pos = 0;
        while ((pos = temp.find("//")) != std::string::npos)
        {
            std::string token = temp.substr(0, pos);
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            partes.push_back(token);
            temp.erase(0, pos + 2);
        }

        temp.erase(0, temp.find_first_not_of(" \t"));
        temp.erase(temp.find_last_not_of(" \t") + 1);
        partes.push_back(temp);

        std::string mensagem = partes.size() > 0 ? partes[0] : "";
        std::string titulo = partes.size() > 1 ? partes[1] : "Aviso";
        std::string iconStr = partes.size() > 2 ? partes[2] : "info";
        std::string buttonsStr = partes.size() > 3 ? partes[3] : "ok";

        notify::NotifyIcon icon = notify::NotifyIcon::Information;
        std::transform(iconStr.begin(), iconStr.end(), iconStr.begin(), ::tolower);
        if (iconStr == "info" || iconStr == "information")
        {
            icon = notify::NotifyIcon::Information;
        }
        else if (iconStr == "warning")
        {
            icon = notify::NotifyIcon::Warning;
        }
        else if (iconStr == "error")
        {
            icon = notify::NotifyIcon::Error;
        }
        else if (iconStr == "question")
        {
            icon = notify::NotifyIcon::Question;
        }
        else
        {
            icon = notify::NotifyIcon::None;
        }
        notify::NotifyButtons buttons = notify::NotifyButtons::Ok;
        std::transform(buttonsStr.begin(), buttonsStr.end(), buttonsStr.begin(), ::tolower);
        if (buttonsStr == "ok")
        {
            buttons = notify::NotifyButtons::Ok;
        }
        else if (buttonsStr == "okcancel")
        {
            buttons = notify::NotifyButtons::OkCancel;
        }
        else if (buttonsStr == "yesno")
        {
            buttons = notify::NotifyButtons::YesNo;
        }
        else if (buttonsStr == "yesnocancel")
        {
            buttons = notify::NotifyButtons::YesNoCancel;
        }
        else if (buttonsStr == "retrycancel")
        {
            buttons = notify::NotifyButtons::RetryCancel;
        }

        notify::notify(mensagem.c_str(), titulo.c_str(), icon, buttons);
    }
    else if (comando == "power")
    {
        if (_DEFINE == "off")
        {
            system("shutdown /s /t 0");
        }
        else if (_DEFINE == "reset")
        {
            system("shutdown /r /t 0");
        }
        else if (_DEFINE == "cancel")
        {
            system("shutdown /a");
        }
        else
        {
            PRINT_ERROR("Erro, use apenas 'off', 'cancel' ou 'reset'", true);
        }
    }
    else if (comando == "upper")
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Nada para converter", true);
            return;
        }

        _DEFINE = TO_UPPER(_DEFINE);
    }
    else if (comando == "lower")
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Nada para converter", true);
            return;
        }

        _DEFINE = TO_LOWER(_DEFINE);
    }
    else if (comando == "capitalize")
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Nada para capitalizar", true);
            return;
        }

        _DEFINE = CAPITALIZE(_DEFINE);
    }
    else if (comando == "len")
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Nada para medir", true);
            return;
        }

        PRINT_BLUE(std::to_string(_DEFINE.length()), true);
    }
    else if (comando == "open")
    {
        if (_DEFINE.empty())
        {
            PRINT_ERROR("Nada definido para abrir", true);
            return;
        }

        OPEN(_DEFINE);
    }

    else if (comando == "takefood")
    {
        std::vector<std::string> comidas = {
            "🍎", "🍌", "🍕", "🍔", "🍟",
            "🌭", "🍣", "🍩", "🍪", "🍫",
            "🍿", "🥗", "🥩", "🍜", "🍝"};

        std::uniform_int_distribution<> distrib(0, comidas.size() - 1);
        int i = distrib(gen);
        PRINT_SYS(comidas[i], true);
    }
    else // ou da erro ou executa qualquer ngc no path
    {
        std::string cmd = comandoOriginal;
        if (!cmd.empty())
        {
            STARTUPINFOA si = {sizeof(si)};
            PROCESS_INFORMATION pi;

            char cmdBuffer[1024];
            strncpy(cmdBuffer, cmd.c_str(), sizeof(cmdBuffer) - 1);
            cmdBuffer[sizeof(cmdBuffer) - 1] = '\0';

            if (!CreateProcessA(NULL, cmdBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
            {
                // DWORD err = GetLastError();
                PRINT_ERROR("Comando não reconhecido", true);
            }
            else
            {
                WaitForSingleObject(pi.hProcess, INFINITE);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
        }
    }
}

void EXEC_MULTIPLE(const std::string &linha)
{
    size_t pos = 0;
    size_t nextAnd, nextDelay;

    std::string restante = RemoverComentario(linha);

    while (true)
    {
        nextAnd = restante.find(AND_OPERATOR);
        nextDelay = restante.find(DELAY_OPERATOR);

        size_t next;
        bool isDelay = false;

        if (nextAnd == std::string::npos && nextDelay == std::string::npos)
        {
            std::string cmd = trim(restante);
            if (!cmd.empty())
            {
                COMANDOS_EXEC(cmd);
            }
            break;
        }

        if (nextDelay != std::string::npos &&
            (nextAnd == std::string::npos || nextDelay < nextAnd))
        {
            next = nextDelay;
            isDelay = true;
        }
        else
        {
            next = nextAnd;
        }

        std::string cmd = trim(restante.substr(0, next));
        if (!cmd.empty())
        {
            COMANDOS_EXEC(cmd);
        }

        if (isDelay)
        {
            std::string resto = restante.substr(next + DELAY_OPERATOR.length());
            size_t spacePos = resto.find(' ');
            std::string delayStr;
            if (spacePos != std::string::npos)
            {
                delayStr = resto.substr(0, spacePos);
            }
            else
            {
                delayStr = resto;
            }

            int delay_ms = 1000; // padrão
            if (!delayStr.empty())
            {
                try
                {
                    delay_ms = std::stoi(delayStr);
                }
                catch (...)
                {
                    PRINT_ERROR("Valor de delay inválido, use @@@@VALOR", true);
                }
            }

            Sleep(delay_ms);
        }

        if (isDelay)
        {
            std::string resto = restante.substr(next + DELAY_OPERATOR.length());
            size_t spacePos = resto.find(' ');
            if (spacePos != std::string::npos)
            {
                restante.erase(0, next + DELAY_OPERATOR.length() + spacePos);
            }
            else
            {
                restante.erase(0, restante.length());
            }
        }
        else
        {
            restante.erase(0, next + AND_OPERATOR.length());
        }

        restante = trim(restante);
    }
}

bool RUN_SCRIPT_FILE(const std::string &arquivo)
{
    std::wstring wpath = UTF8ToWide(arquivo);

    FILE *f = _wfopen(wpath.c_str(), L"r");

    if (!f)
    {
        wpath = UTF8ToWide(arquivo + ".trmax"); // tenta com .trmax
        f = _wfopen(wpath.c_str(), L"r");
    }

    if (!f)
    {
        PRINT_ERROR("Erro, não foi possível abrir o arquivo", true);
        return false;
    }

    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), f))
    {
        std::string linha = buffer;
        linha = trim(linha);

        if (!linha.empty())
        {
            EXEC_MULTIPLE(linha);
        }
    }

    fclose(f);
    return true;
}

int main(int argc, char *argv[])
{
    enableANSI();
    SetConsoleTitleA("Terminal MAX");
    bool ranFromArgs = false;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--version")
        {
            PRINT_SYS(_VERSION, true);
            return 0;
        }
        else if (arg == "--exec")
        {
            if (i + 1 < argc)
            {
                EXEC_MULTIPLE(argv[i + 1]);
                ranFromArgs = true;
                break;
            }
            else
            {
                PRINT_ERROR("Erro, --exec precisa e um comando pra funcionar", true);
                return 1;
            }
        }
        else if (arg == "--run")
        {
            if (i + 1 < argc)
            {
                if (RUN_SCRIPT_FILE(argv[i + 1]))
                {
                    ranFromArgs = true;
                }
                break;
            }

            else
            {
                PRINT_ERROR("Erro, --run precisa de um arquivo", true);
                return 1;
            }
        }
    }

    if (ranFromArgs)
    {
        return 0;
    }

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    discord_rpc_CHECK();
    std::string startDir = startdir_CHECK();

    if (!startDir.empty())
    {
        if (!ChangeDirectory(startDir, false))
        {
            ChangeDirectory(WideToUTF8(GetDesktopPath()), false);
        }
    }
    else
    {
        ChangeDirectory(WideToUTF8(GetDesktopPath()), false);
    }

    char user[UNLEN + 1];
    DWORD size = UNLEN + 1;

    GetUserNameA(user, &size);
    _APELIDO_WINDOWS = user;
    MOPTS::clear_opts = false;
    MOPTS::color = false;
    MOPTS::all_color_line = false;
    sounds_CHECK();
    apelido_CHECK();
    image_char_CHECK();
    _DEFINE = LerConfig("H_DEFINE_.cfg"); // salva uma variavel pro terminal
    if (_DISCORD_RPC_VALUE)
    {
        iniciarDiscordRPC();
        discord_disponivel = true;
    }
    ASCII_CALL();
    PRINT_SYS("Olá " + CAPITALIZE(_APELIDO) + "!", true);
    prompt_color_CHECK();
    PLAY_SOUND("intro");
    while (true)
    {
        SetConsoleTitleA("Terminal MAX");
        if (exited == true)
        {
            Discord_Shutdown();
            break;
        }
        if (pularlinhaw == true)
        {
            std::cout << "\n";
            pularlinhaw = false;
        }
        if (_PROMPT_COLOR_VALUE == true) // ve se pode usar cores
        {
            std::cout << "[" << icolor::blue() << "M" << icolor::finished() << icolor::white() << "A" << icolor::finished() << icolor::blue() << "X" << icolor::finished() << icolor::blue() << icolor::finished() << icolor::neon_green() << "@" << icolor::finished() << icolor::gray_10() << GetCurrentPath() << icolor::finished() << "]> ";
        }
        else
        {
            std::cout << "[MAX@" << GetCurrentPath() << "]> ";
        }

        std::string cmd;        // salva oq usuario digitou
        getline(std::cin, cmd); // input

        EXEC_MULTIPLE(cmd); // executa todos os comandos usados
    }
    Discord_Shutdown();
    return 0; // so retorna que o programa deu tudo certo
} // cabou