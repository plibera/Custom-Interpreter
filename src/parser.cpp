#include "parser.h"

using namespace std;


Token Parser::getNextToken() {
    if(EOTReceived)
        throw runtime_error("EOT already processed");
    currentToken = lexer.getToken();
    if(currentToken.classType == EOT_TOKEN)
    {
        EOTReceived = true;
    }
    return currentToken;
}

void Parser::generateError(std::string msg)
{
    throw runtime_error(msg+" Line:"+to_string(currentToken.lineNumber+1)+" pos:"+to_string(currentToken.linePosition));
}

std::shared_ptr<Program> Parser::parse()
{
    getNextToken();
    shared_ptr<Program> program = make_shared<Program>();
    program->pos = Position(currentToken);
    std::shared_ptr<Definition> definition;
    std::shared_ptr<Statement> statement;
    variant<std::shared_ptr<Definition>, std::shared_ptr<Statement>> element;
    while(!EOTReceived)
    {
        if(definition = parseDefinition())
        {
            element = definition;
            program->program.push_back(element);
            continue;
        }
        if(statement = parseStatement())
        {
            element = statement;
            program->program.push_back(element);
            continue;
        }
        generateError("Error: not a definition or a statement");
    }
    return program;
}


std::shared_ptr<Definition> Parser::parseDefinition()
{
    shared_ptr<Definition> definition;
    shared_ptr<TypeDefinition> typeDefinition;
    if(definition = parseIdentifierOrFunctionDefinition())
    {
        return definition;
    }
    if(typeDefinition = parseTypeDefinition())
    {
        definition = make_shared<Definition>();
        definition->pos = Position(currentToken);
        definition->definition = typeDefinition;
        return definition;
    }
    return nullptr;
}

std::shared_ptr<Statement> Parser::parseStatement()
{
    auto statement = make_shared<Statement>();
    statement->pos = Position(currentToken);
    std::shared_ptr<Instruction> instruction;
    if(consume(KEYWORD_TOKEN, T_LEFTBRACKET))
    {
        while(!consume(KEYWORD_TOKEN, T_RIGHTBRACKET))
        {
            if(instruction = parseInstruction())
                statement->instructions.push_back(instruction);
            else
                generateError("Error parsing instruction inside the statement ");
        }
    }
    else
    {
        if(instruction = parseInstruction())
            statement->instructions.push_back(instruction);
        else
            return nullptr;
        statement->newBlock = false;
    }
    return statement;
}


std::shared_ptr<Instruction> Parser::parseInstruction()
{
    shared_ptr<Instruction> instruction = make_shared<Instruction>();
    instruction->pos = Position(currentToken);
    std::shared_ptr<IfStatement> ifStatement;
    std::shared_ptr<WhileStatement> whileStatement;
    std::shared_ptr<ReturnStatement> returnStatement;
    std::shared_ptr<Definition> definition;
    std::shared_ptr<Expression> expression;

    if(ifStatement = parseIfStatement())
    {
        instruction->instruction = ifStatement;
        return instruction;
    }
    if(whileStatement = parseWhileStatement())
    {
        instruction->instruction = whileStatement;
        return instruction;
    }
    if(returnStatement = parseReturnStatement())
    {
        instruction->instruction = returnStatement;
        expect(KEYWORD_TOKEN, T_SEMICOLON, "Expected ';'");
        return instruction;
    }
    if(definition = parseIdentifierOrFunctionDefinition(true))
    {
        instruction->instruction = get<shared_ptr<VariableDeclaration>>(definition->definition);
        expect(KEYWORD_TOKEN, T_SEMICOLON, "Expected ';'");
        return instruction;
    }
    if(expression = parseExpression())
    {
        instruction->instruction = expression;
        expect(KEYWORD_TOKEN, T_SEMICOLON, "Expected ';'");
        return instruction;
    }
    return nullptr;
}


