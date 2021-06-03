#include "interpreter.h"

using namespace std;

int Interpreter::execute()
{
    shared_ptr<Program> program = parser.parse();
    returnValue = evaluate(program);
    if(auto returnCode = get_if<long long>(returnValue->value.get()))
    {
        cerr<<"Program returned "<<*returnCode<<endl;
        return 0;
    }
    if(returnValue == nullptr)
    {
        cerr<<"Program finished without return statement."<<endl;
        return 0;
    }
    if(returnValue->value == nullptr)
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
            if(auto variable = scope.getValue((*identifier)->identifier))
            {
                variable->value = evaluate(binaryExpression->rhs)->value;
                return variable;
            }
            else
            {
                throw runtime_error("Variable "+(*identifier)->identifier+" does not exist");
            }
        }
        else
        {
            throw runtime_error("Attempt to assign value to something else than an identifier");
        }
    }
    shared_ptr<Value> leftValue = evaluate(binaryExpression->lhs);
    shared_ptr<Value> rightValue = evaluate(binaryExpression->rhs);
    long long *operatorId;
    if(!(operatorId = get_if<long long>(&binaryExpression->op.value)))
    {
        throw runtime_error("Token operator value is of wrong type");
    } 
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

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<FunCall> funCall)
{
    return nullptr;
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
    throw runtime_error("Unknown literal type");
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Identifier> identifier)
{
    return nullptr;
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
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<WhileStatement> whileStatement)
{
    return nullptr;
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<ReturnStatement> returnStatement)
{
    return evaluate(returnStatement->expression);
}

void Interpreter::evaluate(std::shared_ptr<Definition> definition)
{
}

void Interpreter::evaluate(std::shared_ptr<FunDefinition> funDefinition)
{
}

void Interpreter::evaluate(std::shared_ptr<TypeDefinition> typeDefinition)
{
}

void Interpreter::evaluate(std::shared_ptr<VariableDeclaration> variableDeclaration)
{
}