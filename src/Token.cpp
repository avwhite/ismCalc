#include "Token.h"

Token::Token(TokenType type, std::string value)
{
    this->value = value;
    this->type = type;
}

Token::~Token()
{
    //dtor
}
