#include <chessVisual.h>
#include <chess.h>
#include <standardIO.h>
#include <syscalls.h>
#include <maths.h>
#include <string.h>

#define DIM 8
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8

#define statusLine 736
#define commandLine 752

extern int board[8][8][3];
int rotation = 0;

void printBoard(){
    int original_s = 16; //Size de la font
    int scaled_s = 80; //Size de los cuadrados 
    int initial_x = 32; //Posicion inicial del tablero
    int initial_y = 32; //Posicion inicial del tablero

    char * pawn  = {
             "________________"
             "________________"
             "________________"
             "________________"
             "________________"
             "________________"
             "_______XX_______"
             "______XXXX______"
             "_____XXXXXX_____"
             "______XXXX______"
             "_____XXXXXX_____"
             "______XXXX______"
             "______XXXX______"
             "_____XXXXXX_____"
             "____XXXXXXXX____"
             "________________"
    };

    char * tower = {
            "________________"
            "________________"
            "__XXX_XXXX_XXX__"
            "__XXX_XXXX_XXX__"
            "__XXX_XXXX_XXX__"
            "__XXXXXXXXXXXX__"
            "___XXXXXXXXXX___"
            "____XXXXXXXX____"
            "____XXXXXXXX____"
            "____XXXXXXXX____"
            "____XXXXXXXX____"
            "____XXXXXXXX____"
            "___XXXXXXXXXX___"
            "__XXXXXXXXXXXX__"
            "_XXXXXXXXXXXXXX_"
            "________________"
    };

    char * bishop = {
            "________________"
            "________________"
            "________X_______"
            "______XXXX______"
            "_____X_XXXX_____"
            "____XXX_XXXX____"
            "_____XXX_XX_____"
            "_______XX_______"
            "_______XX_______"
            "______XXXX______"
            "______XXXX______"
            "_____XXXXXX_____"
            "_____XXXXXX_____"
            "_____XXXXXX_____"
            "____XXXXXXXX____"
            "________________"
    };

    char * knight = {
            "________________"
            "________________"
            "____XX__XXX_____"
            "__XXXXXXXXXXX___"
            "_XXXXXXXXX_XXX__"
            "_XXXXXX_XXXXXXX_"
            "_XXXXXX___XXXXX_"
            "_XXXXXXXX___XXX_"
            "__XXXXXXXXX_____"
            "___XXXXXXXXX____"
            "___XXXXXXXXXX___"
            "__XXXXXXXXXXXX__"
            "__XXXXXXXXXXXX__"
            "__XXXXXXXXXXXX__"
            "_XXXXXXXXXXXXXX_"
            "________________"
    };

    char * queen = {
            "________________"
            "______XXXX______"
            "_____XXXXXX_____"
            "____XXXXXXXX____"
            "_____XXXXXX_____"
            "______XXXX______"
            "_____XXXXXX_____"
            "_______XX_______"
            "_______XX_______"
            "_______XX_______"
            "_______XX_______"
            "______XXXX______"
            "______XXXX______"
            "____XXXXXXXX____"
            "___XXXXXXXXXX___"
            "________________"
    };

    char * king = {
            "________________"
            "_______XX_______"
            "_____XXXXXX_____"
            "_______XX_______"
            "____XXXXXXXX____"
            "_____X_XX_X_____"
            "______XXXX______"
            "_______XX_______"
            "______XXXX______"
            "______XXXX______"
            "______XXXX______"
            "______XXXX______"
            "____XXXXXXXX____"
            "___XXXXXXXXXX___"
            "___XXXXXXXXXX___"
            "________________"
    };

    char * baseBoard = {
            "X_X_X_X_"
            "_X_X_X_X"
            "X_X_X_X_"
            "_X_X_X_X"
            "X_X_X_X_"
            "_X_X_X_X"
            "X_X_X_X_"
            "_X_X_X_X"
    };

    /**
     * Impresion de las letra y numeros
     */
    int row = initial_y + scaled_s / 2 - CHAR_HEIGHT; //8 es el char_width;
    int col = initial_x + scaled_s / 2 - CHAR_WIDTH;
    int rightCol = initial_x + scaled_s * DIM + 8;
    int leftCol = initial_x / 2;
    int bottomRow = initial_y + scaled_s * DIM;
    int topRow = 8;
    char buffer[2] = {0};
    switch(rotation) {
        case 0: //Rotacion 0°
            for(int i = 0; i < DIM; i++) {
                *buffer = '0' + DIM - i; //Izquierda y Derecha
                printFrom(buffer, row, leftCol); //Izquierda
                printFrom(buffer, row, rightCol); //Derecha
                *buffer = 'A' + i; //Arriba y Abajo
                printFrom(buffer, topRow, col); //Arriba
                printFrom(buffer, bottomRow, col); //Abajo
                col += scaled_s;
                row += scaled_s;
            }
            break;
        case 1:
            for(int i = 0; i < DIM; i++) {
                *buffer = 'A' + i; //Izquierda y Derecha
                printFrom(buffer, row, leftCol); //Izquierda
                printFrom(buffer, row, rightCol); //Derecha
                *buffer = '1' + i;  //Arriba y Abajo
                printFrom(buffer, topRow, col); //Arriba
                printFrom(buffer, bottomRow, col); //Abajo
                col += scaled_s;
                row += scaled_s;
            }
            break;
        case 2:
            for(int i = 0; i < DIM; i++) {
                *buffer = '1' + i;; //Izquierda y Derecha
                printFrom(buffer, row, initial_x / 2); //Izquierda
                printFrom(buffer, row, rightCol); //Derecha
                *buffer = 'A' + DIM - 1 - i;; //Arriba y Abajo
                printFrom(buffer, topRow, col); //Arriba
                printFrom(buffer, bottomRow, col); //Abajo
                col += scaled_s;
                row += scaled_s;
            }
            break;
        case 3:
            for(int i = 0; i < DIM; i++) {
                *buffer = 'A' + DIM - 1 - i; //Izquierda y Derecha
                printFrom(buffer, row, leftCol); //Izquierda
                printFrom(buffer, row, rightCol); //Derecha
                *buffer = '0' + DIM - i; //Arriba y Abajo
                printFrom(buffer, topRow, col); //Arriba
                printFrom(buffer, bottomRow, col); //Abajo
                col += scaled_s;
                row += scaled_s;
            }
            break;
    }

    /**
     * Impresión del tablero
     */
    int matrix[scaled_s * scaled_s];
    char * aux = baseBoard;

    int x = initial_x;
    int y = initial_y;
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            int iAux = i;
            int jAux = j;
            rotateIndex(&iAux, &jAux, DIM, rotation);
            scaleMatrix(aux + iAux * DIM + jAux, matrix, 1, scaled_s, BEIGE, BROWN);
            draw(matrix, y, x, scaled_s, scaled_s);
            x += scaled_s;
        }
        y += scaled_s;
        x = initial_x;
    } 

    /**
     * Colocacion de las piezas
    **/
    for(int i = 0 ; i < 8 ; i++) {
        for(int j = 0 ; j < 8 ; j++) {
            if (board[i][j][PIECE] != 0) {
                switch (board[i][j][PIECE]) {
                    case WHITE_KING:
                        scaleMatrix(king, matrix, original_s, scaled_s, WHITE, -1);
                        break;
                    case WHITE_QUEEN:
                        scaleMatrix(queen, matrix, original_s, scaled_s, WHITE, -1);
                        break;
                    case WHITE_BISHOP:
                        scaleMatrix(bishop, matrix, original_s, scaled_s, WHITE, -1);
                        break;
                    case WHITE_KNIGHT:
                        scaleMatrix(knight, matrix, original_s, scaled_s, WHITE, -1);
                        break;
                    case WHITE_ROOK:
                        scaleMatrix(tower, matrix, original_s, scaled_s, WHITE, -1);
                        break;
                    case WHITE_PAWN:
                        scaleMatrix(pawn, matrix, original_s, scaled_s, WHITE, -1);
                        break;
                    case BLACK_KING:
                        scaleMatrix(king, matrix, original_s, scaled_s, BLACK, -1);
                        break;
                    case BLACK_QUEEN:
                        scaleMatrix(queen, matrix, original_s, scaled_s, BLACK, -1);
                        break;
                    case BLACK_BISHOP:
                        scaleMatrix(bishop, matrix, original_s, scaled_s, BLACK, -1);
                        break;
                    case BLACK_KNIGHT:
                        scaleMatrix(knight, matrix, original_s, scaled_s, BLACK, -1);
                        break;
                    case BLACK_ROOK:
                        scaleMatrix(tower, matrix, original_s, scaled_s, BLACK, -1);
                        break;
                    case BLACK_PAWN:
                        scaleMatrix(pawn, matrix, original_s, scaled_s, BLACK, -1);
                        break;
                }
                int iAux = i;
                int jAux = j;
                rotateIndex(&iAux, &jAux, DIM, rotation);
                draw(matrix, scaled_s * iAux + initial_y, jAux * scaled_s + initial_x, scaled_s, scaled_s);
            }
        }
    }
}

