#include <standardIO.h>
#include <string.h>
#include <chess.h>
#include <moves.h>

/*
POR FAVOR QUE LAS PIEZAS BLANCAS SEAN DEL 1 AL 6 Y LAS NEGRAS DEL 7 AL 13 BITTE BITTE 
    K = 1 / 7
    Q = 2 / 8
    B = 3 / 9
    K = 4 / 10
    R = 5 / 11
    P = 6 / 12
*/

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
int kingDead = 0;
int moves = 0;
int localGameStarted = 0;
int pause = 0;
int whiteTimer , blackTimer  = 0;

void incrementTimer(){
    if( (moves %2) == 0 )
        whiteTimer++;
    else
        blackTimer++; //preguntale al fotto de chicken little
} // che en que momentio le paso e
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

/*
    K = 1 / 7
    Q = 2 / 8
    B = 3 / 9
    N = 4 / 10
    R = 5 / 11
    P = 6 / 12
*/
int makeMove(int fromX, int fromY, int toX, int toY, int playNumber){ 
    //while move!=0 que pida que le entren una instruccion bien
    switch (board[fromX][fromY]){
    case 1:
    case 7: 
        return moveKing(fromX,fromY,toX,toY);
    case 2:
    case 8: 
        return moveQueen(fromX,fromY,toX,toY);
    case 3:
    case 9: 
        return moveBishop(fromX,fromY,toX,toY);
    case 4:
    case 10: 
        return moveKnight(fromX,fromY,toX,toY);
    case 5:
    case 11: 
        return moveRook(fromX,fromY,toX,toY);
    case 6:
    case 12:
        return movePawn(fromX,fromY,toX,toY,playNumber);
    default:
        return 0;
    }
    return 0;
}
void kingEaten(){
    kingDead = 1;
}

void runChess(int entry){
    if (entry == 0 || localGameStarted == 0) init(); //initializes or clears board
    play();
       
}
int isWhitesTurn(){
    return moves%2==0;
}
void play(){ //while kingDead != 0
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
    ////syscall con puntero a funcion !!!!!!!!
    addAlarm(&incrementTimer, 15); //no se cual es el numero porque no hay multiplo lol 
    //pero el 5 es multiplo de 15.
}