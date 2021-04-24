#include "token.h"



std::map<std::string, int> keywordMap{
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


std::map<std::string, int> operatorMap{
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

std::map<std::string, int> operatorIdMap{
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


std::string Token::toString()
{
    std::string s;
    switch (classType)
    {
        case UNKNOWN_TOKEN:
            s += "Unknown";
            break;
        case EOT_TOKEN:
            s += "EOT";
            break;
    }
    return s;
}


std::string KeywordToken::toString()
{
    std::string s = "Keyword<";
    switch(type)
    {
        case T_IF:
            s += "if";
            break;
        case T_ELSE:
            s += "else";
            break;
        case T_WHILE:
            s += "while";
            break;
        case T_RETURN:
            s += "return";
            break;
        case T_OR:
            s += "or";
            break;
        case T_AND:
            s += "and";
            break;
        case T_NOT:
            s += "not";
            break;
        case T_INT:
            s += "int";
            break;
        case T_FLOAT:
            s += "float";
            break;
        case T_BOOL:
            s += "bool";
            break;
        case T_STRING:
            s += "string";
            break;
        case T_TRUE:
            s += "true";
            break;
        case T_FALSE:
            s += "false";
            break;
        case T_VOID:
            s += "void";
            break;
        case T_CLASS:
            s += "class";
            break;
        case T_PUBLIC:
            s += "public";
            break;
        case T_LEFTPAREN:
            s += "left_paren";
            break;
        case T_RIGHTPAREN:
            s += "right_paren";
            break;
        case T_SEMICOLON:
            s += "semicolon";
            break;
        case T_LEFTBRACKET:
            s += "left_bracket";
            break;
        case T_RIGHTBRACKET:
            s += "right_bracket";
            break;
        case T_ACCESS:
            s += "access_operator";
            break;
        case T_COMMA:
            s += "comma";
            break;
    }
    s += ">";
    return s;
}


std::string OperatorToken::toString()
{
    std::string s = "Operator<";
    switch(type)
    {
        case T_ASSIGN:
            s += "Assign";
            break;
        case T_EQ:
            s += "Eq(";
            if(operatorType == 0)
                s += "==";
            else
                s += "!=";
            s += ")";
            break;
        case T_REL:
            s += "Rel(";
            switch(operatorType)
            {
                case 0:
                    s += "<";
                    break;
                case 1:
                    s += ">";
                    break;
                case 2:
                    s += "<=";
                    break;
                case 3:
                    s += ">=";
                    break;
            }
            s += ")";
            break;
        case T_ADD:
            s += "Add(";
            if(operatorType == 0)
                s += "+";
            else
                s += "-";
            s += ")";
            break;
        case T_MUL:
            s += "Mul(";
            if(operatorType == 0)
                s += "*";
            else
                s += "/";
            s += ")";
            break;
        case T_EXP:
            s += "Exp";
            break;
    }
    s += ">";
    return s;
}




std::string IdentifierToken::toString()
{
    std::string s = "Identifier<";
    switch(type)
    {
        case T_VAR:
            s += "Variable(" + name + ")";
            break;
        case T_TYPE:
            s += "Type(" + name + ")";
            break;
    }
    s += ">";
    return s;
}



std::string LiteralToken::toString()
{
    std::string s = "Literal<";
    switch(type)
    {
        case T_INT_LIT:
            s += "Integer(" + std::to_string(std::get<long long>(value)) + ")";
            break;
        case T_FLOAT_LIT:
            s += "Float(" + std::to_string(std::get<double>(value)) + ")";
            break;
        case T_STRING_LIT:
            s += "String(" + std::get<std::string>(value) + ")";
            break;
    }
    s += ">";
    return s;
}