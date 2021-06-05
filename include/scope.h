#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <variant>
#include <memory>
#include <sstream>

#include "objects.h"
#include "value.h"


struct Scope
{
    int maxStackSize;
    std::stack<std::vector<std::map<std::string, std::shared_ptr<Value>>>> localScope;
    std::map<std::string, std::shared_ptr<Value>> globalScope;
    Scope(int maxStackSize = 500);

    Position currentPos;

    void newInstructionBlock();
    void endInstructionBlock();
    void newLevel();
    void endLevel();
    void addVariable(std::string identifier, std::shared_ptr<Value> value);
    void assignValue(std::string identifier, std::shared_ptr<Value> value);
    void assignValue(std::string object, std::string identifier, std::shared_ptr<Value> value);
    void assignValue(std::shared_ptr<Value> l, std::shared_ptr<Value> r);
    bool isPublic(std::string &object, std::string &identifier);
    std::shared_ptr<Value> getValue(std::string identifier);
    std::shared_ptr<Value> getValue(std::string object, std::string identifier);

    void startTypeDefinition();
    std::map<std::string, std::shared_ptr<Value>> endTypeDefinition();
};