std::shared_ptr<Expression> Parser::parseExpression()
{
    if(accept(KEYWORD_TOKEN, T_NOT))
    {
        shared_ptr<BinaryExpression> binaryExpression = make_shared<BinaryExpression>();
        binaryExpression->lhs = make_shared<Expression>();
        binaryExpression->lhs->expression = make_shared<Literal>();
        binaryExpression->op = currentToken;
        binaryExpression->pos = Position(currentToken);
        getNextToken();
        binaryExpression->rhs = parseExpression();
        shared_ptr<Expression> expression = make_shared<Expression>();
        expression->expression = binaryExpression;
        expression->pos = binaryExpression->pos;
        return expression;
    }
    return parseAssignExpression();
}


shared_ptr<Expression> Parser::parseBinaryExpression(function<shared_ptr<Expression>()> parseChildExpression,
    int operatorClass, int operatorType, bool operationRightToLeft)
{
    shared_ptr<BinaryExpression> binaryExpression = make_shared<BinaryExpression>();
    binaryExpression->pos = Position(currentToken);
    shared_ptr<Expression> lhs;
    shared_ptr<Expression> rhs;
    vector<shared_ptr<Expression>> expressions;
    vector<Token> operators;
    Token currentOperator;

    if(!(lhs = parseChildExpression()))
    {
        return nullptr;
    }

    expressions.push_back(lhs);

    while(accept(operatorClass, operatorType))
    {
        currentOperator = currentToken;
        getNextToken();
        if(!(rhs = parseChildExpression()))
            generateError("Expected expression");
        operators.push_back(currentOperator);
        expressions.push_back(rhs);
    }

    if(expressions.size() == 1)
        return expressions[0];

    if(operationRightToLeft)
    {
        binaryExpression->lhs = expressions[expressions.size()-2];
        binaryExpression->op = operators[expressions.size()-2];
        binaryExpression->rhs = expressions[expressions.size()-1];
        for(int i = expressions.size() - 3; i >= 0; --i)
        {
            shared_ptr<Expression> prevExpression = make_shared<Expression>();
            prevExpression->pos = Position(currentToken);
            prevExpression->expression = binaryExpression;
            binaryExpression = make_shared<BinaryExpression>();
            binaryExpression->pos = Position(currentToken);
            binaryExpression->lhs = expressions[i];
            binaryExpression->op = operators[i];
            binaryExpression->rhs = prevExpression;
        }
        shared_ptr<Expression> result = make_shared<Expression>();
        result->pos = Position(currentToken);
        result->expression = binaryExpression;
        return result;
    }
    binaryExpression->lhs = expressions[0];
    binaryExpression->op = operators[0];
    binaryExpression->rhs = expressions[1];
    for(int i = 1; i < expressions.size() - 1; ++i)
    {
        shared_ptr<Expression> prevExpression = make_shared<Expression>();
        prevExpression->pos = Position(currentToken);
        prevExpression->expression = binaryExpression;
        binaryExpression = make_shared<BinaryExpression>();
        binaryExpression->pos = Position(currentToken);
        binaryExpression->lhs = prevExpression;
        binaryExpression->op = operators[i];
        binaryExpression->rhs = expressions[i+1];
    }
    shared_ptr<Expression> result = make_shared<Expression>();
    result->pos = Position(currentToken);
    result->expression = binaryExpression;
    return result;
}

bool Parser::accept(int operatorClass, int operatorType)
{
    if(currentToken.classType == operatorClass && currentToken.type == operatorType)
    {
        return true;
    }
    return false;
}

bool Parser::consume(int operatorClass, int operatorType)
{
    if(currentToken.classType == operatorClass && currentToken.type == operatorType)
    {
        getNextToken();
        return true;
    }
    return false;
}

bool Parser::expect(int operatorClass, int operatorType, string msg)
{
    if(currentToken.classType == operatorClass && currentToken.type == operatorType)
    {
        getNextToken();
        return true;
    }
    generateError(msg);
    return false;
}

std::shared_ptr<Expression> Parser::parseAssignExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parseOrExpression, this), OPERATOR_TOKEN, T_ASSIGN, true);
}

