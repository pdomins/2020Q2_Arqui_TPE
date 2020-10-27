#include <time.h>
#include <stdint.h>
#include <keyboardDriver.h>
#include <videoDriver.h>

#include <lib.h>

static void int_20();
static void int_21();


void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21();
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}
static int par = 0;
void int_21(){
	keyboard_management();
	char character [1];
	if(par%2==0) {
		call80(0, 1, character);
		call80(1, 1, character);
	}
	par++;
}