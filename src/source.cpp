#include "source.h"
#include <iomanip>

using namespace std;


Source::Source(std::istream& stream)
: input(stream), sourceIndex(-1), lineNumber(0), lineIndex(-1)
{}

const char Source::get()
{
    const char c = input.get();
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

const int Source::getSourceIndex()
{
    return sourceIndex;
}

const int Source::getLineNumber()
{
    return lineNumber;
}

const int Source::getLineIndex()
{
    return lineIndex;
}
