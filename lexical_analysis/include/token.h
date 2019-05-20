#if !defined(__TOKEN_H__)
#define __TOKEN_H__
#include <string>


enum TokenType {
    // 错误
    ERROR = -1,
    // EOF
    STOP = 0,
    // 常量
    CONST,
    // 函数
    FUNC,
    // 标识符
    ID,
    // 数字
    NUM,
    // 赋值 =
    ASSIGN,
    // 加减乘除 +, -, *, / , ^
    S_PLUS,S_MINUS,S_MULT,S_DIV,S_POW,
    // 括号
    L_PARENT,R_PARENT,
    // 分号 ; 语句分隔符
    SEMICOLON,
    // 求解 问号?
    SLOVE,

};

class Token {
private:
    TokenType token_type;
    // int len;
    union {
        double numval;
        char strval[32];
        char charval;
    } val;

public:
    Token(TokenType t):token_type(t) {};
    void setNum(double number);
    void setStr(const char* str,unsigned len);
    double getNum();
    const char * getStr(char * ret);
    TokenType getTokenType();
    void setTokenType(TokenType t);
    char getChar();
    void setChar(const char c);
    ~Token();
};


int paser_token(const char* p,Token* token);
int get_num_val(const char* p, Token* tk);
int get_str_val(const char* p,Token* tk);

std::string  token_to_str(TokenType tk);



#endif // __TOKEN_H__
