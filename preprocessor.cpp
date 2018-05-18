#include "preprocessor.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "converter.h"
#include "headache.h"
#include "linker.h"
#include "blockquote.h"
#include "Menu.h"
class converter;

preprocessor::preprocessor()
{
    paragraph=false;
    paragraph_activated= false;
}

preprocessor::~preprocessor()
{
    //dtor
}

void preprocessor::emphasis(std::string& current , code& coder)
{
    if(coder.get_code_block()== true ) return;
    current+=' ';
    int emphasis_stage=0;
    int start;
    bool strong_chance=false;
    bool strong=false;
    int ending;
    for(size_t i=0; i< current.length(); i++)
    {
        switch(emphasis_stage)
        {
        case 0:
            {
                if(current[i] == '*' || current[i] == '_') emphasis_stage=1;
                start=i;
                break;
            }
        case 1:
            {
                if(current[i] == '*' || current[i] == '_') emphasis_stage=2;
                else
                {
                    emphasis_stage= 3;
                }
                break;
            }
        case 2:
            {
                strong_chance=true;
                emphasis_stage= 3;
                break;
            }
        case 3:
            {
                if(current[i] == '*' || current[i] == '_' )
                {
                    ending= i;
                    emphasis_stage= 4;
                }

                    break;
            }
        case 4:
            {
                if(current[i] == '*' || current[i] == '_' )
                {
                    strong=true;
                }
                emphasis_stage= 5;
                break;
            }
        case 5:
            {
                if(strong == true )
                {
                    if(Menu::lowercase== true)
                    {
                        current.erase(start, 2);
                        current.insert(start, "<strong>");
                        ending+=6;
                        current.erase(ending, 2);
                        current.insert(ending, "</strong>");

                    }
                    else
                    {
                        current.erase(start, 2);
                        current.insert(start, "<STRONG>");
                        ending+=6;
                        current.erase(ending, 2);
                        current.insert(ending, "</STRONG>");
                    }
                }
                else
                {
                    if(Menu::lowercase== true)
                    {
                        current.erase(start, 1);
                        current.insert(start, "<em>");
                        ending+=3;
                        current.erase(ending, 1);
                        current.insert(ending, "</em>");
                    }
                    else
                    {
                        current.erase(start, 1);
                        current.insert(start, "<EM>");
                        ending+=3;
                        current.erase(ending, 1);
                        current.insert(ending, "</EM>");

                    }
                }
                emphasis_stage= 0;
                strong=false;
                strong_chance=false;
                break;
            }
        }
    }
 current.erase(current.length()-1, 1);
}

void preprocessor::prepare(converter& conv) ///< Funkcja dodająca standardowe elementy dla
{
    if(Menu::lowercase==false)
    {
        conv.push("<!DOCTYPE HTML>");
        conv.push("<HTML>");
        conv.push("<HEAD>");
        conv.push("<META http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">");
        conv.push("</HEAD>");
        conv.push("<BODY>");
        conv.push("");
    }
    else
    {
        conv.push("<!DOCTYPE html>");
        conv.push("<html>");
        conv.push("<head>");
        conv.push("<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">");
        conv.push("</head>");
        conv.push("<body>");
        conv.push("");
    }
    for(size_t i=0; i<conv.get_input_size(); i++)
    {
        conv.push(conv.get_input(i));
    }

    if(Menu::lowercase==false)
    {
        conv.push("");
        conv.push("</BODY>");
        conv.push("</HTML>");
    }
    else
    {
        conv.push("");
        conv.push("</body>");
        conv.push("</html>");
    }
}
void preprocessor:: add_paragraph(converter& conv, std:: string& previous, std::string& current, headache& head ) ///< Funkcja dodajaca nowy paragraf jeśli potrzeba, dodajaca przejścia do nowej linii
{
    bool maybe=false;
    if(current.size()> 1)
    {
            if(current[0]=='<' && (current[1]!='a' && current[1]!='A' && current[1]!='s' && current[1]!='S' && current[1]!='e' && current[1]!='E') || current[0]=='[' ) maybe=true;
    }
    if(paragraph == true && previous[previous.length()-1]== ' ' &&  previous[previous.length()-2]== ' ' )
    {
            if(Menu::lowercase== true)
            {
                previous.append("<br>");
            }
            else
            {
                previous.append("<BR>");
            }
    }
    if(conv.get_special()== false && paragraph_activated == false && head.get_empty()== false  && maybe == false )
    {
        if(Menu::space== false)
        {
            if(Menu::lowercase== true)
            {
                 current.insert(conv.get_tab_indent(),"<p>" );
            }
            else
            {
                 current.insert(conv.get_tab_indent(),"<P>" );
            }
        }
        else
        {
            if(Menu::lowercase== true)
            {
                 current.insert(conv.get_space_indent(),"<p>" );
            }
            else
            {
                 current.insert(conv.get_space_indent(),"<P>" );
            }
        }
        paragraph_activated=true;
        paragraph=true;
    }
    if(maybe== true)
    {
        paragraph= false;
    }
    if( (conv.get_special()== true  || head.get_empty()==true || paragraph== false ) &&  paragraph_activated == true  )
    {
        if(Menu::lowercase== true)
        {
                 previous.append("</p>");
        }
        else
        {
                  previous.append("</P>");
        }
        paragraph_activated=false;
        paragraph=false;
    }
}
