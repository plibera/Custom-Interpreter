#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <sstream>

#include "parser.h"
#include "value.h"
#include "scope.h"


class Interpreter
{
    Parser parser;
    Scope scope;
    FunctionVector functions;
    std::map<std::string, std::shared_ptr<TypeDefinition>> types;
    std::string currentObject;

    //Value returned by the last execution
    std::shared_ptr<Value> lastReturnValue;

    //These evaluations can only return a value with a return statement
    std::shared_ptr<Value> evaluate(std::shared_ptr<Program> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Statement> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Instruction> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<IfStatement> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<WhileStatement> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<ReturnStatement> element);

    //Functions used to perform function calls of custom functions and embedded functions
    std::shared_ptr<Value> evaluateCustomFunction(std::shared_ptr<Statement> statement);
    std::shared_ptr<Value> evaluatePrintFunction(std::shared_ptr<Statement> statement);
    std::shared_ptr<Value> evaluatePrintlnFunction(std::shared_ptr<Statement> statement);
    std::shared_ptr<Value> evaluateStrFunction(std::shared_ptr<Statement> statement);
    std::shared_ptr<Value> evaluateFloatFunction(std::shared_ptr<Statement> statement);
    std::shared_ptr<Value> evaluateIntFunction(std::shared_ptr<Statement> statement);
    std::shared_ptr<Value> evaluateBoolFunction(std::shared_ptr<Statement> statement);

    //These evaluations return the evaluated value
    std::shared_ptr<Value> evaluate(std::shared_ptr<BinaryExpression> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<FunCall> element);
    std::shared_ptr<Value> runFunction(FunctionEntry &function, std::string &identifier, std::vector<std::shared_ptr<Value>> &argumentValues, Position &position);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Expression> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Literal> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Identifier> element);

    //These evaluations do not return anything and only modify interpreters internal elements
    void evaluate(std::shared_ptr<Definition> element);
    void evaluate(std::shared_ptr<FunDefinition> element);
    void evaluate(std::shared_ptr<TypeDefinition> element);
    void evaluate(std::shared_ptr<VariableDeclaration> element);

    void createEmbeddedFunctions();
    //Creates and adds a function with a given name and callback with a single argument of type Int, Float, String or Bool
    void createEmbeddedFunction(std::string identifier, Token type, std::function<std::shared_ptr<Value>(std::shared_ptr<Statement>)> callback);

public:
    Interpreter(std::istream& stream) : parser(stream), currentObject("") { createEmbeddedFunctions(); }

    int execute();

    std::shared_ptr<Value> getLastReturnValue() { return lastReturnValue; }
};