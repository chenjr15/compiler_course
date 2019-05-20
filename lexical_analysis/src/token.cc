#include <iostream>
#include <cctype>
#include <regex>
#include "token.h"
#include "match.h"
using namespace std;


/**
 * 解析字符串中的token
 * @param  {char*} p      :  待解析的字符串
 * @param  {Token*} token :  传入用于返回的token指针
 * @return {int}          :
 */
int  paser_token(const char* p,Token* token) {
    if (!p || !token) {
        return -1;
    }

    int len = 1;
    TokenType token_type = ERROR;
    switch (*p) {
    case 0:
        token_type = STOP;
        break;
    case '+':
        token_type = S_PLUS;
        break;
    case '-':
        token_type = S_MINUS;
        break;
    case '*':
        token_type = S_MULT;
        break;
    case '/':
        token_type = S_DIV;
        break;
    case '^':
        token_type = S_POW;
        break;
    case '?':
        token_type = SLOVE;
        break;
    case ';':
        token_type = SEMICOLON;
        break;
    case '=':
        token_type = ASSIGN;
        break;
    case '(':
        token_type = L_PARENT;
        break;
    case ')':
        token_type = R_PARENT;
        break;
    default:
        token_type = ERROR;
        break;
    }
    token->setTokenType(token_type);
    if (token_type == ERROR) {
        if (isdigit(*p)) {
            // 尝试判断成数字
            len = get_num_val(p,token);

        } else if (isalpha(*p)||*p == '_') {
            // 尝试判断成标识符
            len =  get_str_val(p,token);

        } else {
            cout << "! can't paser "<<*p << endl;
            token->setTokenType(ERROR);
        }
    } else {
        len = 1;
    }

    return len;
}

int get_num_val(const char* p, Token* tk) {
    // 确定长度
    unsigned len= 0 ;
    const char* head = p;
    string test;

    while (isdigit(*p) || *p == '.') {
        test+=*p;
        len++;
        p++;

    }

    bool match = match_num(head,len);
    if (match) {
        tk->setNum( stod(test));
        tk->setTokenType(NUM);

    } else {
        tk->setTokenType(ERROR);
    }


    p = head;

    return len;
}
int get_str_val(const char* p, Token* tk) {
    // 确定长度
    unsigned len= 0 ;
    const char* head = p;
    while (isalnum(*p) || *p == '_') {
        len++;
        p++;
    }
    bool match =match_id(head,len);
    if (match) {
        tk->setTokenType(ID);
        tk->setStr(head,len);

    } else {
        tk->setTokenType(ERROR);

    }



    return len;
}

string  token_to_str(TokenType tk) {
    if (tk<0|| tk>SLOVE) {
        return "ERROR";
    }
    string type_name_table[]= {
        "STOP",
        "CONST",
        "FUNC",
        "ID",
        "NUM",
        "ASSIGN",
        "S_PLUS","S_MINUS","S_MULT","S_DIV","S_POW",
        "L_PARENT","R_PARENT",
        "SEMICOLON",
        "SLOVE",
    };
    return type_name_table[tk];
}

void Token::setNum(double number) {
    val.numval = number;
}
void Token::setStr(const char* str,unsigned len) {
    for (size_t i = 0; i < len && *(str+i); i++) {
        val.strval[i] = *(str+i);
    }
}
char Token::getChar() {
    return val.charval;

}
void Token::setChar(char c) {
    val.charval = c;
}
double Token::getNum() {

    return val.numval;
}

char const* Token::getStr(char * ret) {
    if (ret) {
        for (size_t i = 0; i < 32; i++) {
            *ret++ = val.strval[i];
        }
    }

    return val.strval;
}

TokenType Token::getTokenType() {
    return token_type;
}
void Token::setTokenType(TokenType t) {
    token_type = t;
}
Token::~Token() {
}