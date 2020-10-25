#include <lib.h>
#include <timerDriver.h>

#define UNI 15
#define DEC 240

void getLocalTime(char* local_time){ //returns hh:mm:ss
    int sec_bcd = getSeconds();
    int min_bcd = getMinutes();
    int hour_bcd = getHours();
    int day_bcd = getDay();

    local_time[0] = ((hour_bcd & DEC)>>4) + '0';
    local_time[1] = (hour_bcd & UNI) + '0';
    local_time[2] = ':';
    local_time[3] = ((min_bcd & DEC)>>4) + '0';
    local_time[4] = (min_bcd & UNI) + '0';
    local_time[5] = ':';
    local_time[6] = ((sec_bcd & DEC)>>4) + '0';
    local_time[7] = (sec_bcd & UNI) + '0';
    local_time[8] = '-';
    local_time[9] = ((day_bcd & DEC)>>4) + '0';
    local_time[10] = (day_bcd & UNI) + '0';
    local_time[11] = '\0';
}
