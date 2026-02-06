/*
MOPTS
WINDOWS & UNIX

#include <iostream>
#include "MOPTS.h" // biblioteca

void OPTION1(const std::string &classe) // funcao 1
{
    std::cout << classe << " selecionada" << std::endl;
}

void OPTION2(const std::string &classe) // funcao 2
{
    std::cout << classe << " selecionada" << std::endl;
}

void OPTION3(const std::string &classe) // funcao 3
{
    std::cout << classe << " selecionada" << std::endl;
}

int main()
{
    MOPTS::color = true;
    // Ativa o uso de cores na opção selecionada
    // true  = fundo branco e texto preto
    // false = sem destaque de cor
    MOPTS::all_color_line = true;
    // Define se a linha inteira da opção ficará destacada
    // true  = a linha inteira é colorida
    // false = apenas o texto da opção é colorido
    MOPTS::clear_opts = true;
    // Define se o console será limpo após selecionar uma opção
    // true  = limpa o console antes de executar a função
    // false = mantém o menu visível

    MOPTS::MenuOption opcoes[] = {
        // opcoes
        {"Opcao 1", "CLASS1", OPTION1},
        {"Opcao 2", "CLASS2", OPTION2},
        {"Opcao 3", "CLASS3", OPTION3},
    };
    // 1. "Opcao X" -> opção
    // 2. "CLASS X" -> classe (informacao que manda para funcao)
    // 3. "OPTIONX" -> funcao que executa

    MOPTS::ShowMenu("Descricao de cima", opcoes, "", "Descricao de baixo"); // mostrar no terminal

    // 1. "Descricao de cima"  -> texto exibido antes das opções (vazio = sem descricao)
    // 2. opcoes               -> lista de opções do menu
    // 3. ""                   -> marcador da opção selecionada (vazio = sem marcador)
    // 4. "Descricao de baixo" -> texto exibido após as opções (vazio = sem descricao)
    return 0;
}


    Não precisa dar créditos, fiz no tédio
*/
#pragma once
#ifndef MOPTS_H
#define MOPTS_H

#include <iostream>
#include <string>

#ifdef _WIN32 // janelinha
#include <conio.h>
#include <windows.h>
#else // outros
#include <termios.h>
#include <unistd.h>
#endif

namespace MOPTS // MOPTS::
{
#ifdef _WIN32
    WORD originalColor = 0;
#endif

    bool all_color_line = false; // destaca linha inteira
    bool clear_opts = false;     // limpa console ao selecionar
    bool color = false;          // usa cores

    typedef void (*MenuFunc)(const std::string &);

    struct MenuOption // configuracoes
    {
        std::string texto;  // texto (literal)
        std::string classe; // classes para funcoes
        MenuFunc func;      // funcoes
    };

    inline void ClearConsole() // UAU!
    {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count, cellCount;

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;

        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacter(hConsole, ' ', cellCount, {0, 0}, &count);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, {0, 0}, &count);
        SetConsoleCursorPosition(hConsole, {0, 0});
#else
        std::cout << "\033[2J\033[H";
#endif
    }

    inline void SetHighlight()
    {
#ifdef _WIN32
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE // fundo branco
            // foreground preto (0)
        );
#else
        std::cout << "\033[47m\033[30m"; // fundo branco, texto preto
#endif
    }

    inline void ResetColor()
    {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalColor);
#else
        std::cout << "\033[0m";
#endif
    }

    inline int GetKey()
    {
#ifdef _WIN32
        return _getch();
#else
        termios oldt, newt;
        int ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
#endif
    }

    template <size_t N>
    inline void ShowMenu( // mostra no terminal
        const std::string &desc,
        MenuOption (&opcoes)[N],
        const std::string &marcador,
        const std::string &desc2)
    {
        int selecionado = 0;
        const int total = static_cast<int>(N);
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(hConsole, &info);
        originalColor = info.wAttributes;
#endif

        while (true)
        {
            ClearConsole(); // uau

            if (!desc.empty())
                std::cout << desc << '\n';

#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole, &info);
            int largura = info.dwSize.X;
#else
            int largura = 80; // geralmente é 80, sei n, se quiser pode mudar isso
#endif

            for (int i = 0; i < total; i++)
            {
                bool ativo = (i == selecionado);

                if (ativo && color)
                    SetHighlight();

                if (ativo && all_color_line)
                    std::cout << std::string(largura, ' ') << "\r";

                if (!marcador.empty())
                    std::cout << (ativo ? marcador : "  ");

                std::cout << opcoes[i].texto << '\n';

                if (ativo && color)
                    ResetColor();
            }

            if (!desc2.empty())
                std::cout << desc2 << '\n';

            int tecla = GetKey();

#ifdef _WIN32
            if (tecla == 224) // setas
            {
                tecla = GetKey();
                if (tecla == 72)
                    selecionado = (selecionado - 1 + total) % total;
                if (tecla == 80)
                    selecionado = (selecionado + 1) % total;
            }
#else
            if (tecla == 27)
            {
                if (GetKey() == 91)
                {
                    int seta = GetKey();
                    if (seta == 'A')
                        selecionado = (selecionado - 1 + total) % total;
                    if (seta == 'B')
                        selecionado = (selecionado + 1) % total;
                }
            }
#endif

            if (tecla == 'w' || tecla == 'W') // pa cima
                selecionado = (selecionado - 1 + total) % total;

            if (tecla == 's' || tecla == 'S') // pa baixo
                selecionado = (selecionado + 1) % total;

            if (tecla == 10 || tecla == 13 || tecla == 32) // sim
            {
                if (clear_opts)
                    ClearConsole();

                if (opcoes[selecionado].func)
                    opcoes[selecionado].func(opcoes[selecionado].classe);

                return;
            }
        }
    }
}

#endif // cabou...