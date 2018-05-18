#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <fstream>
#include "converter.h"
#include "///home/michal/Desktop/School-projects/utf8_v2_3_4/source/utf8.h"


class Menu///< Klasa pomocnicza do obsługi plików, zapisu, odczytu oraz trzymająca pewne ważne stałe takie jak argumenty wywołania programu
{
    public:
        Menu();
         void static Mainmenu(int argc, char** argv); ///< Funkcja od której działanie programu się zaczyna i wktórej wnętrzu wszystko się dzieje
         void static help(char** argv); ///< Funkcja pokazuje pomocne informacje jak obsługiwać program po podaniu przez użytkowania argumentu wywołania programu *help*
         void static open_file(int argc, char** argv);///< Funkcja wczytująca zawartość pliku do stringa
         void static no_arguments(int argc); ///< Sprawdzamy czy program został w ogóle uruchomiony zjakimkolwiek argumentem
         void static conversion(); ///< Funkcja od której zaczyna sie proces tłumaczenia markdown na html
         void static options(int argc, char** argv); ///< Funkcja wprowadzająca w życie opcje jakie podał użytkownik przy podawaniu argumentów wywołania
         static std::fstream markdown; ///< Strumień plikowy służacy do odczytu danych z pliku wejściowego
         static std::stringstream nonsense; ///< Bezsensowny stringstream do wczytywania danych hurtem
         static std::string temp; ///< Tymczasowy string służący do przechowywania danych
         static std::string output_name; ///< zmienna trzymająca nazwe pliku wyjściowego
         static bool lowercase; ///< Zmienna określająca czy tagi mają być lowercase czy uppercase
         static bool space; ///< zmienna określająca czy wcięcia mają być realizowane jako taby czy spacje

    protected:

    private:
};

#endif // MENU_H
