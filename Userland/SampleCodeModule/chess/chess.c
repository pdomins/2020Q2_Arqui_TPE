#include <standardIO.h>
#include <string.h>
#include <chess.h>
#include <moves.h>
#include <chessVisual.h>
#include <syscalls.h>
#include <maths.h>

#define INSTRUCTION_LENGTH 4
#define MAX_TIME 500

#define IS_ALPHA(c) ( (c <= '9' && c >= '0') || (c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') )

/*      B   N
    K = 1 / 7
    Q = 2 / 8
    B = 3 / 9
    K = 4 / 10
    R = 5 / 11
    P = 6 / 12
*/

/**
 * Tablero
**/
char piecesName[] = {KING,QUEEN,ROOK,BISHOP,KNIGHT,PAWN}; // (piecesName[board[x][y][0] - 1)%6] ESTO SE USA??????
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
int exitSave = 0, exitWithoutSave = 0;
int whiteTicks , blackTicks  = 0;
int maxTimeReached = 0;
int statusLine = 736;
int line = 752; //Son pixeles
int col = 0;
char whiteMoves[50][5]={{0}}, blackMoves[50][5]={{0}};

int timerReference;
void incrementTimer(){
    if(isWhitesTurn())
        whiteTicks++;
    else
        blackTicks++;
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
    return exitSave;
}

int isWhitesTurn(){
    return turns%2==0;
}

void play(){
    exitSave = 0;
    char buffer[100] = {0};
    while(!kingDead && !exitSave && !exitWithoutSave && !maxTimeReached){
        char c;
        int position = 0;
        while ((c = getChar()) != '\n'){
            if (c!=0){
                switch (c){
                    case '\b':
                        if (position > 0){
                            buffer[--position] = 0;
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
                    case 'r':
                    case 'R':
                        rotate();
                        printBoard();
                        break;
                    default:
                        if (position<10 && IS_ALPHA(c)){
                        buffer[position++] = c;
                        putCharFrom(c, line, col);
                        col += 8;
                        }
                        break;
                } 
            }
            if(abs(whiteTicks - blackTicks) > MAX_TIME){
                maxTimeReached = 1;
                break;
            }
            if(exitSave){
                break;
            }
            if (exitWithoutSave){
                break;
            }
            if(col >= 1024) {
                col = 0;
                    
            }
            printTime(whiteTicks/18,blackTicks/18);
        }
        col = 0;
        clearLine();
        
        if(position == INSTRUCTION_LENGTH){
            int fromCol, fromRow, toCol, toRow;
            parseInstruction(buffer, &fromCol, &fromRow, &toCol, &toRow);
            if (makeMove(fromRow,fromCol,toRow,toCol)){
                switch (turns%2)
                {
                case 0:
                    strcpy(whiteMoves[(int)turns/2],buffer);
                    break;
                case 1:
                    strcpy(blackMoves[(int)turns/2],buffer);
                    break;
                }
                turns++; //si es un movimiento valido, cambio de turno
                printBoard();
            }
        }
    }

    if (!exitSave && !exitWithoutSave && !maxTimeReached){
        printFrom("ganaste logi apreta enter para volver a la yel MAESTRO",statusLine,0);
        while ((getChar())!='\n');
    }else if (maxTimeReached){
        printFrom("inactivity. apreta enter para volver a yel",statusLine,0);
        while ((getChar())!='\n');        clearLine();

    }
    clearScreen();
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
    exitSave = 1; //returns to shell
}

void exit(){
    exitWithoutSave = 1; //returns to shell
}

void newGame(){ //pone todo lo global en 0 y llena el tablero de nuevo
    exitWithoutSave = 0;
    kingDead = 0;
    turns = 0;
    exitSave = 0;
    whiteTicks = 0;
    blackTicks  = 0;
    maxTimeReached = 0;
    fillBoard();
    //poner todo lo global en 0
}

void runChess(int entry){
    if (entry == 0 || exitWithoutSave ) newGame(); //initializes or clears board
    clearScreen();
    printBoard();
    setAlarm(&incrementTimer, 1);
    play(); //setea exitSave=0 y llama a play
    setAlarm(&incrementTimer, 0);
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
            board[i][j][PIECE] = 0;
        }        
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
        board[1][i][PIECE] = BLACK_PAWN;
        board[6][i][PIECE] = WHITE_PAWN;
    }
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


