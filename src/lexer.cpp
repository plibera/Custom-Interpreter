#include "lexer.h"

using namespace std;

Lexer::Lexer(std::istream& stream)
:source(stream)
{
    nextChar = source.get();
}


Token Lexer::getToken()
{
    skipWhitesAndComments();
    pos = source.getSourceIndex();
    lNum = source.getLineNumber();
    lPos = source.getLineIndex();
    if(nextChar == EOF)
    {
        return Token(EOT_TOKEN, 0, pos, lNum, lPos);
    }

    token = nullptr;
    token = buildOneCharToken();
    if(token != nullptr)
        return *token;
    token = buildKeywordOrIdentifier();
    if(token != nullptr)
        return *token;
    token = buildOperator();
    if(token != nullptr)
        return *token;
    token = buildStringLiteral();
    if(token != nullptr)
        return *token;
    token = buildNumericLiteral();
    if(token != nullptr)
        return *token;
    nextChar = source.get();
    
    return Token(UNKNOWN_TOKEN, 0, pos, lNum, lPos);
}


void Lexer::skipWhitesAndComments()
{
    bool isComment = nextChar == '#';
    while(isspace(nextChar) || isComment)
    {
        nextChar = source.get();
        if(nextChar == '\n')
            isComment = false;
        if(nextChar == '#')
            isComment = true;
        if(nextChar == EOF)
            return;
    }
}


Token* Lexer::buildOneCharToken()
{
    switch(nextChar)
    {
        case '(':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_LEFTPAREN, pos, lNum, lPos);
        case ')':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_RIGHTPAREN, pos, lNum, lPos);
        case ';':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_SEMICOLON, pos, lNum, lPos);
        case '{':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_LEFTBRACKET, pos, lNum, lPos);
        case '}':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_RIGHTBRACKET, pos, lNum, lPos);
        case '.':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_ACCESS, pos, lNum, lPos);
        case ',':
            nextChar = source.get();
            return new Token(KEYWORD_TOKEN, T_COMMA, pos, lNum, lPos);
        default:
            return nullptr;
    }
}


Token* Lexer::buildKeywordOrIdentifier()
{
    if(!isalpha(nextChar))
        return nullptr;

    int counter = 0;
    stringstream ss;
    ss<<nextChar;
    counter++;
    nextChar = source.get();
    while(isalnum(nextChar) || nextChar == '_')
    {
        ss<<nextChar;
        counter++;
        if(counter > MAX_IDENTIFIER_LENGTH)
            throw runtime_error("Identifier name exceeded maximum length");
        nextChar = source.get();
    }
    string name = ss.str();
    
    auto it = keywordMap.find(name);
    if(it != keywordMap.end())
    {
        return new Token(KEYWORD_TOKEN, it->second, pos, lNum, lPos);
    }
    if(islower(name[0]))
        return new Token(IDENTIFIER_TOKEN, T_VAR, pos, lNum, lPos, name);
    else
        return new Token(IDENTIFIER_TOKEN, T_TYPE, pos, lNum, lPos, name);
}


Token* Lexer::buildOperator()
{
    if(nextChar == '=')
    {
        nextChar = source.get();
        if(nextChar == '=')
        {
            nextChar = source.get();
            return new Token(OPERATOR_TOKEN, operatorMap.at("=="), pos, lNum, lPos, operatorIdMap.at("=="));
        }
        else
        {
            return new Token(OPERATOR_TOKEN, operatorMap.at("="), pos, lNum, lPos, operatorIdMap.at("="));
        }
    }
    if(nextChar == '!')
    {
        nextChar = source.get();
        if(nextChar == '=')
        {
            nextChar = source.get();
            return new Token(OPERATOR_TOKEN, operatorMap.at("!="), pos, lNum, lPos, operatorIdMap.at("!="));
        }
        else
        {
            return new Token(UNKNOWN_TOKEN, 0, pos, lNum, lPos);
        }
        
    }
    if(nextChar == '<')
    {
        nextChar = source.get();
        if(nextChar == '=')
        {
            nextChar = source.get();
            return new Token(OPERATOR_TOKEN, operatorMap.at("<="), pos, lNum, lPos, operatorIdMap.at("<="));
        }
        else
        {
            return new Token(OPERATOR_TOKEN, operatorMap.at("<"), pos, lNum, lPos, operatorIdMap.at("<"));
        }
    }
    if(nextChar == '>')
    {
        nextChar = source.get();
        if(nextChar == '=')
        {
            nextChar = source.get();
            return new Token(OPERATOR_TOKEN, operatorMap.at(">="), pos, lNum, lPos, operatorIdMap.at(">="));
        }
        else
        {
            return new Token(OPERATOR_TOKEN, operatorMap.at(">"), pos, lNum, lPos, operatorIdMap.at(">"));
        }
    }
    if(nextChar == '+')
    {
        nextChar = source.get();
        return new Token(OPERATOR_TOKEN, operatorMap.at("+"), pos, lNum, lPos, operatorIdMap.at("+"));
    }
    if(nextChar == '-')
    {
        nextChar = source.get();
        return new Token(OPERATOR_TOKEN, operatorMap.at("-"), pos, lNum, lPos, operatorIdMap.at("-"));
    }
    if(nextChar == '/')
    {
        nextChar = source.get();
        return new Token(OPERATOR_TOKEN, operatorMap.at("/"), pos, lNum, lPos, operatorIdMap.at("/"));
    }
    if(nextChar == '*')
    {
        nextChar = source.get();
        if(nextChar == '*')
        {
            nextChar = source.get();
            return new Token(OPERATOR_TOKEN, operatorMap.at("**"), pos, lNum, lPos, operatorIdMap.at("**"));
        }
        else
        {
            return new Token(OPERATOR_TOKEN, operatorMap.at("*"), pos, lNum, lPos, operatorIdMap.at("*"));
        }
    }
    return nullptr;
}


