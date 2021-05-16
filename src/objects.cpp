#include "objects.h"

using namespace std;

std::string Program::to_string(int indent)
{
    cout<<"Program"<<endl;
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Program"<<endl;
    for(auto element : program)
    {
        if(element.index() == 0)
        {
            ss<<std::get<std::shared_ptr<Definition>>(element)->to_string(indent+4);
        }
        else
        {
            ss<<std::get<std::shared_ptr<Statement>>(element)->to_string(indent+4);
        }
    }
    return ss.str();
}


std::string Definition::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Definition"<<endl;
    if(definition.index() == 0)
    {
        ss<<std::get<std::shared_ptr<FunDefinition>>(definition)->to_string(indent+4);
    }
    else
    {
        ss<<std::get<std::shared_ptr<TypeDefinition>>(definition)->to_string(indent+4);
    }
    return ss.str();
}

std::string Statement::to_string(int indent)
{
    cout<<"Statement"<<endl;
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Statement"<<endl;
    for(auto instruction : instructions)
    {
        ss<<instruction->to_string(indent+4);
    }
    return ss.str();
}

std::string FunDefinition::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Function definition: "<<type->toString()<<" "<<identifier<<endl;
    for(auto expression : arguments)
    {
        ss<<expression->to_string(indent+4);
    }
    ss<<statement->to_string(indent+4);
    return ss.str();
}


std::string TypeDefinition::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Type definition: "<<type->toString()<<endl;
    for(auto expression : expressions)
    {
        ss<<expression->to_string(indent+4);
    }
    for(auto function : functions)
    {
        ss<<function->to_string(indent+4);
    }
    return ss.str();
}


std::string BinaryExpression::to_string(int indent)
{
    cout<<"Binary expression"<<endl;
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Binary expression: "<<endl;
    ss<<lhs->to_string(indent+4);
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<op->toString()<<endl;
    ss<<rhs->to_string(indent+4);
    return ss.str();
}

std::string FunCall::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Function call: "<<identifier<<" arguments:"<<endl;
    for(auto argument : arguments)
    {
        argument->to_string(indent+4);
    }
    return ss.str();
}

std::string Expression::to_string(int indent)
{
    cout<<"Expression"<<endl;
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Expression: "<<endl;
    switch(expression.index())
    {
        case 0:
            ss<<get<shared_ptr<BinaryExpression>>(expression)->to_string(indent+4);
            break;
        case 1:
            ss<<get<shared_ptr<FunCall>>(expression)->to_string(indent+4);
            break;
        case 2:
            ss<<get<shared_ptr<Literal>>(expression)->to_string(indent+4);
            break;
        case 3:
            ss<<get<shared_ptr<Identifier>>(expression)->to_string(indent+4);
            break;
        case 4:
            ss<<get<shared_ptr<Declaration>>(expression)->to_string(indent+4);
            break;
    }
    return ss.str();
}

std::string Literal::to_string(int indent)
{
    cout<<"Literal"<<endl;
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Literal: "<<literal->toString()<<endl;
    return ss.str();
}

std::string Identifier::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    if(isTypeMember)
        ss<<"Identifier: Type: "<<type->toString()<<" Member: "<<identifier->toString()<<endl;
    else
        ss<<"Identifier: "<<identifier->toString()<<endl;
    return ss.str();
}

std::string Instruction::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Instruction: "<<endl;
    switch(instruction.index())
    {
        case 0:
            ss<<get<shared_ptr<Expression>>(instruction)->to_string(indent+4);
            break;
        case 1:
            ss<<get<shared_ptr<IfStatement>>(instruction)->to_string(indent+4);
            break;
        case 2:
            ss<<get<shared_ptr<WhileStatement>>(instruction)->to_string(indent+4);
            break;
        case 3:
            ss<<get<shared_ptr<ReturnStatement>>(instruction)->to_string(indent+4);
            break;
    }
    return ss.str();
}

std::string IfStatement::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"If statement: condition, if true, if false:"<<endl;
    ss<<condition->to_string(indent+4);
    ss<<statementTrue->to_string(indent+4);
    ss<<statementFalse->to_string(indent+4);
    return ss.str();
}

std::string WhileStatement::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"While statement: condition, statement:"<<endl;
    ss<<condition->to_string(indent+4);
    ss<<statement->to_string(indent+4);
    return ss.str();
}

std::string ReturnStatement::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Return statement:"<<endl;
    ss<<expression->to_string(indent+4);
    return ss.str();
}

std::string Declaration::to_string(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        ss<<" ";
    ss<<"Declaration: "<<type->toString()<<" "<<identifier->toString()<<endl;
    return ss.str();
}