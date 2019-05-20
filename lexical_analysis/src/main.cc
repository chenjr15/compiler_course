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
        std::list<Token*> tokenList;
        Token* tk = nullptr;

        const  char * p = line.c_str();
        // p++;
        int len= 0;

        while (*p) {
            tk = new Token(Token::ERROR);
            len = paser_token(p,tk);
            if (len<=0) {
                std::cout<<"ERROR "<< p<<std::endl;
                break;
            } else {
                tokenList.push_back(tk);
                p = p+len;
            }
        }
        for(auto token = tokenList.begin(); token!= tokenList.end(); token++) {
            std::cout<< (*token)->to_string() <<std::endl;
        }
        std::cout << "----" << std::endl;
    }

}