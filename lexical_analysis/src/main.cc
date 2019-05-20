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
            tk = new Token(ERROR);
            len = paser_token(p,tk);
            if (len<=0) {
                std::cout<<"ERROR "<< p<<std::endl;
                break;
            } else {
                tokenList.push_back(tk);
                p = p+len;
            }
        }
        for(auto pos = tokenList.begin(); pos!= tokenList.end(); pos++) {
            Token* token = *pos;
            std::cout << "token: "<<token_to_str(token->getTokenType());
            if (token->getTokenType() == NUM) {
                std::cout<<"\t"<<token->getNum();
            } else if (token->getTokenType() == ID) {
                putchar('\t');
                for (size_t i = 0; i < 32&& *(token->getStr(nullptr)+i); i++) {
                    putchar(*(token->getStr(nullptr)+i));
                }
                // putchar('\n');
            } else if (token->getTokenType() == ERROR) {
                fprintf(stderr,"ERROR!\n");
            }
            std::cout<< std::endl;
        }
        std::cout << "----" << std::endl;
    }

}