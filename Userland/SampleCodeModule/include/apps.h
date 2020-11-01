#ifndef APPS_H
#define APPS_H
#include <stdint.h>

#define PROGRAMS 5

typedef struct{
    char name[10];
    void(*f)(int, char [][25]);
    char description[200];
}programs;

extern programs commands[PROGRAMS];

void infoReg(int args, char argv[][25]);
void printMem(int args, char argv[][25]);
void time(int args, char argv[][25]);
void showApps(int args, char argv[][25]);
void chess(int args, char argv[][25]);
void throwDivZero();




#endif