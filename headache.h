#ifndef HEADACHE_H
#define HEADACHE_H
#include <iostream>
#include <cstring>
#include <fstream>
#include "various_lists.h"
#include "converter.h"
#include "preprocessor.h"
#include "code.h"
class various_lists;
class code;

class headache
{
    public:
        headache(); ///< konstruktor zerujacy parametry headache
        ~headache();
        void change(std::string& current, std::string& next  ); ///< Funkcja dodająca nagłówki do lini jesli takie znajdzie
        void check(std::string current, std::string next, bool last, various_lists& listing ); ///< Funkcja sprawdzająca daną linię pod względem interesujących nas parametrów
        void add_horizontal( std::string& current); ///< Funkcja dodająca linie horyzontalną
        void check_empty( std::string& current);///< Funkcja sprawdzająca czy linia jest pusta
        void reset(); ///< Funkcja reserujaca parametry obiektu
        void horizon(std::string& current,  code& coder); ///< Funkcja wyszukujaca linii horyzontalnej
        bool get_header(); ///< Funkcja zwracająca czy znaleziono header;
        bool get_empty(); ///< Funkcja zwracająca informacje czy mamy do czynienia z pustą linią

    protected:

    private:
        int header_level; ///< wielkość  nagłówka
        bool etx; ///< flaga czy mamy nagłówek w stylu etx
        bool setex1; ///< flaga czy mamy nagłówek w stylu setex1
        bool setex2; ///< flaga czy mamy nagłówek w stylu setex2
        bool emptiness; ///< flaga czy linia jest pusta
        bool horizontal; ///< flaga czy mamy linie horyzontalną
        char horizontal_sign ; ///< zmienna pomocnicza do wykrywania horyzontalnej lini
        int horizontal_count; ///< licznik czy mamy wystarczającą ilość odpowiednich znaków do lini horyzontalnej
        int place; ///< zmienna trzymająca miejsce gdzie znaleźliśmy nagłówek
        void clean(std::string& current);///< Funkcja usuwająca zbędne hashe
};

#endif // HEADACHE_H
