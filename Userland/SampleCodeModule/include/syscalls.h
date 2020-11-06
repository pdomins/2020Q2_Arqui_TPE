#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <types.h>
#include <stdint.h>

int read(char * buffer, int length);
void write(char * buffer, int row, int col, int color);
void draw(int * matrix, int row, int col, int rows, int columns);
void getTime(date myDate);
void getRegisters(uint64_t * registers);
void memoryDump(char * dir, char * dump);
void clearScreen();
int addAlarm(void (*func) (void), int ticks);
#endif