#ifndef LINKER_H
#define LINKER_H
#include <iostream>
#include <cstring>
#include <fstream>
#include "converter.h"
#include "headache.h"
#include "preprocessor.h"
#include "linker.h"

#include "Menu.h"
using namespace std;
class converter;
class linker
{
    public:

        linker(); 						 ///< konstruktor zerujący parametry
        void check(string& current );				 ///< sprawdzamy co mamy w lini
        void reset( ); 						 ///< przywracamy atrybuty obiektu do stanu pierwotnego(zerujemy)
        void look(vector<string>& output, unsigned int  start ); ///< szukamy po pliku w celu odnalezienia odnośników do linii
        void change (string& current ); 			 ///< wstawiamy linki
        void clean(converter& conv, vector<string>& output); 	 ///< czyścimy plik ze zbędnych odnośników do linków
        void write(); 						 ///< funkcja składająca w całość link do wczytanias
        bool get_ready(); 					 ///< funkcja zwracająca falgę czy dodano link

        ~linker();

    protected:

    private:
        unsigned int  stage; 	 ///< faza sprawdzania czy mamy do czynienia z linkiem
        unsigned int  beginning; ///< start potencjalnego linku
        unsigned int  length; 	 ///< długość danych do usunięcia
        string title; 		 ///< tytuł linku
        string link; 		 ///< nazwa linku
        bool ready;		 ///< flaga czy link był
        bool title_used; 	 ///< falga czy dodajemy tytuł linku
        bool reference_link; 	 ///< flaga czy szukamy linku w stylu referencji
        string name; 		 ///< nazwa
        string id; 		 ///< id linku do znalezienia
        string final_sentence; 	 ///< ostateczny string do wklejenia
        vector<string> lines_to_delete; ///< linie które trzeba usunąć
};

#endif // LINKER_H
