/*
 * Vincent Testagrossa
 * Project 2: Expression Evaluator
 * 02OCT2022
 *
 * Requirements: expression, subexpression, operand, variable, literal, parse.
 *
 * Description: 
 * Parses the next operand as a literal, variable, or another expression, as defined in the grammar.
 */
#include <cctype>
#include <iostream>
#include <istream>
#include <list>
#include <string>

using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "operand.h"
#include "variable.h"
#include "literal.h"
#include "parse.h"

Expression* Operand::parse()
{
    char paren;
    double value;

    cin >> ws;
    if (isdigit(cin.peek()))
    {
        cin >> value;
        Expression* literal = new Literal(value);
        return literal;
    }
    if (cin.peek() == '(')
    {
        cin >> paren;
        return SubExpression::parse();
    }
    else
        return new Variable(parseName());
    return 0;
}
Expression* Operand::parse(istream& input)
{
    //modified to use a reference to the istream argument instead of cin.
    char paren;
    double value;

    input >> ws;
    if (isdigit(input.peek()))
    {
        input >> value;
        Expression* literal = new Literal(value);
        return literal;
    }
    if (input.peek() == '(')
    {
        input >> paren;
        return SubExpression::parse(input);
    }
    else
        return new Variable(parseName(input));
    return 0;
}