#include "headache.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "various_lists.h"
#include "converter.h"
#include "headache.h"
#include "preprocessor.h"

headache::headache()///< Konstruktor zerujący wszystko co sie da
{
        header_level = 0;
        etx = false;
        setex1 = false;
        setex2 = false ;
        emptiness = true;
        horizontal =false;
        horizontal_sign = 'a';
        horizontal_count = 0;
        place = 0;
}
headache::~headache()
{
    //pusto
}

void headache::reset() ///< resetujemy wartości które są określone dla kazdej pętli odzielnie
{
        header_level = 0;
        etx = false;
        setex1 = false;
        setex2 = false ;
        emptiness = true;
        horizontal = false;
        horizontal_sign ='a';
        horizontal_count = 0;
        place = 0;
}
void headache::check(std::string current, std::string next, bool last, various_lists& listing) ///< Funkcja sprawdzająca czy są to interesujące nas headery
{
    if(listing.get_ordered_list() == true || listing.get_unordered_list() == true ) return; ///< Jeśli w linii wykryto już wyliczenie to nie ma co dalej kombinować
    for(size_t i = 0; i < current.length(); i++)
    {
        if(current[i] == '#')
        {
            etx = true;
            if(header_level < 6) header_level++;
            if(header_level == 0) place = i;
            continue;
        }
        else
        {
            if(etx == true && current[i] ==' ')
            {
                return;
            }
        }
    }
    if(last == true) return;
    for(size_t i = 0; i < next.length(); i++)
    {

        if(next[i] == '=')
        {
            if(!emptiness) setex2 = true;
        }
        else
        {
            if(setex2 == true && next[i] != '=')
            {
               setex2 = false;
                return;
            }
        }

        if(next[i] == '-')
        {
            if(!emptiness) setex1 = true;
        }
        else
        {
            if(setex1 == true && next[i] !='-')
            {
               setex1 = false;
               return;
            }
        }

     }
}

void headache::change(std::string& current, std::string& next) ///< Dodajemy nagłówki do linii
{
        current.erase(place , header_level );
        switch(header_level) ///< Dodajemy róźnej wielkości nagłówki w zależności od tego co znaleźliśmy
        {
        case 1:
            {
                if(Menu::lowercase == false)
                {
                    current.insert(place , "<H1>" );
                    clean(current);
                    current.append("</H1>");
                }
                else
                {
                    current.insert(place , "<h1>" );
                    clean(current);
                    current.append("</h1>");
                }
                break;
            }
        case 2:
            {
                if(Menu::lowercase == false)
                {
                   current.insert(place , "<H2>" );
                   clean(current);
                   current.append("</H2>");
                }
                else
                {
                   current.insert(place , "<h2>" );
                   clean(current);
                   current.append("</h2>");
                }
                break;
            }
        case 3:
            {
                if(Menu::lowercase == false)
                {
                    current.insert(place , "<H3>" );
                    clean(current);
                    current.append("</H3>");
                }
                else
                {
                    current.insert(place , "<h3>" );
                    clean(current);
                    current.append("</h3>");
                }
                break;
            }
        case 4:
            {
                if(Menu::lowercase == false)
                {
                    current.insert(place , "<H4>" );
                    clean(current);
                    current.append("</H4>");
                }
                else
                {
                    current.insert(place , "<h4>" );
                    clean(current);
                    current.append("</h4>");
                }
                break;
            }
        case 5:
            {
                if(Menu::lowercase == false)
                {
                   current.insert(place , "<H5>" );
                   clean(current);
                   current.append("</H5>");
                }
                else
                {
                   current.insert(place , "<h5>" );
                   clean(current);
                   current.append("</h5>");
                }
                break;
            }
        case 6:
            {
                if(Menu::lowercase == false)
                {
                    current.insert(place , "<H6>" );
                    clean(current);
                    current.append("</H6>");
                }
                else
                {
                    current.insert(place , "<h6>" );
                    clean(current);
                    current.append("</h6>");
                }
                break;
            }
        }
        if(header_level > 0) return; ///< Strażnik abyśmy przypadkiem nie dostali kilku nagłówków na raz

        if(setex1 == true) ///< Jeśli znaleliśmy nagłówek w stylu setex to go dodajemy
        {
                if(Menu::lowercase == false)
                {
                    current.insert(place , "<H1>" );
                    current.append("</H1>");
                }
                else
                {
                    current.insert(place , "<h1>" );
                    current.append("</h1>");
                }
                next.clear();
        }
        if(setex2 == true) ///< Jeśli znaleliśmy nagłówek w stylu setex to go dodajemy
        {

                if(Menu::lowercase == false)
                {
                   current.insert(place , "<H2>" );
                   current.append("</H2>");
                }
                else
                {
                   current.insert(place , "<h2>" );
                   current.append("</h2>");
                }
                next.clear();
        }
}
void  headache::check_empty( std::string& current)
{
    for(size_t i = 0; i < current.length(); i++)
    {
        if(current[i] != ' ' || current[i] != '\t') emptiness = false; ///< Sprawdzamy czy linia jest pusta
    }
}

void  headache::add_horizontal( std::string& current)///< Dodajmey linię horyzontalną
{
    if(horizontal == true )
        {
                if(Menu::lowercase == false)
                {
                   current.clear();
                   current.append("<HR>");
                }
                else
                {
                   current.clear();
                   current.append("<hr>");
                }
        }
}
void headache::clean(std::string& current) ///< Czyścimy nadmierna ilość hashy
{
    int number = 0;
    int place;
    for(size_t i = current.length()-1; i >= 0; i--)
    {
        if(current[i] == '#') number++;
        else
        {
           place = i+1;
            break;
        }
    }
    current.erase(place ,number);
}
void headache::horizon(std::string& current, code& coder) ///< Sprawdzamy czy znaleźliśmy może horyzontalną linię
{
    if( coder.get_code_block() == true) return;
    for(size_t i = 0; i < current.length(); i++)
    {

        if(i == 0)
        {
            if(current[i] == '-' || current[i] == '*' || current[i] == '_')
            {

                horizontal_sign = current[i];
                horizontal_count += 1;
            }
        }
        else
        {
            if(horizontal_sign == 'a') return;
            if(current[i] == horizontal_sign )
            {
                horizontal_count++;
                if(horizontal_count == 3) horizontal = true;
            }
            else
            {
                if(current[i] != ' ')
                {
                        horizontal = false;
                        return;
                }
            }
        }
    }
}
bool headache::get_header() ///< funkcja określająca czy znaleziono jakichs nagłówek
{
    if(header_level > 0) return true;
    if(horizontal || setex1 || setex2 || etx ) return true;
    return false;
}
bool headache::get_empty()///< Funkcja zwracająca informacje czy linia jest może pusta
{
    return emptiness;
}
