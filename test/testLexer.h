#pragma once

#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"



TEST(LexerTest, ConstructsIfKeywordToken) {
    std::stringstream ss;
    ss<<"if iff If ifek";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_IF, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 3, 0, 3, "iff"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 7, 0, 7, "If"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 10, 0, 10, "ifek"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 14, 0, 14));
    delete lexer;
}


TEST(LexerTest, ConstructsElseKeywordToken) {
    std::stringstream ss;
    ss<<"else esle Else elsek";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_ELSE, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 5, 0, 5, "esle"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 10, 0, 10, "Else"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 15, 0, 15, "elsek"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 20, 0, 20));
    delete lexer;
}


TEST(LexerTest, ConstructsWhileKeywordToken) {
    std::stringstream ss;
    ss<<"while whil While whilek";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_WHILE, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 6, 0, 6, "whil"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 11, 0, 11, "While"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 17, 0, 17, "whilek"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 23, 0, 23));
    delete lexer;
}


TEST(LexerTest, ConstructsReturnKeywordToken) {
    std::stringstream ss;
    ss<<"return retur Return retrun";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RETURN, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 7, 0, 7, "retur"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 13, 0, 13, "Return"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 20, 0, 20, "retrun"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 26, 0, 26));
    delete lexer;
}


TEST(LexerTest, ConstructsOrKeywordToken) {
    std::stringstream ss;
    ss<<"or o Or orr";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_OR, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 3, 0, 3, "o"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 5, 0, 5, "Or"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 8, 0, 8, "orr"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 11, 0, 11));
    delete lexer;
}


TEST(LexerTest, ConstructsAndKeywordToken) {
    std::stringstream ss;
    ss<<"and an And andy";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_AND, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 4, 0, 4, "an"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 7, 0, 7, "And"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 11, 0, 11, "andy"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 15, 0, 15));
    delete lexer;
}


TEST(LexerTest, ConstructsNotKeywordToken) {
    std::stringstream ss;
    ss<<"not no Not note";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_NOT, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 4, 0, 4, "no"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 7, 0, 7, "Not"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 11, 0, 11, "note"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 15, 0, 15));
    delete lexer;
}


TEST(LexerTest, ConstructsIntKeywordToken) {
    std::stringstream ss;
    ss<<"Int int In Ints";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_INT, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 4, 0, 4, "int"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 8, 0, 8, "In"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 11, 0, 11, "Ints"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 15, 0, 15));
    delete lexer;
}


TEST(LexerTest, ConstructsFloatKeywordToken) {
    std::stringstream ss;
    ss<<"Float float Floa Floats";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_FLOAT, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 6, 0, 6, "float"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 12, 0, 12, "Floa"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 17, 0, 17, "Floats"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 23, 0, 23));
    delete lexer;
}


TEST(LexerTest, ConstructsBoolKeywordToken) {
    std::stringstream ss;
    ss<<"Bool bool Boo Bools";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_BOOL, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 5, 0, 5, "bool"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 10, 0, 10, "Boo"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 14, 0, 14, "Bools"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 19, 0, 19));
    delete lexer;
}

TEST(LexerTest, ConstructsStringKeywordToken) {
    std::stringstream ss;
    ss<<"String string Strin Strings";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_STRING, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 7, 0, 7, "string"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 14, 0, 14, "Strin"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 20, 0, 20, "Strings"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 27, 0, 27));
    delete lexer;
}

TEST(LexerTest, ConstructsTrueKeywordToken) {
    std::stringstream ss;
    ss<<"true tru True trues";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_TRUE, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 5, 0, 5, "tru"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 9, 0, 9, "True"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 14, 0, 14, "trues"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 19, 0, 19));
    delete lexer;
}

TEST(LexerTest, ConstructsFalsetKeywordToken) {
    std::stringstream ss;
    ss<<"false fals False falses";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_FALSE, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 6, 0, 6, "fals"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 11, 0, 11, "False"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 17, 0, 17, "falses"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 23, 0, 23));
    delete lexer;
}

TEST(LexerTest, ConstructsVoidKeywordToken) {
    std::stringstream ss;
    ss<<"Void void Voi Voids";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_VOID, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 5, 0, 5, "void"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 10, 0, 10, "Voi"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 14, 0, 14, "Voids"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 19, 0, 19));
    delete lexer;
}

