#include <iostream>
#include <list>
#include "token.h"
#include "cstdio"
int main(int argc, char *argv[]) {
    /* make compiler happy */
    argc = *argv[0];
    if(argc<0) argc = 1;

    std::string line;

    while (std::getline(std::cin,line)) {
        std::list<Token> tokenList;
        analyse_token_line(line,tokenList);
        for(auto token = tokenList.begin(); token!= tokenList.end(); token++) {
            std::cout<< token->to_string() <<std::endl;
        }
        std::cout << "----" << std::endl;
    }

}