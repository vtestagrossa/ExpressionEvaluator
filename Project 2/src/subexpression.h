class SubExpression: public Expression
{
public:
    SubExpression(Expression* left, Expression* right);
    SubExpression(Expression* left);
    SubExpression(Expression* left, Expression* right, Expression* condition);
    static Expression* parse();
    static Expression* parse(istream& input);
    static void validateInput(char input, char expected);
protected: 
    Expression* left;
    Expression* right;
    Expression* condition;
};    