void printTime(int secondsWhite, int secondsBlack){
    int timeDiff = abs(secondsBlack-secondsWhite);
    int minWhite = secondsWhite / 60;
    secondsWhite %= 60;
    int minBlack = secondsBlack/ 60;
    secondsBlack %= 60;
    int color_time = 0xffc32b;
    int color_diff = 0x38ad34;
    int cursor = 40;
    char aux[22] = {0};
    for(int i = 0; i < 22 - 1 ; i++){
        aux[i]= ' ';
    }
    aux[5] = ':'; aux[18] = ':';
    itoa(minWhite, aux + 3, 2);
    itoa(secondsWhite, aux + 6, 2);
    itoa(minBlack, aux + 16, 2);
    itoa(secondsBlack, aux + 19, 2);   
    printcFrom(aux, cursor, 740, color_time);
    /*printcFrom(aux, cursor, 764, color_time);
    printcFrom(":", cursor, 780, color_time);
    printcFrom(aux,cursor,788,color_time);
    
    printcFrom("        ", cursor, 804, color_time);
    printcFrom(aux, cursor, 764, color_time);

    printcFrom(aux,cursor,892,color_time);*/
    cursor += CHAR_HEIGHT;
    char difference[16] = {0};
    for(int i = 0; i < 16 - 1; i++) {
        difference[i] = ' ';
    }
    difference[9]='+';
    difference[12]=':';
    itoa(timeDiff / 60, difference + 10, 2);
    itoa(timeDiff % 60, difference + 13, 2);
    printcFrom(difference,cursor,740,color_diff);
}
extern char whiteMoves[50][5];
extern char blackMoves[50][5];
int color_log = 0xadadad;
     char * arrowFont = {
            /*"_________"
            "_________"
            "____X____"
            "___XXX___"
            "__XXXXX__"
            "_XXXXXXX_"
            "XXXXXXXXX"
            "_________"
            "_________"*/
            "______X__"
            "_____XX__"
            "____XXX__"
            "___XXXX__"
            "__XXXXX__"
            "___XXXX__"
            "____XXX__"
            "_____XX__"
            "______X__"
    };

    int arrow[9*9];

    char * delete = {
            "_________"
            "_________"
            "_________"
            "_________"
            "_________"
            "_________"
            "_________"
            "_________"
            "_________"
    };

    int deletion[9*9];

