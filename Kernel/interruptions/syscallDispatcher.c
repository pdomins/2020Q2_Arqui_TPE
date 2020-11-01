#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timerDriver.h>
#include <library.h>


#define TIME_SYSCALL 10
#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define INFO_REG 8
#define MEM_DUMP 9

#define MEM_BYTES 32

int readHandler(int length, char* toRead);
int writeHandler(int length, char* toWrite, int row, int col,int color);
void getTime(date myDate);
void memDumpHandler(uint64_t * dir, uint64_t * dump);
void infoRegHandler(uint64_t firstP[]);


int syscallDispatcher(uint64_t call, uint64_t firstP, uint64_t secondP, uint64_t thirdP, uint64_t fourthP,uint64_t fifthP) {
	switch (call) {
		case READ_SYSCALL:
			return readHandler((int) firstP, (char*) secondP); // 0 read
		case WRITE_SYSCALL:
			return writeHandler((int) firstP, (char*) secondP,(int) thirdP, (int) fourthP, (int) fifthP); // 1 write
		case TIME_SYSCALL: 
			getTime((date) firstP);
			return 0;
		case INFO_REG:
			infoRegHandler((uint64_t*) firstP);
			return 0;
		case MEM_DUMP:
			memDumpHandler((uint64_t *) firstP, (uint64_t *) secondP);
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

void memDumpHandler(uint64_t * dir, uint64_t * dump) {
	for(int i = 0; i < 4; i++) { //Cambiar el cuatro por defines, seria algo asi como MEM_BYTES / sizeof(uint64_t)
		dump[i] = dir[i];
	}
	return;
}

void infoRegHandler(uint64_t firstP[]){
	fillWithRegs(firstP);
	return;
}
