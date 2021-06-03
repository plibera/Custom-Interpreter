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
    //Value returned by the last execution
    std::shared_ptr<Value> lastReturnValue;

    //These evaluations can only return a value with a return statement
    std::shared_ptr<Value> evaluate(std::shared_ptr<Program> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Statement> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Instruction> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<IfStatement> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<WhileStatement> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<ReturnStatement> element);

    //These evaluations return the evaluated value
    std::shared_ptr<Value> evaluate(std::shared_ptr<BinaryExpression> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<FunCall> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Expression> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Literal> element);
    std::shared_ptr<Value> evaluate(std::shared_ptr<Identifier> element);

    //These evaluations do not return anything and only modify interpreters internal elements
    void evaluate(std::shared_ptr<Definition> element);
    void evaluate(std::shared_ptr<FunDefinition> element);
    void evaluate(std::shared_ptr<TypeDefinition> element);
    void evaluate(std::shared_ptr<VariableDeclaration> element);

public:
    Interpreter(std::istream& stream) : parser(stream) {}

    int execute();

    std::shared_ptr<Value> getLastReturnValue() { return lastReturnValue; }
};