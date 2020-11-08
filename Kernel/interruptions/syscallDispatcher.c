#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timerDriver.h>
#include <library.h>
#include <time.h>


#define READ_SYSCALL 0
#define WRITE_SYSCALL 1
#define DRAW_SYSCALL 2
#define CLEAR_SYSCALL 3
#define INFO_REG 8
#define MEM_DUMP 9
#define TIME_SYSCALL 10
#define SET_ALARM 11
#define SCREEN_HEIGHT 12
#define SCREEN_WIDTH 13

#define MEM_BYTES 32

int readHandler(int length, char *toRead);

int writeHandler(int length, char *toWrite, int row, int col, int color);

int drawHandler(int *matrix, int row, int col, int rows, int columns);

void getTime(date myDate);

void memDumpHandler(char *dir, char *dump);

void infoRegHandler(uint64_t firstP[]);

void clearScreenHandler();

int screenHeightHandler();

int screenWidthHandler();


int syscallDispatcher(uint64_t call, uint64_t firstP, uint64_t secondP, uint64_t thirdP, uint64_t fourthP,
                      uint64_t fifthP) {
    switch (call) {
        case READ_SYSCALL:
            return readHandler((int) firstP, (char *) secondP); // 0 read
        case WRITE_SYSCALL:
            return writeHandler((int) firstP, (char *) secondP, (int) thirdP, (int) fourthP, (int) fifthP); // 1 write
        case DRAW_SYSCALL:
            return drawHandler((int *) firstP, (int) secondP, (int) thirdP, (int) fourthP, (int) fifthP);
        case TIME_SYSCALL:
            getTime((date) firstP);
            return 0;
        case INFO_REG:
            infoRegHandler((uint64_t *) firstP);
            return 0;
        case MEM_DUMP:
            memDumpHandler((char *) firstP, (char *) secondP);
            return 0;
        case CLEAR_SYSCALL:
            clearScreenHandler();
            return 0;
        case SET_ALARM:
            addFunc((void *) firstP, secondP);
            return 0;
        case SCREEN_HEIGHT:
            return screenHeightHandler();
        case SCREEN_WIDTH:
            return screenWidthHandler();
        default:
            return -1;
    }
    return -1;
}

int readHandler(int length, char *toRead) {
    return readBuffer(length, toRead);
}

int writeHandler(int length, char *toWrite, int row, int col, int color) {
    return printStringFrom(toWrite, length, row, col, color);
}

int drawHandler(int *matrix, int row, int col, int rows, int columns) {
    return drawMatrix(matrix, row, col, rows, columns);
}

void getTime(date myDate) {
    getLocalDate(myDate);
}

void memDumpHandler(char *dir, char *dump) {
    for (int i = 0;
         i < MEM_BYTES; i++ ) {
        dump[i] = dir[i];
    }
}

void infoRegHandler(uint64_t firstP[]) {
    fillWithRegs(firstP);
}

void clearScreenHandler() {
    clearScreen();
}

int screenHeightHandler() {
    return screenHeight();
}

int screenWidthHandler() {
    return screenWidth();
}