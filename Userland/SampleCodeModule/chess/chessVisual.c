#include <chessVisual.h>
#include <chess.h>
#include <chessFont.h>
#include <standardIO.h>
#include <syscalls.h>
#include <maths.h>
#include <string.h>

#define DIM 8
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8
#define statusLine (getHeight() - CHAR_HEIGHT * 2)
#define commandLine (getHeight() - CHAR_HEIGHT)
#define LOG_MAX_HEIGHT (getHeight() - CHAR_HEIGHT * 2)

extern int board[DIM][DIM][3];
extern int turns;
int rotation = 0; //0 if 0°, 1 if 90°, 2 if 180°, 3 if 270°
int arrow[9 * 9];
int deletion[9 * 9];
int logCursor;
int initLogRow;
extern int movesWhite;
extern int movesBlack;
extern char whiteMoves[50][5];
extern char blackMoves[50][5];

void checkBoundLog();

void printBoard() {
    int original_s = 16; //Size de la font
    int scaled_s = 80; //Size de los cuadrados 
    int initial_x = 32; //Posicion inicial del tablero
    int initial_y = 32; //Posicion inicial del tablero

    /**
     * Impresion de letras y numeros
     */
    int row = initial_y + scaled_s / 2 - CHAR_HEIGHT;
    int col = initial_x + scaled_s / 2 - CHAR_WIDTH;
    int rightCol = initial_x + scaled_s * DIM + 8;
    int leftCol = initial_x / 2;
    int bottomRow = initial_y + scaled_s * DIM;
    int topRow = 8;
    char buffer[2] = {0};
    switch (rotation) {
        case 0: //Rotacion 0°
            for (int i = 0; i < DIM; i++) {
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
            for (int i = 0; i < DIM; i++) {
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
            for (int i = 0; i < DIM; i++) {
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
            for (int i = 0; i < DIM; i++) {
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
    char *aux = baseBoard;

    int x = initial_x;
    int y = initial_y;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
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
    if (turns % 2 == 0) {
        clearLine(statusLine);
        printcFrom("It's player 1 turn", statusLine, 0, color_log);
    } else {
        clearLine(statusLine);
        printcFrom("It's player 2 turn", statusLine, 0, color_log);
    }
}

void printTime(int secondsWhite, int secondsBlack) {
    int timeDiff = abs(secondsBlack - secondsWhite);
    int minWhite = secondsWhite / 60;
    secondsWhite %= 60;
    int minBlack = secondsBlack / 60;
    secondsBlack %= 60;
    int cursor = 40;
    char aux[22] = {0};
    for (int i = 0; i < 22 - 1; i++) {
        aux[i] = ' ';
    }
    aux[5] = ':';
    aux[18] = ':';
    itoa(minWhite, aux + 3, 2);
    itoa(secondsWhite, aux + 6, 2);
    itoa(minBlack, aux + CHAR_HEIGHT, 2);
    itoa(secondsBlack, aux + 19, 2);
    printcFrom(aux, cursor, LOG_MAX_HEIGHT, color_time);
    cursor += CHAR_HEIGHT;
    char difference[CHAR_HEIGHT] = {0};
    for (int i = 0; i < CHAR_HEIGHT - 1; i++) {
        difference[i] = ' ';
    }
    difference[9] = '+';
    difference[12] = ':';
    itoa(timeDiff / 60, difference + 10, 2);
    itoa(timeDiff % 60, difference + 13, 2);
    printcFrom(difference, cursor, LOG_MAX_HEIGHT, color_diff);
}

void printLog() {
    logCursor = 24;
    initLogRow = 80;

    printcFrom("q :quit    p :pause    r:rotate", statusLine - CHAR_HEIGHT, getWidth() - 32 * CHAR_WIDTH, color_log);
    printcFrom("Player 1        Player 2", logCursor, LOG_MAX_HEIGHT, color_log);
    logCursor += (CHAR_HEIGHT * 4);

    for (int i = 0, log = logCursor; i < movesWhite; i++) {
        printcFrom(whiteMoves[i], (log % LOG_MAX_HEIGHT), LOG_MAX_HEIGHT + 4 * 8, color_log);
        log += CHAR_HEIGHT;
        initLogRow += CHAR_HEIGHT;
        if (log >= LOG_MAX_HEIGHT)
            logCursor = 56;
    }
    for (int i = 0; i < movesBlack; i++) {
        printcFrom(blackMoves[i], logCursor, LOG_MAX_HEIGHT + CHAR_HEIGHT * 8, color_log);
        logCursor += CHAR_HEIGHT;
        checkBoundLog();

    }

    scaleMatrix(arrowFont, arrow, 9, 9, color_log, -1);
    draw(arrow, initLogRow, 956, 9, 9);
}

void updateLog(char *buffer, int turn) {
    if (turn % 2 == 0) {
        printcFrom(buffer, logCursor, LOG_MAX_HEIGHT + 4 * 8, color_log);
        scaleMatrix(blank, deletion, 9, 9, -1, 0x0);
        scaleMatrix(arrowFont, arrow, 9, 9, color_log, -1);
        draw(deletion, initLogRow, 956, 9, 9);
        draw(arrow, initLogRow += CHAR_HEIGHT, 956, 9, 9);

    } else {
        printcFrom(buffer, logCursor, LOG_MAX_HEIGHT + CHAR_HEIGHT * 8, color_log);
        logCursor += CHAR_HEIGHT;
        checkBoundLog();
    }
}

void rotate() {
    rotation++;
    rotation %= 4;
}

void printExitMessage(int turn, int exitType) { //0 if a king is dead 1 if time runs out
    switch (exitType) {
        case 0: //the king is captured so the current turn is the losers one
            if (turn % 2 == 0)
                printFrom("Player 1 your king has been captured- Player 2 wins! Press \"ENTER\" to return to shell.",
                          statusLine, 0);
            else
                printFrom("Player 2 your king has been captured- Player 1 wins! Press \"ENTER\" to return to shell.",
                          statusLine, 0);
            break;
        case 1: //due to inactivy. the current turn is the losers one
            if (turn % 2 == 0)
                printFrom("Player 1 you have run out of time- Player 2 wins! Press \"ENTER\" to return to shell.",
                          statusLine, 0);
            else
                printFrom("Player 2 you have run out of time- Player 1 wins! Press \"ENTER\" to return to shell.",
                          statusLine, 0);
        default:
            break;
    }
    while ((getChar()) != '\n');
}

void checkBoundLog() {
    if (logCursor >= LOG_MAX_HEIGHT) {
        logCursor = 56;
    }
}