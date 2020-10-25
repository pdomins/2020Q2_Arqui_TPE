#include <keyboardDriver.h>
#include <lib.h>

#include <videoDriver.h>

#define KEYS 59 // o 60?
#define MIN_SCAN 0 MAX_SCAN 59 
char buffer[5];
int prev = 0;
int curr = 0; 
static char pressCodes[KEYS][2] = {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'},
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

void keyboard_management(){
    int scan_code = read_keyboard();
    prev = curr;
    buffer[curr++] = pressCodes[scan_code][0];
    curr = curr % 5;
}

void printLatest(){
    char toPrint = buffer[prev];
    draw_char(toPrint, 10 , 100 , 0xeb8334);
}