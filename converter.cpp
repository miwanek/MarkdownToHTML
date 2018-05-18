#include <iostream>
#include <cstring>
#include <fstream>
#include "converter.h"
#include "headache.h"
#include "preprocessor.h"
#include "linker.h"
#include "blockquote.h"
#include "various_lists.h"
#include "code.h"
\

converter::converter()
{
    space_indent=0;
    tab_indent=0;
    special= false;
}

converter::~converter()
{
    //dtor
}

void converter::translate()///< Najważniejsza i najgroźniejsz funkcja w programie
{
    headache head;
    preprocessor processor;
    linker link ;
    code coder;
    blockquote block;
    various_lists listing;
    processor.prepare( *this);
    bool last= false;
    for(size_t i=7; i< this->output.size()-1; i++)
    {
        int moved=0;
        if(i == output.size()-1 ) last= true;
        coder.simple_check(output[i]);
        head.check_empty(output[i] );
        head.horizon(output[i], coder );
        head.add_horizontal(output[i]);
        listing.check( output[i] ,  last );
        if(listing.finish( *this,    i ) == true)
        {
            i++;
            moved++;
        }
        coder.correct(output[i]);
        if(coder.change( *this ,i , output[i]) == true )
        {
            moved++;
            i++ ;
        }
        if( listing.move_forward( *this ,  i  ) == true )
        {
            moved++;
            i++ ;
        }
        listing.change(output[i] , output[i+1] );
        head.check(output[i], output[i+1],last, listing );
        head.change(output[i], output[i+1] );
        link.check(output[i] );
        link.look( output, i );
        link.write();
        link.change(output[i]);
        processor.emphasis(output[i], coder);
        special_sign( head, link, coder, listing);
        if(i>0 ) processor.add_paragraph( *this,  output[i-1 - moved],  output[i], head );
        head.reset();
        listing.reset();
        link.reset();
        coder.set_previous_code_block();
        coder.reset();
        special=false;
    }
    link.clean(*this , output);
}
 void converter::load(std::string temp) ///< Funkcja rozbijająca wczytywany plik na linię
 {

    std::string helpful;
    converter::input.reserve(100);
     for( size_t i=0; i<temp.length(); i++)
     {
        if(temp[i] == '\n' )
        {
            input.push_back(helpful);
            helpful="";
        }
        else
        {
            helpful+=temp[i];

        }
     }

 }
  void converter::show_input() ///< Funkcja wypisująca zawartość wektora input
 {
    for(size_t i =0; i<input.size(); i++)
    {
       std::cout<<input[i]<<std::endl;
    }
    std::cout<<input.size();
 }
   void converter::show_output() ///< Funkcja wypisująca zawartość wektora output
 {
    for(size_t i =0; i<output.size(); i++)
    {
       std::cout<<output[i]<<std::endl;
    }
    std::cout<<output.size();
 }
 void converter::save(std::string output_name) ///< Funkcja zapisujaca plik typu html o podanej nazwie
 {
    std::fstream html;
    html.open(output_name.c_str(),std::ios::out);
    for(size_t i =0; i<output.size(); i++)
    {
        html<<output[i]<<std::endl;
    }
    html.close();
 }

  void converter::push(std::string new_one ) ///< Funkcja dopisujaca na koniec wektora output nową linię
  {
      output.push_back(new_one);
  }

  std::string converter::get_input( unsigned int i)///< funkcja zwracająca dana linię wejściową
  {
      return this->input[i];
  }
  std::string converter::get_output( unsigned int i) ///< funkcja zwracajaca do danej lini wektora
  {
      return this->output[i];
  }

  size_t  converter::get_input_size()///< Funkcja zwraca ilość linii danych wejściowych
  {
     return this->input.size();
  }

  void converter::insert_new(std::string phrase, int place ) ///< funkcja wstawiajaca nową linie w dane miejsce
  {
      output.insert(output.begin()+ place, phrase );
  }

  void converter::delete_line( int place ) ///< Funkcja usuwająca linie
  {
      output.erase(output.begin()+ place );
  }

  bool converter::get_special( ) ///< Funkcja zwracająca czy wykryto specjalny znak
  {
      return special;
  }

  void converter::special_sign( headache& head, linker& link, code& coder, various_lists& listing   )
  {
      if(coder.get_code_block()== true || listing.get_ordered_list() == true || listing.get_unordered_list() == true  || head.get_header() == true )
      {
        special= true;
      }
      else
      {
          special= false;
      }
  }
 unsigned int converter::get_tab_indent()
 {
     return  tab_indent;
 }
  unsigned int converter::get_space_indent()
 {
     return  space_indent;
 }
 void converter::clean()
 {
    output.clear();
    input.clear();
 }


