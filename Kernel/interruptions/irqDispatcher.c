#include <time.h>
#include <stdint.h>

#include <videoDriver.h>

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

void int_21(){
	for(int i = 1; i < 128; i++) {
    	draw_pixel(i, i, 0xffffff);
    }
}