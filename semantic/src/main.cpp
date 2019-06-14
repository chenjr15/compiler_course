#include <iostream>
#include "cstdio"
#include <list>
#include "token.h"
#include "parser.h"
using namespace std;
int main(int argc, char *argv[]) {
    /* make compiler happy */
    argc = *argv[0];
    if(argc<0) argc = 1;

    string line;
    cout<<"\033[33m# >\033[0m";
    while (std::getline(std::cin,line)) {


        std::list<Token> tokenList;
        bool analyse_success =analyse_token_line(line,tokenList);
        if (!analyse_success)
        {
            cout<< "词法错误."<<endl;
            cout<<"\033[33m# >\033[0m";
            continue;
        }
        
        if (tokenList.empty()) {
            cout<< ""<<endl;
            cout<<"\033[33m# >\033[0m";
            continue;
        }
        for(auto token = tokenList.begin(); token!= tokenList.end(); token++) {
            std::cout<< token->to_string() <<", ";
        }
        std::cout<< std::endl << "----" << std::endl;
        parse(tokenList);
        cout<<"\033[33m# >\033[0m";

    }

}