std::shared_ptr<Expression> Parser::parseOrExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parseAndExpression, this), KEYWORD_TOKEN, T_OR);
}

std::shared_ptr<Expression> Parser::parseAndExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parseEqExpression, this), KEYWORD_TOKEN, T_AND);
}

std::shared_ptr<Expression> Parser::parseEqExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parseRelExpression, this), OPERATOR_TOKEN, T_EQ);
}

std::shared_ptr<Expression> Parser::parseRelExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parseAddExpression, this), OPERATOR_TOKEN, T_REL);
}

std::shared_ptr<Expression> Parser::parseAddExpression()
{
    long long *opId;
    if(accept(OPERATOR_TOKEN, T_ADD) && (opId = get_if<long long>(&currentToken.value)) && *opId == operatorIdMap.at("-"))
    {
        auto exp = make_shared<Expression>();
        exp->pos = Position(currentToken);
        auto binExp = make_shared<BinaryExpression>();
        binExp->pos = Position(currentToken);
        auto lhs = make_shared<Expression>();
        lhs->pos = Position(currentToken);
        shared_ptr<Literal> literal = make_shared<Literal>();
        literal->pos = Position(currentToken);
        literal->literal = Token(LITERAL_TOKEN, T_INT_LIT, currentToken.position, currentToken.lineNumber, currentToken.linePosition, (long long)0);
        lhs->expression = literal;
        binExp->lhs = lhs;
        binExp->op = currentToken;
        getNextToken();
        if(binExp->rhs = parseExpression())
        {
            exp->expression = binExp;
            return exp;
        }
        return nullptr;
    }
    return parseBinaryExpression(bind_front(&Parser::parseMulExpression, this), OPERATOR_TOKEN, T_ADD);
}

std::shared_ptr<Expression> Parser::parseMulExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parseExpExpression, this), OPERATOR_TOKEN, T_MUL);
}

std::shared_ptr<Expression> Parser::parseExpExpression()
{
    return parseBinaryExpression(bind_front(&Parser::parsePrimaryExpression, this), OPERATOR_TOKEN, T_EXP, true);
}

std::shared_ptr<Expression> Parser::parsePrimaryExpression()
{
    shared_ptr<Expression> expression;
    if(consume(KEYWORD_TOKEN, T_LEFTPAREN))
    {
        expression = parseAssignExpression();
        if(!consume(KEYWORD_TOKEN, T_RIGHTPAREN))
            generateError("')' expected");
        return expression;
    }
    if(expression = parseLiteral())
        return expression;
    return parseIdentifierOrFunctionCall();
}


std::shared_ptr<Expression> Parser::parseLiteral()
{
    if(currentToken.classType != LITERAL_TOKEN && !accept(KEYWORD_TOKEN, T_TRUE) && !accept(KEYWORD_TOKEN, T_FALSE))
        return nullptr;
    shared_ptr<Literal> literal = make_shared<Literal>();
    literal->pos = Position(currentToken);
    literal->literal = currentToken;
    shared_ptr<Expression> expression = make_shared<Expression>();
    expression->pos = Position(currentToken);
    expression->expression = literal;
    getNextToken();
    return expression;
}

