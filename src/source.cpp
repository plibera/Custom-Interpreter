#include "source.h"
#include <iomanip>

using namespace std;


Source::Source(std::istream& stream)
: input(stream), sourceIndex(-1), lineNumber(0), lineIndex(-1)
{}

char Source::get()
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

int Source::getSourceIndex() const
{
    return sourceIndex;
}

int Source::getLineNumber() const
{
    return lineNumber;
}

int Source::getLineIndex() const
{
    return lineIndex;
}
