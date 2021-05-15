#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#include "token.h"
#include "source.h"

#define MAX_IDENTIFIER_LENGTH 128
#define MAX_STRING_LITERAL_LENGTH 4096

class Lexer
{
    Source source;
    char nextChar;
    int pos;
    int lNum;
    int lPos;
    Token* token;

    void skipWhitesAndComments();
    //Builds parentheses, brackets, semicolon
    Token* buildOneCharToken();

    Token* buildKeywordOrIdentifier();
    //Builds operator tokens
    Token* buildOperator();

    Token* buildStringLiteral();

    Token* buildNumericLiteral();

public:
    Lexer(std::istream& stream);
    ~Lexer() {delete token;}

    Token getToken();
};