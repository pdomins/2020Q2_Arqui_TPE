#ifndef STRING_H
#define STRING_H
#include<types.h>

void itoa(int value, char* buffer, int length);
void dateToString(date myDate,char *buffer,char separator, int length);
char* strcpy(char *destination, char *source);
void println(char *toPrint);
int strlen(char* string);
#endif