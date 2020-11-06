#include <standardIO.h>
#include <string.h>
#include <chess.h>
#include <moves.h>
#include <chessVisual.h>
#include <syscalls.h>
#include <maths.h>

#define TOTAL_PIECES 16 
#define KING 'K' 
#define QUEEN 'Q'
#define ROOK 'R' //torres
#define BISHOP 'B' //alfil
#define KNIGHT 'N' // N of kNight cause K was alreardy TAKEN BY SOMEONE ...
#define PAWN 'P'
#define BOARD_SIZE 8
#define INSTRUCTION_LENGTH 4



//Define para el id de cada pieza
/*      B   N
    K = 1 / 7
    Q = 2 / 8
    B = 3 / 9
    K = 4 / 10
    R = 5 / 11
    P = 6 / 12
*/

//Defines de colores
#define BEIGE 0xe8c99b //240,208,159 | 255,205,190 | 255,220,170 | 232, 201, 155
#define BROWN 0xaa8255 //170,80,40 | 180,110, 80 | 170,130,85
#define WHITE 0xFFFFFF //Es blanco pero no taaaan blanco
#define BLACK 0x0000000

/**
 * Tablero
**/
char piecesName[] = {KING,QUEEN,ROOK,BISHOP,KNIGHT,PAWN}; // (piecesName[board[x][y][0] - 1)%6]
int  board[8][8][3]={{{0}}}; // {posX, posY, vect[3] = {numPieza, 0/1 movimiento, color fondo}};
void parseInstruction(char* buffer, int *fromCol, int *fromRow, int *toCol, int *toRow);
void exit();

void init();
void play();
void fillBoard();
void clearLine(); //Limpia la linea donde se escriben los comandos
void pause(); //pausa el juego
void printBoard();
int isWhitesTurn();

int kingDead = 0;
int turns = 0;
int paused = 0;
int whiteTimer , blackTimer  = 0;

int statusLine = 736;
int line = 752; //Son pixeles
int col = 0;


void incrementTimer(){
    if( (turns %2) == 0 )
        whiteTimer++;
    else
        blackTimer++; 
}

int makeMove(int fromRow, int fromCol, int toRow, int toCol){
    if(!isValidCoord(fromRow,fromCol)) return 0;
    if ((isWhitePiece(board[fromRow][fromCol][PIECE]) && !isWhitesTurn()) ||
            (!isWhitePiece(board[fromRow][fromCol][PIECE]) && isWhitesTurn())) 
                return 0;
    switch (board[fromRow][fromCol][0]){
        case WHITE_KING:
        case BLACK_KING: 
            return moveKing(fromRow,fromCol,toRow,toCol);
        case WHITE_QUEEN:
        case BLACK_QUEEN: 
            return moveQueen(fromRow,fromCol,toRow,toCol);
        case WHITE_BISHOP:
        case BLACK_BISHOP: 
            return moveBishop(fromRow,fromCol,toRow,toCol);
        case WHITE_KNIGHT:
        case BLACK_KNIGHT: 
            return moveKnight(fromRow,fromCol,toRow,toCol);
        case WHITE_ROOK:
        case BLACK_ROOK: 
            return moveRook(fromRow,fromCol,toRow,toCol);
        case WHITE_PAWN:
        case BLACK_PAWN:
            return movePawn(fromRow,fromCol,toRow,toCol);
        default:
            return 0;
    }
    return 0;
}
void kingEaten(){
    kingDead = 1;
}
int hasPrevGame(){
    return paused;
}

int isWhitesTurn(){
    return turns%2==0;
}

void play(){ //while kingDead != 0 && pausedd != 1
    paused = 0;
    char buffer[100] = {0};
    while(!kingDead && !paused){
        char c;
        int position = 0;
        while ((c = getChar())!='\n'){
            if (c!=0){
                switch (c)
                {
                case '\b':
                    if (position > 0){
                        buffer[--position] = 0;
                        //removeChar();
                        if(col >= 0) {
                            col -= 8;
                        }
                        putCharFrom(' ', line, col);
                    }
                    break;
                case 'p':
                case 'P':
                    pause();
                    break;
                case 'q':
                case 'Q':
                    exit();
                    break;
                default:
                    buffer[position++] = c;
                    putCharFrom(c, line, col);
                    col += 8;
                    break;
                } 
            }
            if(paused)
                break;
            if(col >= 1024) {
                col = 0;
                    
            }
        }
        col = 0;
        clearLine();
        
        if(position == INSTRUCTION_LENGTH){
            int fromCol, fromRow, toCol, toRow;
            parseInstruction(buffer, &fromCol, &fromRow, &toCol, &toRow);
            if (makeMove(fromRow,fromCol,toRow,toCol)){
                turns++; //si es un movimiento valido, cambio de turno
                printBoard();
            }
        } 
    }
    if (!paused){
        /*HALT*/
    }
    return;
}
void parseInstruction(char* buffer, int *fromCol, int *fromRow, int *toCol, int *toRow){
    toMayus(buffer);
    *fromCol = buffer[0] - 'A';
    *fromRow = 7 - (buffer[1] - '0' -1);
    *toCol = buffer[2] - 'A';
    *toRow = 7 - (buffer[3] - '0' - 1);
}

void clearLine() {
    printFrom("                                                                                                ", line, col);
}

void pause(){
    clearScreen();
    paused = 1; //returns to shell
}

void exit(){
    pause(); //TODO
}
void newGame(){
    kingDead = 0;
    turns = 0;
    paused = 0;
    whiteTimer = 0;
    blackTimer  = 0;
    fillBoard();
    
    ////syscall con puntero a funcion !!!!!!!!
   // addAlarm(&incrementTimer, 15); //no se cual es el numero porque no hay multiplo lol 
    //pero el 5 es multiplo de 15.
    //poner todo lo global en 0
}

void runChess(int entry){
    if (entry == 0) newGame(); //initializes or clears board
    clearScreen();
    printBoard();
    play(); //setea paused=0 y llama a play
}

void fillBoard() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(i % 2 == 0 && j % 2 == 0) {
                board[i][j][BACKGROUND_COLOR] = BEIGE;
            } else {
                board[i][j][BACKGROUND_COLOR] = BROWN;
            }
            
            board[i][j][MOVEMENTS] = 0;
        }        
    }
    /*for(int i = 0; i < BOARD_SIZE; i++) {
        board[1][i][PIECE] = BLACK_PAWN;
        board[6][i][PIECE] = WHITE_PAWN;
    }*/
    board[0][0][PIECE] = BLACK_ROOK;
    board[0][1][PIECE] = BLACK_KNIGHT;
    board[0][2][PIECE] = BLACK_BISHOP;
    board[0][3][PIECE] = BLACK_QUEEN;
    board[0][4][PIECE] = BLACK_KING;
    board[0][5][PIECE] = BLACK_BISHOP;
    board[0][6][PIECE] = BLACK_KNIGHT;
    board[0][7][PIECE] = BLACK_ROOK;

    board[7][0][PIECE] = WHITE_ROOK;
    board[7][1][PIECE] = WHITE_KNIGHT;
    board[7][2][PIECE] = WHITE_BISHOP;
    board[7][3][PIECE] = WHITE_QUEEN;
    board[7][4][PIECE] = WHITE_KING;
    board[7][5][PIECE] = WHITE_BISHOP;
    board[7][6][PIECE] = WHITE_KNIGHT;
    board[7][7][PIECE] = WHITE_ROOK;
}


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
