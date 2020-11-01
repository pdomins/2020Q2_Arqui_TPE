#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <types.h>
#include <stdint.h>

int read(char * buffer, int length);
void write(char * buffer, int row, int col, int color);
void getTime(date myDate);
void getRegisters(uint64_t * registers);
void memoryDump(uint64_t * dir, uint64_t * dump);

#endif