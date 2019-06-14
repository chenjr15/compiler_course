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
    cout<<"# >";
    while (std::getline(std::cin,line)) {


        std::list<Token> tokenList;
        analyse_token_line(line,tokenList);
        if (tokenList.empty()) {
            cout<< "Empty input."<<endl;
            continue;
        }
        for(auto token = tokenList.begin(); token!= tokenList.end(); token++) {
            std::cout<< token->to_string() <<", ";
        }
        std::cout<< std::endl << "----" << std::endl;
        parse(tokenList);
        cout<<"# >";

    }

}