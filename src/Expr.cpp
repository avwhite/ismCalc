#include "Expr.h"

///////////////////////
//Val implementation//
/////////////////////
Val::Val(double value)
{
    val = value;
    error = false;
}

Val::~Val()
{
    //dtor
}

optDouble Val::eval()
{
    return optDouble(val, true);
}

//////////////////////
//Op implementation//
////////////////////
Op::Op(OpType opType, Expr* lefts, Expr* rights)
{
    type = opType;
    left = lefts;
    right = rights;
    error = false;
}

Op::~Op()
{
    delete left;
    delete right;
}

optDouble Op::eval()
{
    if(right->error == true || left->error == true)
        return optDouble(0,false);
    optDouble l = left->eval();
    optDouble r = right->eval();
    if(l.second == false || r.second == false)
        return optDouble(0,false);

    switch (type)
    {
        case ADD: return optDouble(l.first + r.first, true); break;
        case SUB: return optDouble(l.first - r.first, true); break;
        case MUL: return optDouble(l.first * r.first, true); break;
        case DIV: return optDouble(l.first / r.first, true); break;
    }
}

/////////////////////////
//Paran implementation//
///////////////////////

Paran::Paran(Expr* expr)
{
    this->expr = expr;
    error = false;
}

Paran::~Paran()
{
    delete expr;
}

optDouble Paran::eval()
{
    return expr->eval();
}
