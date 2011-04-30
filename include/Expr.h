#ifndef EXPR_H
#define EXPR_H

#include <utility>

typedef std::pair<double,bool> optDouble;

enum OpType {ADD, SUB, MUL, DIV};

class Expr
{
    public:
        virtual optDouble eval() = 0;
        bool error;
};

class Op : public Expr
{
    public:
        Op(OpType opType, Expr* lefts, Expr* rights);
        virtual ~Op();

        optDouble eval();
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

        optDouble eval();
    private:
        double val;
};

class Paran : public Expr
{
    public:
        Paran(Expr* expr);
        virtual ~Paran();

        optDouble eval();
    private:
        Expr* expr;
};

#endif // EXPR_H
