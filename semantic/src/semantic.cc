#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "parser.h"
#include "semantic.h"
using namespace std;
AstNode* cal(int prod_index,vector<AstNode*>& right) {
    auto rule =  production_rule_table[prod_index];
    AstNode* ret;
    ret = new AstNode(rule.left);
    if (prod_index == 2) {
        string id = right[0]->value.getStr(nullptr);
        double val =  right[2]->value.getNum();
        var_table[id] = val;

    } else if (prod_index == 3) {

        double val =  right[1]->value.getNum();
        ret->value.setNum(val);
        // cout<<val<<endl;
    } else if (prod_index == 4) {

        double val1 =  right[0]->value.getNum();
        double val2 =  right[2]->value.getNum();
        ret->value.setNum(val1+val2);

    } else if (prod_index == 5) {

        double val1 =  right[0]->value.getNum();
        double val2 =  right[2]->value.getNum();
        ret->value.setNum(val1-val2);

    } else if (prod_index == 6) {

        double val1 =  right[0]->value.getNum();
        ret->value.setNum(val1);

    } else if (prod_index == 7) {

        double val1 =  right[0]->value.getNum();
        double val2 =  right[2]->value.getNum();

        ret->value.setNum(val1*val2);
    } else if (prod_index == 8) {

        double val1 =  right[0]->value.getNum();
        double val2 =  right[2]->value.getNum();

        ret->value.setNum(val1/val2);
    } else if (prod_index == 9) {

        double val1 =  right[0]->value.getNum();
        double val2 =  right[2]->value.getNum();

        ret->value.setNum(powf64(val1,val2));
    } else if (prod_index == 10) {

        double val1 =  right[0]->value.getNum();
        // double val2 =  right[2]->value.getNum();

        ret->value.setNum(val1);
    } else if (prod_index == 11) {

        double val1 =  right[1]->value.getNum();
        // double val2 =  right[2]->value.getNum();

        ret->value.setNum(-val1);
    } else if (prod_index == 12) {

        double val1 =  right[0]->value.getNum();
        // double val2 =  right[2]->value.getNum();

        ret->value.setNum(val1);
    } else if (prod_index == 13) {

        double val1 =  right[1]->value.getNum();
        // double val2 =  right[2]->value.getNum();
        ret->value.setNum(val1);
    } else if (prod_index == 14) {
        // 常量的处理
        double val1;
        if (right[0]->value.getStr(0) == "PI") {
            val1 = M_PI;
        } else if(right[0]->value.getStr(0) == "E") {
            val1 = M_E;
        } else if(right[0]->value.getStr(0) == "G") {
            val1 = 9.8;
        }

        // double val2 =  right[2]->value.getNum();
        ret->value.setNum(val1);
    } else if (prod_index == 15) {
        // 常量的处理
        string id = right[0]->value.getStr(nullptr);
        auto iter =  var_table.find(id);
        double val  =0;
        if (iter!=var_table.end()) {
            //  找到
            val = iter->second;
        }

        // double val2 =  right[2]->value.getNum();
        ret->value.setNum(val);
    } else if (prod_index == 16) {
        // 函数的处理
        double val = 0;

        string id = right[0]->value.getStr(nullptr);
        auto arg= right[2];
        auto arg_count = arg->children.size();
        // 单参数函数
        if (arg_count ==3 ) {
            if ( arg->children[2]->children.size()>1) {
                arg_count = 3;
                cout<<"函数"<<id<<"参数过多!"<<endl;
            } else {
                arg_count = 2;
            }
        }
        if (arg_count == 1) {
            double arg1 = arg->value.getNum();
            if (id=="sin") {
                val=sinf64(arg1);
            } else if (id=="cos") {
                val=cosf64(arg1);

            } else if (id=="tg") {
                val=tanf64(arg1);
            } else if (id=="ctg") {
                val=1.0/tanf64(arg1);
            } else if (id=="log") {
                // 单参数时以二为底
                val=log2f64(arg1);
            } else if (id=="lg") {
                val=log10f64(arg1);
            } else if (id=="ln") {
                val=logf64(arg1);
            }
        } else if (arg_count ==2) {
            if(id =="log") {
                double arg1 = arg->children[0]->value.getNum();
                double arg2 = arg->children[2]->value.getNum();
                val = log10f64(arg1)/log10f64(arg2);

            } else {
                cout<<"函数"<<id<<"无法识别!"<<endl;
            }

        }
        // double val2 =  right[2]->value.getNum();
        ret->value.setNum(val);
    } else if (prod_index == 17) {

        double val =right[0]->value.getNum() ;

        ret->value.setNum(val);
    } else if (prod_index == 18) {

        // double val =right[0]->value.getNum() ;

        // ret->value.setNum(val);
    }

    for (size_t i = 0; i<right.size(); ++i) {
        ret->add_child(right[i]);
    }

    return ret;
}
std::map<std::string,double> var_table;