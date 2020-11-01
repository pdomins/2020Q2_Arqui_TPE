#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <types.h>

int read(char * buffer, int length);
void write(char * buffer, int row, int col, int color);
void getTime(date myDate);

#endif