TEST(LexerTest, ConstructsClassKeywordToken) {
    std::stringstream ss;
    ss<<"class clas Class classs";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_CLASS, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 6, 0, 6, "clas"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 11, 0, 11, "Class"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 17, 0, 17, "classs"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 23, 0, 23));
    delete lexer;
}

TEST(LexerTest, ConstructsPublicKeywordToken) {
    std::stringstream ss;
    ss<<"public publi Public publics";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_PUBLIC, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 7, 0, 7, "publi"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 13, 0, 13, "Public"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 20, 0, 20, "publics"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 27, 0, 27));
    delete lexer;
}

TEST(LexerTest, ConstructsLeftparenKeywordToken) {
    std::stringstream ss;
    ss<<"((ab (&(123(";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_LEFTPAREN, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_LEFTPAREN, 1, 0, 1));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_LEFTPAREN, 5, 0, 5));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_LEFTPAREN, 7, 0, 7));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_LEFTPAREN, 11, 0, 11));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer;
}


TEST(LexerTest, ConstructsRightparenKeywordToken) {
    std::stringstream ss;
    ss<<"))ab )&)123)";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RIGHTPAREN, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RIGHTPAREN, 1, 0, 1));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RIGHTPAREN, 5, 0, 5));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RIGHTPAREN, 7, 0, 7));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RIGHTPAREN, 11, 0, 11));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer;
}

TEST(LexerTest, ConstructsLeftbracketKeywordToken) {
    std::stringstream ss;
    ss<<"{";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_LEFTBRACKET, 0, 0, 0));
    delete lexer;
}

TEST(LexerTest, ConstructsRightbracketKeywordToken) {
    std::stringstream ss;
    ss<<"}";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_RIGHTBRACKET, 0, 0, 0));
    delete lexer;
}

TEST(LexerTest, ConstructsAccessKeywordToken) {
    std::stringstream ss;
    ss<<".";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_ACCESS, 0, 0, 0));
    delete lexer;
}

TEST(LexerTest, ConstructsSemicolonKeywordToken) {
    std::stringstream ss;
    ss<<";";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_SEMICOLON, 0, 0, 0));
    delete lexer;
}

TEST(LexerTest, ConstructsCommaKeywordToken) {
    std::stringstream ss;
    ss<<",";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_COMMA, 0, 0, 0));
    delete lexer;
}



TEST(LexerTest, ConstructsAssignEqTokens)
{
    std::stringstream ss;
    ss<<"= == === =! =^ a=b a!=b";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ASSIGN, 0, 0, 0, operatorIdMap.at("=")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_EQ, 2, 0, 2, operatorIdMap.at("==")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_EQ, 5, 0, 5, operatorIdMap.at("==")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ASSIGN, 7, 0, 7, operatorIdMap.at("=")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ASSIGN, 9, 0, 9, operatorIdMap.at("=")));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 10, 0, 10)));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ASSIGN, 12, 0, 12, operatorIdMap.at("=")));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 13, 0, 13)));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 15, 0, 15, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ASSIGN, 16, 0, 16, operatorIdMap.at("=")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 17, 0, 17, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 19, 0, 19, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_EQ, 20, 0, 20, operatorIdMap.at("!=")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 22, 0, 22, "b")));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 23, 0, 23)));
    delete lexer;
}


TEST(LexerTest, ConstructsRelTokens)
{
    std::stringstream ss;
    ss<<"a<b a<=b a>b a>=b >>=><=";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 0, 0, 0, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 1, 0, 1, operatorIdMap.at("<")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 4, 0, 4, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 5, 0, 5, operatorIdMap.at("<=")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 7, 0, 7, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 9, 0, 9, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 10, 0, 10, operatorIdMap.at(">")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 11, 0, 11, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 13, 0, 13, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 14, 0, 14, operatorIdMap.at(">=")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 16, 0, 16, "b")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 18, 0, 18, operatorIdMap.at(">")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 19, 0, 19, operatorIdMap.at(">=")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 21, 0, 21, operatorIdMap.at(">")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_REL, 22, 0, 22, operatorIdMap.at("<=")));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 24, 0, 24)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsAddTokens)
{
    std::stringstream ss;
    ss<<"a+b a-b";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 0, 0, 0, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ADD, 1, 0, 1, operatorIdMap.at("+")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 4, 0, 4, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ADD, 5, 0, 5, operatorIdMap.at("-")));
    /*t = lexer->getToken();    
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 6, 0, 6, "b")));*/
    delete lexer;
}

