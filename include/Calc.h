#ifndef CALC_H
#define CALC_H

#include <string>
#include <vector>
#include <utility>
#include <stdlib.h>
#include "Token.h"
#include "Expr.h"

typedef std::pair<std::vector<Token>,std::vector<Token> > tPair;

class Calc
{
    public:
        Calc();
        virtual ~Calc();

        optDouble calc(std::string expression);
    private:
        std::vector<Token> tokenize(std::string input);
        Expr* parse(std::vector<Token> tokens);

        //data structure containing variables
        //data structure containing functions
};

#endif // CALC_H
