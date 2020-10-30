#ifndef LIB64_H
#define LIB_64_H
#include <types.h>
#include <stdint.h>

/** Estas se van, como Macri
void sysRead(int length, char* readArray);
void sysWrite(int length, char* writeArray);
void sysTime(date myDate);**/

void _syscall(uint64_t syscall, ...);

#endif