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
            auto newValue = evaluate(binaryExpression->rhs);
            scope.assignValue((*identifier)->identifier, newValue);
            return newValue;
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
    throw runtime_error("Could not evaluate binary expression");
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<FunCall> funCall)
{
    return nullptr;
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
        if(literal->literal.type = T_TRUE)
        {
            return make_shared<Value>(true);
        }
        if(literal->literal.type = T_FALSE)
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
    throw runtime_error("Unknown literal type");
}

std::shared_ptr<Value> Interpreter::evaluate(std::shared_ptr<Identifier> identifier)
{
    //cout<<"Evaluating identifier"<<endl;
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
        scope.newInstructionBlock();
        if(returnValue = evaluate(ifStatement->statementTrue))
        {
            return returnValue;
        }
        scope.endInstructionBlock();
    }
    else if(ifStatement->statementFalse != nullptr)
    {
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
    throw runtime_error("Could not evaluate definition");
}

void Interpreter::evaluate(std::shared_ptr<FunDefinition> funDefinition)
{
}

void Interpreter::evaluate(std::shared_ptr<TypeDefinition> typeDefinition)
{
}

void Interpreter::evaluate(std::shared_ptr<VariableDeclaration> variableDeclaration)
{
    //cout<<"Evaluating variable declaration"<<endl;
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
                scope.addVariable(variableDeclaration->identifier, make_shared<Value>(""));
                break;
            case T_BOOL:
                scope.addVariable(variableDeclaration->identifier, make_shared<Value>(false));
                break;
            default:
                throw runtime_error("Unknown variable type");
        }
    }
    if(variableDeclaration->expression != nullptr)
    {
        scope.assignValue(variableDeclaration->identifier, evaluate(variableDeclaration->expression));
    }
}