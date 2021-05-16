#include "parser.h"

using namespace std;


void Parser::getNextToken() {
    cout<<"Get next token"<<endl;
    if(EOTReceived)
        throw runtime_error("EOT already processed");
    currentToken = lexer.getToken();
    if(currentToken.classType == EOT_TOKEN)
    {
        EOTReceived = true;
    }
}

std::shared_ptr<Program> Parser::parse()
{
    cout<<"Parse"<<endl;
    currentToken = lexer.getToken();
    shared_ptr<Program> program = make_shared<Program>();
    std::shared_ptr<Definition> definition;
    std::shared_ptr<Statement> statement;
    variant<std::shared_ptr<Definition>, std::shared_ptr<Statement>> element;
    while(!EOTReceived)
    {
        if((definition = parseDefinition()))
        {
            element = definition;
            program->program.push_back(element);
            continue;
        }
        if((statement = parseStatement()))
        {
            element = statement;
            program->program.push_back(element);
            continue;
        }
        cout<<"ERROR "<<currentToken.position<<endl;
        getNextToken();
    }
    return program;
}


std::shared_ptr<Definition> Parser::parseDefinition()
{
    cout<<"Parse definition"<<endl;
    auto definition = make_shared<Definition>();
    return nullptr;
}

std::shared_ptr<Statement> Parser::parseStatement()
{
    cout<<"Parse statement"<<endl;
    auto statement = make_shared<Statement>();
    std::shared_ptr<Instruction> instruction;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTBRACKET)
    {
        getNextToken();
        while(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTBRACKET))
        {
            if((instruction = parseInstruction()))
                statement->instructions.push_back(instruction);
            else
                return nullptr;
        }
        getNextToken();
    }
    else
    {
        if((instruction = parseInstruction()))
            statement->instructions.push_back(instruction);
        else
            return nullptr;
    }
    return statement;
}


std::shared_ptr<Instruction> Parser::parseInstruction()
{
    cout<<"Parse instruction"<<endl;
    shared_ptr<Instruction> instruction = make_shared<Instruction>();
    std::shared_ptr<IfStatement> ifStatement;
    std::shared_ptr<WhileStatement> whileStatement;
    std::shared_ptr<ReturnStatement> returnStatement;
    std::shared_ptr<Expression> expression;

    /*if((ifStatement = parseIfStatement()))
    {
        instruction->instruction = ifStatement;
        return instruction;
    }
    if((whileStatement = parseWhileStatement()))
    {
        instruction->instruction = whileStatement;
        return instruction;
    }
    if((returnStatement = parseReturnStatement()))
    {
        instruction->instruction = returnStatement;
        return instruction;
    }*/
    if((expression = parseExpression()))
    {
        instruction->instruction = expression;
        return instruction;
    }
    return nullptr;
}


std::shared_ptr<Expression> Parser::parseExpression()
{
    cout<<"Parse expression"<<endl;
    return parseAssignExpression();
}


shared_ptr<Expression> Parser::parseBinaryExpression(function<shared_ptr<Expression>()> parseChildExpression,
    function<shared_ptr<Token>()> parseOperator, bool operationRightToLeft)
{
    cout<<"Parse binary expression"<<endl;
    shared_ptr<BinaryExpression> binaryExpression = make_shared<BinaryExpression>();
    shared_ptr<Expression> lhs;
    shared_ptr<Expression> rhs;
    vector<shared_ptr<Expression>> expressions;
    vector<shared_ptr<Token>> operators;
    shared_ptr<Token> currentOperator;

    if(!(lhs = parseChildExpression()))
        return nullptr;

    expressions.push_back(lhs);

    while((currentOperator = parseOperator()))
    {
        if(!(rhs = parseChildExpression()))
            throw runtime_error("Expected expression at "+to_string(currentToken.position));
        operators.push_back(currentOperator);
        expressions.push_back(rhs);
    }

    if(expressions.size() == 1)
        return expressions[0];

    if(operationRightToLeft)
    {
        for(int i = expressions.size() - 2; i >= 0; --i)
        {
            shared_ptr<Expression> prevExpression = make_shared<Expression>();
            prevExpression->expression = binaryExpression;
            binaryExpression = make_shared<BinaryExpression>();
            binaryExpression->lhs = expressions[i];
            binaryExpression->op = operators[i];
            binaryExpression->rhs = prevExpression;
        }
        shared_ptr<Expression> result = make_shared<Expression>();
        result->expression = binaryExpression;
        return result;
    }
    binaryExpression->lhs = expressions[0];
    binaryExpression->op = operators[0];
    binaryExpression->rhs = expressions[1];
    for(int i = 1; i < expressions.size() - 1; ++i)
    {
        shared_ptr<Expression> prevExpression = make_shared<Expression>();
        prevExpression->expression = binaryExpression;
        binaryExpression = make_shared<BinaryExpression>();
        binaryExpression->lhs = prevExpression;
        binaryExpression->op = operators[i];
        binaryExpression->rhs = expressions[i+1];
    }
    shared_ptr<Expression> result = make_shared<Expression>();
    result->expression = binaryExpression;
    return result;
}

