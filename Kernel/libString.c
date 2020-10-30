#include<videoDriver.h>
#include<stdint.h>
#include<libString.h>

void printStringColor(char * string, int colour){
    for (int i = 0; string[i]!='\0'; i++){
        draw_char(string[i],colour);
    }
}

void printStringFrom(char* string, int row, int col){
    if (row == -1 || col == -1 )
    {
        printString(string);
        return;
    }
    for (int i = 0; string[i]!='\0'; i++){
        draw_char_from(string[i],row,col,0xFFFFFF);
    }
}

void printString(char* string){
    printStringColor(string, 0xFFFFFF);
}

void uint_tToBase(uint64_t value,char* buffer, int base){
    if (base < 2 || base > 26) return;
    char* aux = buffer;
    while (value>0){ //luego de este ciclo el numero me queda en buffer pero invertido
        int r = value%base;
        *aux++ = (r >= 10)?  r + 'A' - 10 : r + '\0';
        value/=base;
    }
    *aux = 0; 

    char *reversed, *ordered; 
    reversed = buffer;
    ordered = aux - 1;
    while (reversed < ordered){ //invierto el string en buffer
        char c = *reversed;
        *reversed = *ordered;
        *ordered = c;
        reversed++;
        ordered--;
    }
}

void printOnBaseN(uint64_t value, int base){
    char buffer[10];
    uint_tToBase(value,buffer,base);
    printString(buffer);
}

void printInt(int number){
    if (number < 0){
        putChar("-");
    }
    printOnBaseN(number,10);
}

void printHex(uint64_t number){
    printOnBaseN(number,16);
}

void printBinary(uint64_t number){
    printOnBaseN(number,2);
}

void println(char* string){
    
    for (int i = 0; string[i]!='\0'; i++)
    {
        draw_char(string[i],0x1FFFFF);
    }
    //mover el puntero a la proxima linea draw_char('\n)?
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

void drawMatrix(char** matrix, int rows, int columns);
