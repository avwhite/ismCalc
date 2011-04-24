#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include "Expr.h"
#include "Token.h"

using namespace std;

template<class T>
pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, int index);
template<class T, typename iterator>
std::pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, iterator index);
std::vector<Token> tokenize(std::string input);
Expr* parse(std::vector<Token> tokens);


int main()
{
    /*Expr* a = new Val(10);
    Expr* b = new Val(10);
    Expr* d = new Op(ADD, a, b);
    Expr* e = new Val(20);
    Expr* f = new Op(MUL, d, e);


    cout << f->eval() << endl;
    delete f;

    std::vector<int> l1;
    for (int i = 0; i < 10; ++i)
    {
        l1.push_back(i);
    }
    pair<std::vector<int>,std::vector<int> > res = split(l1, 122);
    for(std::vector<int>::iterator i = res.first.begin(); i != res.first.end(); ++i)
    {
        cout << *i << std::endl;
    }
    cout << endl;
    for(std::vector<int>::iterator i = res.second.begin(); i != res.second.end(); ++i)
    {
        cout << *i << std::endl;
    }*/
    vector<Token> tok = tokenize("11*22+2");
    for(std::vector<Token>::iterator i = tok.begin(); i != tok.end(); ++i)
    {
        cout << (*i).value << std::endl;
    }

    Expr* e = parse(tok);
    cout << e->eval() << endl;


    return 0;
}

std::vector<Token> tokenize(std::string input)
{
    vector<Token> res;

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
            res.push_back(Token(OP, string(1,current)));
        }
    }
    return res;
}

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

template<class T, typename iterator>
std::pair<std::vector<T>,std::vector<T> > split(std::vector<T> vec, iterator index)
{
    std::vector<T> head;
    std::vector<T> tail;

    head.assign(vec.begin(), index);
    tail.assign(++index, vec.end());

    return std::pair<std::vector<T>,std::vector<T> >(head, tail);
}


typedef std::pair<std::vector<Token>,std::vector<Token> > tPair;

//this implementation is recursive(not even tail recursive) and is probably very inefficient.
Expr* parse(std::vector<Token> tokens)
{
    if(tokens.size() == 1 && tokens.at(0).type == VAL)
    {
        //this is going to be ar leaf node, just return the value.
        Expr* e = new Val(atof(tokens.at(0).value.c_str()));
        return e;
    }

    //This is not a leaf node, start looking for operators in the correct order.
    int i2;
    vector<Token>::iterator i;
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

    cout << "somethings fucked" << endl;
    return NULL;
}
