#include <time.h>
#include <stdint.h>

static unsigned long ticks = 0;

void (*function) (void);
int enabled = 0;

void timer_handler() {
	ticks++;
	if(enabled){
		function();
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void addFunc(void (*func) (void), int flag){
	function = func;
	enabled = flag;
}