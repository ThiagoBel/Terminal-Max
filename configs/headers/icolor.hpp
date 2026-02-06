//      ######      :####:    .2025.     ##          .####.    ######:
//      ######      ######    ######     ##          ######    #######
//        ##      :##:  .#   :##  ##:    ##         :##  ##:   ##   :##
//        ##      ##         ##:  :##    ##         ##:  :##   ##    ##
//        ##      ##.        ##    ##    ##         ##    ##   ##   :##
//        ##      ##         ##    ##    ##         ##    ##   #######:
//        ##      ##         ##    ##    ##         ##    ##   ######
//        ##      ##.        ##    ##    ##         ##    ##   ##   ##.
//        ##      ##         ##:  :##    ##         ##:  :##   ##   ##
//        ##      :##:  .#   :##  ##:    ##         :##  ##:   ##   :##
//      ######      ######    ######     ########    ######    ##    ##:
//      ######      :####:    .####.     ########    .####.    ##    ###
// Made by ThiagoBel

#ifndef ICOLOR_HPP
#define ICOLOR_HPP

#include <string>
#include <cstdlib>
#include <ctime>

namespace icolor
{
    extern "C" long write(int, const void *, unsigned long);

    struct Say
    {
        Say &operator<<(const char *txt)
        {
            unsigned long len = 0;
            while (txt[len])
                len++;

            write(1, txt, len);
            return *this;
        }

        Say &operator<<(const std::string &txt)
        {
            write(1, txt.c_str(), txt.size());
            return *this;
        }

        Say &operator<<(std::string (*fn)())
        {
            return *this << fn();
        }
    };

    struct Sayln
    {
        ~Sayln()
        {
            const char nl = '\n';
            write(1, &nl, 1);
        }

        Sayln &operator<<(const char *txt)
        {
            unsigned long len = 0;
            while (txt[len])
                len++;
            write(1, txt, len);
            return *this;
        }

        Sayln &operator<<(const std::string &txt)
        {
            write(1, txt.c_str(), txt.size());
            return *this;
        }

        Sayln &operator<<(std::string (*fn)())
        {
            return *this << fn();
        }
    };

    Say say;
    Sayln sayln;

