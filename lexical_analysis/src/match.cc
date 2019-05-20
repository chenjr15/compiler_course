#include "match.h"

bool match_num(const char* s, int len) {
    const char* head = s;
    num_stat_t current_stat = NUM_S0;
    while ((s-head)<len) {
        switch (*s) {
        case '.':
            current_stat = num_move_table[current_stat][1];
            break;
        case '0':
            current_stat = num_move_table[current_stat][2];
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            current_stat = num_move_table[current_stat][3];
            break;
        default:
            current_stat = NUM_ERROR_STAT;
            break;
        }
        ++s;
        if (current_stat == NUM_ERROR_STAT) {
            return false;
        }
    }
    for (size_t i = 0; i < num_terminate_stat_table_size; i++) {
        if (num_terminate_stat_table[i] == current_stat) {
            return true;
        }

    }
    return false;


}


bool match_id(const char* s, int len) {
    if (len>32) {
        return false;
    }

    const char* head = s;
    id_stat_t current_stat = ID_S0;

    while ((s-head)<len) {
        if ( (*s>='0' && *s <='9')  ) {
            current_stat = id_move_table[current_stat][1];

        } else if ((*s =='_') || ((*s>='a') && (*s <='z')) ||((*s>='A') &&( *s <='Z'))  ) {
            current_stat = id_move_table[current_stat][2];

        } else {
            current_stat =ID_ERROR_STAT;
            return false;
        }

        ++s;
    }

    for (size_t i = 0; i < id_terminate_stat_table_size; i++) {
        if (id_terminate_stat_table[i] == current_stat) {
            return true;
        }
    }
    return false;
}


num_stat_t num_move_table[][4] {
    {NUM_S0,NUM_ERROR_STAT,NUM_S1,NUM_S2},
    {NUM_S1,NUM_S3,NUM_ERROR_STAT,NUM_ERROR_STAT},
    {NUM_S2,NUM_S3,NUM_S5,NUM_S4},
    {NUM_S3,NUM_ERROR_STAT,NUM_S7,NUM_S6},
    {NUM_S4,NUM_S3,NUM_S5,NUM_S4},
    {NUM_S5,NUM_S3,NUM_S5,NUM_S4},
    {NUM_S6,NUM_S3,NUM_S7,NUM_S6},
    {NUM_S7,NUM_ERROR_STAT,NUM_S7,NUM_S6},
};
const unsigned num_terminate_stat_table_size = 5;
num_stat_t num_terminate_stat_table[] = {
    // NUM_S0,
    NUM_S1,
    NUM_S2,
    // NUM_S3,
    NUM_S4,
    NUM_S5,
    NUM_S6,
    // NUM_S7,
};


id_stat_t id_move_table[][3]= {
    {ID_S0,ID_ERROR_STAT,ID_S1},
    {ID_S1,ID_S2,ID_S3},
    {ID_S2,ID_S2,ID_S3},
    {ID_S3,ID_S2,ID_S3}

};
const unsigned id_terminate_stat_table_size = 3;
id_stat_t id_terminate_stat_table[] {
    ID_S1,ID_S2,ID_S3
};
