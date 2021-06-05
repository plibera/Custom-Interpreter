#pragma once

#include <iostream>
#include <gtest/gtest.h>
#include <variant>

#include "interpreter.h"


TEST(InterpreterTest, interpretsReturn) {
    std::stringstream ss;
    ss<<"return 5;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, interpretsComparison) {
    std::stringstream ss;
    ss<<"return 1 < 5;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_TRUE(*value);
}

TEST(InterpreterTest, interpretsComparison2) {
    std::stringstream ss;
    ss<<"return 1 > 5;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_FALSE(*value);
}

TEST(InterpreterTest, interpretsComparison3) {
    std::stringstream ss;
    ss<<"return 1 <= 5;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_TRUE(*value);
}

TEST(InterpreterTest, interpretsComparison4) {
    std::stringstream ss;
    ss<<"return 1 >= 5;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_FALSE(*value);
}

TEST(InterpreterTest, interpretsAddition) {
    std::stringstream ss;
    ss<<"return 2+2;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 4);
}

TEST(InterpreterTest, interpretsSubtraction) {
    std::stringstream ss;
    ss<<"return 5-2;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 3);
}

TEST(InterpreterTest, interpretsMultiplication) {
    std::stringstream ss;
    ss<<"return 2*3;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 6);
}

TEST(InterpreterTest, interpretsDivision) {
    std::stringstream ss;
    ss<<"return 6/2;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 3);
}

TEST(InterpreterTest, divisionByZero) {
    std::stringstream ss;
    ss<<"return 2/0;";
    Interpreter interpreter(ss);
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, interpretsExponent) {
    std::stringstream ss;
    ss<<"return 2**3;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 8);
}

TEST(InterpreterTest, interpretsAnd) {
    std::stringstream ss;
    ss<<"return true and false;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_FALSE(*value);
}

TEST(InterpreterTest, interpretsOr) {
    std::stringstream ss;
    ss<<"return true or false;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_TRUE(*value);
}

TEST(InterpreterTest, interpretsNot) {
    std::stringstream ss;
    ss<<"return not true;";
    Interpreter interpreter(ss);
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_FALSE(*value);
}

TEST(InterpreterTest, multipleAssignment) {
    std::stringstream ss;
    ss<<"Int a; Int b; a=b=5; return a;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, properMaths) {
    std::stringstream ss;
    ss<<"return 2*(2+2);";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 8);
}

TEST(InterpreterTest, properMaths2) {
    std::stringstream ss;
    ss<<"return 2*2+2;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 6);
}

TEST(InterpreterTest, properMaths3) {
    std::stringstream ss;
    ss<<"return 2/2*2;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 2);
}

TEST(InterpreterTest, properMaths4) {
    std::stringstream ss;
    ss<<"return 4**3**2;";
    Interpreter interpreter(ss);
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 262144);
}

TEST(InterpreterTest, performsAssignment) {
    std::stringstream ss;
    ss<<"Int a = 5; return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, performsAssignment2) {
    std::stringstream ss;
    ss<<"Int a; a = 5; return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, controlsScope) {
    std::stringstream ss;
    ss<<"{Int a; a = 5;} return a;";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, controlsScope2) {
    std::stringstream ss;
    ss<<"Int a; {a = 5;} return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, preventsRedefinition) {
    std::stringstream ss;
    ss<<"Int a = 5; Int a = 7; return a;";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, preventsRedefinition2) {
    std::stringstream ss;
    ss<<"Int a = 5; {Int a = 7;} return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, preventsRedefinition3) {
    std::stringstream ss;
    ss<<"{Int a = 5;} Int a = 7; return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 7);
}

TEST(InterpreterTest, interpretsIf) {
    std::stringstream ss;
    ss<<"Int a; if(true) { a = 5; } return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, interpretsIf2) {
    std::stringstream ss;
    ss<<"Int a = 3; if(a < 3) { a = 5; } else {a = 8;} return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 8);
}

TEST(InterpreterTest, interpretsWhile) {
    std::stringstream ss;
    ss<<"Int a = 0; while( a < 10 ) { a = a + 1; } return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 10);
}

TEST(InterpreterTest, interpretsWhile2) {
    std::stringstream ss;
    ss<<"Int a = 0; while( a < 10 ) { a = a + 1; if(a > 5) { return a; }} return 0;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 6);
}

TEST(InterpreterTest, interpretsWhile3) {
    std::stringstream ss;
    ss<<"String s = \"0\"; while(s) { return 10; }";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, interpretsWhile4) {
    std::stringstream ss;
    ss<<"Int a = 5; while(a) { a = a-1; } return a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 0);
}

TEST(InterpreterTest, interpretsPrint) {
    std::stringstream ss;
    ss<<"print(\"Test\");";
    Interpreter interpreter(ss);

    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    interpreter.execute();
    std::string output = buffer.str();

    std::cout.rdbuf(sbuf);

    ASSERT_EQ(output, "Test");
}