std::shared_ptr<Expression> Parser::parseIdentifierOrFunctionCall()
{
    if(!accept(IDENTIFIER_TOKEN, T_VAR))
        return nullptr;
    
    string object;
    string idStr = get<string>(currentToken.value);
    getNextToken();

    if(consume(KEYWORD_TOKEN, T_ACCESS))
    {
        object = idStr;
        idStr = "";

        if(!accept(IDENTIFIER_TOKEN, T_VAR))
            generateError("Expected identifier after '.'");

        idStr = get<string>(currentToken.value);
        getNextToken();
    }

    if(!consume(KEYWORD_TOKEN, T_LEFTPAREN))
    {
        //Parse identifier
        shared_ptr<Identifier> identifier = make_shared<Identifier>();
        identifier->pos = Position(currentToken);
        identifier->object = object;
        identifier->identifier = idStr;
        shared_ptr<Expression> expression = make_shared<Expression>();
        expression->pos = Position(currentToken);
        expression->expression = identifier;
        return expression;
    }

    //Parse function call

    shared_ptr<FunCall> funCall = make_shared<FunCall>();
    funCall->pos = Position(currentToken);
    funCall->object = object;
    funCall->identifier = idStr;
    shared_ptr<Expression> expression;
    bool firstArgument = true;
    do
    {
        if(!(expression = parseExpression()))
        {
            if(firstArgument)
            {
                break;
            }
            else
            {
                generateError("Expected expression after ','");
            }
        }
        firstArgument = false;
        funCall->arguments.push_back(expression);
    } while(consume(KEYWORD_TOKEN, T_COMMA));

    expect(KEYWORD_TOKEN, T_RIGHTPAREN, "Expected ')'");

    expression = make_shared<Expression>();
    expression->pos = Position(currentToken);
    expression->expression = funCall;
    return expression;
}

std::shared_ptr<IfStatement> Parser::parseIfStatement()
{
    if(!consume(KEYWORD_TOKEN, T_IF))
        return nullptr;
    expect(KEYWORD_TOKEN, T_LEFTPAREN, "Expected '(' after 'if'");
    
    shared_ptr<IfStatement> ifStatement = make_shared<IfStatement>();
    ifStatement->pos = Position(currentToken);
    if(!(ifStatement->condition = parseExpression()))
        generateError("Expected condition expression after '('");
    expect(KEYWORD_TOKEN, T_RIGHTPAREN, "Expected ')' after condition");

    if(!(ifStatement->statementTrue = parseStatement()))
        generateError("Expected statement after ')'");
    if(consume(KEYWORD_TOKEN, T_ELSE))
    {
        if(!(ifStatement->statementFalse = parseStatement()))
            generateError("Expected statement after 'else'");
    }
    return ifStatement;
}

std::shared_ptr<WhileStatement> Parser::parseWhileStatement()
{
    if(!consume(KEYWORD_TOKEN, T_WHILE))
        return nullptr;

    expect(KEYWORD_TOKEN, T_LEFTPAREN, "Expected '(' after 'while'");
    
    shared_ptr<WhileStatement> whileStatement = make_shared<WhileStatement>();
    whileStatement->pos = Position(currentToken);
    
    if(!(whileStatement->condition = parseExpression()))
        generateError("Expected condition expression after '('");
    
    expect(KEYWORD_TOKEN, T_RIGHTPAREN, "Expected ')' after condition");

    if(!(whileStatement->statement = parseStatement()))
        generateError("Expected statement after ')'");
    return whileStatement;
}

std::shared_ptr<ReturnStatement> Parser::parseReturnStatement()
{
    if(!consume(KEYWORD_TOKEN, T_RETURN))
        return nullptr;

    shared_ptr<ReturnStatement> returnStatement = make_shared<ReturnStatement>();
    returnStatement->pos = Position(currentToken);
    returnStatement->expression = parseExpression();
    return returnStatement;
}

