#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {OP, VAL};

class Token
{
    public:
        Token(TokenType type, std::string value);
        virtual ~Token();
        TokenType type;
        std::string value;
};

#endif // TOKEN_H
