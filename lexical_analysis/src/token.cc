#include <iostream>
#include <cctype>
#include <regex>
#include "token.h"
#include "match.h"
#include "predefined.h"
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
    Token::TokenType token_type = Token::ERROR;
    switch (*p) {
    case 0:
        token_type = Token::STOP;
        break;
    case '+':
        token_type = Token::S_PLUS;
        break;
    case '-':
        token_type = Token::S_MINUS;
        break;
    case '*':
        token_type = Token::S_MULT;
        break;
    case '/':
        token_type = Token::S_DIV;
        break;
    case '^':
        token_type = Token::S_POW;
        break;
    case '?':
        token_type = Token::SLOVE;
        break;
    case ',':
        token_type = Token::COMMA;
        break;
    case ';':
        token_type = Token::SEMICOLON;
        break;
    case '=':
        token_type = Token::ASSIGN;
        break;
    case '(':
        token_type = Token::L_PARENT;
        break;
    case ')':
        token_type = Token::R_PARENT;
        break;
    default:
        token_type = Token::ERROR;
        break;
    }
    token->setTokenType(token_type);
    if (token_type == Token::ERROR) {
        if (isdigit(*p)) {
            // 尝试判断成数字
            len = get_num_val(p,token);

        } else if (isalpha(*p)||*p == '_') {
            // 尝试判断成标识符
            len =  get_str_val(p,token);

        } else if (isspace(*p++)) {
            // 对于空白字符要跳过多个
            token_type = Token::SEPARATOR;
            while (isspace(*p++)) {
                ++len;
            }
            token->setTokenType(token_type);
        } else {
            cout << "! can't paser "<<*p << endl;
            token->setTokenType(Token::ERROR);
        }
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
        tk->setTokenType(Token::NUM);

    } else {
        tk->setTokenType(Token::ERROR);
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
        tk->setTokenType(Token::ID);
        // 对于标识符进一步判断他是否是常量和函数
        if (isFunc(tk->getStr(nullptr))) {
            tk->setTokenType(Token::FUNC);
        } else if (isConst(tk->getStr(nullptr))) {
            tk->setTokenType(Token::CONST);
        }
        tk->setStr(head,len);

    } else {
        tk->setTokenType(Token::ERROR);

    }



    return len;
}
const string Token::type_name_table[]= {
    "STOP",
    "CONST",
    "FUNC",
    "ID",
    "NUM",
    "ASSIGN",
    "S_PLUS","S_MINUS","S_MULT","S_DIV","S_POW",
    "L_PARENT","R_PARENT",
    "COMMA",
    "SEMICOLON",
    "SLOVE",
    "SEPARATOR",
};


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

string Token::getStr(char * ret) {
    if (ret) {
        for (size_t i = 0; i < 32; i++) {
            *ret++ = val.strval[i];
        }
    }
    string _strval;
    for (size_t i = 0; i < 32 && *(val.strval+i); i++) {
        _strval += val.strval[i];
    }
    return _strval;
}

Token::TokenType Token::getTokenType() {
    return token_type;
}
void Token::setTokenType(TokenType t) {
    token_type = t;
}
std::string Token::to_string() {
    if (token_type<0 && token_type<__TABLE_SIZE) {
        return "<ERROR Token>";
    }
    string str;
    str+="< ";
    str+=type_name_table[token_type];
    str+=" ";
    switch (token_type) {
    case FUNC:
    case CONST:
    case ID:
        str += getStr(nullptr);
        break;
    case NUM:
        str+= std::to_string(val.numval);
        break;
    default:
        break;
    }
    str+=" >";
    return str;
}
Token::~Token() {
}