#ifndef EXPR_H
#define EXPR_H

enum OpType {ADD, SUB, MUL, DIV};

class Expr
{
    public:
        virtual double eval() = 0;
        bool error;
};

class Op : public Expr
{
    public:
        Op(OpType opType, Expr* lefts, Expr* rights);
        virtual ~Op();

        double eval();
    private:
        Expr* left;
        Expr* right;
        OpType type;
};

class Val : public Expr
{
    public:
        Val(double value);
        virtual ~Val();

        double eval();
    private:
        double val;
};

#endif // EXPR_H
