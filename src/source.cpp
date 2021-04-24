#include "source.h"
#include <iomanip>

using namespace std;


Source::Source(std::istream& stream)
: input(stream)
{
    sourceIndex = 0;
    lineNumber = 0;
    lineIndex = 0;
}

char Source::get()
{
    char c = input.get();
    sourceIndex++;
    if(c == '\n')
    {
        lineNumber++;
        lineIndex = 0;
    }
    else
    {
        lineIndex++;
    }
    return c;
}

int Source::getSourceIndex()
{
    return sourceIndex;
}

int Source::getLineNumber()
{
    return lineNumber;
}

int Source::getLineIndex()
{
    return lineIndex;
}
