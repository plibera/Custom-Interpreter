#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.h"
#include "token.h"
#include "parser.h"

using namespace std;


int main(int argc, char* argv[])
{
    Parser *parser;
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
        parser = new Parser(file);
    }
    else
    {
        parser = new Parser(std::cin);
    }
    
    /*Token token = lexer->getToken();
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
    delete lexer;*/

    shared_ptr<Program> program = parser->parse();
    cout<<"Finished"<<endl;
    cout<<program->to_string()<<endl;
}