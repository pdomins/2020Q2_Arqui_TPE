#include <videoDriver.h>
#include <stdint.h>
#include <library.h>
#include <registers.h>
#include <naiveConsole.h>

#define BUFFER64_BITS 20

int printStringFrom(char* string, int length, int row, int col, int color){
    int printedCharacters = 0;

    if (row == -1 || col == -1 ){
        for (int i = 0; i < length; i++){
            if(draw_char(string[i],color)) {
                printedCharacters++;
            }         
        }
    } else {
        for (int i = 0; i < length; i++){
            if(draw_char_from(string[i],row,col,color)) {
                printedCharacters++;
            }       
        }
    }
    return printedCharacters;
}

int printError(char * string) {
    printcln(string, 0xff0000);
    return 0;

}

void println(char * string){
    print(string);
    print("\n");
}

void print(char * string){
    printStringFrom(string, strlen(string), -1, -1, 0x000000);
}

void printc(char* string, int color){
    printStringFrom(string, strlen(string), -1,-1,color);
}

void printcln(char* string, int color) {
    printc(string, color);
    print("\n");
}

void printRegisters(uint64_t *rsp){
    char buffer[BUFFER64_BITS]={0};
    char regis[][4]={"R15","R14","R13","R12","R11","R10","R9 ","R8 ","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RIP","CS ","FLG","RSP"};

    for (int i = 0; i < TOTAL_REGISTERS; i++){
        printc(regis[i],0xFF0000);
        printc(": ",0xFF0000);
        turnToBaseN(rsp[i], 16, buffer, BUFFER64_BITS);
        println(buffer);
    }
}

int strlen(char * string) { 
    int length = 0;
    while(*string != 0) {
        length++; 
        string++;
    }
    return length;
}