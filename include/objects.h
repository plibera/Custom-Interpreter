#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <sstream>

#include "token.h"


struct Definition;
struct Statement;
struct FunDefinition;
struct TypeDefinition;
struct BinaryExpression;
struct FunCall;
struct Expression;
struct Literal;
struct Identifier;
struct Instruction;
struct IfStatement;
struct WhileStatement;
struct ReturnStatement;
struct VariableDeclaration;


struct Program
{
    std::vector<std::variant<std::shared_ptr<Definition>, std::shared_ptr<Statement>>> program;

    std::string to_string(int indent = 0);
};


struct Definition
{
    std::variant<std::shared_ptr<FunDefinition>, std::shared_ptr<TypeDefinition>, std::shared_ptr<VariableDeclaration>> definition;

    std::string to_string(int indent = 0);
};

struct Statement
{
    std::vector<std::shared_ptr<Instruction>> instructions;

    std::string to_string(int indent = 0);
};

struct FunDefinition
{
    Token type;
    std::string identifier;
    std::vector<std::shared_ptr<VariableDeclaration>> arguments;
    std::shared_ptr<Statement> statement;
    bool isPublic;

    FunDefinition(bool isPublic = true) : isPublic(isPublic) {}

    std::string to_string(int indent = 0);
};

struct TypeDefinition
{
    Token type;
    std::vector<std::shared_ptr<VariableDeclaration>> variables;
    std::vector<std::shared_ptr<FunDefinition>> functions;

    std::string to_string(int indent = 0);
};


struct BinaryExpression
{
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;
    Token op;

    std::string to_string(int indent = 0);
};



struct FunCall
{
    std::string object;
    std::string identifier;
    std::vector<std::shared_ptr<Expression>> arguments;

    std::string to_string(int indent = 0);
};

struct Expression
{
    std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<FunCall>, std::shared_ptr<Literal>, std::shared_ptr<Identifier>> expression;

    std::string to_string(int indent = 0);
};

struct Literal
{
    Token literal;

    std::string to_string(int indent = 0);
};

struct Identifier
{
    std::string object;
    std::string identifier;

    std::string to_string(int indent = 0);
};

struct Instruction
{
    std::variant<std::shared_ptr<Expression>,
                 std::shared_ptr<IfStatement>,
                 std::shared_ptr<WhileStatement>,
                 std::shared_ptr<ReturnStatement>,
                 std::shared_ptr<VariableDeclaration>> instruction;

    std::string to_string(int indent = 0);
};

struct IfStatement
{
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> statementTrue;
    std::shared_ptr<Statement> statementFalse;

    std::string to_string(int indent = 0);
};

struct WhileStatement
{
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> statement;

    std::string to_string(int indent = 0);
};

struct ReturnStatement
{
    std::shared_ptr<Expression> expression;

    std::string to_string(int indent = 0);
};

struct VariableDeclaration
{
    Token type;
    std::string identifier;
    std::shared_ptr<Expression> expression;
    bool isPublic;

    VariableDeclaration(bool isPublic = true) : isPublic(isPublic) {}

    std::string to_string(int indent = 0);
};