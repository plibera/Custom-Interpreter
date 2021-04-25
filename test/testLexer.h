#pragma once

#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"


class LexerTest : public ::testing::Test
{
protected:
    //Lexer* lexer;
    //std::stringstream ss;

    bool areTokensEqual(Token* a, Token* b);
    LexerTest()
    {}

    ~LexerTest() override
    {}

    void SetUp() override
    {
        //lexer = new Lexer(ss);
    }

    void TearDown() override
    {
        //ss.str(std::string());
        //delete lexer;
    }
};


TEST_F(LexerTest, ConstructsIfKeywordToken) {
    std::stringstream ss;
    Lexer* lexer = new Lexer(ss);
    ss<<"if iff If ifek";
    Token* t = lexer->getToken();
    std::cout<<t->toString()<<std::endl;
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_IF, 0, 0, 0)));
}