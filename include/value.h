#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <sstream>
#include <math.h>
#include <functional>

#include "objects.h"

struct FunDefinition;
struct Statement;
struct Value;

typedef std::pair<std::shared_ptr<FunDefinition>, std::function<std::shared_ptr<Value>(std::shared_ptr<Statement>)>> FunctionEntry;
typedef std::vector<FunctionEntry> FunctionVector;



struct CustomType
{
    std::string typeName;
    std::map<std::string, std::shared_ptr<Value>> attributes;
    std::map<std::string, bool> isPublic;
    std::map<std::string, bool> isFunctionPublic;
    FunctionVector functions;

    CustomType(std::string typeName, std::map<std::string, std::shared_ptr<Value>> attributes, std::map<std::string, bool> isPublic,
        std::map<std::string, bool> isFunctionPublic, FunctionVector functions)
        :typeName(typeName), attributes(attributes), isPublic(isPublic), isFunctionPublic(isFunctionPublic), functions(functions) {}
};


typedef std::variant<long long, double, std::string, std::shared_ptr<CustomType>, bool> ValueType;

struct Value
{
    //Pointer to be able to return an empty value and have a distinction between returning nothing and not returning
    std::shared_ptr<ValueType> value;

    Value(long long value) : value(std::make_shared<ValueType>(value)) {}
    Value(bool value) : value(std::make_shared<ValueType>(value)) {}
    Value(double value) : value(std::make_shared<ValueType>(value)) {}
    Value(std::string value) : value(std::make_shared<ValueType>(value)) {}
    Value(std::shared_ptr<CustomType> value) : value(std::make_shared<ValueType>(value)) {}
    Value() : value(nullptr) {}

    friend bool operator<(const Value& l, const Value& r);
    friend bool operator>(const Value& l, const Value& r);
    friend bool operator<=(const Value& l, const Value& r);
    friend bool operator>=(const Value& l, const Value& r);
    friend bool operator==(const Value& l, const Value& r);
    friend bool operator!=(const Value& l, const Value& r);

    friend Value operator+(const Value& l, const Value& r);
    friend Value operator-(const Value& l, const Value& r);
    friend Value operator*(const Value& l, const Value& r);
    friend Value operator/(const Value& l, const Value& r);
    friend Value operator^(const Value& l, const Value& r);

    bool logicalValue();
};