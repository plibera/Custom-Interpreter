#pragma once

#include <iostream>
#include <variant>
#include <map>


enum TokenClass {
    UNKNOWN_TOKEN,
    EOT_TOKEN,
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
    T_TRUE,
    T_FALSE,
    T_VOID,
    T_CLASS,
    T_PUBLIC,
    T_LEFTPAREN,
    T_RIGHTPAREN,
    T_SEMICOLON,
    T_LEFTBRACKET,
    T_RIGHTBRACKET,
    T_ACCESS,
    T_COMMA
};

extern std::map<std::string, int> keywordMap;

enum OperatorType {
    T_ASSIGN,
    T_EQ,
    T_REL,
    T_ADD,
    T_MUL,
    T_EXP
};

extern std::map<std::string, int> operatorMap;
extern std::map<std::string, int> operatorIdMap;

enum IdentifierType {
    T_TYPE,
    T_VAR
};

enum LiteralType {
    T_INT_LIT,
    T_FLOAT_LIT,
    T_STRING_LIT
};



struct Token
{
    int classType;
    int type;

    int position;
    int lineNumber;
    int linePosition;

    Token(int classType, int type, int pos, int lineNum, int linePos)
    : classType(classType), type(type), position(pos), lineNumber(lineNum), linePosition(linePos) {}
    virtual ~Token(){}

    virtual std::string toString();
};


struct KeywordToken
: Token
{
    KeywordToken(int type, int pos, int lineNum, int linePos)
    :Token(KEYWORD_TOKEN, type, pos, lineNum, linePos) {}

    virtual std::string toString();
};


struct OperatorToken
: Token
{
    int operatorType;

    OperatorToken(int type, int pos, int lineNum, int linePos, int opType)
    :Token(OPERATOR_TOKEN, type, pos, lineNum, linePos), operatorType(opType) {}

    virtual std::string toString();
};

struct IdentifierToken
: Token
{
    std::string name;

    IdentifierToken(int type, int pos, int lineNum, int linePos, std::string name)
    :Token(IDENTIFIER_TOKEN, type, pos, lineNum, linePos), name(name) {}

    virtual std::string toString();
};


struct LiteralToken
: Token
{
    std::variant<long long, double, std::string> value;

    LiteralToken(int type, int pos, int lineNum, int linePos, long long value)
    :Token(LITERAL_TOKEN, type, pos, lineNum, linePos), value(value) {}

    LiteralToken(int type, int pos, int lineNum, int linePos, double value)
    :Token(LITERAL_TOKEN, type, pos, lineNum, linePos), value(value) {}

    LiteralToken(int type, int pos, int lineNum, int linePos, std::string value)
    :Token(LITERAL_TOKEN, type, pos, lineNum, linePos), value(value) {}

    virtual std::string toString();
};