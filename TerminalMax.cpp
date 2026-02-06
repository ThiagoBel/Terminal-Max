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
#define STB_IMAGE_IMPLEMENTATION
#undef UNICODE
#include <iostream>
#include <vector>
#include <algorithm>
#include <direct.h>
#include <windows.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <locale>
#include <shlobj.h>
#include <string>
#include <cstdio>
#include <Lmcons.h>
#include <fcntl.h>
#include <io.h>

#include "configs/headers/MOPTS.h"
#include "configs/headers/icolor.hpp"
#include "configs/headers/stb_image.h"
#include "configs/discord/discord_rpc.h"
std::string _DEFINE = "";          // negocio definido
std::string _VERSION = "1.0.0";    // versao do terminal
std::string AND_OPERATOR = "&&&&"; // o ngc de adicao de comandos
bool exited = false;               // ve se o usuario quer sair
bool IMAGE_CHAR_OPT = false;       // bagulho de otimização de imagens
bool discord_disponivel = false;   // ve se o discord tá aberto pra usar o RPC
bool _DISCORD_RPC_VALUE = true;    // ve o bagui do rpc do discord
std::string _APELIDO = "";         // apelido do usuario
std::string _APELIDO_WINDOWS = ""; // apelido do WINDOWS do usuario
DiscordEventHandlers handlers;
DiscordRichPresence presence;

void iniciarDiscordRPC() // RPC do discord
{
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(
        "1469464608749256805", // Application ID
        &handlers,
        1,
        NULL);

    memset(&presence, 0, sizeof(presence));

    presence.details = "Terminal MAX";
    presence.largeImageKey = "maxlogo";
    presence.largeImageText = "Terminal MAX";
    presence.startTimestamp = time(NULL);

    Discord_UpdatePresence(&presence);

    discord_disponivel = true;
}

void HELP_CMD()
{
    std::cout << "TerminalMax v" << _VERSION << "\n\n";

    std::cout << "define <valor>      - define valor temporário\n";
    std::cout << "#define <valor>     - define valor permanente\n";
    std::cout << "&define             - limpa valor permanente\n";
    std::cout << "$define             - mostra valor definido\n";
    std::cout << "terminalinfo        - informações do terminal\n";
    std::cout << "cmdinfo             - alias de terminalinfo\n";
    std::cout << "version             - mostra versão\n";
    std::cout << "exit                - sai do terminal\n";
    std::cout << "exitf               - saída forçada\n";
    std::cout << "cls / clear         - limpa a tela\n";
    std::cout << "help                - mostra ajuda\n";
    std::cout << "test                - comando de teste\n";
    std::cout << "exec                - executa programa definido\n";
    std::cout << "run                 - executa script (.trmax)\n";
    std::cout << "say                 - imprime valor definido\n";
    std::cout << "mkfile / newfile    - cria arquivo\n";
    std::cout << "mkdir / newfolder   - cria pasta\n";
    std::cout << "rmfile / delfile    - deleta arquivo\n";
    std::cout << "rmdir / delfolder   - deleta pasta\n";
    std::cout << "ls / dir / $        - lista arquivos\n";
    std::cout << "local               - muda para diretório definido\n";
    std::cout << "$local              - mostra diretório atual\n";
    std::cout << "to_desktop          - vai para Desktop\n";
    std::cout << "check_storage       - mostra armazenamento\n";
    std::cout << "$storage            - alias de check_storage\n";
    std::cout << "$apelido            - mostra apelido\n";
    std::cout << "$apelidos           - alias de $apelido\n";
    std::cout << "image               - imagem -> ASCII\n";
    std::cout << "configs             - abre menu de configs\n";
    std::cout << "credits             - mostra todos os créditos\n";
    std::cout << "clear_cmd           - limpa TODAS configs\n\n\n";

    std::cout << "--version           - mostra versão do TerminalMax\n";
    std::cout << "--exec <cmd>        - executa comando direto\n";
    std::cout << "--run <arquivo>     - executa script\n";
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
        conteudo += linha;

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
        Discord_Shutdown();
    }
}

