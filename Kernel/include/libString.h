#ifndef LIB_STRING_H
#define LIB_STRING_H
#include <stdint.h>

    void printString(char* string,int length);
    void printStringColor(char * string,int length, int colour);
    void printStringFrom(char* string,int length, int row, int col, int colour);
    void printInt(int number);
    void printHex(uint64_t number); //esta bueno para imprimir registros y posiciones de memoria
    void printBinary(uint64_t number);
    void putChar(char character);
    void putCharColor(char character, int colour);
    int strlen(char* string);

#endif