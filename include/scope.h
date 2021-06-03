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

    void newInstructionBlock();
    void endInstructionBlock();
    void newLevel();
    void endLevel();
    bool addVariable(std::string identifier, std::shared_ptr<Value> value);
    std::shared_ptr<Value> getValue(std::string identifier);
};