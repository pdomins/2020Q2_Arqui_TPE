#ifndef KEY_DRIVER_H
#define KEY_DRIVER_H

#include <stdint.h>

void keyboard_management(uint64_t *rsp);

int readBuffer(int length, char *toWrite);

void takeSnapshot(uint64_t *rsp);

void fillWithRegs(uint64_t *buffer);

#endif