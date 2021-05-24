#include "token.h"


using namespace std;

bool Token::operator==(Token &other)
{
    if(classType != other.classType)
    {
        cerr<<"Different token class"<<endl;
        return false;
    }
    if(type != other.type)
    {
        cerr<<"Different token type"<<endl;
        return false;
    }
    if(position != other.position)
    {
        cerr<<"Different token position: "<<position<<", "<<other.position<<endl;
        return false;
    }
    if(lineNumber != other.lineNumber)
    {
        cerr<<"Different token line number"<<endl;
        return false;
    }
    if(linePosition != other.linePosition)
    {
        cerr<<"Different token line position"<<endl;
        return false;
    }
    if(value != other.value)
    {
        cerr<<"Different token value"<<endl;
        return false;
    }
    return true;
}

bool Token::operator==(Token &&other)
{
    Token t = other;
    return operator==(t);
}

const std::string Token::toString()
{
    switch (classType)
    {
        case KEYWORD_TOKEN:
            return keywordToString();
        case OPERATOR_TOKEN:
            return operatorToString();
        case IDENTIFIER_TOKEN:
            return identifierToString();
        case LITERAL_TOKEN:
            return literalToString();
        case EOT_TOKEN:
            return "EOT";
        default:
            return "Unknown";
    }
}


const std::string Token::keywordToString()
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


const std::string Token::operatorToString()
{
    std::string s = "Operator<";
    switch(type)
    {
        case T_ASSIGN:
            s += "Assign";
            break;
        case T_EQ:
            s += "Eq(";
            if(std::get<long long>(value) == 0)
                s += "==";
            else
                s += "!=";
            s += ")";
            break;
        case T_REL:
            s += "Rel(";
            switch(std::get<long long>(value))
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
            if(std::get<long long>(value) == 0)
                s += "+";
            else
                s += "-";
            s += ")";
            break;
        case T_MUL:
            s += "Mul(";
            if(std::get<long long>(value) == 0)
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




const std::string Token::identifierToString()
{
    std::string s = "Identifier<";
    switch(type)
    {
        case T_VAR:
            s += "Variable(" + std::get<std::string>(value) + ")";
            break;
        case T_TYPE:
            s += "Type(" + std::get<std::string>(value) + ")";
            break;
    }
    s += ">";
    return s;
}



const std::string Token::literalToString()
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