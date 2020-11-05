#ifndef CHESS_H
#define CHESS_H

//Defines para acceder a los campos del tablero
#define PIECE 0
#define MOVEMENTS 1
#define BACKGROUND_COLOR 2

enum pieces {WHITE_KING = 1, WHITE_QUEEN, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK, WHITE_PAWN,
            BLACK_KING, BLACK_QUEEN, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK, BLACK_PAWN};

void runChess(int entry);
int hasPrevGame();
void kingEaten();


#endif