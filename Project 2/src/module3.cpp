/*
 * Vincent Testagrossa
 * Project 2: Expression Evaluator
 * 02OCT2022
 *
 * Requirements: expression, subexpression, symboltable, parse.
 * 
 * Description: Accepts a file input, or input from cin in the following format:
 * 
 * <program> -> <exp> , <assigns> ;
 * <exp> -> ( <operand> <op> <operand> ) | 
 *          ( <operand ':' <operand> '?' <operand> ) |
 *          ( <operand> '!' )
 * <op> -> '+' | '-' | '*' | '/' | '>' | '<' | '=' | '&' | '|'
 * <operand> -> <literal> | <variable> | <exp> 
 * <assigns> -> <assigns> , <assign> | <assign>
 * <assign> -> <variable> = <literal>
 * 
 * If the args are file input, the program reads file by file, line by line, evaluating each expression
 * on a line. If there are no args, the user is prompted for input in the terminal. 
 */
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "symboltable.h"
#include "parse.h"

SymbolTable symbolTable;

void parseExpression();
void parseExpression(istream& input);
void parseAssignments();
void parseAssignments(istream& input);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        try {
            //Sets the istream to reference cin, then passes the reference to the parseExpression(input) method.
            istream& input = cin;
            parseExpression(input);
            std::cout << "Press any key to exit." << argv[0] << endl;
            int flag = _getch();
            return 0;
        }
        catch (const std::invalid_argument & e) {
            std::cout << e.what() << std::endl;
            int flag = _getch();
            return -1;
        }
    }
    else if (argc >= 2)
    {
        try{
            /* 
                Detects one or more file was opened with the program. Calls fileReader and passes the string to parseExpression().
            */
            for (int i = 1; i < argc; i++)
            { 
                //sets the inputfilestream to the current argument and tests for failure to load a file.
                ifstream ifn(argv[i]);
                if (ifn.fail())
                {
                    std::cout << "File not found " << argv[i] << endl;
                    return 1;
                }
                //reading the file line by line into a string, which is converted into a stringstream to be passed as an istream.
                string line;
                while (std::getline(ifn, line))
                {
                    stringstream convertedLine;
                    std::cout << line << " " << endl;
                    convertedLine << line;
                    istream& input = convertedLine;
                    parseExpression(input);
                    std::cout << endl;
                    symbolTable.clear();
                }
            }
            std::cout << "Press any key to exit." << endl;
            int flag = _getch();
            return 0;
        }
        catch (const std::invalid_argument & e) {
            //prints the syntax error to cout.
            std::cout << e.what() << std::endl;
            int flag = _getch();
            return -1;
        }
    }
    
}
void parseExpression() 
{
    //default parseExpression() method. Uses cin without redirecting to an istream of a selected type.
    Expression* expression;
    char paren, comma;

    std::cout << "Enter expression: ";
    cin >> paren;
    SubExpression::validateInput(paren, '(');
    expression = SubExpression::parse();
    cin >> comma;
    SubExpression::validateInput(comma, ',');
    parseAssignments();
    std::cout << "Value = " << expression->evaluate() << endl;
}
void parseExpression(istream& input)
{
    //uses an istream reference to handle input and calls the overloaded parse methods.
    Expression* expression;
    char paren, comma;

    input >> paren;
    SubExpression::validateInput(paren, '(');
    expression = SubExpression::parse(input);
    input >> comma;
    SubExpression::validateInput(comma, ',');
    parseAssignments(input);
    std::cout << "Value = " << expression->evaluate() << endl;
}
void parseAssignments()
{
    //default for parseAssignments(). Takes no istream reference.
    char assignop, delimiter;
    string variable;
    double value;
    do
    {
        variable = parseName();
        cin >> ws >> assignop >> value >> delimiter;
        symbolTable.insert(variable, value);
    }
    while (delimiter == ',');
}
void parseAssignments(istream& input)
{
    //Takes a reference to an istream to handle input for parsing assignments.
    char assignop, delimiter;
    string variable;
    double value;
    do
    {
        variable = parseName(input);
        input >> ws >> assignop >> value >> delimiter;
        symbolTable.insert(variable, value);
    } while (delimiter == ',');
}