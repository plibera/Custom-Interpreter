#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;


int main(int argc, char* argv[])
{
    Interpreter* interpreter;
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
        interpreter = new Interpreter(file);
    }
    else
    {
        interpreter = new Interpreter(std::cin);
    }

    long long retVal = 0;
    try
    {
        retVal = interpreter->execute();
    }
    catch(const std::exception& e)
    {
        cerr<<"Program error: ";
        cerr << e.what() << '\n';
    }
    delete interpreter;
}