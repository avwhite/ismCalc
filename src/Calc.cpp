#include "Calc.h"

//These functions should be included from somewhere! --------------------------------------

/*
 *! this function needs error checking. Crashes if 0 > index > vec.size() !
 *splits a vector into two at index.
 *The element at index is not included in any of the two new vectors.
 *The new vectors are retuned in a std::pair structure.
 */
template<class T>
std::pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, int index)
{
    std::vector<T> head;
    std::vector<T> tail;

    head.assign(vec.begin(), vec.begin()+index);
    tail.assign(vec.begin()+index+1, vec.end());

    return std::pair<std::vector<T>,std::vector<T> >(head, tail);
}

//this one does not work, which is fucking annoying since it should!
template<class T, typename iterator>
std::pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, iterator index)
{
    std::vector<T> head;
    std::vector<T> tail;

    head.assign(vec.begin(), index);
    tail.assign(++index, vec.end());

    return std::pair<std::vector<T>,std::vector<T> >(head, tail);
}

//------------------------------------------------------------------------------------

Calc::Calc()
{
    //ctor
}

Calc::~Calc()
{
    //dtor
}

double Calc::calc(std::string expression)
{
    return parse(tokenize(expression))->eval();
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

    //This is not a leaf node, start looking for operators in the correct order.
    int i2;
    std::vector<Token>::iterator i;
    for( i = tokens.begin(), i2 = 0; i != tokens.end(); ++i, ++i2)
    {
        Token t = *i;
        if(t.type == OP && (t.value == "+" || t.value == "-"))
        {
            tPair tp = split(tokens, i2);

            Expr* e = new Op((t.value == "+") ? (ADD) : (SUB), parse(tp.first), parse(tp.second));
            return e;
        }
    }

    for(i = tokens.begin(), i2 = 0; i != tokens.end(); ++i, ++i2)
    {
        Token t = *i;
        if(t.type == OP && (t.value == "*" || t.value == "/"))
        {
            tPair tp = split(tokens, i2);

            Expr* e = new Op((t.value == "*") ? (MUL) : (DIV), parse(tp.first), parse(tp.second));
            return e;
        }
    }

    //Log some form of error message somewhere, becaouse this is NEVER supposed to be executed!
    return NULL;
}
