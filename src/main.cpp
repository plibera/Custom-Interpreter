#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.h"
#include "token.h"

using namespace std;


Token* getToken()
{
    IdentifierToken* token = new IdentifierToken();
    token->name = "test";
    return token;
}

int main(int argc, char* argv[])
{
    /*Lexer *lexer;
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
    
    c = 0;
    while(c != EOF)
    {
        c = lexer->get();
        cout<<c;
    }
    cout<<endl;*/
}