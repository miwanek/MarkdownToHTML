#include "linker.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "converter.h"
#include "headache.h"
#include "preprocessor.h"
#include "linker.h"
#include "blockquote.h"
#include "Menu.h"
linker::linker()
{
    stage=0;
    title="";
    link="";
    ready=false;
    id="";
    title_used= false;
    length=0;
    beginning=0;
    final_sentence="";
    reference_link=false;
    name="";
}

linker::~linker()
{
    //dtor
}

void linker::check(string& current ) ///< Szukamy linku lub odnośnika do linku w podanej nam linii
{
    for(size_t i=0; i< current.length(); i++ )
    {
        switch(stage)
        {
            case 0:
                {
                    if(current[i]== '[' )
                    {
                        stage=1;
                        beginning= i;
                        length++;
                    }
                    break;
                }
            case 1:
                {
                    if(  current[i]!= ']' )
                    {
                    name+=current[i];
                    }
                    else
                    {
                    stage= 2;
                    }
                    length++;
                    break;
                }
            case 2:
                {
                    if(current[i] == '(') stage=3;
                    if(current[i] == '[') stage=7;
                    if(current[i] != '[' && current[i] != '(') stage= 6;
                    length++;
                    break;
                }
            case 3:
                {
                    if(current[i]== '"' )
                    {
                        stage= 4;
                        length++;
                        break;
                    }
                    if(current[i]== ')' )
                    {
                        stage = 6;
                        ready=true;
                    }
                    else
                    {
                        link+= current[i];
                    }
                    length++;
                    break;
                }
            case 4:
                {
                    length++;
                    if(current[i]== ')')
                    {
                        stage = 6 ;
                        ready=true;
                        break;
                    }
                    if(  current[i]!= '"' )
                    {
                    title +=current[i];
                    }
                    else
                    {
                    stage= 5;
                    title_used= true;
                    }
                    break;
                }
            case 5:
                {
                    if(current[i]== ')')
                    {
                        stage = 6 ;
                        ready= true;
                    }
                    length++;
                    break;
                }
            case 6:
                {
                    break;
                }
            case 7:
                {
                    if(current[i]== ']' )
                    {
                        stage=6;
                        if(id == "") id= name;
                        reference_link=true;
                    }
                    else
                    {
                        id+= current[i] ;
                    }
                    length++;
                    break;
                }

        }

    }

}

void linker::write()
{
    if(ready == true )
    {
        if(Menu::lowercase == true )
        {
            final_sentence+="<a href=\"";
        }
        else
        {
            final_sentence+="<A href=\"";
        }
        final_sentence+=link;
        final_sentence+="\"";
        if(title_used == true )
        {
            final_sentence+="title=\"";
            final_sentence+= title;
            final_sentence+= "\"";
        }
        final_sentence+= ">";
        final_sentence+= name;
        if(Menu::lowercase == true )
        {
            final_sentence+="</a>";
        }
        else
        {
            final_sentence+="</A>";
        }
    }
}

void linker::reset()
{
    stage=0;
    title="";
    link="";
    ready=false;
    id="";
    title_used= false;
    length=0;
    beginning=0;
    final_sentence="";
    reference_link=false;
    name="";

}
bool linker::get_ready()
{
    return ready;
}

void linker::look(vector<string>& output, unsigned int start)
{
    if(reference_link == true )
    {
        for(size_t i =0; i< output.size(); i++)
        {
            if(ready == true )
            {
                lines_to_delete.push_back(output[i-1]);
                return;
            }
            stage= 0;
            string same="";
            title="";
            link="";
            if(ready == true ) return;
            if(i != start)
            {

                for(size_t j=0; j<output[i].size(); j++)
                {
                    switch(stage)
                    {
                    case 0:
                        {
                            if(output[i][j] == '[') stage= 1;
                            break;
                        }
                    case 1:
                        {
                            if(output[i][j] == ']') stage= 2;
                            else
                            {
                                same+=output[i][j];
                            }
                            break;
                        }
                    case 2:
                        {
                            if(same != id) stage= 7;
                            else
                            {
                                if(output[i][j]==':') stage= 3;
                                else
                                {
                                    stage= 7;
                                }
                            }
                            break;
                        }
                    case 3:
                        {
                            if(output[i][j]!='\t' && output[i][j]!=' ')
                            {
                                stage = 4;
                                link+= output[i][j];
                            }
                            break;
                        }
                    case 4:
                        {
                            if(output[i][j]== ' ')
                            {
                                stage= 5;
                                ready=true;
                            }
                            else
                            {
                                link+= output[i][j];
                            }
                            break;
                        }
                    case 5:
                        {
                            if(output[i][j] == '"' ||  output[i][j] == '\'' || output[i][j] == '(' ) stage= 6;
                            break;

                        }
                    case 6:
                        {
                            if( output[i][j] == '"' ||  output[i][j] == '\'' || output[i][j] == ')' )
                            {
                                stage= 7;
                                title_used= true;
                                ready=true;
                            }
                            else
                            {
                                title+= output[i][j] ;
                            }
                            break;

                        }
                    case 7:
                        {
                            break;
                        }

                    }
                }
            }
        }

    }
}

void linker::change (string& current )
{
    if(ready== true)
    {
        current.erase(beginning , length);
        current.insert(beginning , final_sentence );
    }

}
void linker::clean(converter& conv, vector<string>& output )
{
    for(size_t i=0; i< output.size(); i++)
    {
        for(int j=0; j< lines_to_delete.size(); j++)
        {
            if(lines_to_delete[j] == output[i] )
            {
                conv.delete_line(i);
                j=-1;
            }
        }
    }
    lines_to_delete.clear();
}
