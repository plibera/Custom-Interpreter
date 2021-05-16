#include "objects.h"

using namespace std;


std::string makeIndent(int indent)
{
    std::stringstream ss;
    for(int i = 0; i < indent; ++i)
        if(i%4 == 0)
            ss<<"|";
        else
            ss<<" ";
    return ss.str();
}

std::string Program::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Program:"<<endl;
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
    ss<<makeIndent(indent);
    ss<<"Definition:"<<endl;
    if(definition.index() == 0)
    {
        ss<<std::get<std::shared_ptr<FunDefinition>>(definition)->to_string(indent+4);
    }
    else if(definition.index() == 1)
    {
        ss<<std::get<std::shared_ptr<TypeDefinition>>(definition)->to_string(indent+4);
    }
    else
    {
        ss<<std::get<std::shared_ptr<VariableDeclaration>>(definition)->to_string(indent+4);
    }
    
    return ss.str();
}

std::string Statement::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Statement:"<<endl;
    for(auto instruction : instructions)
    {
        ss<<instruction->to_string(indent+4);
    }
    return ss.str();
}

std::string FunDefinition::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    if(statement)
        ss<<"Function definition: "<<type->toString()<<" "<<identifier<<endl;
    else
        ss<<"Function declaration: "<<type->toString()<<" "<<identifier<<endl;
    for(auto expression : arguments)
    {
        ss<<expression->to_string(indent+4);
    }
    if(statement)
        ss<<statement->to_string(indent+4);
    return ss.str();
}


std::string TypeDefinition::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Type definition: "<<type->toString()<<endl;
    for(auto expression : variables)
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
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Binary expression: "<<endl;
    ss<<lhs->to_string(indent+4);
    ss<<makeIndent(indent+4);
    ss<<op->toString()<<endl;
    ss<<rhs->to_string(indent+4);
    return ss.str();
}

std::string FunCall::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    if(object != "")
        ss<<"Function call: Object: "<<object<<" Member: "<<identifier;
    else
        ss<<"Identifier: "<<identifier;
    ss<<"  Arguments: "<<arguments.size()<<endl;
    for(auto argument : arguments)
    {
        ss<<argument->to_string(indent+4);
    }
    return ss.str();
}

std::string Expression::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
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
    }
    return ss.str();
}

std::string Literal::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Literal: "<<literal->toString()<<endl;
    return ss.str();
}

std::string Identifier::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    if(object != "")
        ss<<"Identifier: Object: "<<object<<" Member: "<<identifier<<endl;
    else
        ss<<"Identifier: "<<identifier<<endl;
    return ss.str();
}

std::string Instruction::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
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
    ss<<makeIndent(indent);
    ss<<"If statement: condition, if true, if false:"<<endl;
    ss<<condition->to_string(indent+4);
    ss<<statementTrue->to_string(indent+4);
    if(statementFalse)
        ss<<statementFalse->to_string(indent+4);
    else
        ss<<makeIndent(indent+4)<<"Null"<<endl;
    return ss.str();
}

std::string WhileStatement::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"While statement: condition, statement:"<<endl;
    ss<<condition->to_string(indent+4);
    ss<<statement->to_string(indent+4);
    return ss.str();
}

std::string ReturnStatement::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Return statement:"<<endl;
    ss<<expression->to_string(indent+4);
    return ss.str();
}

std::string VariableDeclaration::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"VariableDeclaration: "<<type->toString()<<" "<<identifier<<endl;
    return ss.str();
}