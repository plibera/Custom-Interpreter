#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <istream>


class Source
{
    std::istream& input;
    int sourceIndex;
    int lineNumber;
    int lineIndex;

public:
    Source(std::istream& stream);

    char get();
    int getSourceIndex();
    int getLineNumber();
    int getLineIndex();
};