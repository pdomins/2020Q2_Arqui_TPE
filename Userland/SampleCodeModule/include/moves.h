#ifndef MOVES_H
#define MOVES_H

//functions that return 1 if the moves were executed correctly, 0 if else.

int movePawn(int fromRow, int fromCol, int toRow, int toCol);

int moveKnight(int fromRow, int fromCol, int toRow, int toCol);

int moveKnight(int fromRow, int fromCol, int toRow, int toCol);

int moveKing(int fromRow, int fromCol, int toRow, int toCol);

int moveRook(int fromRow, int fromCol, int toRow, int toCol);

int moveBishop(int fromRow, int fromCol, int toRow, int toCol);

int moveQueen(int fromRow, int fromCol, int toRow, int toCol);

int shortCastling();

int longCastling();

int isValidCoord(int x, int y);

int isWhitePiece(int pieceNumber);

#endif