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
    ASSERT_THROW(interpreter.execute(), std::runtime_error);
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