#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timerDriver.h>
#include <libString.h>

int readHandler(int length, char* toRead);
int writeHandler(int length, char* toWrite, int row, int col);
void getTime(date myDate);


void syscallDispatcher(uint64_t call, uint64_t firstP, uint64_t secondP, uint64_t thirdP, uint64_t fourthP) {
	switch (call) {
		case 0:
			readHandler((int)firstP, (char*) secondP); //0 read
			break;
		case 1:
			writeHandler((int)firstP, (char*) secondP,(int) thirdP, (int) fourthP); //1 write
			break;
		case 10: 
			getTime((date) firstP);
			break;
	}
	return;
}

int readHandler(int length, char* toRead){
    readBuffer(length, toRead);
    return 0;
}

int writeHandler(int length, char* toWrite, int row, int col){
	printStringFrom(toWrite,row,col);
    return 0;
}

void getTime(date myDate){
	getLocalDate(myDate);
}
