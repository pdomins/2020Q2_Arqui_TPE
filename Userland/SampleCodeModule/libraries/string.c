#include <string.h>
#include <types.h>
#include <syscalls.h>

#define IS_DIGIT(c) (c >= '0' && c <= '9')


void itoa(int value, char *buffer, int length) {
    for (int i = 0; i < length; i++) {
        buffer[length - i - 1] = value % 10 + '0';
        value /= 10;
    }
}

void dateToString(date myDate, char *buffer, char separator, int length) {

    itoa(myDate->day, buffer, 2);
    buffer[2] = separator;
    itoa(myDate->month, buffer + 3, 2);
    buffer[5] = separator;
    itoa(myDate->year, buffer + 6, 2);
    buffer[8] = ' ';
    itoa(myDate->hour, buffer + 9, 2);
    buffer[11] = ':';
    itoa(myDate->minutes, buffer + 12, 2);
    buffer[14] = ':';
    itoa(myDate->seconds, buffer + 15, 2);
    buffer[18] = 0;
}

char *strcpy(char *destination, char *source) {
    char *start = destination;

    while (*source != 0) {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = 0;
    return start;
}

int strlen(char *string) {
    int count = 0;
    while (string[count] != 0) {
        count++;
    }
    return count;
}

int strcmp(char *stringA, char *stringB) {
    int i = 0;
    for (; stringA[i] == stringB[i]; i++) {
        if (stringA[i] == 0)
            return 0;
    }
    return stringA[i] - stringB[i];
}

int strtoks(char *string, char delimiter, char buffer[][25]) {
    int i = 0;
    int j = 0, z = 0;
    while (string[i] != 0) {
        z = 0;
        while (string[i] != delimiter && string[i] != 0) {
            buffer[j][z++] = string[i++];
        }
        buffer[j][z] = 0;
        if (z != 0) j++;
        i++;
    }
    return j; //Cantidad de tokens
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

//Convierte un string en hexa a un int. 
uint64_t stringToInt(char *num) {
    toMayus(num);
    uint64_t value = 0;
    for (int i = 0; num[i] != '\0'; i++) {
        value *= 16;
        value += IS_DIGIT(num[i]) ? (num[i] - '0') : (num[i] - 'A' + 10);
    }
    return value;
}

void toMayus(char *num) {
    int i = 0;
    while (num[i] != 0) {
        if (num[i] >= 'a' && num[i] <= 'z') {
            num[i] -= ('a' - 'A');
        }
        i++;
    }
}