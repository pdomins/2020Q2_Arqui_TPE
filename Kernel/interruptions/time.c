#include <time.h>
#include <stdint.h>

#define MAX_DIM 5

typedef struct time
{
	void (*f) (void);
	int elapse;
}functions;

functions toApply[5] = {0};
int dimVec = 0;

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

int addFunc(void (*func) (void), int crit){
	if(dimVec < MAX_DIM){
		toApply[dimVec++].f = func;
		toApply[dimVec++].elapse = crit;
		return dimVec - 1;
	}
	return -1;
}