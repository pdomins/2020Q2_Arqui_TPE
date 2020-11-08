#ifndef _TIME_H_
#define _TIME_H_

void timer_handler();

int ticks_elapsed();

int seconds_elapsed();

void addFunc(void (*func)(void), int ticks);

#endif