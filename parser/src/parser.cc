#include "parser.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
void print_stack(vector<TokenStatus>&  stack) {

    for(auto item : stack) {
        cout<<"["<<Token::getTokenName(item.first.getTokenType())<<" "<<item.second<<"], ";
    }
    cout<<endl;
}


string print_node(AstNode* t,int ident = 0) {
    string s;
    s += "{";
    s+="\"name\":\"";
    s+=Token::getTokenName(t->value.getTokenType());
    s+="\",\"children\":";
    if (t->children.size()) {
        s+="[";
        for (size_t i = 0; i < t->children.size(); i++) {
            s+=  print_node((t->children)[i],ident+t->value.to_string().size()+2);

        }
        s += "]";

    } else {
        s+="None";
    }
    s += "},";
    
    return s;
}
void print_tree(vector<AstNode*> t) {
    string s;
    s += "[";
    for(auto node : t) {
        s+=print_node(node);
    }
    s += "]";

    // cout<<s;
    // cout<<endl;
    // 调用Python输出树
    ofstream f("t.py",ios::trunc);
    f<<"import json\ns = "<<s<<"\ns = json.dumps(s,indent=2)\nprint(s)\n";
    f.close();
    system("python3 t.py");
    cout<<endl;

}
AstNode* parse(list<Token> &tokens) {
    vector<AstNode*> tree_stack;
    vector<TokenStatus> stack= {{Token::STOP,0}};

    auto token_iter = tokens.begin();
    auto cur_token = *token_iter;
    int err = 0;
    while (true) {
        cout<<"\n\n----------"<<endl;
        print_stack(stack);
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

        string action =  action_table[(--stack.end())->second][cur_token.getTokenType()];
        cout<<"---> "<<action<<endl;
        if (action == "x") {
            err=1;
            break;
        } else if (*action.c_str() == 's') {
            // 移进
            int status = std::atoi(action.c_str()+1);
            TokenStatus t = {cur_token,status};
            stack.push_back(t);
            tree_stack.push_back(new AstNode(cur_token));
            ++token_iter;
        } else if (*action.c_str() == 'r') {
            // 规约
            // 产生式序号
            int prod_index = std::atoi(action.c_str()+1);
            auto prod= production_rule_table[prod_index];
            // 匹配产生式右边的符号出栈
            vector<AstNode*> right;
            for (int i = 0; i < prod.right_count; ++i) {
                stack.pop_back();
                right.push_back(*(--tree_stack.end()));
                tree_stack.pop_back();
            }
            // 剪枝
            AstNode* new_node = new AstNode(prod.left);
            for (int i = right.size() - 1; i >= 0; i--) {
                new_node->add_child(right[i]);
            }

            tree_stack.push_back(new_node);
            // 根据goto表寻找当前规约后的新状态
            int status = (--stack.end())->second;
            status = goto_table[status][prod.left-Token::TERMINATOR-1];
            // 将产生式左边及状态入栈
            stack.push_back({prod.left,status});
        } else if (action=="accept") {
            // 成功
            print_tree(tree_stack);

            break;
        }

    }
    if (err) {
        printf("ERROR! while parsing !\n");
    }

    return nullptr;
}
