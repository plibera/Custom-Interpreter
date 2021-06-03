#include "scope.h"

using namespace std;

Scope::Scope(int maxStackSize)
    : maxStackSize(maxStackSize)
{}


void Scope::newInstructionBlock()
{
    map<string, shared_ptr<Value>> blockScope;
    localScope.top().push_back(blockScope);
}

void Scope::endInstructionBlock()
{
    localScope.top().pop_back();
}

void Scope::newLevel()
{
    if(localScope.size() >= maxStackSize)
    {
        throw runtime_error("Stack size limit exceeded");
    }
    vector<map<string, shared_ptr<Value>>> levelScope;
    localScope.push(levelScope);
}

void Scope::endLevel()
{
    localScope.pop();
}

bool Scope::addVariable(std::string identifier, std::shared_ptr<Value> value)
{
    if(localScope.size() == 0)
    {
        globalScope.insert(make_pair(identifier, value));
    }
    else
    {
        localScope.top()[localScope.top().size()-1].insert(make_pair(identifier, value));
    }
}

std::shared_ptr<Value> Scope::getValue(std::string identifier)
{
    for(auto it = localScope.top().rbegin(); it != localScope.top().rend(); ++it)
    {
        auto element = it->find(identifier);
        if(element != it->end())
        {
            return element->second;
        }
    }
    auto element = globalScope.find(identifier);
    if(element != globalScope.end())
    {
        return element->second;
    }
}