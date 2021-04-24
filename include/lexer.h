#pragma once

#include <iostream>
#include <string>

#include "source.h"

class Lexer
{
    Source source;
    char nextChar;


public:
    Lexer(std::istream& stream);
};