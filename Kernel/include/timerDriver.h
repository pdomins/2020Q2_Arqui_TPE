#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

typedef struct dateInfo {
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;

} dateInfo;

typedef struct dateInfo *date;

void getLocalDate(date myDate);

#endif