    inline std::string finished() { return "\033[0m"; } // end
    inline std::string bold() { return "\033[1m"; }
    inline std::string dim() { return "\033[2m"; }
    inline std::string underline() { return "\033[4m"; }
    inline std::string blink() { return "\033[5m"; }
    inline std::string reverse() { return "\033[7m"; }
    inline std::string hidden() { return "\033[8m"; }
    inline std::string black() { return "\033[30m"; }
    inline std::string red() { return "\033[31m"; }
    inline std::string green() { return "\033[32m"; }
    inline std::string yellow() { return "\033[33m"; }
    inline std::string blue() { return "\033[34m"; }
    inline std::string magenta() { return "\033[35m"; }
    inline std::string cyan() { return "\033[36m"; }
    inline std::string white() { return "\033[37m"; }
    inline std::string bg_black() { return "\033[40m"; }
    inline std::string bg_red() { return "\033[41m"; }
    inline std::string bg_green() { return "\033[42m"; }
    inline std::string bg_yellow() { return "\033[43m"; }
    inline std::string bg_blue() { return "\033[44m"; }
    inline std::string bg_magenta() { return "\033[45m"; }
    inline std::string bg_cyan() { return "\033[46m"; }
    inline std::string bg_white() { return "\033[47m"; }
    inline std::string bright_black() { return "\033[90m"; }
    inline std::string bright_red() { return "\033[91m"; }
    inline std::string bright_green() { return "\033[92m"; }
    inline std::string bright_yellow() { return "\033[93m"; }
    inline std::string bright_blue() { return "\033[94m"; }
    inline std::string bright_magenta() { return "\033[95m"; }
    inline std::string bright_cyan() { return "\033[96m"; }
    inline std::string bright_white() { return "\033[97m"; }
    inline std::string orange() { return "\033[38;5;208m"; }
    inline std::string pink() { return "\033[38;5;213m"; }
    inline std::string violet() { return "\033[38;5;141m"; }
    inline std::string light_cyan() { return "\033[38;5;87m"; }
    inline std::string bg_orange() { return "\033[48;5;208m"; }
    inline std::string bg_pink() { return "\033[48;5;213m"; }
    inline std::string bg_violet() { return "\033[48;5;141m"; }
    inline std::string bg_light_cyan() { return "\033[48;5;87m"; }
    inline std::string bg_light_gray() { return "\033[48;5;250m"; }
    inline std::string bg_dark_gray() { return "\033[48;5;238m"; }
    inline std::string bg_bright_black() { return "\033[100m"; }
    inline std::string bg_bright_red() { return "\033[101m"; }
    inline std::string bg_bright_green() { return "\033[102m"; }
    inline std::string bg_bright_yellow() { return "\033[103m"; }
    inline std::string bg_bright_blue() { return "\033[104m"; }
    inline std::string bg_bright_magenta() { return "\033[105m"; }
    inline std::string bg_bright_cyan() { return "\033[106m"; }
    inline std::string bg_bright_white() { return "\033[107m"; }
    inline std::string gray_0() { return "\033[38;5;232m"; }
    inline std::string gray_1() { return "\033[38;5;233m"; }
    inline std::string gray_2() { return "\033[38;5;234m"; }
    inline std::string gray_3() { return "\033[38;5;235m"; }
    inline std::string gray_4() { return "\033[38;5;236m"; }
    inline std::string gray_5() { return "\033[38;5;237m"; }
    inline std::string gray_6() { return "\033[38;5;238m"; }
    inline std::string gray_7() { return "\033[38;5;239m"; }
    inline std::string gray_8() { return "\033[38;5;240m"; }
    inline std::string gray_9() { return "\033[38;5;241m"; }
    inline std::string gray_10() { return "\033[38;5;242m"; }
    inline std::string gray_11() { return "\033[38;5;243m"; }
    inline std::string gray_12() { return "\033[38;5;244m"; }
    inline std::string gray_13() { return "\033[38;5;245m"; }
    inline std::string gray_14() { return "\033[38;5;246m"; }
    inline std::string gray_15() { return "\033[38;5;247m"; }
    inline std::string gray_16() { return "\033[38;5;248m"; }
    inline std::string gray_17() { return "\033[38;5;249m"; }
    inline std::string gray_18() { return "\033[38;5;250m"; }
    inline std::string gray_19() { return "\033[38;5;251m"; }
    inline std::string gray_20() { return "\033[38;5;252m"; }
    inline std::string gray_21() { return "\033[38;5;253m"; }
    inline std::string gray_22() { return "\033[38;5;254m"; }
    inline std::string gray_23() { return "\033[38;5;255m"; }
    inline std::string teal() { return "\033[38;5;30m"; }
    inline std::string sky_blue() { return "\033[38;5;117m"; }
    inline std::string lime() { return "\033[38;5;118m"; }
    inline std::string olive() { return "\033[38;5;100m"; }
    inline std::string brown() { return "\033[38;5;94m"; }
    inline std::string gold() { return "\033[38;5;220m"; }
    inline std::string salmon() { return "\033[38;5;209m"; }
    inline std::string coral() { return "\033[38;5;203m"; }
    inline std::string purple() { return "\033[38;5;99m"; }
    inline std::string lavender() { return "\033[38;5;225m"; }
    inline std::string cyan_2() { return "\033[38;5;51m"; }
    inline std::string magenta_2() { return "\033[38;5;201m"; }
    inline std::string chartreuse() { return "\033[38;5;118m"; }
    inline std::string spring_green() { return "\033[38;5;48m"; }
    inline std::string aquamarine() { return "\033[38;5;122m"; }
    inline std::string deep_sky_blue() { return "\033[38;5;39m"; }
    inline std::string dodger_blue() { return "\033[38;5;33m"; }
    inline std::string royal_blue() { return "\033[38;5;63m"; }
    inline std::string steel_blue() { return "\033[38;5;67m"; }
    inline std::string slate_blue() { return "\033[38;5;99m"; }
    inline std::string midnight_blue() { return "\033[38;5;19m"; }
    inline std::string hot_pink() { return "\033[38;5;205m"; }
    inline std::string deep_pink() { return "\033[38;5;198m"; }
    inline std::string indian_red() { return "\033[38;5;167m"; }
    inline std::string firebrick() { return "\033[38;5;124m"; }
    inline std::string crimson() { return "\033[38;5;197m"; }
    inline std::string dark_orange() { return "\033[38;5;166m"; }
    inline std::string tomato() { return "\033[38;5;202m"; }
    inline std::string light_salmon() { return "\033[38;5;216m"; }
    inline std::string wheat() { return "\033[38;5;223m"; }
    inline std::string khaki() { return "\033[38;5;228m"; }
    inline std::string tan() { return "\033[38;5;180m"; }
    inline std::string plum() { return "\033[38;5;176m"; }
    inline std::string orchid() { return "\033[38;5;170m"; }
    inline std::string thistle() { return "\033[38;5;182m"; }
    inline std::string indigo() { return "\033[38;5;54m"; }
    inline std::string bg_chartreuse() { return "\033[48;5;118m"; }
    inline std::string bg_spring_green() { return "\033[48;5;48m"; }
    inline std::string bg_aquamarine() { return "\033[48;5;122m"; }
    inline std::string bg_deep_sky_blue() { return "\033[48;5;39m"; }
    inline std::string bg_dodger_blue() { return "\033[48;5;33m"; }
    inline std::string bg_royal_blue() { return "\033[48;5;63m"; }
    inline std::string bg_steel_blue() { return "\033[48;5;67m"; }
    inline std::string bg_slate_blue() { return "\033[48;5;99m"; }
    inline std::string bg_midnight_blue() { return "\033[48;5;19m"; }
    inline std::string bg_hot_pink() { return "\033[48;5;205m"; }
    inline std::string bg_deep_pink() { return "\033[48;5;198m"; }
    inline std::string bg_indian_red() { return "\033[48;5;167m"; }
    inline std::string bg_firebrick() { return "\033[48;5;124m"; }
    inline std::string bg_crimson() { return "\033[48;5;197m"; }
    inline std::string bg_dark_orange() { return "\033[48;5;166m"; }
    inline std::string bg_tomato() { return "\033[48;5;202m"; }
    inline std::string bg_light_salmon() { return "\033[48;5;216m"; }
    inline std::string bg_wheat() { return "\033[48;5;223m"; }
    inline std::string bg_khaki() { return "\033[48;5;228m"; }
    inline std::string bg_tan() { return "\033[48;5;180m"; }
    inline std::string bg_plum() { return "\033[48;5;176m"; }
    inline std::string bg_orchid() { return "\033[48;5;170m"; }
    inline std::string bg_thistle() { return "\033[48;5;182m"; }
    inline std::string bg_indigo() { return "\033[48;5;54m"; }
    inline std::string wine() { return "\033[38;2;128;0;32m"; }
    inline std::string bg_wine() { return "\033[48;2;128;0;32m"; }
    inline std::string ruby() { return "\033[38;2;155;17;30m"; }
    inline std::string burgundy() { return "\033[38;2;128;0;64m"; }
    inline std::string maroon() { return "\033[38;2;128;0;0m"; }
    inline std::string mint() { return "\033[38;2;152;255;152m"; }
    inline std::string emerald() { return "\033[38;2;0;201;87m"; }
    inline std::string azure() { return "\033[38;2;0;127;255m"; }
    inline std::string navy() { return "\033[38;2;0;0;128m"; }
    inline std::string beige() { return "\033[38;2;245;245;220m"; }
    inline std::string ivory() { return "\033[38;2;255;255;240m"; }
    inline std::string chocolate() { return "\033[38;2;210;105;30m"; }
    inline std::string coffee() { return "\033[38;2;111;78;55m"; }
    inline std::string peach() { return "\033[38;2;255;203;164m"; }
    inline std::string apricot() { return "\033[38;2;251;206;177m"; }
    inline std::string neon_green() { return "\033[38;2;57;255;20m"; }
    inline std::string neon_blue() { return "\033[38;2;0;255;255m"; }
    inline std::string neon_pink() { return "\033[38;2;255;20;147m"; }
    inline std::string bg_ruby() { return "\033[48;2;155;17;30m"; }
    inline std::string bg_burgundy() { return "\033[48;2;128;0;64m"; }
    inline std::string bg_maroon() { return "\033[48;2;128;0;0m"; }
    inline std::string bg_mint() { return "\033[48;2;152;255;152m"; }
    inline std::string bg_emerald() { return "\033[48;2;0;201;87m"; }
    inline std::string bg_azure() { return "\033[48;2;0;127;255m"; }
    inline std::string bg_navy() { return "\033[48;2;0;0;128m"; }
    inline std::string bg_beige() { return "\033[48;2;245;245;220m"; }
    inline std::string bg_ivory() { return "\033[48;2;255;255;240m"; }
    inline std::string bg_chocolate() { return "\033[48;2;210;105;30m"; }
    inline std::string bg_coffee() { return "\033[48;2;111;78;55m"; }
    inline std::string bg_peach() { return "\033[48;2;255;203;164m"; }
    inline std::string bg_apricot() { return "\033[48;2;251;206;177m"; }
    inline std::string bg_neon_green() { return "\033[48;2;57;255;20m"; }
    inline std::string bg_neon_blue() { return "\033[48;2;0;255;255m"; }
    inline std::string bg_neon_pink() { return "\033[48;2;255;20;147m"; }
    inline std::string error() { return "\033[38;2;255;0;0m"; }
    inline std::string sucess() { return "\033[38;2;144;238;144m"; }
    inline std::string warn() { return "\033[38;2;255;255;0m"; }
    inline std::string info() { return "\033[38;2;100;200;255m"; }
    inline std::string fatal() { return "\033[38;2;255;80;80m\033[48;2;60;0;0m"; }

    inline std::string coloredText(const std::string &text, const std::string &color)
    {
        return color + text + finished();
    }
    inline std::string rainbow(const std::string &text)
    {
        std::string result;

        static bool seeded = false;
        if (!seeded)
        {
            std::srand((unsigned)std::time(nullptr));
            seeded = true;
        }

        for (char c : text)
        {
            int r = std::rand() % 256;
            int g = std::rand() % 256;
            int b = std::rand() % 256;

            result += "\033[38;2;";
            result += std::to_string(r);
            result += ";";
            result += std::to_string(g);
            result += ";";
            result += std::to_string(b);
            result += "m";
            result += c;
        }

        result += finished();
        return result;
    }
    
}
#endif