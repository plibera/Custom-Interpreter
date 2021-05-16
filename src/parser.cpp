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
    getNextToken();
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
        throw runtime_error("Error: not a definition or a statement: "+to_string(currentToken.position));
    }
    return program;
}


std::shared_ptr<Definition> Parser::parseDefinition()
{
    cout<<"Parse definition"<<endl;
    shared_ptr<Definition> definition;
    shared_ptr<TypeDefinition> typeDefinition;
    if((definition = parseIdentifierOrFunctionDefinition()))
    {
        return definition;
    }
    if((typeDefinition = parseTypeDefinition()))
    {
        definition = make_shared<Definition>();
        definition->definition = typeDefinition;
        return definition;
    }
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
                throw runtime_error("Error parsing instruction inside the statement: "+to_string(currentToken.position));
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

    if((ifStatement = parseIfStatement()))
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
        parseSemicolon();
        return instruction;
    }
    if((expression = parseExpression()))
    {
        instruction->instruction = expression;
        parseSemicolon();
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
    int operatorClass, int operatorType, bool operationRightToLeft)
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

    while(currentToken.classType == operatorClass && currentToken.type == operatorType)
    {
        currentOperator = acceptOperator();
        if(!(rhs = parseChildExpression()))
            throw runtime_error("Expected expression at "+to_string(currentToken.position));
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

std::shared_ptr<Expression> Parser::parseAssignExpression()
{
    cout<<"Parse assign exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseOrExpression, this), OPERATOR_TOKEN, T_ASSIGN, true);
}

std::shared_ptr<Expression> Parser::parseOrExpression()
{
    cout<<"Parse or exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseAndExpression, this), KEYWORD_TOKEN, T_OR);
}

std::shared_ptr<Expression> Parser::parseAndExpression()
{
    cout<<"Parse and exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseEqExpression, this), KEYWORD_TOKEN, T_AND);
}

std::shared_ptr<Expression> Parser::parseEqExpression()
{
    cout<<"Parse eq exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseRelExpression, this), OPERATOR_TOKEN, T_EQ);
}

std::shared_ptr<Expression> Parser::parseRelExpression()
{
    cout<<"Parse rel exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseAddExpression, this), OPERATOR_TOKEN, T_REL);
}

std::shared_ptr<Expression> Parser::parseAddExpression()
{
    cout<<"Parse add exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseMulExpression, this), OPERATOR_TOKEN, T_ADD);
}

std::shared_ptr<Expression> Parser::parseMulExpression()
{
    cout<<"Parse mul exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parseExpExpression, this), OPERATOR_TOKEN, T_MUL);
}

std::shared_ptr<Expression> Parser::parseExpExpression()
{
    cout<<"Parse exp exp"<<endl;
    return parseBinaryExpression(bind(&Parser::parsePrimaryExpression, this), OPERATOR_TOKEN, T_EXP, true);
}

std::shared_ptr<Expression> Parser::parsePrimaryExpression()
{
    cout<<"Parse primary exp"<<endl;
    shared_ptr<Expression> expression;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTPAREN)
    {
        getNextToken();
        expression = parseAssignExpression();
        if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTPAREN))
            throw runtime_error("')' expected");
        getNextToken();
        return expression;
    }
    if((expression = parseLiteral()))
        return expression;
    return parseIdentifierOrFunctionCall();
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

std::shared_ptr<IfStatement> Parser::parseIfStatement()
{
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_IF))
        return nullptr;

    getNextToken();
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTPAREN))
        throw runtime_error("Expected '(' after 'if': "+to_string(currentToken.position));
    getNextToken();
    shared_ptr<IfStatement> ifStatement = make_shared<IfStatement>();
    if(!(ifStatement->condition = parseExpression()))
        throw runtime_error("Expected condition expression after '(': "+to_string(currentToken.position));
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTPAREN))
        throw runtime_error("Expected ')' after condition: "+to_string(currentToken.position));
    getNextToken();
    if(!(ifStatement->statementTrue = parseStatement()))
        throw runtime_error("Expected statement after ')': "+to_string(currentToken.position));
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_ELSE)
    {
        getNextToken();
        if(!(ifStatement->statementFalse = parseStatement()))
            throw runtime_error("Expected statement after 'else': "+to_string(currentToken.position));
    }
    return ifStatement;
}

std::shared_ptr<WhileStatement> Parser::parseWhileStatement()
{
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_WHILE))
        return nullptr;

    getNextToken();
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTPAREN))
        throw runtime_error("Expected '(' after 'while': "+to_string(currentToken.position));
    getNextToken();
    shared_ptr<WhileStatement> whileStatement = make_shared<WhileStatement>();
    if(!(whileStatement->condition = parseExpression()))
        throw runtime_error("Expected condition expression after '(': "+to_string(currentToken.position));
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTPAREN))
        throw runtime_error("Expected ')' after condition: "+to_string(currentToken.position));
    getNextToken();
    if(!(whileStatement->statement = parseStatement()))
        throw runtime_error("Expected statement after ')': "+to_string(currentToken.position));
    return whileStatement;
}

