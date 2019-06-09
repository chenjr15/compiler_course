#if !defined(__TOKEN_H__)
#define __TOKEN_H__
#include <string>
#include <list>

class Token {

public:
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
        // 逗号 , 参数分隔符
        COMMA,
        // 分号 ; 语句分隔符
        SEMICOLON,
        // 求解 问号?
        SLOVE,
        // 分隔符 空白字符
        SEPARATOR,

        // 用于标识该枚举常量表的最大大小
        __TABLE_SIZE
    };

    Token(TokenType t ):token_type(t),val({.intval=0}) {};
    void setNum(double number);
    void setStr(const char* str,unsigned len);
    double getNum();
    std::string getStr(char * ret);
    TokenType getTokenType();
    void setTokenType(TokenType t);
    char getChar();
    void setChar(const char c);
    std::string to_string();
    ~Token();
private:
    TokenType token_type;
    // int len;
    union {
        double numval;
        char strval[32];
        char charval;
        int intval;
    } val;
    static const std::string type_name_table[];
    static const unsigned type_name_table_size = __TABLE_SIZE;
};


/**
 *  解析一行语句中的token
 * @param  {string} line          : 待解析的string
 * @param  {vector<Token>} tokens : 解析结果会被push_back至此
 * @return {bool}                 : 解析遇到问题时返回false
 */
bool analyse_token_line(std::string& line,std::list<Token>& tokens);
/**
 *  流式解析字符串中的token
 * @param  {char*} p      :  待解析的字符指针
 * @param  {Token*} token :  传入用于返回的token指针
 * @return {int}          :  解析到的token长度
 */
int analyse_token(const char* p,Token* token) ;
int get_num_val(const char* p, Token* tk);
int get_str_val(const char* p,Token* tk);




#endif // __TOKEN_H__
