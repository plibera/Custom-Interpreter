#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.h"
#include "token.h"

using namespace std;


Token* getToken()
{
    IdentifierToken* token = new IdentifierToken(T_VAR, 0, 0, 0, "test");
    return token;
}

int main(int argc, char* argv[])
{
    Lexer *lexer;
    std::ifstream file;
    if(argc > 1)
    {
        string filename = argv[1];
        file.open(filename);
        if(!file.is_open())
        {
            cerr<<"Could not open file"<<endl;
            return 1;
        }
        lexer = new Lexer(file);
    }
    else
    {
        lexer = new Lexer(std::cin);
    }
    
    Token* token = lexer->getToken();
    int lineNum = 0;
    while(token->classType != EOT_TOKEN)
    {
        if(lineNum < token->lineNumber)
        {
            cout<<endl;
            lineNum = token->lineNumber;
        }
        switch(token->classType)
        {
            case KEYWORD_TOKEN:
            {
                KeywordToken* tk = dynamic_cast<KeywordToken*>(token);
                cout<<tk->toString()<<" ";
                break;
            }
            case OPERATOR_TOKEN:
            {
                OperatorToken* tk = dynamic_cast<OperatorToken*>(token);
                cout<<tk->toString()<<" ";
                break;
            }
            case IDENTIFIER_TOKEN:
            {
                IdentifierToken* tk = dynamic_cast<IdentifierToken*>(token);
                cout<<tk->toString()<<" ";
                break;
            }
            case LITERAL_TOKEN:
            {
                LiteralToken* tk = dynamic_cast<LiteralToken*>(token);
                cout<<tk->toString()<<" ";
                break;
            }
            default:
                cout<<token->toString()<<" ";
                break;
        }
        token = lexer->getToken();
    }
    cout<<endl;
}