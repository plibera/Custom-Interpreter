#pragma once

#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"



bool areTokensEqual(Token* a, Token* b);


TEST(LexerTest, ConstructsIfKeywordToken) {
    std::stringstream ss;
    ss<<"if iff If ifek";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_IF, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 3, 0, 3, "iff")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 7, 0, 7, "If")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 10, 0, 10, "ifek")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 14, 0, 14)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsElseKeywordToken) {
    std::stringstream ss;
    ss<<"else esle Else elsek";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_ELSE, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 5, 0, 5, "esle")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 10, 0, 10, "Else")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 15, 0, 15, "elsek")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 20, 0, 20)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsWhileKeywordToken) {
    std::stringstream ss;
    ss<<"while whil While whilek";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_WHILE, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 6, 0, 6, "whil")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 11, 0, 11, "While")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 17, 0, 17, "whilek")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 23, 0, 23)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsReturnKeywordToken) {
    std::stringstream ss;
    ss<<"return retur Return retrun";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RETURN, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 7, 0, 7, "retur")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 13, 0, 13, "Return")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 20, 0, 20, "retrun")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 26, 0, 26)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsOrKeywordToken) {
    std::stringstream ss;
    ss<<"or o Or orr";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_OR, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 3, 0, 3, "o")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 5, 0, 5, "Or")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 8, 0, 8, "orr")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 11, 0, 11)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsAndKeywordToken) {
    std::stringstream ss;
    ss<<"and an And andy";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_AND, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 4, 0, 4, "an")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 7, 0, 7, "And")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 11, 0, 11, "andy")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 15, 0, 15)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsNotKeywordToken) {
    std::stringstream ss;
    ss<<"not no Not note";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_NOT, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 4, 0, 4, "no")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 7, 0, 7, "Not")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 11, 0, 11, "note")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 15, 0, 15)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsIntKeywordToken) {
    std::stringstream ss;
    ss<<"Int int In Ints";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_INT, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 4, 0, 4, "int")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 8, 0, 8, "In")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 11, 0, 11, "Ints")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 15, 0, 15)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsFloatKeywordToken) {
    std::stringstream ss;
    ss<<"Float float Floa Floats";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_FLOAT, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 6, 0, 6, "float")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 12, 0, 12, "Floa")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 17, 0, 17, "Floats")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 23, 0, 23)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsBoolKeywordToken) {
    std::stringstream ss;
    ss<<"Bool bool Boo Bools";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_BOOL, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 5, 0, 5, "bool")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 10, 0, 10, "Boo")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 14, 0, 14, "Bools")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 19, 0, 19)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsStringKeywordToken) {
    std::stringstream ss;
    ss<<"String string Strin Strings";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_STRING, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 7, 0, 7, "string")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 14, 0, 14, "Strin")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 20, 0, 20, "Strings")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 27, 0, 27)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsTrueKeywordToken) {
    std::stringstream ss;
    ss<<"true tru True trues";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_TRUE, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 5, 0, 5, "tru")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 9, 0, 9, "True")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 14, 0, 14, "trues")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 19, 0, 19)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsFalsetKeywordToken) {
    std::stringstream ss;
    ss<<"false fals False falses";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_FALSE, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 6, 0, 6, "fals")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 11, 0, 11, "False")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 17, 0, 17, "falses")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 23, 0, 23)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsVoidKeywordToken) {
    std::stringstream ss;
    ss<<"Void void Voi Voids";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_VOID, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 5, 0, 5, "void")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 10, 0, 10, "Voi")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 14, 0, 14, "Voids")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 19, 0, 19)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsClassKeywordToken) {
    std::stringstream ss;
    ss<<"class clas Class classs";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_CLASS, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 6, 0, 6, "clas")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 11, 0, 11, "Class")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 17, 0, 17, "classs")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 23, 0, 23)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsPublicKeywordToken) {
    std::stringstream ss;
    ss<<"public publi Public publics";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_PUBLIC, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 7, 0, 7, "publi")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_TYPE, 13, 0, 13, "Public")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 20, 0, 20, "publics")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 27, 0, 27)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsLeftparenKeywordToken) {
    std::stringstream ss;
    ss<<"((ab (&(123(";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTPAREN, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTPAREN, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTPAREN, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTPAREN, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTPAREN, 11, 0, 11)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}


TEST(LexerTest, ConstructsRightparenKeywordToken) {
    std::stringstream ss;
    ss<<"))ab )&)123)";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTPAREN, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTPAREN, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTPAREN, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTPAREN, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTPAREN, 11, 0, 11)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsLeftbracketKeywordToken) {
    std::stringstream ss;
    ss<<"{{ab {&{123{";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTBRACKET, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTBRACKET, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTBRACKET, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTBRACKET, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_LEFTBRACKET, 11, 0, 11)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsRightbracketKeywordToken) {
    std::stringstream ss;
    ss<<"}}ab }&}123}";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTBRACKET, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTBRACKET, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTBRACKET, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTBRACKET, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_RIGHTBRACKET, 11, 0, 11)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsAccessKeywordToken) {
    std::stringstream ss;
    ss<<"..ab .&.123.";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_ACCESS, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_ACCESS, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_ACCESS, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_ACCESS, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 8, 0, 8)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsSemicolonKeywordToken) {
    std::stringstream ss;
    ss<<";;ab ;&;123;";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_SEMICOLON, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_SEMICOLON, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_SEMICOLON, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_SEMICOLON, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_SEMICOLON, 11, 0, 11)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}

TEST(LexerTest, ConstructsCommaKeywordToken) {
    std::stringstream ss;
    ss<<",,ab ,&,123,";
    Lexer* lexer = new Lexer(ss);
    Token* t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_COMMA, 0, 0, 0)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_COMMA, 1, 0, 1)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new IdentifierToken(T_VAR, 2, 0, 2, "ab")));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_COMMA, 5, 0, 5)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(UNKNOWN_TOKEN, 0, 6, 0, 6)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_COMMA, 7, 0, 7)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new LiteralToken(T_INT_LIT, 8, 0, 8, (long long)123)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new KeywordToken(T_COMMA, 11, 0, 11)));
    t = lexer->getToken();
    ASSERT_TRUE(areTokensEqual(t, new Token(EOT_TOKEN, 0, 12, 0, 12)));
    delete lexer, t;
}



