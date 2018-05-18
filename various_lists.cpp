#include "various_lists.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "converter.h"


various_lists::various_lists()
{
    unordered_list=false;
    ordered_list= false;
    unordered_list_chance = false;
    ordered_list_chance= 0;
    length= 0;
    blank= 0;
    active_ordered= false;
    active_unordered= false;

}

void various_lists::reset() ///< Funkcja resetująca atrybuty  funkcji
{
    unordered_list=false;
    ordered_list= false;
    unordered_list_chance = false;
    ordered_list_chance= 0;
    length= 0;
    blank= 0;
}
void various_lists::set_active_ordered( bool state)
{
    active_ordered= state;
}

bool various_lists::get_active_ordered( ) ///< funkcja zwracająca wartość flagi mówiącej o trwaniu listy numerowanej
{
    return active_ordered;
}

void various_lists:: check(std::string current, bool last) ///< funkcja sprawdzająca czy znaleźlismy jakąś listę
{

    for(size_t i=0; i<current.length()  ; i++)
    {
        if(blank > 3 ) break;
        if( ( current[i]== '+' || current[i]== '-' || current[i]== '*' ) && unordered_list_chance == false )
        {
            unordered_list_chance = true; ///< Pojawia się możliwość, że mamy do czynienia z listą nieoznaczoną
            length++;
        }
        else
        {
            if( unordered_list_chance == true && current[i] == ' ')
            {
                unordered_list = true;
                length++;
                return;
            }
            if( ( current[i]== ' ' || current[i]== '<' ) && unordered_list_chance== false )
            {
                blank++;
                length++;
            }
            else break; ///< Jeśli pojawi się cos innego to już nie ma szans na liste nieoznaczoną
        }
    }
    blank=0;
    length=0;
    for(size_t i=0; i<current.length() ; i++)
    {
        if(blank > 3 && ordered_list_chance == 0) return;

        if( current[i]>= '0' && current[i]<= '9' && ordered_list_chance== 0 ) ///< Sprawdzamy czy mamy doczynienia z liczbą dziesietną
        {
            ordered_list_chance= 1;
            length++;
        }
        else
        {
            if( ordered_list_chance == 1 )
            {
               if(current[i] == '.')
               {
                   ordered_list_chance= 2;
                    length++;
                    continue;
               }
               else
               {
                   if( current[i]> '9' ||  current[i]< '0') return;
               }
                length++;
            }

            if( ordered_list_chance == 2)
            {
                if( current[i] == ' ') ordered_list= true;
                length++;
                return;
            }

            if( ordered_list_chance == 0 )
            {
                length++;
                blank++;
                if( current[i]!= ' ' && current[i]!= '<' ) return; ///< Jeśli pojawi się cos innego to już nie ma szans na liste oznaczoną
            }
        }
    }
    blank=0;
    //if(last==true) return;
}

bool various_lists:: move_forward( converter& conv,  size_t current_place ) ///< funkcja dodająca tag rozpoczynający listę
{
    if( unordered_list == true && active_unordered == false )
    {
        if(Menu::lowercase==false)
        {
            conv.insert_new("<UL>", current_place);
        }
        else
        {
            conv.insert_new("<ul>", current_place);
        }
        active_unordered= true;
        return true;
    }

    if( ordered_list== true  && active_ordered == false )
    {
        if(Menu::lowercase==false)
        {
            conv.insert_new("<OL>", current_place);
        }
        else
        {
            conv.insert_new("<ol>",  current_place);
        }
        active_ordered=true;
        return true;
    }
    return false;
}

void various_lists::change(std::string& current, std::string& next  )
{
    if( ( unordered_list== true ||  ordered_list ==  true ) && ( active_ordered == true || active_unordered == true ) )
    {
        current.erase(0 , length);
        if(Menu::lowercase == false)
        {
            current.insert( 0 , "<LI>" );
            current.append( "</LI>" );
        }
        else
        {
            current.insert( 0, "<li>" );
            current.append( "</li>" );
        }

    }
}

bool various_lists::get_unordered_list( )
{
    return unordered_list;
}

bool various_lists::get_ordered_list( )
{
    return ordered_list;
}


bool various_lists:: finish ( converter& conv,   size_t current_place )
{
    if( unordered_list == false && active_unordered ==true  )
    {
        if(Menu::lowercase==false)
        {
            conv.insert_new("</UL>", current_place);
        }
        else
        {
            conv.insert_new("</ul>", current_place);
        }
        active_unordered=false;
        return true;
    }

    if( ordered_list== false && active_ordered ==true )
    {
        if(Menu::lowercase==false)
        {
            conv.insert_new("</OL>", current_place);
        }
        else
        {
            conv.insert_new("</ol>",  current_place);
        }
        active_ordered=false;
        return true;
    }
    return false;
}

