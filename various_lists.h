#ifndef VARIOUS_LISTS_H
#define VARIOUS_LISTS_H
#include <iostream>
#include <cstring>
#include <fstream>
#include "converter.h"
#include "preprocessor.h"
#include "linker.h"
#include "blockquote.h"
class converter;

class various_lists
{
    public:
        various_lists(); ///< konstruktor zerujący wszystkie parametry
        void check( std::string current, bool last ); ///< funkcja sprawdzjąca co mamy w lini
        void change(std::string& current, std::string& next ); ///< funkcja dodająca do lini znaczniki list
        bool move_forward( converter& conv,  size_t current_place );
        bool get_ordered_list( ); ///< zwraca czy mamy w lini liste uporządkowaną
        bool get_unordered_list( );  ///< zwraca czy mamy w lini liste nieuporządkowaną
        bool finish ( converter& conv ,   size_t current_place );  ///< funkcja zwraca czy dodany tag kończący listę
        void reset() ; ///< resetujemy dane zawarte w obiekcie
        bool get_active_ordered(); ///< funkcja
        void set_active_ordered( bool state);


    protected:

    private:
         bool unordered_list;///< flaga czy znaleźliśmy liste nienumerowaną
         bool ordered_list; ///< flaga czy znaleźliśmy liste numerowaną
         bool unordered_list_chance ; ///<
         int ordered_list_chance; ///< pomocniczy licznik do sprawdzania czy jest szansa na listę
         int length ; ///< długość ciągu do wycięcia
         int blank; ///< liczba poprzedzających pustych lini
         bool active_ordered ; ///< czy lista numerowana już się zaczeła
         bool active_unordered ; ///< czy lista nienumerowana już się zaczeła
};

#endif // VARIOUS_LISTS_H
