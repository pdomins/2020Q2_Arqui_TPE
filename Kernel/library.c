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