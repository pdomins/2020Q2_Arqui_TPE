#include <lib.h>
#include <timerDriver.h>

#define UNI 15
#define DEC 240

void getLocalDate(date myDate) {
    int sec_bcd = getSeconds();
    int min_bcd = getMinutes();
    int hour_bcd = getHours();
    int day_bcd = getDay();
    int month_bcd = getMonth();
    int year_bcd = getYear();

    myDate->day = ((day_bcd & DEC) >> 4) * 10;
    myDate->day += (day_bcd & UNI);

    myDate->month = ((month_bcd & DEC) >> 4) * 10;
    myDate->month += (month_bcd & UNI);

    myDate->year = ((year_bcd & DEC) >> 4) * 10;
    myDate->year += (year_bcd & UNI);

    myDate->seconds = ((sec_bcd & DEC) >> 4) * 10;
    myDate->seconds += (sec_bcd & UNI);

    myDate->minutes = ((min_bcd & DEC) >> 4) * 10;
    myDate->minutes += (min_bcd & UNI);

    myDate->hour = ((hour_bcd & DEC) >> 4) * 10;
    myDate->hour += (hour_bcd & UNI);
}