#ifndef LIB_STRING_H
#define LIB_STRING_H
#include <stdint.h>

    void printString(char* string);
    void printStringColor(char * string, int colour);
    void printStringFrom(char* string, int row, int col);
    void printInt(int number);
    void printHex(uint64_t number); //esta bueno para imprimir registros y posiciones de memoria
    void printBinary(uint64_t number);
    void println(char* string);
    void putChar(char character);
    void putCharColor(char character, int colour);
    void drawMatrix(char** matrix, int rows, int columns);
    int strlen(char* string);

#endif