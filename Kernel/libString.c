#include<videoDriver.h>
#include<stdint.h>
#include<libString.h>

void printStringColor(char * string,int length, int colour){
    for (int i = 0; i<length; i++){
        draw_char(string[i],colour);
    }
}

void printStringFrom(char* string,int length, int row, int col, int colour){
    if (colour == -1) colour = 0xFFFFFF;
    if (row == -1 || col == -1 ){
        printStringColor(string,length,colour);
        return;
    }
    for (int i = 0; i<length; i++){
        draw_char_from(string[i],row,col,colour);
    }
}

void printString(char* string,int length){
    printStringColor(string,length,0xFFFFFF);
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

void printOnBaseN(uint64_t value, int base){
    char buffer[10];
    int length = uint_tToBase(value,buffer,base);
    if (length == -1) return;
    printString(buffer,length);
}

void printInt(int number){
    if (number < 0){
        putChar('-');
    }
    printOnBaseN(number,10);
}

void printHex(uint64_t number){
    printOnBaseN(number,16);
}

void printBinary(uint64_t number){
    printOnBaseN(number,2);
}

void putCharColor(char character, int colour){
    draw_char(character,colour);
}

void putChar(char character){ 
    putCharColor(character, 0xFFFFF);
}

int strlen(char* string){ //al final no la use :)
    int count = 0;
    while(string[count]!='\0'){
        count++;
    }
    return count;
}

