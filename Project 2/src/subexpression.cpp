/*
 * Vincent Testagrossa
 * Project 2: Expression Evaluator
 * 02OCT2022
 *
 * Requirements: expression, subexpression, operand, plus, minus, times, divide, greaterThan, lessThan, equalTo, logAnd, logOr, logNeg,
 * conditional.
 *
 * Description:
 * Determines the type of subexpression as defined in the grammar, then returns the proper operation for the left, left and right, or 
 * left right and condition. Handles basic input validation and throws invalid_argument exceptions as a syntaxError.
 */
#include <iostream>
#include <fstream>
using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "operand.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "greaterThan.h"
#include "lessThan.h"
#include "equalTo.h"
#include "logAnd.h"
#include "logOr.h"
#include "logNeg.h"
#include "conditional.h"

SubExpression::SubExpression(Expression* left)
{
    //Used for logical negation operations. Only the left expression is passed.
    this->left = left;
}
SubExpression::SubExpression(Expression* left, Expression* right)
{
    //Normal expressions with a left and a right side.
    this->left = left;
    this->right = right;
}
SubExpression::SubExpression(Expression* left, Expression* right, Expression* condition)
{
    //3 sided expression for conditionals. Left if true, right if false, and the condition to be true or false.
    this->left = left;
    this->right = right;
    this->condition = condition;
}
Expression* SubExpression::parse()
{
    //The base method that parses subexpressions. Takes no istream input and assumes cin.
    Expression* left;
    Expression* right;
    Expression* condition;
    char operation, paren, question;
    
    left = Operand::parse();
    cin >> operation;
    if (operation == '!')
    {
        cin >> paren;
        validateInput(paren, ')');
        return new LogNeg(left);
    }
    else if (operation == ':')
    {
        right = Operand::parse();
        cin >> question;
        validateInput(question, '?');
        condition = Operand::parse();
        cin >> paren;
        validateInput(paren, ')');
        return new Conditional(left, right, condition);
    }
    else
    {
        right = Operand::parse();
        cin >> paren;
        validateInput(paren, ')');
    }
    switch (operation)
    {
        case '+':
            return new Plus(left, right);
        case '-':
            return new Minus(left, right);
        case '*':
            return new Times(left, right);
        case '/':
            return new Divide(left, right);
        case '>':
            return new GreaterThan(left, right);
        case '<':
            return new LessThan(left, right);
        case '=':
            return new EqualTo(left, right);
        case '&':
            return new LogAnd(left, right);
        case '|':
            return new LogOr(left, right);
        default:
            string errorMsg = "Invalid Operation: '";
            errorMsg += operation;
            errorMsg += "'.";
            throw std::invalid_argument(errorMsg);
    }
    return 0;
}
Expression* SubExpression::parse(istream& input)
{
    //extended parse method. Takes an istream reference and uses it for an input stream.
    Expression* left;
    Expression* right;
    Expression* condition;
    char operation, paren, question;

    left = Operand::parse(input);
    input >> operation;
    //First checks operation for special cases, like not and conditional, so the constructor can be called as needed.
    if (operation == '!')
    {
        //the next character was '!'. Validates the following is paren, then continues with logical negation.
        input >> paren;
        validateInput(paren, ')');
        return new LogNeg(left);
    }
    else if (operation == ':')
    {
        //Next character signifies a conditional, so the right, a question mark, and the condition need to be parsed.
        right = Operand::parse(input);
        input >> question;
        validateInput(question, '?');
        condition = Operand::parse(input);
        input >> paren;
        validateInput(paren, ')');
        return new Conditional(left, right, condition);
    }
    else
    {
        //Regular operation detected. parse the right and look for a closing paren.
        right = Operand::parse(input);
        input >> paren;
        validateInput(paren, ')');
    }
    switch (operation)
    {
        //checks for valid operations and returns the operation to the caller.
        case '+':
            return new Plus(left, right);
        case '-':
            return new Minus(left, right);
        case '*':
            return new Times(left, right);
        case '/':
            return new Divide(left, right);
        case '>':
            return new GreaterThan(left, right);
        case '<':
            return new LessThan(left, right);
        case '=':
            return new EqualTo(left, right);
        case '&':
            return new LogAnd(left, right);
        case '|':
            return new LogOr(left, right);
        default:
            //operation is invalid, so throw an exception.
            string errorMsg = "Invalid Operation: '";
            errorMsg += operation;
            errorMsg += "'.";
            throw std::invalid_argument(errorMsg);
    }
    return 0;
}
//used for some basic input validation.
void SubExpression::validateInput(char input, char expected) {
    //Checks the input against the expected character and throws invalid_argument if they don't match.
    if (input != expected)
    {
        string errorMsg = "Invalid Syntax: '";
        errorMsg += input;
        errorMsg += "'. '";
        errorMsg += expected;
        errorMsg += "' expected.";
        throw std::invalid_argument(errorMsg);
    }
}
        