std::shared_ptr<Token> Parser::acceptOperator()
{
    cout<<"Accept operator"<<endl;
    auto ret = make_shared<Token>();
    *ret = currentToken;
    getNextToken();
    return ret;
}

std::shared_ptr<Token> Parser::parseAssignOperator()
{
    cout<<"Parse assign op"<<endl;
    if(currentToken.classType == OPERATOR_TOKEN && currentToken.type == T_ASSIGN)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseOrOperator()
{
    cout<<"Parse or op"<<endl;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_OR)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseAndOperator()
{
    cout<<"Parse and op"<<endl;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_AND)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseEqOperator()
{
    cout<<"Parse eq op"<<endl;
    if(currentToken.classType == OPERATOR_TOKEN && currentToken.type == T_EQ)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseRelOperator()
{
    cout<<"Parse rel op"<<endl;
    if(currentToken.classType == OPERATOR_TOKEN && currentToken.type == T_REL)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseAddOperator()
{
    cout<<"Parse add op"<<endl;
    if(currentToken.classType == OPERATOR_TOKEN && currentToken.type == T_ADD)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseMulOperator()
{
    cout<<"Parse mul op"<<endl;
    if(currentToken.classType == OPERATOR_TOKEN && currentToken.type == T_MUL)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Token> Parser::parseExpOperator()
{
    cout<<"Parse exp op"<<endl;
    if(currentToken.classType == OPERATOR_TOKEN && currentToken.type == T_EXP)
    {
        return acceptOperator();
    }
    return nullptr;
}

std::shared_ptr<Expression> Parser::parseAssignExpression()
{
    cout<<"Parse assign exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseOrExpression, this), bind(&Parser::parseAssignOperator, this), true);
}

std::shared_ptr<Expression> Parser::parseOrExpression()
{
    cout<<"Parse or exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseAndExpression, this), bind(&Parser::parseOrOperator, this));
}

std::shared_ptr<Expression> Parser::parseAndExpression()
{
    cout<<"Parse and exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseEqExpression, this), bind(&Parser::parseAndOperator, this));
}

std::shared_ptr<Expression> Parser::parseEqExpression()
{
    cout<<"Parse eq exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseRelExpression, this), bind(&Parser::parseEqOperator, this));
}

std::shared_ptr<Expression> Parser::parseRelExpression()
{
    cout<<"Parse rel exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseAddExpression, this), bind(&Parser::parseRelOperator, this));
}

std::shared_ptr<Expression> Parser::parseAddExpression()
{
    cout<<"Parse add exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseMulExpression, this), bind(&Parser::parseAddOperator, this));
}

std::shared_ptr<Expression> Parser::parseMulExpression()
{
    cout<<"Parse mul exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseExpExpression, this), bind(&Parser::parseMulOperator, this));
}

std::shared_ptr<Expression> Parser::parseExpExpression()
{
    cout<<"Parse exp exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parsePrimaryExpression, this), bind(&Parser::parseExpOperator, this), true);
}

std::shared_ptr<Expression> Parser::parsePrimaryExpression()
{
    cout<<"Parse primary exp"<<endl;
    shared_ptr<Expression> expression;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTPAREN)
    {
        getNextToken();
        expression = parseAssignExpression();
        if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTPAREN)
            throw runtime_error("')' expected");
        getNextToken();
        return expression;
    }
    if((expression = parseLiteral()))
        return expression;
    expression = parseIdentifierOrFunctionCall();
}


std::shared_ptr<Expression> Parser::parseLiteral()
{
    cout<<"Parse literal"<<endl;
    if(currentToken.classType != LITERAL_TOKEN)
        return nullptr;
    shared_ptr<Literal> literal = make_shared<Literal>();
    literal->literal = make_shared<Token>(currentToken);
    shared_ptr<Expression> expression = make_shared<Expression>();
    expression->expression = literal;
    getNextToken();
    return expression;
}

std::shared_ptr<Expression> Parser::parseIdentifierOrFunctionCall()
{
    cout<<"Parse identifier or function call"<<endl;
    return nullptr;
}

