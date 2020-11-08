#ifndef LIB_64_H
#define LIB_64_H

#include <types.h>
#include <stdint.h>

int _syscall(uint64_t syscall, ...);

void invalidOpCode();

#endif