/*
 * Vincent Testagrossa
 * Project 2: Expression Evaluator
 * 02OCT2022
 *
 * Requirements: See includes.
 *
 * Description:
 * Parses the name of a variable into a string from a stream. 
 */
#include <cctype>
#include <iostream>
#include <istream>
#include <string>
using namespace std;

#include "parse.h"
string parseName()
{
    char alnum;
    string name = "";

    cin >> ws;
    while (isalnum(cin.peek()))
    {
        cin >> alnum;
        name += alnum;
    }
    return name;
}
string parseName(istream& input)
{
    char alnum;
    string name = "";

    input >> ws;
    while (isalnum(input.peek()))
    {
        input >> alnum;
        name += alnum;
    }
    return name;
}