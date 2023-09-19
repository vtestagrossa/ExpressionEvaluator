/*
 * Vincent Testagrossa
 * Project 2: Expression Evaluator
 * 02OCT2022
 *
 * Requirements: symboltable
 *
 * Description:
 * Stores, retrieves and clears variable names and values to/from/in a vector. 
 */
#include <string>
#include <vector>
using namespace std;

#include "symboltable.h"


void SymbolTable::insert(string variable, int value)
{
    const Symbol& symbol = Symbol(variable, value);
    elements.push_back(symbol);
}

void SymbolTable::clear()
{
    //required for multiple uses while reading lines from a file or multiple files. If clear isn't called, elements
    //retains previous values and returns the first result, so if another variable has the same symbol, the incorrect
    //result is returned.
    elements.clear();
}

double SymbolTable::lookUp(string variable) const
{
    for (int i = 0; i < elements.size(); i++)
        if (elements[i].variable == variable)
             return elements[i].value;
    return -1;
}