std::shared_ptr<ReturnStatement> Parser::parseReturnStatement()
{
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RETURN))
        return nullptr;

    getNextToken();
    shared_ptr<ReturnStatement> returnStatement = make_shared<ReturnStatement>();
    if(!(returnStatement->expression = parseExpression()))
        throw runtime_error("Expected expression after 'return': "+to_string(currentToken.position));
    return returnStatement;
}

void Parser::parseSemicolon()
{
    cout<<"Parse semicolon"<<endl;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_SEMICOLON)
    {
        getNextToken();
        return;
    }
    throw runtime_error("Expected ';': "+to_string(currentToken.position));
}

std::shared_ptr<Definition> Parser::parseIdentifierOrFunctionDefinition(bool forceIdentifier)
{
    cout<<"Parse identifier or function definition"<<endl;
    if(!(currentToken.classType == IDENTIFIER_TOKEN && currentToken.type == T_TYPE || 
         currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_INT ||
         currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_VOID ||
         currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_FLOAT ||
         currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_STRING))
        return nullptr;
    
    shared_ptr<Token> type = make_shared<Token>();
    *type = currentToken;
    getNextToken();

    if(!(currentToken.classType == IDENTIFIER_TOKEN && currentToken.type == T_VAR))
        throw runtime_error("Expected identifier after type: "+to_string(currentToken.position));
    
    string identifier = get<string>(currentToken.value);
    getNextToken();

    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTPAREN))
    {
        if(type->classType == KEYWORD_TOKEN && type->type == T_VOID)
            throw runtime_error("Identifier of type Void not allowed: "+to_string(currentToken.position));
        //Parse identifier
        if(!forceIdentifier)
            parseSemicolon();
        shared_ptr<VariableDeclaration> variableDeclatation = make_shared<VariableDeclaration>();
        variableDeclatation->type = type;
        variableDeclatation->identifier = identifier;
        shared_ptr<Definition> definition = make_shared<Definition>();
        definition->definition = variableDeclatation;
        return definition;
    }

    if(forceIdentifier)
        throw runtime_error("Unexpected function declaration: "+to_string(currentToken.position));
    
    getNextToken();

    //Parse function definition/declaration

    shared_ptr<FunDefinition> funDefinition = make_shared<FunDefinition>();
    funDefinition->type = type;
    funDefinition->identifier = identifier;
    shared_ptr<Definition> definition;
    shared_ptr<VariableDeclaration> variableDeclaration;
    do
    {
        if(!(definition = parseIdentifierOrFunctionDefinition(true)))
            break;
        variableDeclaration = get<shared_ptr<VariableDeclaration>>(definition->definition);
        funDefinition->arguments.push_back(variableDeclaration);
    } while(parseComma());

    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTPAREN))
        throw runtime_error("Expected ')': "+to_string(currentToken.position));
    getNextToken();

    shared_ptr<Statement> statement;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTBRACKET)
    {
        if((statement = parseStatement()))
            funDefinition->statement = statement;
    }
    else
    {
        parseSemicolon();
    }
    definition = make_shared<Definition>();
    definition->definition = funDefinition;
    return definition;
}

std::shared_ptr<TypeDefinition> Parser::parseTypeDefinition()
{
    cout<<"Parse type definition"<<endl;
    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_CLASS))
        return nullptr;
    getNextToken();
    if(!(currentToken.classType == IDENTIFIER_TOKEN && currentToken.type == T_TYPE))
        throw runtime_error("Expected custom type identifier after 'class': "+to_string(currentToken.position));
    shared_ptr<TypeDefinition> typeDefinition = make_shared<TypeDefinition>();
    typeDefinition->type = make_shared<Token>();
    *typeDefinition->type = currentToken;
    getNextToken();

    if(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_LEFTBRACKET))
        throw runtime_error("Expected '{': "+to_string(currentToken.position));
    getNextToken();

    shared_ptr<Definition> definition;
    shared_ptr<FunDefinition> funDefinition;
    shared_ptr<VariableDeclaration> variable;
    while(!(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_RIGHTBRACKET))
    {
        if(!(definition = parseIdentifierOrFunctionDefinition()))
            throw runtime_error("Expected '}': "+to_string(currentToken.position));
        switch(definition->definition.index())
        {
            case 0:
                funDefinition = get<shared_ptr<FunDefinition>>(definition->definition);
                typeDefinition->functions.push_back(funDefinition);
                break;
            case 2:
                variable = get<shared_ptr<VariableDeclaration>>(definition->definition);
                typeDefinition->variables.push_back(variable);
                break;
            default:
                throw runtime_error("Error parsing custom type: "+to_string(currentToken.position));
        }
    }
    getNextToken();
    parseSemicolon();
    return typeDefinition;
}

bool Parser::parseComma()
{
    cout<<"Parse comma"<<endl;
    if(currentToken.classType == KEYWORD_TOKEN && currentToken.type == T_COMMA)
    {
        getNextToken();
        return true;
    }
    return false;
}