Token* Lexer::buildStringLiteral()
{
    if(nextChar != '"')
        return nullptr;
    stringstream ss;
    nextChar = source.get();
    int counter = 0;
    bool isNextLiteral = false;
    while((nextChar != '"' || isNextLiteral) && nextChar != EOF)
    {
        if(nextChar != '\\' || isNextLiteral)
        {
            if(isNextLiteral && nextChar == 'n')
            {
                ss<<'\n';
            }
            else if(isNextLiteral && nextChar == 't')
            {
                ss<<'\t';
            }
            else
            {
                ss<<nextChar;
                counter++;
            }
            isNextLiteral = false;
        }
        else
        {
            isNextLiteral = true;
        }
        
        if(counter > MAX_STRING_LITERAL_LENGTH)
            throw runtime_error("String literal exceeded maximum allowed length");
        
        nextChar = source.get();
    }
    if(nextChar == EOF)
    {
        return nullptr;
    }
    string value = ss.str();
    nextChar = source.get();
    return new Token(LITERAL_TOKEN, T_STRING_LIT, pos, lNum, lPos, value);
}


Token* Lexer::buildNumericLiteral()
{
    if(!isdigit(nextChar))
        return nullptr;

    double value = 0;
    if(nextChar == '0')
    {
        nextChar = source.get();
        if(nextChar == '.')
        {
            //Continue to fractional part
            nextChar = source.get();
        }
        else if(isalnum(nextChar))
        {
            while(isalnum(nextChar))
            {
                nextChar = source.get();
            }
            return new Token(UNKNOWN_TOKEN, 0, pos, lNum, lPos);
        }
        else
        {
            return new Token(LITERAL_TOKEN, T_INT_LIT, pos, lNum, lPos, (long long)0);
        }
    }
    else
    {
        value = (double)(nextChar-'0');
        nextChar = source.get();
        while(isdigit(nextChar))
        {
            if(value > (std::numeric_limits<long long>::max() - (double)(nextChar-'0'))/10)
                throw runtime_error("Numeric literal exceeded limit");
            value *= 10;
            value += (double)(nextChar-'0');
            nextChar = source.get();                
        }
        if(isalpha(nextChar))
        {
            while(isalnum(nextChar))
            {
                nextChar = source.get();
            }
            return new Token(UNKNOWN_TOKEN, 0, pos, lNum, lPos);
        }
        if(nextChar != '.')
        {
            return new Token(LITERAL_TOKEN, T_INT_LIT, pos, lNum, lPos, (long long)value);
        }
        nextChar = source.get();
    }
    
    //Fractional part
    if(!isdigit(nextChar))
    {
        while(isalnum(nextChar))
        {
            nextChar = source.get();
        }
        return new Token(UNKNOWN_TOKEN, 0, pos, lNum, lPos);
    }

    double multiplier = 1;
    while(isdigit(nextChar))
    {
        if(multiplier <= __DBL_MIN__ * 10)
        {
            throw runtime_error("Floating point literal exceeded resolution limit");
        }
        multiplier *= 0.1;
        value += (double)(nextChar-'0')*multiplier;
        nextChar = source.get();
    }
    
    if(isalpha(nextChar))
    {
        while(isalnum(nextChar))
        {
            nextChar = source.get();
        }
        return new Token(UNKNOWN_TOKEN, 0, pos, lNum, lPos);
    }

    return new Token(LITERAL_TOKEN, T_FLOAT_LIT, pos, lNum, lPos, value);
}