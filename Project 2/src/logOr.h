class LogOr : public SubExpression
{
public:
    LogOr(Expression* left, Expression* right) : SubExpression(left, right)
    {
    }
    int evaluate()
    {
        return left->evaluate() || right->evaluate();
    }
};