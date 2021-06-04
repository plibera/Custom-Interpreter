#include "scope.h"

using namespace std;

Scope::Scope(int maxStackSize)
    : maxStackSize(maxStackSize)
{
    newLevel();
}


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
        throw runtime_error("Stack size limit exceeded "+ currentPos.toString());
    }
    vector<map<string, shared_ptr<Value>>> levelScope;
    localScope.push(levelScope);
}

void Scope::endLevel()
{
    if(localScope.size() == 1)
        throw runtime_error("Cannot scope lower, already at the lowest level "+ currentPos.toString());
    localScope.pop();
}

void Scope::addVariable(std::string identifier, std::shared_ptr<Value> value)
{
    bool variableExists = false;
    if(localScope.top().size() > 0)
    {
        auto element = localScope.top()[localScope.top().size()-1].find(identifier);
        if(element != localScope.top()[localScope.top().size()-1].end())
        {
            variableExists = true;
        }
    }
    else
    {
        auto element = globalScope.find(identifier);
        if(element != globalScope.end())
        {
            variableExists = true;
        }
        
    }
    if(variableExists)
    {
        throw runtime_error("Variable "+identifier+" already exists in this scope "+ currentPos.toString());
    }
    if(localScope.top().size() == 0)
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
    throw runtime_error("Variable "+identifier+" does not exist "+ currentPos.toString());
}

void Scope::assignValue(std::string identifier, std::shared_ptr<Value> value)
{
    if(value == nullptr || value->value == nullptr)
    {
        return;
    }
    auto currentValue = getValue(identifier);
    if(get_if<long long>(currentValue->value.get()))
    {
        if(get_if<long long>(value->value.get()))
        {
            currentValue->value = value->value;
            return;
        }
    }
    if(get_if<double>(currentValue->value.get()))
    {
        if(get_if<double>(value->value.get()))
        {
            currentValue->value = value->value;
            return;
        }
    }
    if(get_if<string>(currentValue->value.get()))
    {
        if(get_if<string>(value->value.get()))
        {
            currentValue->value = value->value;
            return;
        }
    }
    if(get_if<bool>(currentValue->value.get()))
    {
        if(get_if<bool>(value->value.get()))
        {
            currentValue->value = value->value;
            return;
        }
    }
    throw runtime_error("Cannot assign to "+identifier+" because of incompatible types "+ currentPos.toString());
}