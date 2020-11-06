#include <types.h>
#include <lib64.h>
#include <string.h>
#include <stdint.h>

#define TIME_SYSCALL 10
#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define DRAW_SYSCALL 2
#define INFO_REG 8
#define MEM_DUMP 9
#define CLEAR_SYSCALL 3
#define ADD_ALARM 11
#define REMOVE_ALARM 12

int read(char * buffer, int length){
    _syscall(READ_SYSCALL, length, buffer);
    return 0; //Deberia retornar los caracteres que pudo leer
}

void write(char * buffer, int row, int col, int color) { 
    int length = strlen(buffer);
    _syscall(WRITE_SYSCALL, length, buffer, row, col, color);
}

void draw(int * matrix, int row, int col, int rows, int columns) {
    _syscall(DRAW_SYSCALL, matrix, row, col, rows, columns);
}

void clearScreen(){
    _syscall(CLEAR_SYSCALL);
}

void getTime(date myDate){
    _syscall(TIME_SYSCALL, myDate);
}

void getRegisters(uint64_t * registers) {
    _syscall(INFO_REG, registers);
}

void memoryDump(char * dir, char * dump) {
    _syscall(MEM_DUMP, dir, dump);
}

int addAlarm(void (*func) (void), int ticks){
    return _syscall(ADD_ALARM, func, ticks);
}

void removeAlarm(int index){
    _syscall(REMOVE_ALARM, index);
}