int logCursor;
int init_log_row;
extern int movesWhite;
extern int movesBlack;

void printLog(){
    logCursor = 24;
    int color_log = 0xadadad;
    init_log_row = 80;
        

    printcFrom("Player 1        Player 2", (logCursor%704), 740, color_log); 
    logCursor += (CHAR_HEIGHT * 3);
    logCursor += 16;

    for (int i = 0, log = logCursor; i < movesWhite; i++)
    {
        printcFrom(whiteMoves[i],(log%704), 740+4*8, color_log);
        log+=16; init_log_row+=16;
    }
    for (int i = 0; i < movesBlack; i++)
    {
        printcFrom(blackMoves[i],(logCursor%704), 740+16*8, color_log);
        logCursor+=16; 

    }

    scaleMatrix(arrowFont, arrow, 9, 9, color_log, -1);
    draw(arrow, init_log_row, 956, 9, 9);    
}

void updateLog(char *buffer,int turn){
    if(turn%2==0){
        printcFrom(buffer, (logCursor%704), 740+4*8, color_log);
        printcFrom("It's player 2 turn",statusLine, 0, color_log);
        scaleMatrix(delete, deletion, 9, 9, -1, 0x0);
        scaleMatrix(arrowFont, arrow, 9, 9, color_log, -1);
        draw(deletion, init_log_row, 956, 9, 9);
        draw(arrow, init_log_row+=16, 956, 9, 9);

    }else{
        printcFrom(buffer,(logCursor%704), 740+16*8, color_log); logCursor+=16;
        printcFrom("It's player 1 turn", statusLine, 0, 0xFFFFFF);
    }
}


void rotate() {
    rotation++;
    rotation %= 4;
}