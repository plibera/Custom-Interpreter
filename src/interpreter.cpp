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
    if(binaryExpression->op.type == T_ASSIGN)
    {
        if(auto identifier = get_if<shared_ptr<Identifier>>(&binaryExpression->lhs->expression))
        {
            scope.currentPos = binaryExpression->pos;
            auto newValue = evaluate(binaryExpression->rhs);
            if((*identifier)->object == "")
            {
                scope.assignValue((*identifier)->identifier, newValue);
            }
            else
            {
                if((*identifier)->object == "this")
                {
                    scope.assignValue(currentObject, (*identifier)->identifier, newValue);    
                }
                else
                {
                    if(!scope.isPublic((*identifier)->object, (*identifier)->identifier))
                    {
                        throw runtime_error("Attribute "+(*identifier)->identifier+" of "+(*identifier)->object+" is private "+binaryExpression->pos.toString());
                    }
                    scope.assignValue((*identifier)->object, (*identifier)->identifier, newValue);
                }
            }
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
        if(binaryExpression->op.classType == OPERATOR_TOKEN)
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
        else if(binaryExpression->op.classType == KEYWORD_TOKEN)
        {
            if(binaryExpression->op.type == T_AND)
            {
                return make_shared<Value>(leftValue->logicalValue() && rightValue->logicalValue());
            }
            else if(binaryExpression->op.type == T_OR)
            {
                return make_shared<Value>(leftValue->logicalValue() || rightValue->logicalValue());
            }
            else if(binaryExpression->op.type == T_NOT)
            {
                return make_shared<Value>(!rightValue->logicalValue());
            }
        }
    }
    catch(const std::exception& e)
    {
        throw runtime_error(string(e.what()) + " " + binaryExpression->pos.toString());
    }
    throw runtime_error("Could not evaluate binary expression: "+binaryExpression->pos.toString());
}

//TODO
std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<FunCall> funCall)
{
    vector<shared_ptr<Value>> argumentValues;
    for(auto &argument : funCall->arguments)
    {
        auto value = evaluate(argument);
        argumentValues.push_back(make_shared<Value>(*value));
    }
    if(funCall->object == "")
    {
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
                return runFunction(function, funCall->identifier, argumentValues, funCall->pos);
            }
        }
        throw runtime_error("Unknown function "+funCall->identifier+" called: "+funCall->pos.toString());
    }
    else
    {
        scope.currentPos = funCall->pos;
        shared_ptr<Value> valueObject;
        if(funCall->object == "this")
        {
            valueObject = scope.getValue(currentObject);
        } 
        else
        {
            valueObject = scope.getValue(funCall->object);
        }
        shared_ptr<CustomType> customTypeObject;
        if(auto object = get_if<shared_ptr<CustomType>>(valueObject->value.get()))
        {
            customTypeObject = *object;
        }
        else
        {
            throw runtime_error("Could not get custom type object "+funCall->pos.toString());
        }
        for(auto &function : customTypeObject->functions)
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
                if(funCall->object != "this" && !customTypeObject->isFunctionPublic.at(funCall->identifier))
                {
                    throw runtime_error("Function "+funCall->identifier+" of "+funCall->object+" is private "+funCall->pos.toString());
                }
                string oldCurrentObject = currentObject;
                if(funCall->object != "this")
                {
                    currentObject = funCall->object;
                }
                auto retVal = runFunction(function, funCall->identifier, argumentValues, funCall->pos);
                currentObject = oldCurrentObject;
                return retVal;
            }
        }
        throw runtime_error("Unknown function "+funCall->object+"."+funCall->identifier+" called: "+funCall->pos.toString());
    }
}

