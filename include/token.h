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

const std::map<std::string, int> keywordMap{
    {"if", T_IF},
    {"else", T_ELSE},
    {"while", T_WHILE},
    {"return", T_RETURN},
    {"or", T_OR},
    {"and", T_AND},
    {"not", T_NOT},
    {"Int", T_INT},
    {"Float", T_FLOAT},
    {"Bool", T_BOOL},
    {"String", T_STRING},
    {"true", T_TRUE},
    {"false", T_FALSE},
    {"Void", T_VOID},
    {"class", T_CLASS},
    {"public", T_PUBLIC},
    {"(", T_LEFTPAREN},
    {")", T_RIGHTPAREN},
    {";", T_SEMICOLON},
    {"{", T_LEFTBRACKET},
    {"}", T_RIGHTBRACKET},
    {".", T_ACCESS}
};

enum OperatorType {
    T_ASSIGN,
    T_EQ,
    T_REL,
    T_ADD,
    T_MUL,
    T_EXP
};

const std::map<std::string, int> operatorMap{
    {"=", T_ASSIGN},
    {"==", T_EQ},
    {"!=", T_EQ},
    {"<", T_REL},
    {">", T_REL},
    {"<=", T_REL},
    {">=", T_REL},
    {"+", T_ADD},
    {"-", T_ADD},
    {"*", T_MUL},
    {"/", T_MUL},
    {"**", T_EXP},
};

const std::map<std::string, long long> operatorIdMap{
    {"=", 0},
    {"==", 0},
    {"!=", 1},
    {"<", 0},
    {">", 1},
    {"<=", 2},
    {">=", 3},
    {"+", 0},
    {"-", 1},
    {"*", 0},
    {"/", 1},
    {"**", 0},
};

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
    unsigned int classType;
    unsigned int type;

    unsigned int position;
    unsigned int lineNumber;
    unsigned int linePosition;

    std::variant<long long, double, std::string> value;

    Token(int classType, int type, int pos, int lineNum, int linePos, long long value = 0)
    : classType(classType), type(type), position(pos), lineNumber(lineNum), linePosition(linePos), value(value) {}
    Token(int classType, int type, int pos, int lineNum, int linePos, double value)
    : classType(classType), type(type), position(pos), lineNumber(lineNum), linePosition(linePos), value(value) {}
    Token(int classType, int type, int pos, int lineNum, int linePos, std::string value)
    : classType(classType), type(type), position(pos), lineNumber(lineNum), linePosition(linePos), value(value) {}

    bool operator==(Token &other);
    bool operator==(Token &&other);

    const std::string toString();
    const std::string keywordToString();
    const std::string operatorToString();
    const std::string identifierToString();
    const std::string literalToString();
};