#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void *memset(void *destination, int32_t character, uint64_t length);

void *memcpy(void *destination, const void *source, uint64_t length);

char *cpuVendor(char *result);

int getSeconds();

int getMinutes();

int getHours();

int getDay();

int getMonth();

int getYear();

int read_keyboard();

#endif