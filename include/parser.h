#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <queue>


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
    std::shared_ptr<Expression> parseAssignExpression();
    std::shared_ptr<Expression> parseOrExpression();
    std::shared_ptr<Expression> parseAndExpression();
    std::shared_ptr<Expression> parseEqExpression();
    std::shared_ptr<Expression> parseRelExpression();
    std::shared_ptr<Expression> parseAddExpression();
    std::shared_ptr<Expression> parseMulExpression();
    std::shared_ptr<Expression> parseExpExpression();
    std::shared_ptr<Expression> parsePrimaryExpression();
    std::shared_ptr<Expression> parseBinaryExpression(std::function<std::shared_ptr<Expression>()> parseChildExpression,
        int operatorClass, int operatorType, bool operationRightToLeft = false);

    bool accept(int operatorClass, int operatorType);
    bool consume(int operatorClass, int operatorType);
    bool expect(int operatorClass, int operatorType, std::string msg);


    std::shared_ptr<Expression> parseLiteral();
    std::shared_ptr<Expression> parseIdentifierOrFunctionCall();

    std::shared_ptr<IfStatement> parseIfStatement();
    std::shared_ptr<WhileStatement> parseWhileStatement();
    std::shared_ptr<ReturnStatement> parseReturnStatement();

    std::shared_ptr<Definition> parseIdentifierOrFunctionDefinition(bool forceIdentifier = false);
    std::shared_ptr<TypeDefinition> parseTypeDefinition();

    Token getNextToken();

public:
    Parser(std::istream& stream) : lexer(stream) {}

    std::shared_ptr<Program> parse();
};