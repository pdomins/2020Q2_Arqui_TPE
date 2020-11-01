#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timerDriver.h>
#include <library.h>


#define TIME_SYSCALL 10
#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define PRINT_MEM 50

int readHandler(int length, char* toRead);
int writeHandler(int length, char* toWrite, int row, int col,int color);
void getTime(date myDate);


int syscallDispatcher(uint64_t call, uint64_t firstP, uint64_t secondP, uint64_t thirdP, uint64_t fourthP,uint64_t fifthP) {
	switch (call) {
		case READ_SYSCALL:
			return readHandler((int)firstP, (char*) secondP); // 0 read
		case WRITE_SYSCALL:
			return writeHandler((int)firstP, (char*) secondP,(int) thirdP, (int) fourthP, (int) fifthP); // 1 write
		case TIME_SYSCALL: 
			getTime((date) firstP);
			return 0;
		default:
			return -1;
	}
	return -1;
}

int readHandler(int length, char* toRead){
    return readBuffer(length, toRead);
}

int writeHandler(int length, char* toWrite, int row, int col, int color){
	return printStringFrom(toWrite,length,row,col,color);
}

void getTime(date myDate){
	getLocalDate(myDate);
}
