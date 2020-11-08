#include <time.h>
#include <stdint.h>

static unsigned long ticks = 0;

typedef struct function {
    void (*f)(void);

    int enabled;
} function;

function alarm = {0, 0};

void timer_handler() {
    ticks++;
    if (alarm.enabled) {
        alarm.f();
    }
}

int ticks_elapsed() {
    return ticks;
}

int seconds_elapsed() {
    return ticks / 18;
}

void addFunc(void (*func)(void), int flag) {
    alarm.f = func;
    alarm.enabled = flag;
}