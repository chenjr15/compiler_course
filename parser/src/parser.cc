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
        cout<<"----------"<<endl;
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
        cout<<"---> "<<action<<endl;
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
            // 匹配产生式右边的符号出栈
            vector<Token> right;
            for (size_t i = 0; i < prod.right_count; ++i) {
                right.push_back((--slove.end())->first);
                slove.pop_back();
            }
            // 根据goto表寻找当前规约后的新状态
            int status = (--slove.end())->second;
            status = goto_table[status][prod.left-Token::TERMINATOR-1];
            // 将产生式左边及状态入栈
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
