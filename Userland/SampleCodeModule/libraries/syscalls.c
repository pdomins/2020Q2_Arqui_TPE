#include <types.h>
#include <lib64.h>
#include <string.h>
#include <stdint.h>

#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define DRAW_SYSCALL 2
#define CLEAR_SYSCALL 3
#define INFO_REG 8
#define MEM_DUMP 9
#define TIME_SYSCALL 10
#define SET_ALARM 11
#define SCREEN_HEIGHT 12
#define SCREEN_WIDTH 13

int read(char *buffer, int length) {
    return _syscall(READ_SYSCALL, length, buffer);
}

int write(char *buffer, int row, int col, int color) {
    int length = strlen(buffer);
    return _syscall(WRITE_SYSCALL, length, buffer, row, col, color);
}

void draw(int *matrix, int row, int col, int rows, int columns) {
    _syscall(DRAW_SYSCALL, matrix, row, col, rows, columns);
}

void clearScreen() {
    _syscall(CLEAR_SYSCALL);
}

void getTime(date myDate) {
    _syscall(TIME_SYSCALL, myDate);
}

void getRegisters(uint64_t *registers) {
    _syscall(INFO_REG, registers);
}

void memoryDump(char *dir, char *dump) {
    _syscall(MEM_DUMP, dir, dump);
}

void setAlarm(void (*func)(void), int flag) {
    _syscall(SET_ALARM, func, flag);
}

int getHeight() {
    return _syscall(SCREEN_HEIGHT);
}

int getWidth() {
    return _syscall(SCREEN_WIDTH);
}