TEST(InterpreterTest, interpretsPrintln) {
    std::stringstream ss;
    ss<<"println(\"Test\");";
    Interpreter interpreter(ss);

    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    interpreter.execute();
    std::string output = buffer.str();

    std::cout.rdbuf(sbuf);

    ASSERT_EQ(output, "Test\n");
}

TEST(InterpreterTest, interpretsStrFunction) {
    std::stringstream ss;
    ss<<"return str(5);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    std::string *value;
    ASSERT_TRUE(value = std::get_if<std::string>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, "5");
}

TEST(InterpreterTest, interpretsIntFunction) {
    std::stringstream ss;
    ss<<"return int(\"10\");";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 10);
}

TEST(InterpreterTest, interpretsIntFunction2) {
    std::stringstream ss;
    ss<<"return int(10.3);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 10);
}

TEST(InterpreterTest, interpretsFloatFunction) {
    std::stringstream ss;
    ss<<"return float(\"10.5\");";
    Interpreter interpreter(ss);    
    interpreter.execute();
    double *value;
    ASSERT_TRUE(value = std::get_if<double>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 10.5);
}

TEST(InterpreterTest, interpretsFloatFunction2) {
    std::stringstream ss;
    ss<<"return float(10);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    double *value;
    ASSERT_TRUE(value = std::get_if<double>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 10.0);
}

TEST(InterpreterTest, interpretsBoolFunction) {
    std::stringstream ss;
    ss<<"return bool(\"true\");";
    Interpreter interpreter(ss);    
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_TRUE(*value);
}

TEST(InterpreterTest, interpretsBoolFunction2) {
    std::stringstream ss;
    ss<<"return bool(1);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    bool *value;
    ASSERT_TRUE(value = std::get_if<bool>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_TRUE(*value);
}

TEST(InterpreterTest, interpretsCustomFunction) {
    std::stringstream ss;
    ss<<"Int mul(Int a, Int b) { return a*b; } return mul(2, 2);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 4);
}

TEST(InterpreterTest, missingFunctionReturn) {
    std::stringstream ss;
    ss<<"Int mul(Int a, Int b) { Int c = a*b; } mul(1, 2); return 0;";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, voidFunctionReturn) {
    std::stringstream ss;
    ss<<"Void mul(Int a, Int b) { return a*b; } return mul(2, 2);";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, preventsInfiniteRecursion) {
    std::stringstream ss;
    ss<<"Int mul(Int a, Int b) { return mul(a, b+1); } return mul(2, 2);";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, interpretsCustomFunction2) {
    std::stringstream ss;
    ss<<"Int mul(Int a, Int b) { return a*b; } return mul(2, 2);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 4);
}

TEST(InterpreterTest, interpretsCustomFunction3) {
    std::stringstream ss;
    ss<<"Int f() { Int a = 0; while( a < 10 ) { a = a + 1; if(a > 5) { return a; }} return 0;} return f();";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 6);
}

TEST(InterpreterTest, interpretsCustomFunction4) {
    std::stringstream ss;
    ss<<"Int f(Bool a) { if(a) return 5; } return f(true);";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, interpretsCustomFunction5) {
    std::stringstream ss;
    ss<<"Int f(Bool a) { if(a) return 5; } return f(false);";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, voidFunNoReturn) {
    std::stringstream ss;
    ss<<"Int b; Void f() { b = 5; } f(); return b;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, voidFunReturn) {
    std::stringstream ss;
    ss<<"Int b; Void f() { b = 5; return; b = 6; } f(); return b;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, wrongFunCall) {
    std::stringstream ss;
    ss<<"Int f(Bool a) { if(a) return 5; } return f();";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, wrongFunCall2) {
    std::stringstream ss;
    ss<<"Int f(Bool a) { if(a) return 5; } Int a; return f(a);";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, wrongFunCall3) {
    std::stringstream ss;
    ss<<"Int f(Bool a) { if(a) return 5; } return f(true, false);";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, customTypes) {
    std::stringstream ss;
    ss<<"class Type {public Int a;}; Type x; x.a = 5; return x.a;";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, customTypes2) {
    std::stringstream ss;
    ss<<"class Type {Int a;}; Type x; x.a = 5; return x.a;";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}

TEST(InterpreterTest, customTypes3) {
    std::stringstream ss;
    ss<<"class Type {public Int f(){return 5;}}; Type x; return x.f();";
    Interpreter interpreter(ss);    
    interpreter.execute();
    long long *value;
    ASSERT_TRUE(value = std::get_if<long long>(interpreter.getLastReturnValue().get()->value.get()));
    ASSERT_EQ(*value, 5);
}

TEST(InterpreterTest, customTypes4) {
    std::stringstream ss;
    ss<<"class Type {Int f(){return 5;}}; Type x; return x.f();";
    Interpreter interpreter(ss);    
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
}