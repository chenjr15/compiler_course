#include <iostream>
#include <cctype>
#include <regex>
#include <list>
#include "token.h"
#include "match.h"
#include "predefined.h"
using namespace std;

/**
 *  解析一行语句中的token
 * @param  {string} line          : 待解析的string
 * @param  {vector<Token>} tokens : 解析结果会被push_back至此
 * @return {bool}                 : 解析遇到问题时返回false
 */
bool  analyse_token_line(string& line,list<Token>& tokens) {
    // std::list<Token*> tokenList;
    Token* tk = nullptr;
    const  char * p = line.c_str();
    // p++;
    int len= 0;
    while (*p) {
        tk = new Token(Token::ERROR);
        len = analyse_token(p,tk);
        if (len<=0) {
            std::cout<<"ERROR "<< p<<std::endl;
            break;
        } else {
            tk->setStrPosition(line.c_str() - p);
            tokens.push_back(*tk);
            p = p+len;
        }
    }
    return !*p;
}
/**
 *  流式解析字符串中的token
 * @param  {char*} p      :  待解析的字符指针
 * @param  {Token*} token :  传入用于返回的token指针
 * @return {int}          :  解析到的token长度
 */
int  analyse_token(const char* p,Token* token) {
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
            cout << "! can't analyse "<<*p << endl;
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
        tk->setStr(head,len);
        tk->setTokenType(Token::ID);
        // 对于标识符进一步判断他是否是常量和函数
        if (isFunc(tk->getStr(nullptr))) {
            tk->setTokenType(Token::FUNC);
        } else if (isConst(tk->getStr(nullptr))) {
            tk->setTokenType(Token::CONST);
        }

    } else {
        tk->setTokenType(Token::ERROR);

    }



    return len;
}
const string Token::type_name_table[]= {
    "#",
    "const",
    "func",
    "id",
    "num",
    "=",
    "+","-","*","/","^",
    "(",")",
    ",",
    ";",
    "?",
    "separator",

    "T",
    /*   以下是非终结符 */
    // 语句
    "S",
    // 表达式
    "E",
    // 　表达式１
    "E'",
    // 因子
    "F",
    // 参数
    "ARG",
    "NON_TERMINATOR",
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

string double_to_string(double __val) {
    const int __n =
        __gnu_cxx::__numeric_traits<double>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<string>(&std::vsnprintf, __n,
                                           "%g", __val);
}


std::string Token::to_string() {
    if (token_type<0 && token_type<__TABLE_SIZE) {
        return "<ERROR Token>";
    }
    string str;
    str+="'";
    str+=type_name_table[token_type];
    switch (token_type) {
    case FUNC:
    case CONST:
    case ID:
        str+=" ";
        str += getStr(nullptr);
        break;
    case NUM:
        str+=" ";
        str+= double_to_string(val.numval);
        break;
    default:
        break;
    }
    str+="'";
    return str;
}
Token::~Token() {
}
bool Token::isTerminator() {
    return this->token_type < TERMINATOR;
}

void Token::setStrPosition(unsigned a ) {
    str_position = a;
}
unsigned Token::getStrPosition() {
    return str_position;
}

std::string  Token::getTokenName( Token::TokenType t) {
    if (t>=0&& t<__TABLE_SIZE) {
        return type_name_table[t];
    } else {
        return "error";
    }
}