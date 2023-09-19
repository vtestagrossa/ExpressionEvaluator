class LogAnd : public SubExpression
{
public:
    LogAnd(Expression* left, Expression* right) : SubExpression(left, right)
    {
    }
    int evaluate()
    {
        return left->evaluate() && right->evaluate();
    }
};