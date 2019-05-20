#include "predefined.h"
const unsigned func_name_table_size =9 ;
static std::string func_name_table[func_name_table_size] {
    "sin","cos",
    "tg","ctg",
    "log","lg","ln",
};
const unsigned const_name_table_size =3 ;

static std::string const_name_table[const_name_table_size] {
    "PI","E","G"
};

bool isFunc(std::string s) {
    for (size_t i = 0; i < func_name_table_size; i++) {
        if (func_name_table[i] == s) {
            return true;
        }
    }
    return false;

}
bool isConst(std::string s) {
    for (size_t i = 0; i < const_name_table_size; i++) {
        if (const_name_table[i] == s) {
            return true;
        }

    }
    return false;
}