#pragma once

#include <iostream>
#include <variant>


enum TokenClass {
    UNKNOWN_TOKEN,
    KEYWORD_TOKEN,
    OPERATOR_TOKEN,
    IDENTIFIER_TOKEN,
    LITERAL_TOKEN
};

enum KeywordType {
    T_IF,
    T_ELSE,
    T_WHILE,
    T_RETURN,
    T_OR,
    T_AND,
    T_NOT,
    T_INT,
    T_FLOAT,
    T_BOOL,
    T_STRING,
    T_VOID,
    T_CLASS,
    T_PUBLIC,
    T_LEFTPAREN,
    T_RIGHTPAREN,
    T_SEMICOLON,
    T_LEFTBRACKET,
    T_RIGHTBRACKET,
    T_EOT
};

enum OperatorType {
    T_ASSIGN,
    T_EQ,
    T_REL,
    T_ADD,
    T_MUL,
    T_EXP
};

enum IdentifierType {
    T_TYPE,
    T_VAR
};

enum LiteralType {
    T_INT_LIT,
    T_FLOAT_LIT,
    T_BOOL_LIT,
    T_STRING_LIT
};



struct Token
{
    int classType;
    int type;

    int position;
    int lineNumber;
    int linePosition;

    virtual ~Token(){}
};


struct KeywordToken
: Token
{
    KeywordToken() { classType = KEYWORD_TOKEN; }
};


struct OperatorToken
: Token
{
    int operatorType;

    OperatorToken() { classType = OPERATOR_TOKEN; }
};

struct IdentifierToken
: Token
{
    std::string name;

    IdentifierToken() { classType = IDENTIFIER_TOKEN; }
};


struct LiteralToken
: Token
{
    std::variant<long long, double, bool, std::string> value;

    LiteralToken() { classType = LITERAL_TOKEN; }
};