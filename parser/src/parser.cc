#include "parser.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
void print_stack(vector<TokenStatus>&  stack) {

    for(auto item : stack) {
        cout<<"["<<Token::getTokenName(item.first.getTokenType())<<" "<<item.second<<"], ";
    }
    cout<<endl;
}
AstNode* parse(list<Token> &tokens) {
    vector<TokenStatus> slove= {{Token::STOP,0}};
    auto token_iter = tokens.begin();
    auto cur_token = *token_iter;
    int err = 0;
    while (true) {
        print_stack(slove);
        if (token_iter != tokens.end()) {
            cur_token = *token_iter;
        } else {
            cur_token = Token::STOP;
        }
        if (cur_token.getTokenType() == Token::SEPARATOR) {
            // 跳过空格
            ++token_iter;
            continue;
        }



        string action =  action_table[(--slove.end())->second][cur_token.getTokenType()];
        cout<<"-----------\n---> "<<action<<endl;
        if (action == "x") {
            err=1;
            break;
        } else if (*action.c_str() == 's') {
            // 移进
            int status = std::atoi(action.c_str()+1);
            TokenStatus t = {cur_token,status};
            slove.push_back(t);
            ++token_iter;
        } else if (*action.c_str() == 'r') {
            // 规约
            // 产生式序号
            int prod_index = std::atoi(action.c_str()+1);
            auto prod= production_rule_table[prod_index];
            vector<Token> right;
            for (size_t i = 0; i < prod.right_count; ++i) {
                right.push_back((--slove.end())->first);
                slove.pop_back();
            }
            int status = (--slove.end())->second;
            status = goto_table[status][prod.left-Token::TERMINATOR-1];
            slove.push_back({prod.left,status});
        } else if (action=="accept") {
            // 成功
            break;
        }

    }
    if (err) {
        printf("ERROR! while parsing !\n");
    }

    return nullptr;
}
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

const std::string action_table[][16]={
    {"x","x","x","s2","x","x","x","x","x","x","x","x","x","x","x","s3",},
    {"accept","x","x","x","x","x","x","x","x","x","x","x","x","x","x","x",},
    {"x","x","x","x","x","s4","x","x","x","x","x","x","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","x","x","x","x","x","s16","s17","x","x","x","x","x","x","s15","x",},
    {"x","x","x","x","x","x","r6","r6","s18","s19","s20","x","r6","r6","r6","x",},
    {"r10","x","x","x","x","x","r10","r10","r10","r10","r10","x","r10","r10","r10","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","x","x","x","x","x","r12","r12","r12","r12","r12","x","r12","r12","r12","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","x","x","x","x","x","r14","r14","r14","r14","r14","x","r14","r14","r14","x",},
    {"x","x","x","x","x","x","r15","r15","r15","r15","r15","x","r15","r15","r15","x",},
    {"x","s11","x","x","x","x","x","x","x","x","x","s22","x","x","x","x",},
    {"x","x","x","x","x","x","s16","s17","x","x","x","x","x","x","s23","x",},
    {"r3","x","x","x","x","x","x","x","x","x","x","x","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","x","x","x","x","x","s16","s17","x","x","x","x","s24","x","x","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"r2","x","x","x","x","x","x","x","x","x","x","x","s25","x","x","x",},
    {"x","x","x","x","x","x","r13","r13","r13","r13","r13","x","r13","r13","r13","x",},
    {"x","x","x","x","x","x","x","x","x","x","x","x","s27","x","x","x",},
    {"x","x","x","x","x","x","s16","s17","x","x","x","x","r17","s28","x","x",},
    {"x","x","x","x","x","x","r16","r16","r16","r16","r16","x","r16","r16","r16","x",},
    {"x","s11","s13","s12","s9","x","x","s8","x","x","x","s10","x","x","x","x",},
    {"x","x","x","x","x","x","x","x","x","x","x","x","r18","x","x","x",},
    {"x","x","x","x","x","x","r4","r4","s18","s19","s20","x","r4","r4","r4","x",},
    {"x","x","x","x","x","x","r7","r7","r7","r7","r7","x","r7","r7","r7","x",},
    {"x","x","x","x","x","x","r8","r8","r8","r8","r8","x","r8","r8","r8","x",},
    {"x","x","x","x","x","x","r9","r9","r9","r9","r9","x","r9","r9","r9","x",},
    {"x","x","x","x","x","x","r11","r11","r11","r11","r11","x","r11","r11","r11","x",},
    {"x","x","x","x","x","x","r5","r5","s18","s19","s20","x","r5","r5","r5","x",},
};
const int goto_table[][5]={
    {1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,5,6,7,-1,},
    {-1,14,6,7,-1,},
    {-1,-1,-1,7,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,21,6,7,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,30,7,-1,},
    {-1,-1,35,7,-1,},
    {-1,-1,-1,31,-1,},
    {-1,-1,-1,32,-1,},
    {-1,-1,-1,33,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,26,6,7,25,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,26,6,7,29,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,},
};