std::shared_ptr<Value> Interpreter::runFunction(FunctionEntry &function, string &identifier, vector<shared_ptr<Value>> &argumentValues, Position &pos)
{
    if(function.first->statement == nullptr)
    {
        throw runtime_error("Declared but undefined function "+identifier+" called: "+pos.toString());
    }
    shared_ptr<Value> retVal;
    scope.currentPos = pos;
    scope.newLevel();
    scope.newInstructionBlock();
    for(size_t i = 0; i < argumentValues.size(); ++i)
    {
        scope.addVariable(function.first->arguments[i]->identifier, argumentValues[i]);
    }
    retVal = function.second(function.first->statement);
    scope.endInstructionBlock();
    scope.endLevel();
    bool accept = function.first->acceptReturnValue(retVal);
    if(!accept)
    {
        if(retVal != nullptr)
        {
            throw runtime_error("Wrong type of returned value in function "+identifier+": "+pos.toString());
        }
        else
        {
            throw runtime_error("Expected a return statement in function "+identifier+": "+pos.toString());
        }
    }
    return retVal;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Expression> expression)
{
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
    scope.currentPos = identifier->pos;
    if(identifier->object == "")
    {
        return scope.getValue(identifier->identifier);
    }
    if(identifier->object == "this")
    {
        return scope.getValue(currentObject, identifier->identifier);    
    }
    if(!scope.isPublic(identifier->object, identifier->identifier))
    {
        throw runtime_error("Attribute "+identifier->identifier+" of "+identifier->object+" is private "+identifier->pos.toString());
    }
    return scope.getValue(identifier->object, identifier->identifier);
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Instruction> instruction)
{
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
    string typeIdentifier;
    if(auto identifier = get_if<string>(&typeDefinition->type.value))
    {
        typeIdentifier = *identifier;
    } 
    else
    {
        throw runtime_error("Could not get the custom type identifier "+typeDefinition->pos.toString());
    }
    auto element = types.find(typeIdentifier);
    if(element != types.end())
    {
        throw runtime_error("Type "+typeIdentifier+" already defined "+typeDefinition->pos.toString());
    }
    types.insert(make_pair(typeIdentifier, typeDefinition));
}

void Interpreter::evaluate(std::shared_ptr<VariableDeclaration> variableDeclaration)
{
    if(variableDeclaration->identifier == "this")
    {
        throw runtime_error("Variable name \"this\" is not allowed "+variableDeclaration->pos.toString());
    }
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
    else if(variableDeclaration->type.classType == IDENTIFIER_TOKEN)
    {

        string typeIdentifier;
        if(auto identifier = get_if<string>(&variableDeclaration->type.value))
        {
            typeIdentifier = *identifier;
        } 
        else
        {
            throw runtime_error("Could not get the custom type identifier "+variableDeclaration->pos.toString());
        }
        auto typeDefinition = types.find(typeIdentifier);
        if(typeDefinition == types.end())
        {
            throw runtime_error("Type "+typeIdentifier+" does not exist "+variableDeclaration->pos.toString());
        }

        scope.currentPos = variableDeclaration->pos;
        std::map<std::string, bool> isPublic;
        scope.startTypeDefinition();
        for(auto &attribute : typeDefinition->second->variables)
        {
            isPublic.insert(make_pair(attribute->identifier, attribute->isPublic));
            evaluate(attribute);
        }
        auto typeAttributes = scope.endTypeDefinition();

        FunctionVector typeFunctions;
        map<string, bool> isFunctionPublic;

        for(auto & function : typeDefinition->second->functions)
        {
            for(auto it = typeFunctions.begin(); it != typeFunctions.end(); ++it)
            {
                if(*function == *it->first)
                {
                    throw runtime_error("Function with identifier "+function->identifier+" and given arguments already exists: "+function->pos.toString());
                }
            }
            typeFunctions.push_back(make_pair(function, std::bind_front(&Interpreter::evaluateCustomFunction, this)));
            isFunctionPublic.insert(make_pair(function->identifier, function->isPublic));
        }
        scope.addVariable(variableDeclaration->identifier, make_shared<Value>(make_shared<CustomType>(typeIdentifier, typeAttributes, isPublic, isFunctionPublic, typeFunctions)));
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