#include <chessVisual.h>
#include <chess.h>
#include <standardIO.h>
#include <syscalls.h>
#include <maths.h>


extern int board[8][8][3];


void printBoard(){
    int original_s = 16;

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
     * Armado del tablero
     */

    int scaled_s = 80; //Size de los cuadrados
    int matrix[scaled_s * scaled_s];
    char * aux = baseBoard;
    int initial_x = 32;
    int initial_y = 32;
    int x = initial_x;
    int y = initial_y;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            scaleMatrix(aux + i * 8 + j, matrix, 1, scaled_s, BEIGE, BROWN);
            draw(matrix, y, x, scaled_s, scaled_s);
            x += scaled_s;
        }
        y += scaled_s;
        x= initial_x;
    }

    int num = initial_y + scaled_s / 2 - 16; //8 es el char_width
    printFrom("8", num, 16); num+=scaled_s;
    printFrom("7", num, 16); num+=scaled_s;
    printFrom("6", num, 16); num+=scaled_s;
    printFrom("5", num, 16); num+=scaled_s;
    printFrom("4", num, 16); num+=scaled_s;
    printFrom("3", num, 16); num+=scaled_s;
    printFrom("2", num, 16); num+=scaled_s;
    printFrom("1", num, 16);

    num = initial_x + scaled_s / 2;
    printFrom("A", 8, num -8); num+=(scaled_s);
    printFrom("B", 8, num-8); num+=(scaled_s);
    printFrom("C", 8, num-8); num+=(scaled_s);
    printFrom("D", 8, num-8); num+=(scaled_s);
    printFrom("E", 8, num-8); num+=(scaled_s);
    printFrom("F", 8, num-8); num+=(scaled_s);
    printFrom("G", 8, num-8); num+=(scaled_s);
    printFrom("H", 8, num-8);


    /**
     * Seria el log de jugadas
     */

    char * flecha = {
            "_________"
            "_________"
            "____X____"
            "___XXX___"
            "__XXXXX__"
            "_XXXXXXX_"
            "XXXXXXXXX"
            "_________"
            "_________"
    };

    int arrow[9*9];


    int cursor = 24;
    int init_log_row = 80;
    int color_log = 0xadadad;
    int color_time = 0xffc32b;
    int color_diff = 0x38ad34;

    printcFrom("Player 1        Player 2", cursor, 740, 0xFFFFFF); cursor += 16;
    printcFrom("   00:00        00:00   ", cursor, 740, color_time);cursor += 16;
    printcFrom("         +00:00        ", cursor, 740, color_diff);cursor += 16;
    printcFrom("    a4d5        e6h3    ", cursor, 740, color_log);cursor += 16;
    printcFrom("    e3a2        c8a3    ", cursor, 740, color_log);cursor += 16;
    printcFrom("    a6e1        b5c3    ", cursor, 740, color_log);cursor += 16;
    printcFrom("    d4f5        a2a3    ", cursor, 740, color_log);cursor += 16;
    printcFrom("    g6h6        f3g6    ", cursor, 740, color_log);cursor += 16;

    scaleMatrix(flecha, arrow, 9, 9, color_log, -1);
    draw(arrow, init_log_row, 956, 9, 9);
    //draw(scaled_board, 0, 0, s, s);

    //initial_y = 16;
    /*
     * Colocacion de las piezas
    */
    for(int i = 0 ; i < 8 ; i++) {
        for(int j = 0 ; j < 8 ; j++) {
            if(board[i][j][PIECE] != 0) {
                switch(board[i][j][PIECE]) {
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
                    draw(matrix, scaled_s * i + initial_y, j * scaled_s + initial_x, scaled_s, scaled_s);
                }
            }
            
    }
    /*
    //Peones
    //int matrix[scaled_s * scaled_s];
    for(int i = 0 + initial_x; i < scaled_s * 8 + initial_x; i += scaled_s) {
        scaleMatrix(pawn, matrix, original_s, scaled_s, WHITE, -1);
        draw(matrix, scaled_s * 6 + initial_y, i, scaled_s, scaled_s);
        scaleMatrix(pawn, matrix, original_s, scaled_s, BLACK, -1);
        draw(matrix, scaled_s * 1 + initial_y, i, scaled_s, scaled_s);
    }

    //Torre
    scaleMatrix(tower, matrix, original_s, scaled_s, BLACK, -1);
    draw(matrix, 0 + initial_y, 0 + initial_x, scaled_s, scaled_s);
    draw(matrix, 0 + initial_y, scaled_s * 7 + initial_x, scaled_s, scaled_s);
    scaleMatrix(tower, matrix, original_s, scaled_s, WHITE, -1);
    draw(matrix, scaled_s * 7 + initial_y, 0 + initial_x, scaled_s, scaled_s);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 7 + initial_x, scaled_s, scaled_s);

    //Caballo
    scaleMatrix(knight, matrix, original_s, scaled_s, BLACK, -1);
    draw(matrix, 0 + initial_y, scaled_s * 1 + initial_x, scaled_s, scaled_s);
    draw(matrix, 0 + initial_y, scaled_s * 6 + initial_x, scaled_s, scaled_s);
    scaleMatrix(knight, matrix, original_s, scaled_s, WHITE, -1);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 1 + initial_x, scaled_s, scaled_s);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 6 + initial_x, scaled_s, scaled_s);

    //Alfil
    scaleMatrix(bishop, matrix, original_s, scaled_s, BLACK, -1);
    draw(matrix, 0 + initial_y, scaled_s * 2 + initial_x, scaled_s, scaled_s);
    draw(matrix, 0 + initial_y, scaled_s * 5 + initial_x, scaled_s, scaled_s);
    scaleMatrix(bishop, matrix, original_s, scaled_s, WHITE, -1);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 2 + initial_x, scaled_s, scaled_s);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 5 + initial_x, scaled_s, scaled_s);

    //Rey
    scaleMatrix(king, matrix, original_s, scaled_s, BLACK, -1);
    draw(matrix, 0 + initial_y, scaled_s * 4 + initial_x, scaled_s, scaled_s);
    scaleMatrix(king, matrix, original_s, scaled_s, WHITE, -1);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 4 + initial_x, scaled_s, scaled_s);

    //Reina
    scaleMatrix(queen, matrix, original_s, scaled_s, BLACK, -1);
    draw(matrix, 0 + initial_y, scaled_s * 3 + initial_x, scaled_s, scaled_s);
    scaleMatrix(queen, matrix, original_s, scaled_s, WHITE, -1);
    draw(matrix, scaled_s * 7 + initial_y, scaled_s * 3 + initial_x, scaled_s, scaled_s);
    */
}

