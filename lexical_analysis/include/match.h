#ifndef __MATCH_H__
#define __MATCH_H__
#include "token.h"

/* ------- NUMBER  ------ */

enum num_stat_t {
    NUM_ERROR_STAT=-1,
    NUM_S0=0,
    NUM_S1,
    NUM_S2,
    NUM_S3,
    NUM_S4,
    NUM_S5,
    NUM_S6,
    NUM_S7,
};
extern num_stat_t num_move_table[][4];
extern const unsigned num_terminate_stat_table_size;
extern num_stat_t num_terminate_stat_table[];

/**
 *  检测字符串是否为合规的数字字面量
 * @param  {char*} s : 待匹配的字符串
 * @param  {int} len : 待匹配的字符串长度
 * @return {bool}    : 是否匹配数字
 */
bool match_num(const char* s, int len);

/* ------- NUMBER END  ------ */


/* ------- ID ------ */
enum id_stat_t {
    ID_ERROR_STAT=-1,
    ID_S0=0,
    ID_S1,
    ID_S2,
    ID_S3,
};
extern id_stat_t id_move_table[][3];
extern const unsigned id_terminate_stat_table_size;
extern id_stat_t id_terminate_stat_table[];

bool match_id(const char* s, int len);


/* ------- ID END ------ */



#endif // __MATCH_H__

