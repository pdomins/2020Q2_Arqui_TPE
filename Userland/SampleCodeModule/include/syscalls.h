#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <types.h>
#include <stdint.h>

int read(char *buffer, int length);

int write(char *buffer, int row, int col, int color);

void draw(int *matrix, int row, int col, int rows, int columns);

void clearScreen();

void getTime(date myDate);

void getRegisters(uint64_t *registers);

void memoryDump(char *dir, char *dump);

void setAlarm(void (*func)(void), int flag);

int getHeight();

int getWidth();

#endif