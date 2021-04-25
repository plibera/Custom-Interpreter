#include "testLexer.h"

using namespace std;


bool areTokensEqual(Token* a, Token* b)
{
    if(a == nullptr || b == nullptr)
    {
        cerr<<"One fo the tokens is null"<<endl;
        return false;
    }
    if(a->classType != b->classType)
    {
        cerr<<"Different token class"<<endl;
        return false;
    }
    if(a->type != b->type)
    {
        cerr<<"Different token type"<<endl;
        return false;
    }
    if(a->position != b->position)
    {
        cerr<<"Different token position: "<<a->position<<", "<<b->position<<endl;
        return false;
    }
    if(a->lineNumber != b->lineNumber)
    {
        cerr<<"Different token line number"<<endl;
        return false;
    }
    if(a->linePosition != b->linePosition)
    {
        cerr<<"Different token line position"<<endl;
        return false;
    }
    
    if(a->classType == OPERATOR_TOKEN)
    {
        OperatorToken* at = dynamic_cast<OperatorToken*>(a);
        OperatorToken* bt = dynamic_cast<OperatorToken*>(b);
        if(at == nullptr || bt == nullptr)
        {
            cerr<<"One of the tokens cast failed"<<endl;
            return false;
        }
        if(at->operatorType != bt->operatorType)
        {
            cerr<<"Different token operator type"<<endl;
            return false;
        }
    }
    if(a->classType == IDENTIFIER_TOKEN)
    {
        IdentifierToken* at = dynamic_cast<IdentifierToken*>(a);
        IdentifierToken* bt = dynamic_cast<IdentifierToken*>(b);
        if(at == nullptr || bt == nullptr)
        {
            cerr<<"One of the tokens cast failed"<<endl;
            return false;
        }
        if(at->name != bt->name)
        {
            cerr<<"Different token identifier name"<<endl;
            return false;
        }
    }
    if(a->classType == LITERAL_TOKEN)
    {
        LiteralToken* at = dynamic_cast<LiteralToken*>(a);
        LiteralToken* bt = dynamic_cast<LiteralToken*>(b);
        if(at == nullptr || bt == nullptr)
        {
            cerr<<"One of the tokens cast failed"<<endl;
            return false;
        }
        if(at->value != bt->value)
        {
            cerr<<"Different token literal value - Got: "<<get<string>(at->value)<<"  Expected: "<<get<string>(bt->value)<<endl;
            return false;
        }
    }
    return true;
}