#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.h"
#include "token.h"

using namespace std;


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
    
    Token token = lexer->getToken();
    int lineNum = 0;
    while(token.classType != EOT_TOKEN)
    {
        if(lineNum < token.lineNumber)
        {
            cout<<endl;
            lineNum = token.lineNumber;
        }
        cout<<token.toString()<<" ";
        token = lexer->getToken();
    }
    cout<<endl;
    delete lexer;
}