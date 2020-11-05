#ifndef MOVES_H
#define MOVES_H

//functions that return 1 if the moves were executed correctly, 0 if else.

int movePawn(int fromX,int fromY,int toX,int toY, int playNum);
int moveKnight(int fromX,int fromY,int toX,int toY);
int moveKnight(int fromX,int fromY,int toX,int toY);
int moveKing(int fromX,int fromY,int toX,int toY);
int moveRook(int fromX,int fromY,int toX,int toY);
int moveBishop(int fromX,int fromY,int toX,int toY);
int moveQueen(int fromX,int fromY,int toX,int toY);

void kingEaten();

#endif