void discord_rpc_CHECK()
{
    std::string val = LerConfig("_DISCORD_RPC.cfg");

    if (val == "true")
    {
        _DISCORD_RPC_VALUE = true;
    }
    else
    {
        _DISCORD_RPC_VALUE = false;
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
    else if (opt == "voltar")
    {
        // nada
    }
    else
    {
        PRINT_ERROR("Erro na sinalização das configurações", true);
    }
}

std::string GetDesktopPath()
{
    char path[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path);
    return std::string(path);
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

bool RUN_SCRIPT_FILE(const std::string &arquivo);

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
    else if (comando == "exec") // executa um aplicativo
    {
        STARTUPINFOA si = {sizeof(si)};
        PROCESS_INFORMATION pi;

        char cmd[512];
        strncpy(cmd, _DEFINE.c_str(), sizeof(cmd) - 1);
        cmd[sizeof(cmd) - 1] = '\0';

        if (CreateProcessA(
                NULL,
                cmd,
                NULL, NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi))
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }
    else if (comando == "configs") // coisa lina, bonita, cheirosa e maravilhosa
    {
        MOPTS::MenuOption configs_opts[] = {
            {"Images chars", "image_char", CONFIGS_ABA},     // Otimização das imagens
            {"Apelido", "apelido", CONFIGS_ABA},             // Apelidos (Ao inves do nome de usuario do windows)
            {"Diretório inicial", "start_dir", CONFIGS_ABA}, // diretorio que inicia o terminal
            {"Discord RPC", "discord_rpc", CONFIGS_ABA},     // discord rpc (mostra que tu ta "jogando" o terminal)
            {"Voltar", "voltar", CONFIGS_ABA},               // sai
        };

        MOPTS::ShowMenu("Configurações", configs_opts, "> ", "");
    }
    else if (comando == "image") // manda uma imagem, absurdo
    {
        ImagemParaASCII(_DEFINE, 100);
    }
    else if (comando == "clear_cmd")
    {
        MOPTS::MenuOption formatar_cmd_opts[] = {

            {"SIM — limpar tudo", "lp", [](const std::string &)
             {
                 PRINT_SYS("\nLimpando configurações...", true);

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

                 _DEFINE = "";
                 IMAGE_CHAR_OPT = false;
                 _APELIDO = _APELIDO_WINDOWS;

                 PRINT_BLUE("Sucesso", true);
                 PRINT_SYS("Reinicie o terminal para aplicar tudo.", true);
             }},

            {"Cancelar", "cn", [](const std::string &)
             {
                 PRINT_SYS("Cancelado", true);
             }},
        };

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
    else if (comando == "say")
    {
        std::cout << _DEFINE << std::endl;
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
        ChangeDirectory(GetDesktopPath());
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
        PRINT_BLUE("ThiagoBel", true);
    }
    else
    {
        PRINT_ERROR("Erro, comando desconhecido", true); // chora
    }
}

void EXEC_MULTIPLE(const std::string &linha) // usa o negocio de adicao de comandos
{
    size_t start = 0;
    size_t pos;

    while ((pos = linha.find(AND_OPERATOR, start)) != std::string::npos) // loop pra rodar todos os comandos da linha
    {
        std::string cmd = trim(linha.substr(start, pos - start));

        if (!cmd.empty())
        {
            COMANDOS_EXEC(cmd);
        }

        start = pos + AND_OPERATOR.length();
    }

    std::string last = trim(linha.substr(start));

    if (!last.empty())
    {
        COMANDOS_EXEC(last);
    }
}

bool RUN_SCRIPT_FILE(const std::string &arquivo)
{
    std::ifstream file(arquivo);

    if (!file.is_open())
    {
        file.open(arquivo + ".trmax");
    }

    if (!file.is_open())
    {
        PRINT_ERROR("Erro, não foi possível abrir o arquivo", true);
        return false;
    }

    std::string linha;

    while (std::getline(file, linha))
    {
        linha = trim(linha);

        if (!linha.empty())
        {
            EXEC_MULTIPLE(linha);
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
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

    std::string startDir = startdir_CHECK();

    if (!startDir.empty())
    {
        if (!ChangeDirectory(startDir, false))
        {
            ChangeDirectory(GetDesktopPath(), false);
        }
    }
    else
    {
        ChangeDirectory(GetDesktopPath(), false);
    }

    char user[UNLEN + 1];
    DWORD size = UNLEN + 1;

    GetUserNameA(user, &size);
    _APELIDO_WINDOWS = user;
    MOPTS::clear_opts = false;
    MOPTS::color = false;
    MOPTS::all_color_line = false;
    apelido_CHECK();
    image_char_CHECK();
    _DEFINE = LerConfig("H_DEFINE_.cfg"); // salva uma variavel pro terminal
    if (_DISCORD_RPC_VALUE == true)
    {
        iniciarDiscordRPC();
    }
    ASCII_CALL();
    PRINT_SYS("Olá " + _APELIDO + "!", true);
    while (true)
    {
        if (exited == true)
        {
            Discord_Shutdown();
            break;
        }
        std::cout << GetCurrentPath() << " > ";
        std::string cmd;        // salva oq usuario digitou
        getline(std::cin, cmd); // input

        EXEC_MULTIPLE(cmd); // executa todos os comandos usados
    }
    return 0; // so retorna que o programa deu tudo certo
} // cabou