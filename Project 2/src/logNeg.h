class LogNeg: public SubExpression
{
public:
    LogNeg(Expression* left): SubExpression(left)
    {
    }
    int evaluate()
    {
        return !left->evaluate();
    }
};