#ifndef STRING_H
#define STRING_H
#include <types.h>
#include <stdint.h>

void itoa(int value, char* buffer, int length);
void dateToString(date myDate,char *buffer,char separator, int length);
char* strcpy(char *destination, char *source);
int strlen(char* string);
int strcmp(char* stringA, char* stringB);
int strtoks(char*string,char delimiter, char buffer[][25]);
void turnToBaseN(uint64_t value, int base, char *buffer, int bufferLength);
uint64_t stringToInt(char * num);
#endif