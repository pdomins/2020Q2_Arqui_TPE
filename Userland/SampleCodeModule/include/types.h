#ifndef TYPES_H
#define TYPES_H

#define REGISTERS_AMOUNT 19
/**
 * Definición de tipos que comparten userland y kernel.
**/

typedef struct dateInfo {
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;

} dateInfo;

typedef struct dateInfo *date;


#endif