TEST(LexerTest, ConstructsMulExpTokens)
{
    std::stringstream ss;
    ss<<"a*b a/b a**2 ***";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 0, 0, 0, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_MUL, 1, 0, 1, operatorIdMap.at("*")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 4, 0, 4, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_MUL, 5, 0, 5, operatorIdMap.at("/")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 6, 0, 6, "b")));
    t = lexer->getToken();    
    //ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 8, 0, 8, "a")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_EXP, 9, 0, 9, operatorIdMap.at("**")));
    t = lexer->getToken();
    //ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 11, 0, 11, (long long)2)));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_EXP, 13, 0, 13, operatorIdMap.at("**")));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_MUL, 15, 0, 15, operatorIdMap.at("*")));
    t = lexer->getToken();
    delete lexer;
}


TEST(LexerTest, ConstructsIdentifierTokens)
{
    std::stringstream ss;
    ss<<"a ab a0C_ B B0_x a%a aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "a"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 2, 0, 2, "ab"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 5, 0, 5, "a0C_"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 10, 0, 10, "B"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_TYPE, 12, 0, 12, "B0_x"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 17, 0, 17, "a"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(UNKNOWN_TOKEN, 0, 18, 0, 18));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 19, 0, 19, "a"));
    ASSERT_THROW(lexer->getToken(), std::runtime_error); 	
    delete lexer;
}


TEST(LexerTest, ConstructsStringLiteralTokens)
{
    std::stringstream ss;
    ss<<"\"\\\\\"\"";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_STRING_LIT, 0, 0, 0, "\\"));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(UNKNOWN_TOKEN, 0, 4, 0, 4));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 6, 0, 6));
    delete lexer;
}

TEST(LexerTest, ConstructsStringLiteralTokens2)
{
    std::stringstream ss;
    ss<<"\"\\\\\\\"\"";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_STRING_LIT, 0, 0, 0, "\\\""));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 6, 0, 6));
    delete lexer;
}

TEST(LexerTest, ConstructsStringLiteralTokens3)
{
    std::stringstream ss;
    ss<<"\"123456789";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    ASSERT_TRUE(t == Token(UNKNOWN_TOKEN, 0, 0, 0, 0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 11, 0, 11));
    delete lexer;
}

TEST(LexerTest, ConstructsStringLiteralTokens4)
{
    std::stringstream ss;
    ss<<"s = \"To jest string: !@#fs2432!@#$%^&*()_=-=_+_[]p{}P\|';[;';?/?.,>< \n \t \\\"\"";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();    
    ASSERT_TRUE(t == Token(IDENTIFIER_TOKEN, T_VAR, 0, 0, 0, "s"));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(OPERATOR_TOKEN, T_ASSIGN, 2, 0, 2, operatorIdMap.at("=")));
    t = lexer->getToken();    
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_STRING_LIT, 4, 0, 4, "To jest string: !@#fs2432!@#$%^&*()_=-=_+_[]p{}P|';[;';?/?.,>< \n \t \""));
    delete lexer;
}


TEST(LexerTest, ConstructsNumericLiteralTokens)
{
    std::stringstream ss;
    ss<<"0 123 0.5 41.52 01 0.1.1 5. .6 12a";
    Lexer* lexer = new Lexer(ss);
    Token t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_INT_LIT, 0, 0, 0, (long long)0));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_INT_LIT, 2, 0, 2, (long long)123));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_FLOAT_LIT, 6, 0, 6, (double)0.5));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_FLOAT_LIT, 10, 0, 10, (double)41.52));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(UNKNOWN_TOKEN, 0, 16, 0, 16));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_FLOAT_LIT, 19, 0, 19, (double)0.1));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_ACCESS, 22, 0, 22));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_INT_LIT, 23, 0, 23, (long long)1));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(UNKNOWN_TOKEN, 0, 25, 0, 25));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(KEYWORD_TOKEN, T_ACCESS, 28, 0, 28));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(LITERAL_TOKEN, T_INT_LIT, 29, 0, 29, (long long)6));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(UNKNOWN_TOKEN, 0, 31, 0, 31));
    t = lexer->getToken();
    ASSERT_TRUE(t == Token(EOT_TOKEN, 0, 34, 0, 34));
    delete lexer;
}