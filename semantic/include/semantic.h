#if !defined(__SEMANTIC_H__)
#define __SEMANTIC_H__
#include <map>
#include <string>
#include "parser.h"


AstNode* cal(int prod_index,std::vector<AstNode*>& right);

extern std::map<std::string,double> var_table;

#endif // __SEMANTIC_H__
