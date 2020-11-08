#include <naiveConsole.h>

static char buffer[64] = {'0'};
static uint8_t *const video = (uint8_t *) 0xB8000;
static uint8_t *currentVideo = (uint8_t *) 0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

void ncPrint(const char *string) {
    int i;

    for (i = 0; string[i] != 0; i++)
        ncPrintChar(string[i]);
}

void ncPrintChar(char character) {
    *currentVideo = character;
    currentVideo += 2;
}

void ncNewline() {
    do {
        ncPrintChar(' ');
    } while ((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncPrintDec(uint64_t value) {
    ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value) {
    ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value) {
    ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base) {
    turnToBaseN(value, base, buffer, 64);
    ncPrint(buffer);
}

void ncClear() {
    int i;

    for (i = 0; i < height * width; i++)
        video[i * 2] = ' ';
    currentVideo = video;
}

uint64_t turnToBaseN(uint64_t value, int base, char *buffer, int bufferLength) {
    if (base < 2 || base > 26) return -1;

    uint64_t digits = 0;
    int pos = bufferLength - 2;
    //Calculate characters for each digit
    do {
        uint64_t remainder = value % base;
        if ((pos + 1) % 5 == 0) {
            buffer[pos--] = ' ';
        }
        buffer[pos--] = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    } while (value /= base);

    while (pos >= 0) {
        if ((pos + 1) % 5 == 0) {
            buffer[pos--] = ' ';
        }
        buffer[pos--] = '0';
    }
    buffer[bufferLength - 1] = 0;
    return digits;
}