#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>

static int readHandler();
static int writeHandler();


void syscallDispatcher(uint64_t call, uint64_t rsi, uint64_t rdx ) {
	switch (call) {
		case 0:
			readHandler((int)rsi, (char*) rdx); //0 read
			break;
		case 1:
			writeHandler((int)rsi, (char*) rdx); //1 write
			break;
	}
	return;
}

int readHandler(int length, char* toRead){
    readBuffer(toRead);
    return 0;
}

int writeHandler(int length, char* toWrite){
    draw_char(*toWrite, 15,15, 0x1FFFFF);
    return 0;
}

