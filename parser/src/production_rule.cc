#include "parser.h"
#include <vector>
using namespace std;
// 产生式表
const ProductionRule  production_rule_table[] = {
    ProductionRule(Token::STOP,0),
    // STATEMENT1->  STATEMENT     1
    ProductionRule(Token::STOP,vector<Token::TokenType>{Token::STATEMENT}),
    // STATEMENT ->  id = EXP ;    2
    ProductionRule(Token::STATEMENT, vector<Token::TokenType>{Token::ID,Token::ASSIGN,Token::EXP,Token::SEMICOLON}),
    // STATEMENT ->  ? EXP ;       3
    ProductionRule(Token::STATEMENT,vector<Token::TokenType>{Token::SLOVE,Token::EXP,Token::SEMICOLON}),
    // EXP       ->  EXP + EXP1    4
    ProductionRule(Token::EXP,vector<Token::TokenType>{Token::EXP,Token::S_PLUS,Token::EXP_1}),
    // EXP       ->  EXP - EXP1    5
    ProductionRule(Token::EXP,vector<Token::TokenType>{Token::EXP,Token::S_MINUS,Token::EXP_1}),
    // EXP       ->  EXP1  　      6
    ProductionRule(Token::EXP,vector<Token::TokenType>{Token::EXP_1}),
    // EXP1      ->  EXP1 * FACTOR 7
    ProductionRule(Token::EXP_1,vector<Token::TokenType>{Token::EXP_1,Token::S_MULT,Token::FACTOR}),
    // EXP1      ->  EXP1 / FACTOR 8
    ProductionRule(Token::EXP_1,vector<Token::TokenType>{Token::EXP_1,Token::S_DIV,Token::FACTOR}),
    // EXP1      ->  EXP1 ^ FACTOR 9
    ProductionRule(Token::EXP_1,vector<Token::TokenType>{Token::EXP_1,Token::S_POW,Token::FACTOR}),
    // EXP1      ->  FACTOR        10
    ProductionRule(Token::EXP_1,vector<Token::TokenType>{Token::FACTOR}),
    // FACTOR    -> - FACTOR       11
    ProductionRule(Token::FACTOR,vector<Token::TokenType>{Token::S_MINUS,Token::FACTOR}),
    // FACTOR    -> num            12
    ProductionRule(Token::FACTOR,vector<Token::TokenType>{Token::NUM}),
    // FACTOR    ->  ( EXP )       13
    ProductionRule(Token::FACTOR,vector<Token::TokenType>{Token::L_PARENT,Token::EXP,Token::R_PARENT}),
    // FACTOR    -> const          14
    ProductionRule(Token::FACTOR,vector<Token::TokenType>{Token::CONST}),
    // FACTOR    ->  id            15
    ProductionRule(Token::FACTOR,vector<Token::TokenType>{Token::ID}),
    // FACTOR    ->  func ( ARG )  16
    ProductionRule(Token::FACTOR,vector<Token::TokenType>{Token::FUNC,Token::L_PARENT,Token::EXP,Token::R_PARENT}),
    // ARG       ->  EXP           17
    ProductionRule(Token::ARG,vector<Token::TokenType>{Token::EXP}),
    // ARG       ->  EXP, ARG      18
    ProductionRule(Token::ARG,vector<Token::TokenType>{Token::EXP,Token::COMMA,Token::ARG}),


};