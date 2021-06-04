#include "value.h"

using namespace std;

bool operator<(const Value& l, const Value& r)
{
    if(auto left = get_if<long long>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return *left < *right;
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return *left < *right;
        }
    }
    if(auto left = get_if<double>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return *left < *right;
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return *left < *right;
        }
    }
    throw runtime_error("Incompatible types for comparison");
}

bool operator>(const Value& l, const Value& r)
{
    return r < l;
}

bool operator<=(const Value& l, const Value& r)
{
    return !(r < l);
}

bool operator>=(const Value& l, const Value& r)
{
    return !(l < r);
}

bool operator==(const Value& l, const Value& r)
{
    if(auto left = get_if<long long>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return *left == *right;
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return *left == *right;
        }
    }
    if(auto left = get_if<double>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return *left == *right;
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return *left == *right;
        }
    }
    if(auto left = get_if<bool>(l.value.get()))
    {
        if(auto right = get_if<bool>(r.value.get()))
        {
            return *left == *right;
        }
    }
    if(auto left = get_if<string>(l.value.get()))
    {
        if(auto right = get_if<string>(r.value.get()))
        {
            return *left == *right;
        }
    }
    throw runtime_error("Incompatible types for comparison");
}

bool operator!=(const Value& l, const Value& r)
{
    return !(l == r);
}

Value operator+(const Value& l, const Value& r)
{
    if(auto left = get_if<long long>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return Value(*left + *right);
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return Value(*left + *right);
        }
    }
    if(auto left = get_if<double>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return Value(*left + *right);
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return Value(*left + *right);
        }
    }
    if(auto left = get_if<string>(l.value.get()))
    {
        if(auto right = get_if<string>(r.value.get()))
        {
            return Value(*left + *right);
        }
    }
    throw runtime_error("Incompatible types for operator '+'");
}

Value operator-(const Value& l, const Value& r)
{
    if(auto left = get_if<long long>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return Value(*left - *right);
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return Value(*left - *right);
        }
    }
    if(auto left = get_if<double>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return Value(*left - *right);
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return Value(*left - *right);
        }
    }
    throw runtime_error("Incompatible types for operator '-'");
}

Value operator*(const Value& l, const Value& r)
{
    if(auto left = get_if<long long>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return Value(*left * *right);
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return Value(*left * *right);
        }
    }
    if(auto left = get_if<double>(l.value.get()))
    {
        if(auto right = get_if<long long>(r.value.get()))
        {
            return Value(*left * *right);
        }
        if(auto right = get_if<double>(r.value.get()))
        {
            return Value(*left * *right);
        }
    }
    throw runtime_error("Incompatible types for operator '*'");
}

Value operator/(const Value& l, const Value& r)
{
    if(auto right = get_if<long long>(r.value.get()))
    {
        if(*right == 0)
        {
            throw runtime_error("Division by 0");
        }
        if(auto left = get_if<long long>(l.value.get()))
        {
            return Value(*left / *right);
        }
        if(auto left = get_if<double>(l.value.get()))
        {
            return Value(*left / *right);
        }
    }
    if(auto right = get_if<double>(r.value.get()))
    {
        if(*right == 0)
        {
            throw runtime_error("Division by 0");
        }
        if(auto left = get_if<long long>(l.value.get()))
        {
            return Value(*left / *right);
        }
        if(auto left = get_if<double>(l.value.get()))
        {
            return Value(*left / *right);
        }
    }
    throw runtime_error("Incompatible types for operator '/'");
}

Value operator^(const Value& l, const Value& r)
{
    if(auto right = get_if<long long>(r.value.get()))
    {
        if(auto left = get_if<long long>(l.value.get()))
        {
            if(*right >= 0)
            {
                return Value((long long)pow(*left, *right));
            }
            else
            {
                return Value(pow(*left, *right));
            }
        }
        if(auto left = get_if<double>(l.value.get()))
        {
            return Value(pow(*left, *right));
        }
    }
    if(auto right = get_if<double>(r.value.get()))
    {
        if(auto left = get_if<long long>(l.value.get()))
        {
            return Value(pow(*left, *right));
        }
        if(auto left = get_if<double>(l.value.get()))
        {
            return Value(pow(*left, *right));
        }
    }
    throw runtime_error("Incompatible types for operator '**'");
}

bool Value::logicalValue()
{
    if(auto val = get_if<long long>(value.get()))
    {
        return *val != 0;
    }
    if(auto val = get_if<double>(value.get()))
    {
        return *val != 0.0;
    }
    if(auto val = get_if<bool>(value.get()))
    {
        return *val;
    }
    throw runtime_error("Could not convert expression to a logical value");
}