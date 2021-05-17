#pragma once

#include <iostream>
#include <gtest/gtest.h>

#include "parser.h"



TEST(ParserTest, ParsesIdentifier) {
    std::stringstream ss;
    Parser* parser = new Parser(ss, true);
    Token token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    Token token2(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token2);
    std::shared_ptr<Program> program = parser->parse();

    Program program2;
    std::shared_ptr<Statement> statement = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier = std::make_shared<Identifier>();
    identifier->identifier = "x";
    expression->expression = identifier;
    instruction->instruction = expression;
    statement->instructions.push_back(instruction);
    program2.program.push_back(statement);
    ASSERT_EQ(program->to_string(), program2.to_string());
    delete parser;
}

TEST(ParserTest, ParsesAccessIdentifier) {
    std::stringstream ss;
    Parser* parser = new Parser(ss, true);
    Token token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_ACCESS, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token);
    std::shared_ptr<Program> program = parser->parse();

    Program program2;
    std::shared_ptr<Statement> statement = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier = std::make_shared<Identifier>();
    identifier->identifier = "y";
    identifier->object = "x";
    expression->expression = identifier;
    instruction->instruction = expression;
    statement->instructions.push_back(instruction);
    program2.program.push_back(statement);
    ASSERT_EQ(program->to_string(), program2.to_string());
    delete parser;
}

TEST(ParserTest, ParsesAddMulExpression) {
    std::stringstream ss;
    Parser* parser = new Parser(ss, true);
    Token token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_ADD, 0, 0, 0, operatorIdMap.at("+"));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_MUL, 0, 0, 0, operatorIdMap.at("*"));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "z");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token);
    std::shared_ptr<Program> program = parser->parse();

    Program program2;
    std::shared_ptr<Statement> statement = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression2 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression3 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression4 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression5 = std::make_shared<Expression>();
    std::shared_ptr<BinaryExpression> binaryExpression = std::make_shared<BinaryExpression>();
    std::shared_ptr<BinaryExpression> binaryExpression2 = std::make_shared<BinaryExpression>();
    std::shared_ptr<Identifier> identifier = std::make_shared<Identifier>();
    std::shared_ptr<Identifier> identifier2 = std::make_shared<Identifier>();
    std::shared_ptr<Identifier> identifier3 = std::make_shared<Identifier>();
    identifier->identifier = "x";
    identifier2->identifier = "y";
    identifier3->identifier = "z";
    expression->expression = identifier;
    expression2->expression = identifier2;
    expression3->expression = identifier3;
    binaryExpression->lhs = expression2;
    binaryExpression->rhs = expression3;
    binaryExpression->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_MUL, 0, 0, 0, operatorIdMap.at("*")));
    expression4->expression = binaryExpression;
    binaryExpression2->lhs = expression;
    binaryExpression2->rhs = expression4;
    binaryExpression2->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_ADD, 0, 0, 0, operatorIdMap.at("+")));
    expression5->expression = binaryExpression2;
    instruction->instruction = expression5;
    statement->instructions.push_back(instruction);
    program2.program.push_back(statement);
    ASSERT_EQ(program->to_string(), program2.to_string());
    delete parser;
}


TEST(ParserTest, ParsesExpExpression) {
    std::stringstream ss;
    Parser* parser = new Parser(ss, true);
    Token token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_EXP, 0, 0, 0, operatorIdMap.at("**"));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_EXP, 0, 0, 0, operatorIdMap.at("**"));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "z");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token);
    std::shared_ptr<Program> program = parser->parse();

    Program program2;
    std::shared_ptr<Statement> statement = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression2 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression3 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression4 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression5 = std::make_shared<Expression>();
    std::shared_ptr<BinaryExpression> binaryExpression = std::make_shared<BinaryExpression>();
    std::shared_ptr<BinaryExpression> binaryExpression2 = std::make_shared<BinaryExpression>();
    std::shared_ptr<Identifier> identifier = std::make_shared<Identifier>();
    std::shared_ptr<Identifier> identifier2 = std::make_shared<Identifier>();
    std::shared_ptr<Identifier> identifier3 = std::make_shared<Identifier>();
    identifier->identifier = "x";
    identifier2->identifier = "y";
    identifier3->identifier = "z";
    expression->expression = identifier;
    expression2->expression = identifier2;
    expression3->expression = identifier3;
    binaryExpression->lhs = expression2;
    binaryExpression->rhs = expression3;
    binaryExpression->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_EXP, 0, 0, 0, operatorIdMap.at("**")));
    expression4->expression = binaryExpression;
    binaryExpression2->lhs = expression;
    binaryExpression2->rhs = expression4;
    binaryExpression2->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_EXP, 0, 0, 0, operatorIdMap.at("**")));
    expression5->expression = binaryExpression2;
    instruction->instruction = expression5;
    statement->instructions.push_back(instruction);
    program2.program.push_back(statement);
    ASSERT_EQ(program->to_string(), program2.to_string());
    delete parser;
}

