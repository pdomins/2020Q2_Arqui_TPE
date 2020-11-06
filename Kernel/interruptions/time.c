#include <time.h>
#include <stdint.h>

static unsigned long ticks = 0;

void (*function) (void);
int elapse;

void timer_handler() {
	ticks++;
	if(function != 0){
		if( (seconds_elapsed() % elapse) == 0 )
			function();
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void addFunc(void (*func) (void), int crit){
	function = func;
	elapse = crit;
}