#include "interpreter.h"

using namespace std;

int Interpreter::execute()
{
    shared_ptr<Program> program = parser.parse();
    lastReturnValue = evaluate(program);
    if(lastReturnValue == nullptr)
    {
        cerr<<"Program finished without return statement."<<endl;
        return 0;
    }
    if(auto returnCode = get_if<long long>(lastReturnValue->value.get()))
    {
        cerr<<"Program returned "<<*returnCode<<endl;
        return 0;
    }
    if(lastReturnValue->value == nullptr)
    {
        cerr<<"Program returned with no return value"<<endl;
        return 1;
    }
    else
    {
        cerr<<"Program returned value of type different than Int"<<endl;
        return 2;
    }
}


std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Program> program)
{
    //cout<<"Evaluating program"<<endl;
    //cout<<program->to_string()<<endl;
    shared_ptr<Value> returnValue;
    for(auto& element : program->program)
    {
        if(auto definition = get_if<shared_ptr<Definition>>(&element))
        {
            evaluate(*definition);
        }
        else if(auto statement = get_if<shared_ptr<Statement>>(&element))
        {
            if(returnValue = evaluate(*statement))
            {
                return returnValue;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Statement> statement)
{
    //cout<<"Evaluating statement"<<endl;
    shared_ptr<Value> returnValue;
    if(statement->newBlock)
    {
        scope.currentPos = statement->pos;
        scope.newInstructionBlock();
    }
    for(auto& instruction : statement->instructions)
    {
        if(returnValue = evaluate(instruction))
        {
            return returnValue;
        }
    }
    if(statement->newBlock)
    {
        scope.endInstructionBlock();
    }
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<BinaryExpression> binaryExpression)
{
    //cout<<"Evaluating binary expression"<<endl;
    if(binaryExpression->op.type == T_ASSIGN)
    {
        if(auto identifier = get_if<shared_ptr<Identifier>>(&binaryExpression->lhs->expression))
        {
            scope.currentPos = binaryExpression->pos;
            auto newValue = evaluate(binaryExpression->rhs);
            scope.assignValue((*identifier)->identifier, newValue);
            return newValue;
        }
        else
        {
            throw runtime_error("Attempt to assign value to something else than an identifier: "+binaryExpression->pos.toString());
        }
    }
    shared_ptr<Value> leftValue = evaluate(binaryExpression->lhs);
    shared_ptr<Value> rightValue = evaluate(binaryExpression->rhs);
    long long *operatorId;
    if(!(operatorId = get_if<long long>(&binaryExpression->op.value)))
    {
        throw runtime_error("Token operator value is of wrong type: "+binaryExpression->pos.toString());
    } 
    try
    {
        if(binaryExpression->op.type == T_EQ)
        {
            if(*operatorId == operatorIdMap.at("=="))
            {
                return make_shared<Value>(*leftValue == *rightValue);
            }
            if(*operatorId == operatorIdMap.at("!="))
            {
                return make_shared<Value>(*leftValue != *rightValue);
            }
        }
        else if(binaryExpression->op.type == T_REL)
        {
            if(*operatorId == operatorIdMap.at("<"))
            {
                return make_shared<Value>(*leftValue < *rightValue);
            }
            if(*operatorId == operatorIdMap.at(">"))
            {
                return make_shared<Value>(*leftValue > *rightValue);
            }
            if(*operatorId == operatorIdMap.at("<="))
            {
                return make_shared<Value>(*leftValue <= *rightValue);
            }
            if(*operatorId == operatorIdMap.at(">="))
            {
                return make_shared<Value>(*leftValue >= *rightValue);
            }
        }
        else if(binaryExpression->op.type == T_ADD)
        {
            if(*operatorId == operatorIdMap.at("+"))
            {
                return make_shared<Value>(*leftValue + *rightValue);
            }
            if(*operatorId == operatorIdMap.at("-"))
            {
                return make_shared<Value>(*leftValue - *rightValue);
            }
        }
        else if(binaryExpression->op.type == T_MUL)
        {
            if(*operatorId == operatorIdMap.at("*"))
            {
                return make_shared<Value>(*leftValue * *rightValue);
            }
            if(*operatorId == operatorIdMap.at("/"))
            {
                return make_shared<Value>(*leftValue / *rightValue);
            }
        }
        else if(binaryExpression->op.type == T_EXP)
        {
            if(*operatorId == operatorIdMap.at("**"))
            {
                return make_shared<Value>(*leftValue ^ *rightValue);
            }
        }
    }
    catch(const std::exception& e)
    {
        throw runtime_error(string(e.what()) + " " + binaryExpression->pos.toString());
    }
    throw runtime_error("Could not evaluate binary expression: "+binaryExpression->pos.toString());
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<FunCall> funCall)
{
    //cout<<"Evaluating Fun call"<<endl;
    vector<shared_ptr<Value>> argumentValues;
    for(auto &argument : funCall->arguments)
    {
        auto value = evaluate(argument);
        argumentValues.push_back(make_shared<Value>(*value));
    }
    for(auto &function : functions)
    {
        bool accept = false;
        try
        {
            accept = function.first->acceptFunCall(funCall->identifier, argumentValues);
        }
        catch(const std::exception& e)
        {
            throw runtime_error(string(e.what()) + " " + funCall->pos.toString());
        }
        
        if(accept)
        {
            if(function.first->statement == nullptr)
            {
                throw runtime_error("Declared but undefined function "+funCall->identifier+" called: "+funCall->pos.toString());
            }
            shared_ptr<Value> retVal;
            scope.currentPos = funCall->pos;
            scope.newLevel();
            scope.newInstructionBlock();
            for(size_t i = 0; i < argumentValues.size(); ++i)
            {
                scope.addVariable(function.first->arguments[i]->identifier, argumentValues[i]);
            }
            retVal = function.second(function.first->statement);
            scope.endInstructionBlock();
            scope.endLevel();
            accept = function.first->acceptReturnValue(retVal);
            if(!accept)
            {
                if(retVal != nullptr)
                {
                    throw runtime_error("Wrong type of returned value in function "+funCall->identifier+": "+funCall->pos.toString());
                }
                else
                {
                    throw runtime_error("Expected a return statement in function "+funCall->identifier+": "+funCall->pos.toString());
                }
            }
            return retVal;
        }
    }
    throw runtime_error("Unknown function "+funCall->identifier+" called: "+funCall->pos.toString());
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Expression> expression)
{
    //cout<<"Evaluating expression"<<endl;
    shared_ptr<Value> returnValue;
    if(auto binaryExpression = get_if<shared_ptr<BinaryExpression>>(&expression->expression))
    {
        return evaluate(*binaryExpression);
    }
    if(auto funCall = get_if<shared_ptr<FunCall>>(&expression->expression))
    {
        return evaluate(*funCall);
    }
    if(auto literal = get_if<shared_ptr<Literal>>(&expression->expression))
    {
        return evaluate(*literal);
    }
    if(auto identifier = get_if<shared_ptr<Identifier>>(&expression->expression))
    {
        return evaluate(*identifier);
    }
    return make_shared<Value>();
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Literal> literal)
{
    if(literal->literal.classType == KEYWORD_TOKEN)
    {
        if(literal->literal.type == T_TRUE)
        {
            return make_shared<Value>(true);
        }
        if(literal->literal.type == T_FALSE)
        {
            return make_shared<Value>(false);
        }
    }
    if(auto intLiteral = get_if<long long>(&literal->literal.value))
    {
        return make_shared<Value>(*intLiteral);
    }
    if(auto floatLiteral = get_if<double>(&literal->literal.value))
    {
        return make_shared<Value>(*floatLiteral);
    }
    if(auto stringLiteral = get_if<string>(&literal->literal.value))
    {
        return make_shared<Value>(*stringLiteral);
    }
    throw runtime_error("Unknown literal type: "+literal->pos.toString());
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Identifier> identifier)
{
    //cout<<"Evaluating identifier"<<endl;
    scope.currentPos = identifier->pos;
    return scope.getValue(identifier->identifier);
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Instruction> instruction)
{
    //cout<<"Evaluating instruction"<<endl;
    shared_ptr<Value> returnValue;
    if(auto expression = get_if<shared_ptr<Expression>>(&instruction->instruction))
    {
        evaluate(*expression);
    }
    else if(auto ifStatement = get_if<shared_ptr<IfStatement>>(&instruction->instruction))
    {
        if(returnValue = evaluate(*ifStatement))
        {
            return returnValue;
        }
    }
    else if(auto whileStatement = get_if<shared_ptr<WhileStatement>>(&instruction->instruction))
    {
        if(returnValue = evaluate(*whileStatement))
        {
            return returnValue;
        }
    }
    else if(auto returnStatement = get_if<shared_ptr<ReturnStatement>>(&instruction->instruction))
    {
        if(returnValue = evaluate(*returnStatement))
        {
            return returnValue;
        }
    }
    else if(auto variableDeclaration = get_if<shared_ptr<VariableDeclaration>>(&instruction->instruction))
    {
        evaluate(*variableDeclaration);
    }
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<IfStatement> ifStatement)
{
    shared_ptr<Value> returnValue;
    if(evaluate(ifStatement->condition)->logicalValue())
    {
        scope.currentPos = ifStatement->pos;
        scope.newInstructionBlock();
        if(returnValue = evaluate(ifStatement->statementTrue))
        {
            return returnValue;
        }
        scope.endInstructionBlock();
    }
    else if(ifStatement->statementFalse != nullptr)
    {
        scope.currentPos = ifStatement->statementFalse->pos;
        scope.newInstructionBlock();
        if(returnValue = evaluate(ifStatement->statementFalse))
        {
            return returnValue;
        }
        scope.endInstructionBlock();
    }
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<WhileStatement> whileStatement)
{
    shared_ptr<Value> returnValue;
    while(evaluate(whileStatement->condition)->logicalValue())
    {
        scope.currentPos = whileStatement->pos;
        scope.newInstructionBlock();
        if(returnValue = evaluate(whileStatement->statement))
        {
            return returnValue;
        }
        scope.endInstructionBlock();
    }
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<ReturnStatement> returnStatement)
{
    return evaluate(returnStatement->expression);
}

void Interpreter::evaluate(std::shared_ptr<Definition> definition)
{
    //cout<<"Evaluating definition"<<endl;
    if(auto funDefinition = get_if<shared_ptr<FunDefinition>>(&definition->definition))
    {
        evaluate(*funDefinition);
        return;
    }
    else if(auto typeDefinition = get_if<shared_ptr<TypeDefinition>>(&definition->definition))
    {
        evaluate(*typeDefinition);
        return;
    }
    else if(auto variableDeclaration = get_if<shared_ptr<VariableDeclaration>>(&definition->definition))
    {
        evaluate(*variableDeclaration);
        return;
    }
    throw runtime_error("Could not evaluate definition: "+definition->pos.toString());
}

void Interpreter::evaluate(std::shared_ptr<FunDefinition> funDefinition)
{
    for(auto it = functions.begin(); it != functions.end(); ++it)
    {
        if(*funDefinition == *it->first)
        {
            //Enable declaring functions first and defining them later
            if(!(funDefinition->statement != nullptr && it->first->statement == nullptr))
            {
                throw runtime_error("Function with identifier "+funDefinition->identifier+" and given arguments already exists: "+funDefinition->pos.toString());
            }
            else
            {
                it->first = funDefinition;
                return;
            }
        }
    }
    functions.push_back(make_pair(funDefinition, std::bind_front(&Interpreter::evaluateCustomFunction, this)));
}

void Interpreter::evaluate(std::shared_ptr<TypeDefinition> typeDefinition)
{
}

void Interpreter::evaluate(std::shared_ptr<VariableDeclaration> variableDeclaration)
{
    //cout<<"Evaluating variable declaration"<<endl;
    scope.currentPos = variableDeclaration->pos;
    if(variableDeclaration->type.classType == KEYWORD_TOKEN)
    {
        switch(variableDeclaration->type.type)
        {
            case T_INT:
                scope.addVariable(variableDeclaration->identifier, make_shared<Value>((long long) 0));
                break;
            case T_FLOAT:
                scope.addVariable(variableDeclaration->identifier, make_shared<Value>((double) 0));
                break;
            case T_STRING:
                scope.addVariable(variableDeclaration->identifier, make_shared<Value>((string)""));
                break;
            case T_BOOL:
                scope.addVariable(variableDeclaration->identifier, make_shared<Value>(false));
                break;
            default:
                throw runtime_error("Unknown variable type "+variableDeclaration->pos.toString());
        }
    }
    if(variableDeclaration->expression != nullptr)
    {
        scope.assignValue(variableDeclaration->identifier, evaluate(variableDeclaration->expression));
    }
}


std::shared_ptr<Value> Interpreter::evaluateCustomFunction(std::shared_ptr<Statement> statement)
{
    return evaluate(statement);
}

std::shared_ptr<Value> Interpreter::evaluatePrintFunction(std::shared_ptr<Statement> statement)
{
    auto value = scope.getValue("funArgument");
    std::visit([](const auto &x) { std::cout << x; }, *value->value);
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluatePrintlnFunction(std::shared_ptr<Statement> statement)
{
    auto value = scope.getValue("funArgument");
    std::visit([](const auto &x) { std::cout << x << std::endl; }, *value->value);
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluateStrFunction(std::shared_ptr<Statement> statement)
{
    auto value = scope.getValue("funArgument");
    if(auto val = get_if<long long>(value->value.get()))
    {
        return make_shared<Value>(to_string(*val));
    }
    else if(auto val = get_if<double>(value->value.get()))
    {
        return make_shared<Value>(to_string(*val));
    }
    else if(auto val = get_if<bool>(value->value.get()))
    {
        return make_shared<Value>(to_string(*val));
    }
    else if(auto val = get_if<string>(value->value.get()))
    {
        return value;
    }
    throw runtime_error("Type cannot be converted to string: "+statement->pos.toString());
}

std::shared_ptr<Value> Interpreter::evaluateFloatFunction(std::shared_ptr<Statement> statement)
{
    auto value = scope.getValue("funArgument");
    if(auto val = get_if<long long>(value->value.get()))
    {
        return make_shared<Value>(double(*val));
    }
    else if(auto val = get_if<double>(value->value.get()))
    {
        return value;
    }
    else if(auto val = get_if<bool>(value->value.get()))
    {
        return make_shared<Value>(double(*val));
    }
    else if(auto val = get_if<string>(value->value.get()))
    {
        double d;
        d = stod(*val);
        return make_shared<Value>(d);
    }
    throw runtime_error("Type cannot be converted to Float: "+statement->pos.toString());
}

std::shared_ptr<Value> Interpreter::evaluateIntFunction(std::shared_ptr<Statement> statement)
{
    auto value = scope.getValue("funArgument");
    if(auto val = get_if<long long>(value->value.get()))
    {
        return value;
    }
    else if(auto val = get_if<double>(value->value.get()))
    {
        return make_shared<Value>((long long)(*val));
    }
    else if(auto val = get_if<bool>(value->value.get()))
    {
        return make_shared<Value>((long long)(*val));
    }
    else if(auto val = get_if<string>(value->value.get()))
    {
        long long d;
        d = stoll(*val);
        return make_shared<Value>(d);
    }
    throw runtime_error("Type cannot be converted to Int: "+statement->pos.toString());
}

std::shared_ptr<Value> Interpreter::evaluateBoolFunction(std::shared_ptr<Statement> statement)
{
    auto value = scope.getValue("funArgument");
    if(auto val = get_if<long long>(value->value.get()))
    {
        return make_shared<Value>(*val != 0);
    }
    else if(auto val = get_if<double>(value->value.get()))
    {
        return make_shared<Value>(*val != 0);
    }
    else if(auto val = get_if<bool>(value->value.get()))
    {
        return value;
    }
    else if(auto val = get_if<string>(value->value.get()))
    {
        if(*val == "true")
        {
            return make_shared<Value>(true);
        }
        if(*val == "false")
        {
            return make_shared<Value>(false);
        }
        throw runtime_error("String could not be converted to Bool: "+statement->pos.toString());    
    }
    throw runtime_error("Type cannot be converted to Bool: "+statement->pos.toString());
}


void Interpreter::createEmbeddedFunctions()
{
    createEmbeddedFunction("print", Token(KEYWORD_TOKEN, T_VOID), std::bind_front(&Interpreter::evaluatePrintFunction, this));
    createEmbeddedFunction("println", Token(KEYWORD_TOKEN, T_VOID), std::bind_front(&Interpreter::evaluatePrintlnFunction, this));
    createEmbeddedFunction("str", Token(KEYWORD_TOKEN, T_STRING), std::bind_front(&Interpreter::evaluateStrFunction, this));
    createEmbeddedFunction("float", Token(KEYWORD_TOKEN, T_FLOAT), std::bind_front(&Interpreter::evaluateFloatFunction, this));
    createEmbeddedFunction("int", Token(KEYWORD_TOKEN, T_INT), std::bind_front(&Interpreter::evaluateIntFunction, this));
    createEmbeddedFunction("bool", Token(KEYWORD_TOKEN, T_BOOL), std::bind_front(&Interpreter::evaluateBoolFunction, this));
}

void Interpreter::createEmbeddedFunction(std::string identifier, Token type, std::function<std::shared_ptr<Value>(std::shared_ptr<Statement>)> callback)
{
    vector<shared_ptr<VariableDeclaration>> arguments;
    shared_ptr<VariableDeclaration> varDeclaration;

    varDeclaration = make_shared<VariableDeclaration>(Token(KEYWORD_TOKEN, T_INT), "funArgument");
    arguments.push_back(varDeclaration);
    auto funDefinition = make_shared<FunDefinition>(type, identifier, arguments);
    functions.push_back(make_pair(funDefinition, callback));
    arguments.clear();

    varDeclaration = make_shared<VariableDeclaration>(Token(KEYWORD_TOKEN, T_FLOAT), "funArgument");
    arguments.push_back(varDeclaration);
    funDefinition = make_shared<FunDefinition>(type, identifier, arguments);
    functions.push_back(make_pair(funDefinition, callback));
    arguments.clear();

    varDeclaration = make_shared<VariableDeclaration>(Token(KEYWORD_TOKEN, T_STRING), "funArgument");
    arguments.push_back(varDeclaration);
    funDefinition = make_shared<FunDefinition>(type, identifier, arguments);
    functions.push_back(make_pair(funDefinition, callback));
    arguments.clear();

    varDeclaration = make_shared<VariableDeclaration>(Token(KEYWORD_TOKEN, T_BOOL), "funArgument");
    arguments.push_back(varDeclaration);
    funDefinition = make_shared<FunDefinition>(type, identifier, arguments);
    functions.push_back(make_pair(funDefinition, callback));
}