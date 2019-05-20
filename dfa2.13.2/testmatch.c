#include <stdio.h>
#include <stdbool.h>
char status[][2] ={
    // A
    {'B','A'},
    // B
    {'D','E'},
    // C 占位符
    {'0','0'},
    // D
    {'F','G'},
    // E
    {'H','I'},
    // F
    {'F','G'},
    // G
    {'H','I'},
    // H
    {'D','E'},
    // I
    {'B','A'},

};
char move(char now,char input){
    return status[now-'A'][input-'a'];
    
}
bool isExitStatus(char now){
    char* exit_s = "FGHI";
    while((*exit_s)&& (*exit_s != now ))exit_s++;
    return (*exit_s != 0);
}
bool match(char* s){
    char status='A';
    while(*s){
        status = move(status,*s);
        *s++;
    }
    return isExitStatus(status);
}

int main(){
    char* _testcase[]={
        "abb",
        "aba",
        "abab",
        "baa",
        "baaa",
        0
    };
    char** testcase = _testcase;
    while(*testcase){
        printf("Testing: %s result: %s\n", *testcase, match(*testcase) ? "matched" : "MISMATCH");
        testcase++;
    }
    
    
}