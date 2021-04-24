#include "lexer.h"

using namespace std;

Lexer::Lexer(std::istream& stream)
:source(stream)
{
    nextChar = source.get();
}