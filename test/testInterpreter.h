#pragma once

#include <iostream>
#include <gtest/gtest.h>

#include "interpreter.h"


TEST(InterpreterTest, interpretsReturn) {
    std::stringstream ss;
    ss<<"return 5;";
    Interpreter interpreter(ss);
    ASSERT_EQ(interpreter.execute(), 5);
}