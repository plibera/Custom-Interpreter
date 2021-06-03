#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <sstream>

#include "objects.h"


struct Value;

struct CustomType
{
    std::map<std::string, std::shared_ptr<Value>> attributes;
};


typedef std::variant<long long, double, std::string, std::shared_ptr<CustomType>> ValueType;

struct Value
{
    //Pointer to be able to return an empty value and have a distinction between returning nothing and not returning
    std::shared_ptr<ValueType> value;

    Value(long long value) : value(std::make_shared<ValueType>(value)) {}
    Value(double value) : value(std::make_shared<ValueType>(value)) {}
    Value(std::string value) : value(std::make_shared<ValueType>(value)) {}
    Value(std::shared_ptr<CustomType> value) : value(std::make_shared<ValueType>(value)) {}
    Value() : value(nullptr) {}
};