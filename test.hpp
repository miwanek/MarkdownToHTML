#ifndef BOOST_TEST_HPP_INCLUDED
#define BOOST_TEST_HPP_INCLUDED
/*! \file */


#include <vector>
#include <iostream>
#include "headache.h"
#include "Menu.h"
#include "converter.h"
#include "linker.h"
#include "code_inside_markdown.h"
#include "various_lists.h"
#define BOOST_TEST_MODULE my test suite
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE( Basic_function_test ) ///< Sprawdzamy  podstawowe funkcje
{

    {
    char* argv[3];
    int argc = 3;
    argv[0] = new char[20];
    argv[1] = new char[20];
    argv[2] = new char[20];
    string pom;
    pom = "test.md";
    for(int i = 0; i < pom.length(); i++)
    {
         argv[1][i] = pom[i];
    }
    pom = "uppercase";
    for(int i = 0; i < pom.length(); i++)
    {
         argv[2][i] = pom[i];
    }
    argv[0][0] = 'a';
    Menu::options( argc, argv);
    Menu::open_file( argc,  argv);
    converter conv;
    conv.load(Menu::temp);
    conv.translate();
    BOOST_CHECK_EQUAL("<P>alibaba</P>", conv.get_output(7));
    BOOST_CHECK_EQUAL("<UL>", conv.get_output(8));
    BOOST_CHECK_EQUAL("<LI>lista</LI>", conv.get_output(9));
    BOOST_CHECK_EQUAL("</UL>", conv.get_output(10));
    BOOST_CHECK_EQUAL("<H2> nagłówek</H2>", conv.get_output(11));
    BOOST_CHECK_EQUAL("<PRE><CODE>kod", conv.get_output(12));
    BOOST_CHECK_EQUAL("</CODE></PRE>", conv.get_output(13));
    BOOST_CHECK_EQUAL("<P> link : <A href=\"http://google.com/ \"title=\"Google\">Google</A></P>", conv.get_output(14));
    free (argv[0]);
    free (argv[1]);
    free (argv[2]);
    Menu::temp.clear();
    conv.clean();
    Menu::markdown.close();
    Menu::nonsense.str("");
    }
}
BOOST_AUTO_TEST_CASE( Second_test ) ///< Sprawdzamy  dodwanie poprzecznych linii
{
    {
    char* arg[3];
    int c = 3;
    arg[0] = new char[20];
    arg[1] = new char[20];
    arg[2] = new char[20];
    string pom;
    pom="test2.md";
    for(int i = 0; i < pom.length(); i++)
    {
         arg[1][i] = pom[i];
    }
    pom = "uppercase";
    for(int i = 0; i < pom.length(); i++)
    {
         arg[2][i] = pom[i];
    }
    arg[0][0] = 'a';
    Menu::options( c, arg);
    Menu::open_file( c,  arg);
    converter conv2;
    conv2.load(Menu::temp);
    conv2.translate(); 
    BOOST_CHECK_EQUAL("<P>tralala</P>", conv2.get_output(7));
    BOOST_CHECK_EQUAL("<PRE><CODE>blok *kodu*", conv2.get_output(8));
    BOOST_CHECK_EQUAL("jakiś wiadomo &amp;czy nie &amp; ", conv2.get_output(9));
    BOOST_CHECK_EQUAL("</CODE></PRE>", conv2.get_output(10));
    BOOST_CHECK_EQUAL("<UL>", conv2.get_output(11));
    BOOST_CHECK_EQUAL("<LI>lista</LI>", conv2.get_output(12));
    BOOST_CHECK_EQUAL("</UL>", conv2.get_output(13));
    BOOST_CHECK_EQUAL("<P>Zwykły paragraf", conv2.get_output(14)); 
    BOOST_CHECK_EQUAL("<A href=\"https://daringfireball.net/projects/markdown/syntax \"title=\"markdown syntax\">Super link</A>", conv2.get_output(15));
    BOOST_CHECK_EQUAL("A tu mamy ciąg dalszy</P>", conv2.get_output(16));
    BOOST_CHECK_EQUAL("<P>przerwa</P>", conv2.get_output(18));
    BOOST_CHECK_EQUAL("<HR>", conv2.get_output(20));
    BOOST_CHECK_EQUAL("<HR>", conv2.get_output(21));
    BOOST_CHECK_EQUAL("<HR>", conv2.get_output(22));
    BOOST_CHECK_EQUAL("<P>Kiedy byłem, kiedy byłem <EM>małym</EM> chłopcem <STRONG>hej</STRONG>", conv2.get_output(23));
    BOOST_CHECK_EQUAL("Wziął mnie ojciec, wziął mnie ojciec i tak do mnie <STRONG>rzekł</STRONG>  <BR>", conv2.get_output(24));
    BOOST_CHECK_EQUAL("przerwa jest ma być</P>", conv2.get_output(25)); 
    BOOST_CHECK_EQUAL("<H2>Np tu</H2>", conv2.get_output(26));
    free (arg[0]);
    free (arg[1]);
    free (arg[2]);
    Menu::temp.clear();
    conv2.clean();
    Menu::nonsense.str(std::string());
    Menu::markdown.close();
    }


}


#endif // TEST_HPP_INCLUDED
