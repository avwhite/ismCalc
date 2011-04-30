#include "Calc.h"
#include "Utils.h"

#include <iostream>

Calc::Calc()
{
    //ctor
}

Calc::~Calc()
{
    //dtor
}

optDouble Calc::calc(std::string expression)
{
    std::vector<Token> t = tokenize(expression);
    Expr* e = parse(t);
    return e->eval();
}

std::vector<Token> Calc::tokenize(std::string input)
{
    std::vector<Token> res;

    for(int currentIndex = 0; currentIndex < input.length(); ++currentIndex)
    {
        char current = input.at(currentIndex);
        //checks if current is a number (0...9)
        if(current >= 0x30 && current <= 0x39)
        {
            int until = currentIndex;
            while((input.at(until) >= 0x30 && input.at(until) <= 0x39))
            {
                //this part makes sure that until wont ever be bigger than the length of the string
                //It also makes sure the correctt thing happens if the end is reached.
                if(until >= input.length()-1)
                {
                    if(input.at(until) >= 0x30 && input.at(until) <= 0x39)
                        ++until;
                    break;
                }

                ++until;
            }
            std::string num = input.substr(currentIndex, until-currentIndex);
            res.push_back(Token(VAL, num));
            currentIndex = until-1;
        }
        else if(current == '+' || current == '-' || current == '*' || current == '/')
        {
            res.push_back(Token(OP, std::string(1,current)));
        }
        else if(current == '(' || current == ')')
        {
            res.push_back(Token(PARAN, std::string(1, current)));
        }
    }
    return res;
}

Expr* Calc::parse(std::vector<Token> tokens)
{
    if(tokens.size() == 1 && tokens.at(0).type == VAL)
    {
        //this is going to be ar leaf node, just return the value.
        Expr* e = new Val(atof(tokens.at(0).value.c_str()));
        return e;
    }

    if((tokens.front().type == PARAN) && (tokens.front().value == "(") && (tokens.back().type == PARAN && tokens.back().value == ")"))
    {
        std::vector<Token> v;
        v.assign(++tokens.begin(), --tokens.end());
        Expr* e = new Paran(parse(v));
        return e;
    }

    //expression starting with or ending with and operator or containing multiple ops in a row.
    if(tokens.front().type == OP || tokens.back().type == OP)
    {
        Expr* error = new Val(0);
        error->error = true;
        return error;
    }

    //This is not a leaf node, start looking for operators in the correct order.
    int i2;
    //inParan is for keeping track of if we are inside a paranthesis. If this value is 0, then we are not, and we can split the token vector. if it is >0 we can not split it.
    int inParan;
    std::vector<Token>::iterator i;
    for( i = tokens.begin(), i2 = 0, inParan = 0; i != tokens.end(); ++i, ++i2)
    {
        Token t = *i;
        if(t.type == OP && (t.value == "+" || t.value == "-") && inParan == 0)
        {
            tPair tp = split(tokens, i2);

            Expr* e = new Op((t.value == "+") ? (ADD) : (SUB), parse(tp.first), parse(tp.second));
            return e;
        }
        if(t.type == PARAN)
            (t.value == "(") ? (++inParan) : (--inParan);
    }

    for(i = tokens.begin(), i2 = 0, inParan = 0; i != tokens.end(); ++i, ++i2)
    {
        Token t = *i;
        if(t.type == OP && (t.value == "*" || t.value == "/") && inParan == 0)
        {
            tPair tp = split(tokens, i2);

            Expr* e = new Op((t.value == "*") ? (MUL) : (DIV), parse(tp.first), parse(tp.second));
            return e;
        }
        if(t.type == PARAN)
            (t.value == "(") ? (++inParan) : (--inParan);
    }

    //Log some form of error message somewhere, becaouse this is NEVER supposed to be executed!
    return NULL;
}
