#include <lib.h>
#include <timerDriver.h>

#define UNI 15
#define DEC 240

void getLocalTime(char* local_time){ //returns hh:mm:ss
    int pos = 0;
    int sec_bcd = getSeconds();
    int min_bcd = getMinutes();
    int hour_bcd = getHours();
    int day_bcd = getDay();

    local_time[pos++] = ((day_bcd & DEC)>>4) + '0';
    local_time[pos++] = (day_bcd & UNI) + '0';
    local_time[pos++] = ((hour_bcd & DEC)>>4) + '0';
    local_time[pos++] = (hour_bcd & UNI) + '0';
    local_time[pos++] = ((min_bcd & DEC)>>4) + '0';
    local_time[pos++] = (min_bcd & UNI) + '0';
    local_time[pos++] = ((sec_bcd & DEC)>>4) + '0';
    local_time[pos++] = (sec_bcd & UNI) + '0';
    local_time[pos] = '\0';
}