std::shared_ptr<Definition> Parser::parseIdentifierOrFunctionDefinition(bool expectIdentifier)
{
    if(!(accept(IDENTIFIER_TOKEN, T_TYPE) || accept(KEYWORD_TOKEN, T_INT) || accept(KEYWORD_TOKEN, T_VOID) || 
        accept(KEYWORD_TOKEN, T_FLOAT) || accept(KEYWORD_TOKEN, T_BOOL) || accept(KEYWORD_TOKEN, T_STRING)))
        return nullptr;
    
    Token type = currentToken;
    getNextToken();

    if(!accept(IDENTIFIER_TOKEN, T_VAR))
        generateError("Expected identifier after type");
    
    string identifier = get<string>(currentToken.value);
    getNextToken();

    if(!accept(KEYWORD_TOKEN, T_LEFTPAREN))
    {
        if(type.classType == KEYWORD_TOKEN && type.type == T_VOID)
            generateError("Identifier of type Void not allowed");
        
        //Parse identifier
        shared_ptr<VariableDeclaration> variableDeclatation = make_shared<VariableDeclaration>();
        variableDeclatation->pos = Position(currentToken);
        variableDeclatation->type = type;
        variableDeclatation->identifier = identifier;
        if(consume(OPERATOR_TOKEN, T_ASSIGN))
        {
            shared_ptr<Expression> expression;
            if(expression = parseExpression())
            {
                variableDeclatation->expression = expression;
            }
            else
                generateError("Expected expression after '='");
        }

        if(!expectIdentifier)
            expect(KEYWORD_TOKEN, T_SEMICOLON, "Expected ';'");
        shared_ptr<Definition> definition = make_shared<Definition>();
        definition->pos = Position(currentToken);
        definition->definition = variableDeclatation;
        return definition;
    }

    if(expectIdentifier)
        generateError("Unexpected function declaration");
    
    getNextToken();

    //Parse function definition/declaration

    shared_ptr<FunDefinition> funDefinition = make_shared<FunDefinition>();
    funDefinition->pos = Position(currentToken);
    funDefinition->type = type;
    funDefinition->identifier = identifier;
    shared_ptr<Definition> definition;
    shared_ptr<VariableDeclaration> variableDeclaration;
    bool firstArgument = true;
    do
    {
        if(!(definition = parseIdentifierOrFunctionDefinition(true)))
        {
            if(firstArgument)
            {
                break;
            }
            else
            {
                generateError("Expected parameter declaration after ','");
            }
        }
        firstArgument = false;
        variableDeclaration = get<shared_ptr<VariableDeclaration>>(definition->definition);
        funDefinition->arguments.push_back(variableDeclaration);
    } while(consume(KEYWORD_TOKEN, T_COMMA));

    expect(KEYWORD_TOKEN, T_RIGHTPAREN, "Expected ')'");

    shared_ptr<Statement> statement;
    if(accept(KEYWORD_TOKEN, T_LEFTBRACKET))
    {
        if(statement = parseStatement())
            funDefinition->statement = statement;
    }
    else
    {
        expect(KEYWORD_TOKEN, T_SEMICOLON, "Expected ';'");
    }
    definition = make_shared<Definition>();
    definition->pos = Position(currentToken);
    definition->definition = funDefinition;
    return definition;
}

std::shared_ptr<TypeDefinition> Parser::parseTypeDefinition()
{
    if(!consume(KEYWORD_TOKEN, T_CLASS))
        return nullptr;
    if(!accept(IDENTIFIER_TOKEN, T_TYPE))
        generateError("Expected custom type identifier after 'class'");
    shared_ptr<TypeDefinition> typeDefinition = make_shared<TypeDefinition>();
    typeDefinition->pos = Position(currentToken);
    typeDefinition->type = currentToken;
    getNextToken();

    expect(KEYWORD_TOKEN, T_LEFTBRACKET, "Expected '{'");

    shared_ptr<Definition> definition;
    shared_ptr<FunDefinition> funDefinition;
    shared_ptr<VariableDeclaration> variable;
    bool isPublic = false;
    while(!consume(KEYWORD_TOKEN, T_RIGHTBRACKET))
    {
        isPublic = consume(KEYWORD_TOKEN, T_PUBLIC);
        if(!(definition = parseIdentifierOrFunctionDefinition()))
            generateError("Expected '}'");
        switch(definition->definition.index())
        {
            case 0:
                funDefinition = get<shared_ptr<FunDefinition>>(definition->definition);
                funDefinition->isPublic = isPublic;
                typeDefinition->functions.push_back(funDefinition);
                break;
            case 2:
                variable = get<shared_ptr<VariableDeclaration>>(definition->definition);
                variable->isPublic = isPublic;
                typeDefinition->variables.push_back(variable);
                break;
            default:
                generateError("Error parsing custom type");
        }
    }
    expect(KEYWORD_TOKEN, T_SEMICOLON, "Expected ';'");
    return typeDefinition;
}