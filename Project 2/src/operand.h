class Operand: public Expression
{
public:
    static Expression* parse();
    static Expression* parse(istream& input);
};
