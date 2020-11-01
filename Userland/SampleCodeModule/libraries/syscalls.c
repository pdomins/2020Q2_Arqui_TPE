#include <types.h>
#include <lib64.h>
#include <string.h>

#define TIME_SYSCALL 10
#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define DRAW_SYSCALL 2

int read(char * buffer, int length){
    _syscall(READ_SYSCALL, length, buffer);
    return 0; //Deberia retornar los caracteres que pudo leer
}

void write(char * buffer, int row, int col, int color) { 
    int length = strlen(buffer);
    _syscall(WRITE_SYSCALL, length, buffer, row, col, color);
}

void getTime(date myDate){
    _syscall(TIME_SYSCALL, myDate);
}

