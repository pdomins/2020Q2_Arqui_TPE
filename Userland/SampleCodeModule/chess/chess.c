#include <standardIO.h>
#include <string.h>
#include <chess.h>

#define TOTAL_PIECES 16 
#define WHITE 0xFFFFFFF
#define BLACK 0x0000000
#define KING 'K'
#define QUEEN 'Q'
#define ROOK 'R' //torres
#define BISHOP 'B' //alfil
#define KNIGHT 'N' // N of kNight cause K was alreardy TAKEN BY SOMEONE ...
#define PAWN 'P'
#define BOARD_DIM 8

typedef struct{
	char piece;
	int colour;
	int posX;// a=0 b c d e f g h
	int posY;// 0 1 2 3 4 5 6 7
    int hasMoved;
    int isAlive; 
}chessPieces;

typedef struct {
    char piece;
    int color;
    int posX; //a = 0, b, c, d, e, f, g, h
    int posY;// 0 1 2 3 4 5 6 7
    int hasMoved;
    int isAlive;
}chessPiece;

typedef chessPiece * piece;

void init();
void play();

int board[8][8]={{0}};
int moves = 0;
int localGameStarted = 0;
int pause = 0;
int whiteTimer , blackTimer  = 0;

        //jugadorA
//  h  g  f  e  d  c  b  a  
//0                        0
//1                        1
//2                        2
//3                        3
//4                        4
//5                        5
//6                        6
//7                        7
//  h  g  f  e  d  c  b  a  
        //jugadorB

void runChess(int entry){
    if (entry == 0 || localGameStarted == 0) init(); //initializes or clears board
    play();
       
}
int isWhitesTurn(){
    return moves%2==0;
}
void play(){
    return;
}
void pauseGame(){
    pause = 1;
    //returns to shell
}
void exitGame(){
    localGameStarted=0;
    pauseGame();
}

void init(){
}