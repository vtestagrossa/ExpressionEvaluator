/*
 * Vincent Testagrossa
 * Project 2: Expression Evaluator
 * 02OCT2022
 *
 * Requirements: expression, operand, variable, symboltable.
 *
 * Description:
 * Looks up a variable and returns the value.
 */
#include <strstream>
#include <vector>
using namespace std;

#include "expression.h"
#include "operand.h"
#include "variable.h"
#include "symboltable.h"

extern SymbolTable symbolTable;

int Variable::evaluate()
{
    return symbolTable.lookUp(name);
}