TEST(ParserTest, ParsesPrimaryExpression) {
    std::stringstream ss;
    Parser* parser = new Parser(ss, true);
    Token token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_ADD, 0, 0, 0, operatorIdMap.at("*"));
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_LEFTPAREN, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_MUL, 0, 0, 0, operatorIdMap.at("+"));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "z");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_RIGHTPAREN, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token);
    std::shared_ptr<Program> program = parser->parse();

    Program program2;
    std::shared_ptr<Statement> statement = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression2 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression3 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression4 = std::make_shared<Expression>();
    std::shared_ptr<Expression> expression5 = std::make_shared<Expression>();
    std::shared_ptr<BinaryExpression> binaryExpression = std::make_shared<BinaryExpression>();
    std::shared_ptr<BinaryExpression> binaryExpression2 = std::make_shared<BinaryExpression>();
    std::shared_ptr<Identifier> identifier = std::make_shared<Identifier>();
    std::shared_ptr<Identifier> identifier2 = std::make_shared<Identifier>();
    std::shared_ptr<Identifier> identifier3 = std::make_shared<Identifier>();
    identifier->identifier = "x";
    identifier2->identifier = "y";
    identifier3->identifier = "z";
    expression->expression = identifier;
    expression2->expression = identifier2;
    expression3->expression = identifier3;
    binaryExpression->lhs = expression2;
    binaryExpression->rhs = expression3;
    binaryExpression->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_MUL, 0, 0, 0, operatorIdMap.at("*")));
    expression4->expression = binaryExpression;
    binaryExpression2->lhs = expression;
    binaryExpression2->rhs = expression4;
    binaryExpression2->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_ADD, 0, 0, 0, operatorIdMap.at("+")));
    expression5->expression = binaryExpression2;
    instruction->instruction = expression5;
    statement->instructions.push_back(instruction);
    program2.program.push_back(statement);
    ASSERT_EQ(program->to_string(), program2.to_string());
    delete parser;
}


TEST(ParserTest, ParsesIfStatement) {
    std::stringstream ss;
    Parser* parser = new Parser(ss, true);
    Token token(KEYWORD_TOKEN, T_IF, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_LEFTPAREN, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_REL, 0, 0, 0, operatorIdMap.at("<"));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_RIGHTPAREN, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_LEFTBRACKET, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_ASSIGN, 0, 0, 0, operatorIdMap.at("="));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_RIGHTBRACKET, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_ELSE, 0, 0, 0);
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "y");
    parser->addTestToken(token);
    token = Token(OPERATOR_TOKEN, T_ASSIGN, 0, 0, 0, operatorIdMap.at("="));
    parser->addTestToken(token);
    token = Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "x");
    parser->addTestToken(token);
    token = Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0);
    parser->addTestToken(token);
    std::shared_ptr<Program> program = parser->parse();

    Program program2;
    std::shared_ptr<Statement> statement = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction = std::make_shared<Instruction>();
    std::shared_ptr<IfStatement> ifStatement = std::make_shared<IfStatement>();
    std::shared_ptr<Expression> expression = std::make_shared<Expression>();
    std::shared_ptr<BinaryExpression> binaryExpression = std::make_shared<BinaryExpression>();
    std::shared_ptr<Expression> expression2 = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier = std::make_shared<Identifier>();
    std::shared_ptr<Expression> expression3 = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier2 = std::make_shared<Identifier>();
    std::shared_ptr<Statement> statement2 = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction2 = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression4 = std::make_shared<Expression>();
    std::shared_ptr<BinaryExpression> binaryExpression2 = std::make_shared<BinaryExpression>();
    std::shared_ptr<Expression> expression5 = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier3 = std::make_shared<Identifier>();
    std::shared_ptr<Expression> expression6 = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier4 = std::make_shared<Identifier>();
    std::shared_ptr<Statement> statement3 = std::make_shared<Statement>();
    std::shared_ptr<Instruction> instruction3 = std::make_shared<Instruction>();
    std::shared_ptr<Expression> expression7 = std::make_shared<Expression>();
    std::shared_ptr<BinaryExpression> binaryExpression3 = std::make_shared<BinaryExpression>();
    std::shared_ptr<Expression> expression8 = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier5 = std::make_shared<Identifier>();
    std::shared_ptr<Expression> expression9 = std::make_shared<Expression>();
    std::shared_ptr<Identifier> identifier6 = std::make_shared<Identifier>();
    identifier6->identifier = "x";
    identifier5->identifier = "y";
    expression9->expression = identifier6;
    expression8->expression = identifier5;
    binaryExpression3->lhs = expression8;
    binaryExpression3->rhs = expression9;
    binaryExpression3->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_ASSIGN, 0, 0, 0, operatorIdMap.at("=")));
    expression7->expression = binaryExpression3;
    instruction3->instruction = expression7;
    statement3->instructions.push_back(instruction3);
    identifier4->identifier = "y";
    expression6->expression = identifier4;
    identifier3->identifier = "x";
    expression5->expression = identifier3;
    binaryExpression2->lhs = expression5;
    binaryExpression2->rhs = expression6;
    binaryExpression2->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_ASSIGN, 0, 0, 0, operatorIdMap.at("=")));
    expression4->expression = binaryExpression2;
    instruction2->instruction = expression4;
    statement2->instructions.push_back(instruction2);
    identifier->identifier = "x";
    identifier2->identifier = "y";
    expression3->expression = identifier2;
    expression2->expression = identifier;
    binaryExpression->lhs = expression2;
    binaryExpression->rhs = expression3;
    binaryExpression->op = std::make_shared<Token>(Token(OPERATOR_TOKEN, T_REL, 0, 0, 0, operatorIdMap.at("<")));
    expression->expression = binaryExpression;
    ifStatement->condition = expression;
    ifStatement->statementTrue = statement2;
    ifStatement->statementFalse = statement3;
    instruction->instruction = ifStatement;
    statement->instructions.push_back(instruction);
    program2.program.push_back(statement);
    ASSERT_EQ(program->to_string(), program2.to_string());
    delete parser;
}