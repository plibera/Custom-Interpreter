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
    for(const auto& element : program)
    {
        ss << std::visit([&](const auto &ptr) { return ptr->to_string(indent+4); }, element);
    }
    return ss.str();
}


std::string Definition::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Definition:"<<endl;
    ss << std::visit([&](const auto &ptr) { return ptr->to_string(indent+4); }, definition);
    return ss.str();
}

std::string Statement::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Statement:"<<endl;
    for(const auto& instruction : instructions)
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
        ss<<"Function definition: "<<(isPublic?"public ":"private ")<<type.toString()<<" "<<identifier<<endl;
    else
        ss<<"Function declaration: "<<(isPublic?"public ":"private ")<<type.toString()<<" "<<identifier<<endl;
    for(const auto& expression : arguments)
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
    ss<<"Type definition: "<<type.toString()<<endl;
    for(const auto& expression : variables)
    {
        ss<<expression->to_string(indent+4);
    }
    for(const auto& function : functions)
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
    ss<<op.toString()<<endl;
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
        ss<<"Function call: Identifier: "<<identifier;
    ss<<"  Arguments: "<<arguments.size()<<endl;
    for(const auto& argument : arguments)
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
    ss << std::visit([&](const auto &ptr) { return ptr->to_string(indent+4); }, expression);
    return ss.str();
}

std::string Literal::to_string(int indent)
{
    std::stringstream ss;
    ss<<makeIndent(indent);
    ss<<"Literal: "<<literal.toString()<<endl;
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
    ss << std::visit([&](const auto &ptr) { return ptr->to_string(indent+4); }, instruction);
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
    ss<<"VariableDeclaration: "<<(isPublic?"public ":"private ")<<type.toString()<<" "<<identifier<<endl;
    if(expression)
        ss<<expression->to_string(indent+4);
    return ss.str();
}