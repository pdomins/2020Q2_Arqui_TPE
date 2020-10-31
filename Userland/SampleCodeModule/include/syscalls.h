#ifndef SYSCALLS_H
#define SYSCALLS_H
#include<types.h>

char getChar();

void print(char * buffer);

void getTime(date myDate);

void infoReg();

void printMem();
char getChar();
void print(char * buffer);
void printColor(char *buffer, int colour);
void printFromPosition(char* buffer, int row, int col);
void getTime(date myDate);
void infoReg();
void printMem();
#endif