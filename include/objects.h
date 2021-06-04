#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <sstream>

#include "token.h"
#include "value.h"

/**
 * Objects in the document tree
 */

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

struct Value;

struct Position
{
    int position;
    int lineNum;
    int linePos;

    Position(int position=0, int lineNum=0, int linePos=0) : position(position), lineNum(lineNum), linePos(linePos) {}
    Position(Token token) : position(token.position), lineNum(token.lineNumber), linePos(token.linePosition) {}

    std::string toString()
    { 
        return "Line:"+std::to_string(lineNum+1)+" pos:"+std::to_string(linePos);
    }
};


bool areOfCorrespondingType(Token &token, std::shared_ptr<Value> value);


struct Program
{
    std::vector<std::variant<std::shared_ptr<Definition>, std::shared_ptr<Statement>>> program;

    Position pos;
    std::string to_string(int indent = 0);
};


struct Definition
{
    std::variant<std::shared_ptr<FunDefinition>, std::shared_ptr<TypeDefinition>, std::shared_ptr<VariableDeclaration>> definition;

    Position pos;
    std::string to_string(int indent = 0);
};

struct Statement
{
    std::vector<std::shared_ptr<Instruction>> instructions;
    bool newBlock = true;

    Position pos;
    std::string to_string(int indent = 0);
};

struct FunDefinition
{
    Token type;
    std::string identifier;
    std::vector<std::shared_ptr<VariableDeclaration>> arguments;
    std::shared_ptr<Statement> statement;
    bool isPublic;

    FunDefinition(Token type, std::string identifier, std::vector<std::shared_ptr<VariableDeclaration>> arguments,
        std::shared_ptr<Statement> statement = std::make_shared<Statement>(), bool isPublic = true)
            :type(type), identifier(identifier), arguments(arguments), statement(statement), isPublic(isPublic) {}
    FunDefinition(bool isPublic = true) : isPublic(isPublic) {}

    Position pos;
    std::string to_string(int indent = 0);

    bool operator==(const FunDefinition& r);
    bool acceptFunCall(std::string calledIdentifier, std::vector<std::shared_ptr<Value>> &argValues);
    bool acceptReturnValue(std::shared_ptr<Value> value);
};

struct TypeDefinition
{
    Token type;
    std::vector<std::shared_ptr<VariableDeclaration>> variables;
    std::vector<std::shared_ptr<FunDefinition>> functions;

    Position pos;
    std::string to_string(int indent = 0);
};


struct BinaryExpression
{
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;
    Token op;

    Position pos;
    std::string to_string(int indent = 0);
};



struct FunCall
{
    std::string object;
    std::string identifier;
    std::vector<std::shared_ptr<Expression>> arguments;

    Position pos;
    std::string to_string(int indent = 0);
};

struct Expression
{
    std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<FunCall>, std::shared_ptr<Literal>, std::shared_ptr<Identifier>> expression;

    Position pos;
    std::string to_string(int indent = 0);
};

struct Literal
{
    Token literal;

    Position pos;
    std::string to_string(int indent = 0);
};

struct Identifier
{
    std::string object;
    std::string identifier;

    Position pos;
    std::string to_string(int indent = 0);
};

struct Instruction
{
    std::variant<std::shared_ptr<Expression>,
                 std::shared_ptr<IfStatement>,
                 std::shared_ptr<WhileStatement>,
                 std::shared_ptr<ReturnStatement>,
                 std::shared_ptr<VariableDeclaration>> instruction;

    Position pos;
    std::string to_string(int indent = 0);
};

struct IfStatement
{
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> statementTrue;
    std::shared_ptr<Statement> statementFalse;

    Position pos;
    std::string to_string(int indent = 0);
};

struct WhileStatement
{
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> statement;

    Position pos;
    std::string to_string(int indent = 0);
};

struct ReturnStatement
{
    std::shared_ptr<Expression> expression;

    Position pos;
    std::string to_string(int indent = 0);
};

struct VariableDeclaration
{
    Token type;
    std::string identifier;
    std::shared_ptr<Expression> expression;
    bool isPublic;

    VariableDeclaration(Token type, std::string identifier, bool isPublic = true)
        : type(type), identifier(identifier), isPublic(isPublic) {}
    VariableDeclaration(bool isPublic = true) : isPublic(isPublic) {}

    Position pos;
    std::string to_string(int indent = 0);
};