#ifndef LIB_STRING_H
#define LIB_STRING_H

#include <stdint.h>

int printStringFrom(char *string, int length, int row, int col, int colour);

int printError(char *string);

void println(char *string);

void print(char *string);

void printc(char *string, int color);

void printcln(char *string, int color);

void printRegisters(uint64_t *rsp);

int strlen(char *string);

#endif