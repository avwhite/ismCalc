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

double Val::eval()
{
    return val;
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

double Op::eval()
{
    if(right->error == true || left->error == true)
    {
        return 0;
    }
    switch (type)
    {
        case ADD: return left->eval() + right->eval(); break;
        case SUB: return left->eval() - right->eval(); break;
        case MUL: return left->eval() * right->eval(); break;
        case DIV: return left->eval() / right->eval(); break;
    }
}
