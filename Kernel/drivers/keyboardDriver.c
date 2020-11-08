#include <keyboardDriver.h>
#include <lib.h>
#include <registers.h>
#include <stdint.h>

#define KEYS 59
#define MIN_SCAN 0
#define MAX_SCAN 59

#define ESC 0x01
#define BACKSPACE 0x0E
#define TAB 0x0F
#define ENTER 0x1C
#define L_CTRL 0x1D
#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define L_ALT 0x38
#define CAPS_LOCK 0x3A
#define RELEASED_KEY 0x80
#define MAX_PRESSED_KEY 0X7F

#define IS_ALPHA(c) c >= 'a' && c <= 'z'

#define BUFFER_SIZE 10

char buffer[BUFFER_SIZE] = {0};
int prev = 0;
int curr = 0;
static char pressCodes[KEYS][2] =
        {{0,    0},
         {0,    0},
         {'1',  '!'},
         {'2',  '@'},
         {'3',  '#'},
         {'4',  '$'},
         {'5',  '%'},
         {'6',  '^'},
         {'7',  '&'},
         {'8',  '*'},
         {'9',  '('},
         {'0',  ')'},
         {'-',  '_'},
         {'=',  '+'},
         {'\b', '\b'},
         {'\t', '\t'},
         {'q',  'Q'},
         {'w',  'W'},
         {'e',  'E'},
         {'r',  'R'},
         {'t',  'T'},
         {'y',  'Y'},
         {'u',  'U'},
         {'i',  'I'},
         {'o',  'O'},
         {'p',  'P'},
         {'[',  '{'},
         {']',  '}'},
         {'\n', '\n'},
         {0,    0},
         {'a',  'A'},
         {'s',  'S'},
         {'d',  'D'},
         {'f',  'F'},
         {'g',  'G'},
         {'h',  'H'},
         {'j',  'J'},
         {'k',  'K'},
         {'l',  'L'},
         {';',  ':'},
         {'\'', '\"'},
         {'`',  '~'},
         {0,    0},
         {'\\', '|'},
         {'z',  'Z'},
         {'x',  'X'},
         {'c',  'C'},
         {'v',  'V'},
         {'b',  'B'},
         {'n',  'N'},
         {'m',  'M'},
         {',',  '<'},
         {'.',  '>'},
         {'/',  '?'},
         {0,    0},
         {0,    0},
         {0,    0},
         {' ',  ' '},
         {0,    0}};

static int shiftPressed = 0;
static int blockMayus = 0;
static int ctrlPressed = 0;
uint64_t registers[TOTAL_REGISTERS] = {0};

int isSpecialKey(int scanCode);

void preserveRegisters();

void takeSnapshot(uint64_t *rsp);

int isSpecialKey(int scanCode) {
    return scanCode == ESC || scanCode == L_CTRL ||
           scanCode == L_SHIFT || scanCode == R_SHIFT || scanCode == L_ALT || scanCode == CAPS_LOCK;
}

void keyboard_management(uint64_t *rsp) {
    int scan_code = read_keyboard();
    prev = curr;
    switch (scan_code) {
        case L_SHIFT:
        case R_SHIFT:
            shiftPressed = 1;
            break;
        case L_SHIFT + RELEASED_KEY:
        case R_SHIFT + RELEASED_KEY:
            shiftPressed = 0;
            break;
        case CAPS_LOCK:
            blockMayus = blockMayus ? 0 : 1;
            break;
        case L_CTRL:
            ctrlPressed = 1;
            break;
        case L_CTRL + RELEASED_KEY:
            ctrlPressed = 0;
            break;
        case L_ALT:
            break;
    }


    if (scan_code <= MAX_PRESSED_KEY && !isSpecialKey(scan_code)) {
        int secondChar = shiftPressed;
        if (IS_ALPHA(pressCodes[scan_code][0])) {
            secondChar = blockMayus ? 1 - shiftPressed : shiftPressed;
        }
        if (ctrlPressed) {
            if (pressCodes[scan_code][secondChar] == 's')
                takeSnapshot(rsp);
            return;
        }
        buffer[curr++] = pressCodes[scan_code][secondChar];
        curr %= BUFFER_SIZE;
    }
}


int leer = 0;

int readBuffer(int length, char *toWrite) {
    for (int i = 0; i < length; i++) {
        if (buffer[leer] == 0) {
            return i;
        }
        toWrite[i] = buffer[leer];
        buffer[leer] = 0;
        leer = (leer + 1) % BUFFER_SIZE;
    }
    return length;
}

void takeSnapshot(uint64_t *rsp) {
    for (int i = 0; i < TOTAL_REGISTERS; i++) {
        registers[i] = rsp[i];
    }
}

void fillWithRegs(uint64_t *buffer) {
    for (int i = 0; i < TOTAL_REGISTERS; i++) {
        buffer[i] = registers[i];
    }
}
