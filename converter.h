#include <vector>
#include <iostream>
#ifndef CONVERTER_H
#define CONVERTER_H
#include "headache.h"
#include "linker.h"
#include "code_inside_markdown.h"
#include "various_lists.h"
class headache;
class various_lists;
class linker;

class converter///< Najważniejsza klasa w programie zarządzajaca procesem tłumaczenia
{
    public:


        converter();
        ~converter();
        void translate(); ///< Główna funkcja w naszym programie, która wywołuje wszystkie niezbędne do konwersji do html komponenty i procedury
        void load(std::string temp); 			///< funkcja wczytująca
        void save(std::string output_name);	 	///< Funkcja zapisująca do pliku html
        void show_input();				///< pomocnicza funkcja zwracajaca zawartośc wektora output
        void show_output(); 				///< pomocnicza funkcja zwracajaca zawartośc wektora input
        void push(std::string new_one);
        std::string get_input( unsigned int i);
        void insert_new(std::string phrase, int place );///< Funkcja wstawiająca nowego stringa do wektora output na podane miejce
        void delete_line( int place ); 			///< Funkcja usuwająca całkowicie jedną linię z wektora output
        unsigned int get_space_indent(); 		///< Funkcja zwracająca liczbe spacji wcięcia
        unsigned int get_tab_indent(); 			///< Funkcja pokazujaca ilość tabów wcięcia
        bool get_special();				///< Funkcja zwracająca czy wykryto specjalny znacznik
        size_t get_input_size(); 			///< Funkcja zwracająca rozmiar vektora
        void special_sign( headache& head, linker& link, code& coder, various_lists& listing); ///< Funkcja ustawiająca flagę, czy jest coś specjalnego w tej linii np. lista
        std::string get_output( unsigned int i); 	///< Funkcja zwracająca daną linię wektora wyjsciowego do celów testowych
        void clean();

    protected:

    private:
    std::vector<std::string>input; 	///< wektor danych wejsciowych
    std::vector<std::string>output; 	///< wektor  roboczy stringów, na którym wykonujemy niezbedne modyfikacje
    unsigned int space_indent; 		///< zmienna trzymająca ilość spacji wcięcia
    unsigned int tab_indent;		///< zmienna trzymająca ilość spacji wcięcia
    bool special; 			///< zmienna do trzymania znacznika specjalnych znaków
};

#endif // CONVERTER_H
