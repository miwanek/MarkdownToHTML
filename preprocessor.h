#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <fstream>
#include <cstring>
#include <sstream>
#include <fstream>
#include "converter.h"
#include "Menu.h"
#include "headache.h"
class converter;
class code;
class headache;

class preprocessor
{
    public:

        void prepare(converter& conv); ///< Funkcja wstawiająca do pliku wyjściowego podstawowe tagi html
        void emphasis(std::string& current,  code& coder); ///< Funkcja szykająca podkreślonych wyrazów
        void add_paragraph(converter& conv,  std:: string& previous, std::string& current, headache& head ); ///< Funkcja dodająca nowy paragraf
        preprocessor(); ///< zerujący konstruktor
        ~preprocessor();

    protected:

    private:
         bool paragraph; ///< flaga czy znaleźliśmy paragraf
         bool paragraph_activated; ///< flaga czy mieliśmy w poprzednim wypadku z paragrafem
};

#endif // PREPROCESSOR_H
