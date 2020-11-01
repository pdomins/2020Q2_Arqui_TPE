#include <videoDriver.h>
#include <stdint.h>
#include <library.h>

int printStringFrom(char* string,int length, int row, int col, int color){
    int printedCharacters = 0;

    if (row == -1 || col == -1 ){
        for (int i = 0; i < length; i++){
            if(draw_char(string[i],color)) {
                printedCharacters++;
            }         
        }
    } else {
        for (int i = 0; i<length; i++){
            if(draw_char_from(string[i],row,col,color)) {
                printedCharacters++;
            }       
        }
    }
    return printedCharacters;
}

int uint_tToBase(uint64_t value,char* buffer, int base){
    if (base < 2 || base > 26) return -1;
    char* aux = buffer;
    while (value>0){ //luego de este ciclo el numero me queda en buffer pero invertido
        int r = value%base;
        *aux++ = (r >= 10)?  r + 'A' - 10 : r + '\0';
        value/=base;
    }
    *aux = 0; 

    char *reversed, *ordered; 
    int  length=0;
    reversed = buffer;
    ordered = aux - 1;
    while (reversed < ordered){ //invierto el string en buffer
        length++;
        char c = *reversed;
        *reversed = *ordered;
        *ordered = c;
        reversed++;
        ordered--;
    }
    return length;
}

void turnToBaseN(uint64_t value, int base, char *buffer){
    int length = uint_tToBase(value,buffer,base);
    if (length == -1) return;
}



