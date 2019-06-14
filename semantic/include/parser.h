#if !defined(__PARSER_H__)
#define __PARSER_H__

#include <list>
#include <utility>
#include "tree.h"
#include "token.h"
typedef TreeNode<Token> AstNode;
typedef std::pair<Token,int> TokenStatus;

class ProductionRule {
public:
    Token::TokenType left;
    std::vector<Token::TokenType> right;
    int right_count;
    ProductionRule(Token::TokenType l, int count):left(l),right_count(count) {}
    ProductionRule(Token::TokenType l,std::vector<Token::TokenType> _right):left(l),right(_right) {
        right_count = right.size();
    }
};
// 产生式列表
extern const ProductionRule  production_rule_table[];
extern const std::string action_table[][16];
extern const int goto_table[][5];
AstNode* parse(std::list<Token>& tokens);

#endif // __PARSER_H__