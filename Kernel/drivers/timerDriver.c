#include <lib.h>
#include <timerDriver.h>

#define UNI 15
#define DEC 240

int getTime(int num){
    int dec = num & 240;
    dec = dec >> 4;
    int units = num & 15;
    return dec * 10 + units;
}

char* getLocalTime(){ //returns hh:mm:ss
    char local_time[9];
    int sec_bcd = getSeconds();
    int min_bcd = getMinutes();
    int hour_bcd = getHours();

    int seconds = getTime(sec_bcd);
    int mins = getTime(min_bcd);
    int hours = getTime(hour_bcd);

    local_time[0] = ((hour_bcd & DEC)>>4) + '0';
    local_time[1] = (hour_bcd & UNI) + '0';
    local_time[2] = '-';
    local_time[3] = ((min_bcd & DEC)>>4) + '0';
    local_time[4] = (min_bcd & UNI) + '0';
    local_time[5] = '-';
    local_time[6] = ((sec_bcd & DEC)>>4) + '0';
    local_time[7] = (sec_bcd & UNI) + '0';
    local_time[8] = '\0';

    return local_time;
}
