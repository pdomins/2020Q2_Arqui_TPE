#ifndef CHESS_H
#define CHESS_H

//Defines para acceder a los campos del tablero
#define PIECE 0
#define MOVEMENTS 1
#define BACKGROUND_COLOR 2
#define TOTAL_PIECES 16
#define KING 'K'
#define QUEEN 'Q'
#define ROOK 'R'
#define BISHOP 'B'
#define KNIGHT 'N'
#define PAWN 'P'
#define BOARD_SIZE 8

enum pieces {
    WHITE_KING = 1, WHITE_QUEEN, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK, WHITE_PAWN,
    BLACK_KING, BLACK_QUEEN, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK, BLACK_PAWN
};

void runChess(int entry);

int hasPrevGame();

void kingEaten();

int isWhitesTurn();

void clearLine(int line);

int getWhiteTime();

int getBlackTime();

void passantTurn();

void updateTime();

#endif