#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <functional>


#include "token.h"
#include "source.h"
#include "lexer.h"
#include "objects.h"


class Parser
{
    Lexer lexer;
    Token currentToken;
    bool EOTReceived = false;

    std::shared_ptr<Definition> parseDefinition();
    std::shared_ptr<Statement> parseStatement();
    std::shared_ptr<Instruction> parseInstruction();
    std::shared_ptr<Expression> parseExpression();
    std::shared_ptr<Expression> parseBinaryExpression(std::function<std::shared_ptr<Expression>()> parseChildExpression,
        std::function<std::shared_ptr<Token>()> parseOperator, bool operationRightToLeft = false);

    std::shared_ptr<Token> parseAssignOperator();
    std::shared_ptr<Token> parseOrOperator();
    std::shared_ptr<Token> parseAndOperator();
    std::shared_ptr<Token> parseEqOperator();
    std::shared_ptr<Token> parseRelOperator();
    std::shared_ptr<Token> parseAddOperator();
    std::shared_ptr<Token> parseMulOperator();
    std::shared_ptr<Token> parseExpOperator();
    std::shared_ptr<Token> acceptOperator();

    std::shared_ptr<Expression> parseAssignExpression();
    std::shared_ptr<Expression> parseOrExpression();
    std::shared_ptr<Expression> parseAndExpression();
    std::shared_ptr<Expression> parseEqExpression();
    std::shared_ptr<Expression> parseRelExpression();
    std::shared_ptr<Expression> parseAddExpression();
    std::shared_ptr<Expression> parseMulExpression();
    std::shared_ptr<Expression> parseExpExpression();
    std::shared_ptr<Expression> parsePrimaryExpression();

    std::shared_ptr<Expression> parseLiteral();
    std::shared_ptr<Expression> parseIdentifierOrFunctionCall();




    void getNextToken();


public:
    Parser(std::istream& stream) : lexer(stream) {}

    std::shared_ptr<Program> parse();
};