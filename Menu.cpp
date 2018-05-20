#include "Menu.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "converter.h"
#include "include/utf8.h"


using namespace std;

std::fstream Menu::markdown;
std::stringstream Menu::nonsense;
std::string Menu::temp; ///< Tymczasowy string służący do przechowywania danych
std::string Menu::output_name;
bool Menu::lowercase;
bool Menu::space;

void Menu::Mainmenu(int argc, char** argv) ///< W funkcji łapiemy potencjalne błędy takie jak zły format
{
    try
    {
    lowercase = true;
    space = true;
    no_arguments( argc);
    help( argv);
    open_file( argc,  argv);
    options( argc, argv);
    conversion( );
    }
    catch(int e)
    {
        if(e== -1)
        {
            cout << "Podano plik w złym formacie lub o niepoprawnej nazwie" << endl << endl;
            cout << "Uruchom program z komendą *help* by uzyskać" << endl;
            cout << "więcej informacji o tym jak obsługiwać program" << endl;
            exit(0);
        }

        if(e == 0)
        {
            cout << "Podano błędną nazwę pliku wejściowego" << endl << endl;
            cout << "Wpisz do konsoli help bez żadnych innych argumentów" << endl;
            cout << "aby uzyskać więcej informacji" << endl;
            exit(0);
        }

        if(e == 1)
        {
            cout << "Plik nie jest w formacie UTF 8" << endl;
            exit(0);
        }

        if( e == 2)
        {
            cout << "Podano zbyt dużo argumentów" << endl << endl;
            cout << "Uruchom program z poleceniem *help*, " << endl;
            cout << "aby dowiedzieć się jak poprawnie obsługiwać program" << endl;
            exit(0);
        }
    }

}
void Menu::help(char** argv)///< Wyczerpujący help
{
    if(strcmp(argv[1],"help") == 0)
    {
        cout << "Do funkcji można podać kilka argumentów: " << endl << endl;
        cout << "- nazwa ujęta w * * oznacza argument możliwy do  " << endl;
        cout << "  wprowadzenia do programu oczywiście już bez * *" << endl;
        cout << "- *help* wywołane bez innych argumentów pokaze to pomocne menu " << endl;
        cout << "- pierwszy argument musi być zawsze plikiem źródłowym typu txt lub md " << endl;
        cout << "  zawierającym tekst w markdownie  LUB komendą *help*" << endl;
        cout << "- drugi argument powinien zawierać nazwe pliku wynikowego" << endl;
        cout << "  bez jego formatu, choć argument ten można pominąć," << endl;
        cout << "  w przypadku nie podania nazwy pliku" << endl;
        cout << "  wynik działania programu znajdzie się w output.html" << endl;
        cout << "- trzeci argument czyli odpowiednio *lowercase* lub *uppercase*" << endl;
        cout << "  określają jakimi literami mają być zapisane tagi html" << endl;
        cout << "  domyślnie bez podania tego argumentu jest to lowercase" << endl;
        cout << "- czwarty argument moze przyjąć wartości *space* lub *tab*," << endl;
        cout << "  w tym przypadku określa on jak realizowane mają być" << endl;
        cout << "  wcięcia w html: przy użyciu dwóch spacji czy tabulacji" << endl;
        cout << "  w przypadku nie podania argumentu są to spacje" << endl;
        cout << "- podanie większej od czterech liczby argumentów" << endl;
        cout << "  spowoduje przerwanie działania programu" << endl;
        exit(0);
    }
}


void Menu:: open_file(int argc, char** argv)
{
    string open = argv[1];
    bool ok = false;
    int l = open.length();
    if (l < 3) throw -1;
    if(( open[l-1] == 'd' && open[l-2] == 'm') || (open[l-1] == 't' && open[l-2] == 'x' && open[l-3] == 't')) ok = true;
    if(ok == false) throw -1;

    markdown.open( open.c_str(), ios::in);
    if(markdown.good() == false) throw 0;

    nonsense << markdown.rdbuf();
    temp = nonsense.str();

    if(utf8::is_valid(temp.begin(),temp.end()) == false ) throw 1; ///< Sprawdzamy za pomocą funkcji bibliotecznej czy rzeczywiście mamy do czynienia z plikiem zakodowanym w UTF-8
}

void Menu:: no_arguments(int argc)
{
    if(argc == 1)
    {
        cout << " Nie podano żadnych argumentów do programu " << endl;
        cout << " wpisz *help* by uzyskać więcej informacji " << endl;
        exit(0);
    }
}

void Menu::options (int argc, char** argv)
{
    if(argc > 5) throw 2;
    switch(argc)
    {
        case 2:
            {
                output_name = "output.html";
                return;
            }

        case 3:
            {
                if(strcasecmp(argv[2],"uppercase") == 0 )
                {
                lowercase = false;
                output_name = "output.html";
                return;
                }
                if(strcasecmp(argv[2],"lowercase") == 0 )
                {
                lowercase = true;
                output_name = "output.html";
                return;
                }
                if(strcasecmp(argv[2],"tab") == 0 )
                {
                space = false;
                output_name = "output.html";
                return;
                }
                if(strcasecmp(argv[2],"space") == 0 )
                {
                space = true;
                output_name = "output.html";
                return;
                }
                output_name = argv[2];
                output_name += ".html";
                return;
            }

        case 4:
            {
                if(strcasecmp(argv[2],"uppercase") == 0 )  lowercase = false;
                if(strcasecmp(argv[3],"tab") == 0 )
                {
                space = false;
                output_name = "output.html";
                return;
                }
                if(strcasecmp(argv[3],"space") == 0 )
                {
                space = true;
                output_name = "output.html";
                return;
                }
                output_name = argv[3];
                output_name += ".html";
                return;
            }

        case 5:
            {
                if(strcasecmp(argv[2],"uppercase") == 0 )  lowercase = false;
                if(strcasecmp(argv[4],"tab") == 0 ) space = false;
                output_name = argv[3];
                output_name += ".html";
                return;
            }
    }
}

void Menu:: conversion()
{

    converter conv;
    conv.load(temp);
    conv.translate();
    markdown.close();
    conv.save(output_name);

}

