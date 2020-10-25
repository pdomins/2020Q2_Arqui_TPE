#include <keyboardDriver.h>
#include <lib.h>

#include <videoDriver.h>

#define KEYS 59 // o 60? continuara... TAL VEZ? :D
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

#define SPECIAL_KEY (ESC||BACKSPACE||TAB||ENTER||L_CTRL||L_SHIFT||R_SHIFT||L_ALT||CAPS_LOCK)

#define IS_ALPHA(c) c >= 'a' && c <= 'z'  


char buffer[5];
int prev = 0;
int curr = 0; 
static char pressCodes[KEYS][2] = 
{{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'},
{'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, 
{'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'},
{'\b','\b'}, {'\t','\t'}, {'q', 'Q'}, {'w', 'W'},{'e', 'E'},
{'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, 
{'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'},
{0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'},
{'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'},
{';', ':'}, {'\'', '\"'}, {'`', '~'}, {0, 0}, {'\\', '|'},
{'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'},
{'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'},
{0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static int shiftPressed = 0;
static int blockMayus = 0;

int isSpecialKey(int scanCode){
    return scanCode == ESC || scanCode == BACKSPACE || scanCode == ENTER || scanCode == L_CTRL ||
            scanCode == L_SHIFT || scanCode == R_SHIFT || scanCode == L_ALT || scanCode == CAPS_LOCK;
}


void keyboard_management(){
    int scan_code = read_keyboard();
    prev = curr;
    switch(scan_code) {
        case L_SHIFT:
        case R_SHIFT:
            shiftPressed = 1; 
            break;
        case L_SHIFT + RELEASED_KEY:
        case R_SHIFT + RELEASED_KEY:
            shiftPressed = 0; 
            break;
        case CAPS_LOCK:
            blockMayus = blockMayus? 0:1;
            break;
        case L_CTRL:   
        case L_ALT:
            break;
    }
    if(scan_code <= MAX_PRESSED_KEY && !isSpecialKey(scan_code)) {
        int secondChar = shiftPressed;
        if(IS_ALPHA(pressCodes[scan_code][0])){
            secondChar = blockMayus ? 1 - shiftPressed: shiftPressed;
        }
        buffer[curr++] = pressCodes[scan_code][secondChar];
        curr = curr % 5;
        printLatest();
    }
}

static int i = 0;
static int j = 0;
void printLatest(){
    char toPrint = buffer[prev];
    draw_char(toPrint, 0+j , 0+i , 0xeb8334);
    i+=8;

    if(i >= 1024) {
        i = 0;
        j += 16;
    }
    if(j >= 768) {
        j = 0;
    }
}