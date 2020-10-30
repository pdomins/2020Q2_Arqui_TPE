#include <types.h>
#include <lib64.h>
#include <string.h>

#define TIME_SYSCALL 10
#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define PRINTLN_SYSCALL 2

char getChar(int lengt){
    char buffer [1] = {0};
    _syscall(READ_SYSCALL, 1, buffer);
    return *buffer;
}

void print(char * buffer) {
    int length = strlen(buffer);
    _syscall(WRITE_SYSCALL, length, buffer,-1,-1);
}
void printFromPosition(char* buffer, int row, int col){
    int length = strlen(buffer);
    _syscall(WRITE_SYSCALL, length, buffer, row , col);
}
void getTime(date myDate){
    _syscall(TIME_SYSCALL, myDate);
}


void infoReg(){

}

void printMem(){

}
