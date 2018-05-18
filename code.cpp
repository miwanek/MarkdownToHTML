#include "code.h"
#include "Menu.h"

code::code()
{
    code_block=false;
    space_int= 0;
    tab= false ;
    previous_code_block= false;
    space= false;
}

void code::reset()
{
    code_block=false;
    space_int= 0;
    tab= false ;
    space= false;
}

void code::simple_check(string& current)
{
    if(current.length() == 0) return;
    if(current[0] == '\t')
    {
        space_int++;
        code_block= true;
        tab= true;
    }
    for(size_t i=0; i< current.length(); i++)
    {
        if(current[i] == ' ')
        {
            space_int++ ;
            if(space_int== 4)
            {
                code_block= true;
                space=true;
            }
        }
        else
        {
            return;
        }
    }
}
void code::replace_tag(string& current, int i )
{
    if(current[i] == '&')
        {
            current.erase(i,1);
            current.insert(i,"&amp;");
        }
    if(current[i] == '<')
        {
            current.erase(i,1);
            current.insert(i,"&lt;");
        }
    if(current[i] == '>')
        {
            current.erase(i,1);
            current.insert(i,"&gt;");
        }
}


void code::correct(string& current )
{
    for(size_t i=0; i< current.length(); i++)
    {
        if(code_block == true)
        {
            this->replace_tag(current, i );
        }
    }

}

bool code::change( converter& conv, int place, string& current )
{

    if(code_block== true && space== true ) ///< usuwamy wcięcia zgodnie ze składnią markdowna
    {
        current.erase(0, 4 );
        space_int-= 4;
    }
    if(code_block== true && tab == true ) ///< usuwamy wcięcia zgodnie ze składnią markdowna
    {
        current.erase(0,1 ) ;
        space_int-= 1;
    }
    if(code_block == false && previous_code_block== true)
    {
        if(Menu::lowercase == true ) conv.insert_new( "</code></pre>",  place );
        else
        {
            conv.insert_new( "</CODE></PRE>",  place );
        }
        return true;
    }
    if(code_block == true && previous_code_block== false)
    {
        if(Menu::lowercase == true ) current.insert( space_int, "<pre><code>");
        else
        {
            current.insert( space_int,  "<PRE><CODE>");
        }
    }
    return false;
}
bool code::get_code_block()
{
    return code_block;
}

void code::set_previous_code_block()
{
    previous_code_block= code_block;
}
