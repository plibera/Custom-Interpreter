#include "objects.h"

using namespace std;


bool areOfCorrespondingType(Token &token, std::shared_ptr<Value> value)
{
    if(token.classType == KEYWORD_TOKEN)
    {
        switch(token.type)
        {
            case T_INT:
                if(!(get_if<long long>(value->value.get())))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            case T_FLOAT:
                if(!(get_if<double>(value->value.get())))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            case T_STRING:
                if(!(get_if<string>(value->value.get())))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            case T_BOOL:
                if(!(get_if<bool>(value->value.get())))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            case T_VOID:
                throw runtime_error("Void function cannot return value");
            default:
                throw runtime_error("Unknown variable type");
        }
    }
    else if(token.classType == IDENTIFIER_TOKEN && token.type == T_TYPE)
    {
        if(auto customType = get_if<shared_ptr<CustomType>>(value->value.get()))
        {
            if(auto typeIdentifier = get_if<string>(&token.value))
            {
                return *typeIdentifier == (*customType)->typeName;
            }
            return false;
        }
        return false;
    }
    return false;
}


bool FunDefinition::operator==(const FunDefinition& r)
{
    if(identifier != r.identifier)
        return false;
    if(arguments.size() != r.arguments.size())
        return false;
    for(size_t i = 0; i < arguments.size(); ++i)
    {
        arguments[i]->type.resetPosition();
        r.arguments[i]->type.resetPosition();
        if(arguments[i]->type != r.arguments[i]->type)
        {
            return false;
        }
    }
    return true;
}

bool FunDefinition::acceptFunCall(std::string calledIdentifier, std::vector<std::shared_ptr<Value>> &argValues)
{
    if(identifier != calledIdentifier)
    {
        return false;
    }
    if(arguments.size() != argValues.size())
    {
        return false;
    }
    for(size_t i = 0; i < arguments.size(); ++i)
    {
        if(!areOfCorrespondingType(arguments[i]->type, argValues[i]))
        {
            return false;
        }
    }
    return true;
}

bool FunDefinition::acceptReturnValue(std::shared_ptr<Value> value)
{
    if(value == nullptr)
    {
        return type.classType == KEYWORD_TOKEN && type.type == T_VOID;
    }
    if(value->value == nullptr)
    {
        return type.classType == KEYWORD_TOKEN && type.type == T_VOID;
    }
    return areOfCorrespondingType(type, value);
}

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