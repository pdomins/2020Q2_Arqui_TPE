#ifndef STRING_H
#define STRING_H
#include <types.h>

void itoa(int value, char* buffer, int length);
void dateToString(date myDate,char *buffer,char separator, int length);
char* strcpy(char *destination, char *source);
int strlen(char* string);
int strcmp(char* stringA, char* stringB);
int strtoks(char*string,char delimiter, char buffer[][25]);
#endif