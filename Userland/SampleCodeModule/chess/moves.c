#include <chess.h>
#include <chessVisual.h>
#include <moves.h>
#include <maths.h>
#include <string.h>
#include <standardIO.h>
#include <syscalls.h>

#define WHITES_TURN 0
#define BLACK_TURN 1

#define DIM 8
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8
#define statusLine (getHeight() - CHAR_HEIGHT * 2)
#define commandLine (getHeight() - CHAR_HEIGHT)

extern int board[DIM][DIM][3];

void setToMovedPiece(int x, int y);

int sameTeam(int fromRow, int fromCol, int toRow, int toCol);

int isFirstMove(int fromRow, int fromCol);

int isWhiteTurn(int turn);

int possibleCheck();

int move(int (*check)(int, int, int, int), int fromRow, int fromCol, int toRow, int toCol);

int isAvailable(int toRow, int toCol);

int checkPawn(int fromRow, int fromCol, int toRow, int toCol);

int checkKnight(int fromRow, int fromCol, int toRow, int toCol);

int checkKing(int fromRow, int fromCol, int toRow, int toCol);

int checkRook(int fromRow, int fromCol, int toRow, int toCol);

int checkBishop(int fromRow, int fromCol, int toRow, int toCol);

int checkQueen(int fromRow, int fromCol, int toRow, int toCol);

void checkIfKing(int piece);

int isValidRookPath(int fromRow, int fromCol, int toRow, int toCol);

int isValidBishopPath(int fromRow, int fromCol, int toRow, int toCol);

int checkPromotion(int fromRow, int fromCol, int toRow, int toCol);

int validPromotion(char option);

void promote(int toRow, int toCol);

void checkPassant(int fromRow, int fromCol, int toRow, int toCol);

int validPassant(char option, int left, int right);

extern char whiteMoves[50][5];
extern char blackMoves[50][5];
extern int movesWhite;
extern int movesBlack;
extern int turns;

int whiteKing[2] = {7,4};
int blackKing[2] = {0,4};

int movePawn(int fromRow, int fromCol, int toRow, int toCol) {
    return move(checkPawn, fromRow, fromCol, toRow, toCol);
}

int moveKnight(int fromRow, int fromCol, int toRow, int toCol) {
    return move(checkKnight, fromRow, fromCol, toRow, toCol);
}

int moveKing(int fromRow, int fromCol, int toRow, int toCol) {
    return move(checkKing, fromRow, fromCol, toRow, toCol);
}

int moveRook(int fromRow, int fromCol, int toRow, int toCol) {
    return move(checkRook, fromRow, fromCol, toRow, toCol);
}

int moveBishop(int fromRow, int fromCol, int toRow, int toCol) {
    return move(checkBishop, fromRow, fromCol, toRow, toCol);
}

int moveQueen(int fromRow, int fromCol, int toRow, int toCol) {
    return move(checkQueen, fromRow, fromCol, toRow, toCol);
}

int shortCastling(int turn) {
    if(possibleCheck())
        return 0;
        
    if (isWhiteTurn(turn)) {
        if (board[7][4][PIECE] == WHITE_KING && board[7][7][PIECE] == WHITE_ROOK &&
            board[7][4][MOVEMENTS] == 0 && board[7][7][MOVEMENTS] == 0 &&
            board[7][6][PIECE] == 0 && board[7][5][PIECE] == 0) {
            board[7][6][PIECE] = WHITE_KING;
            board[7][6][MOVEMENTS] = 1;
            board[7][5][PIECE] = WHITE_ROOK;
            board[7][5][MOVEMENTS] = 1;
            board[7][4][PIECE] = 0;
            board[7][7][PIECE] = 0;
            return 1;
        }
    } else {
        if (board[0][4][PIECE] == BLACK_KING && board[0][7][PIECE] == BLACK_ROOK &&
            board[0][4][MOVEMENTS] == 0 && board[0][7][MOVEMENTS] == 0 &&
            board[0][6][PIECE] == 0 && board[0][5][PIECE] == 0) {
            board[0][6][PIECE] = BLACK_KING;
            board[0][6][MOVEMENTS] = 1;
            board[0][5][PIECE] = BLACK_ROOK;
            board[0][5][MOVEMENTS] = 1;
            board[0][4][PIECE] = 0;
            board[0][7][PIECE] = 0;
            return 1;
        }
    }
    return 0;
}

int longCastling(int turn) {
    if(possibleCheck())
        return 0;
    
    if (isWhiteTurn(turn)) {
        if (board[7][4][PIECE] == WHITE_KING && board[7][0][PIECE] == WHITE_ROOK &&
            board[7][4][MOVEMENTS] == 0 && board[7][0][MOVEMENTS] == 0 &&
            board[7][1][PIECE] == 0 && board[7][2][PIECE] == 0 && board[7][3][PIECE] == 0) {
            board[7][2][PIECE] = WHITE_KING;
            board[7][2][MOVEMENTS] = 1;
            board[7][3][PIECE] = WHITE_ROOK;
            board[7][3][MOVEMENTS] = 1;
            board[7][4][PIECE] = 0;
            board[7][0][PIECE] = 0;
            return 1;
        }
    } else {
        if (board[0][4][PIECE] == BLACK_KING && board[0][0][PIECE] == BLACK_ROOK &&
            board[0][4][MOVEMENTS] == 0 && board[0][0][MOVEMENTS] == 0 &&
            board[0][1][PIECE] == 0 && board[0][2][PIECE] == 0 && board[0][3][PIECE] == 0) {
            board[0][2][PIECE] = BLACK_KING;
            board[0][2][MOVEMENTS] = 1;
            board[0][3][PIECE] = BLACK_ROOK;
            board[0][3][MOVEMENTS] = 1;
            board[0][4][PIECE] = 0;
            board[0][0][PIECE] = 0;
            return 1;
        }
    }
    return 0;
}

/*
Returns 1 if it's a valid coordinate within the boundaries of the board.
*/
int isValidCoord(int row, int col) {
    return row >= 0 && row <= 7 && col >= 0 && col <= 7;
}

/*
Returns 1 if it's a white piece, 0 if it's black.
*/
int isWhitePiece(int pieceNumber) {
    return pieceNumber >= 0 && pieceNumber <= 6;
}


/**
  * Funciones auxiliares
 */

void setToMovedPiece(int x, int y) {
    board[x][y][MOVEMENTS] = 1;
}

int sameTeam(int fromRow, int fromCol, int toRow, int toCol) {
    if (board[toRow][toCol][PIECE] != 0) {
        return isWhitePiece(board[toRow][toCol][PIECE]) == isWhitePiece(board[fromRow][fromCol][PIECE]);
    }
    return 0;
}

/*
Returns 1 if the piece has not been moved yet.
*/
int isFirstMove(int fromRow, int fromCol) {
    return board[fromRow][fromCol][MOVEMENTS] == 0;
}

int isWhiteTurn(int turn) {
    return turn % 2 == 0;
}

int searchKing(int row, int col){
    int kingRow,kingCol;
    if(isWhitePiece(board[row][col][PIECE])){
        kingRow = blackKing[0];
        kingCol = blackKing[1];
    }else{
        kingRow = whiteKing[0];
        kingCol = whiteKing[1];
    }
    switch (board[row][col][PIECE])
    {
        case BLACK_PAWN:
        case WHITE_PAWN:
            return checkPawn(row, col, kingRow, kingCol);
        case BLACK_BISHOP:
        case WHITE_BISHOP:
            return checkBishop(row, col, kingRow, kingCol);
        case BLACK_ROOK:
        case WHITE_ROOK:
            return checkRook(row, col, kingRow, kingCol);
        case BLACK_KNIGHT:
        case WHITE_KNIGHT:
            return checkKnight(row, col, kingRow ,kingCol);
        case BLACK_QUEEN:
        case WHITE_QUEEN:
            return checkQueen(row, col, kingRow, kingCol);
        case BLACK_KING:
        case WHITE_KING:
            return checkKing(row, col, kingRow , kingCol);
        default:
            return 0;
    }
    return 0;
}

int possibleCheck(){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(board[i][j][PIECE] != 0){
                if(searchKing(i, j)){
                    if(isWhitePiece(board[i][j][PIECE])){
                        printcFrom("The black king is in check. Press \"ENTER\" to continue.",statusLine,0,0xfcba03);
                    }else{
                        printcFrom("The white king is in check. Press \"ENTER\" to continue.",statusLine,0,0xfcba03);
                    }
                    while (getChar() != '\n'){
                        updateTime();
                    }
                    clearLine(statusLine);
                    return 1;
                }
            }
        }    
    }
    return 0;
}


int move(int (*check)(int, int, int, int), int fromRow, int fromCol, int toRow, int toCol) {
    if (check(fromRow, fromCol, toRow, toCol)) {
        checkIfKing(board[toRow][toCol][PIECE]); //checks if the piece to be eaten is a king
        
        if (sameTeam(fromRow, fromCol, toRow, toCol))
            return 0;

        board[toRow][toCol][PIECE] = board[fromRow][fromCol][PIECE];

        if(board[toRow][toCol][PIECE] == WHITE_KING){
            whiteKing[0] = toRow;
            whiteKing[1] = toCol;
        }
        if(board[toRow][toCol][PIECE] == BLACK_KING){
            blackKing[0]=toRow;
            blackKing[1]=toCol;
        }
        if (checkPromotion(fromRow, fromCol, toRow, toCol)) {
            promote(toRow, toCol);
        }

        board[fromRow][fromCol][PIECE] = 0;

        checkPassant(fromRow, fromCol, toRow, toCol);

        setToMovedPiece(toRow, toCol);

        possibleCheck();

        return 1;
    }
    return 0;
}

/*
Returns 1 if it's a free slot.
*/
int isAvailable(int toRow, int toCol) {
    return board[toRow][toCol][PIECE] == 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkPawn(int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidCoord(toRow, toCol))return 0;
    if (!isWhitePiece(board[fromRow][fromCol][PIECE])) { //Si es negra se mueve para abajo
        if (fromCol == toCol && isAvailable(toRow, toCol)) {       //si se esta moviendo
            if (fromRow + 1 == toRow || (fromRow + 2 == toRow && isFirstMove(fromRow, fromCol)))
                return 1;
        } else if (fromRow + 1 == toRow && (fromCol + 1 == toCol || fromCol - 1 == toCol))//si come
            return board[toRow][toCol][PIECE] != 0;  //la pieza que se comeria exista
    } else { //Si es blanca se mueve para arriba
        if (fromCol == toCol && isAvailable(toRow, toCol)) {
            if (fromRow - 1 == toRow || (fromRow - 2 == toRow && isFirstMove(fromRow, fromCol)))
                return 1;
        } else if (fromRow - 1 == toRow && (fromCol + 1 == toCol || fromCol - 1 == toCol))
            return board[toRow][toCol][PIECE] != 0;
    }
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkKnight(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidCoord(toRow, toCol)) { //no chequeo que sea un path valido dado que el caballo puede saltar
        if (fromRow + 2 == toRow || fromRow - 2 == toRow) {
            return fromCol + 1 == toCol || fromCol - 1 == toCol;
        } else if (fromCol + 2 == toCol || fromCol - 2 == toCol) {
            return fromRow + 1 == toRow || fromRow - 1 == toRow;
        }
    }
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkKing(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidCoord(toRow, toCol)) {
        if (fromRow == toRow)
            return fromCol + 1 == toCol || fromCol - 1 == toCol;
        else if (fromRow + 1 == toRow || fromRow - 1 == toRow)
            return fromCol + 1 == toCol || fromCol - 1 == toCol || fromCol == toCol;
    }
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkRook(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidCoord(toRow, toCol))
        if ((fromRow == toRow && fromCol != toCol) || (fromCol == toCol && fromRow != toRow))
            return isValidRookPath(fromRow, fromCol, toRow, toCol);
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkBishop(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidCoord(toRow, toCol))
        if (abs(fromRow - toRow) ==
            abs(fromCol - toCol))  //como se mueve en diagonal, se deben mover n lugares de i y j.
            return isValidBishopPath(fromRow, fromCol, toRow, toCol);
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkQueen(int fromRow, int fromCol, int toRow, int toCol) {
    return checkBishop(fromRow, fromCol, toRow, toCol) || checkRook(fromRow, fromCol, toRow, toCol);
}


void checkIfKing(int piece) {
    if (piece == WHITE_KING || piece == BLACK_KING)
        kingEaten();
}

/*
Returns 1 if it's a valid path, 0 if not.
Also, checks that if a piece is found, its a FOE's one.
*/
int isValidRookPath(int fromRow, int fromCol, int toRow, int toCol) {
    int i = fromRow, j = fromCol;
    if (fromRow == toRow) { //Te moves horizontal
        if (fromCol < toCol) { //Te moves para la derecha
            while (++j != toCol) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        } else { //fromCol > toCol  Te moves para la izquierda
            while (--j != toCol) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        }
    } else { //Te moves vertical
        if (fromRow < toRow) { //Te moves para abajo
            while (++i != toRow) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        } else {
            while (--i != toRow) { //Te moves para arriba
                if (board[i][j][PIECE] != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

/*
Returns 1 if it's a valid path, 0 if not.
Also, checks that if a piece is found, its a FOE's one.
*/

int isValidBishopPath(int fromRow, int fromCol, int toRow, int toCol) {
    int i = fromRow, j = fromCol;
    if (fromRow < toRow) { // Baja
        if (fromCol < toCol) { //Derecha
            while (++i != toRow && ++j != toCol) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        } else { //izquierda
            while (++i != toRow && --j != toCol) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        }
    } else { //Sube
        if (fromCol < toCol) { //Derecha
            while (--i != toRow && ++j != toCol) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        } else { //Izquierda
            while (--i != toRow && --j != toCol) {
                if (board[i][j][PIECE] != 0)
                    return 0;
            }
        }
    }

    return 1;
}

int checkPromotion(int fromRow, int fromCol, int toRow, int toCol) {
    if (board[fromRow][fromCol][PIECE] == WHITE_PAWN) {
        if (toRow == 0) {
            return 1;
        }
    } else if (board[fromRow][fromCol][PIECE] == BLACK_PAWN) {
        if (toRow == 7) {
            return 1;
        }
    }
    return 0;
}

int validPromotion(char option) {
    char buffer[2] = {0};
    buffer[0] = option;
    toMayus(buffer);
    option = buffer[0];
    return option == QUEEN || option == ROOK || option == KNIGHT || option == BISHOP;
}

void promote(int toRow, int toCol) {
    int toAdd = (toRow == 0) ? 0 : 6;
    char option;
    printcFrom("Promotion: 'Q':Queen 'R':Rook 'N':Knight 'B'Bishop", statusLine, 0, 0xfcba03);
    while (!validPromotion(option = getChar()));
    switch (option) {
        case 'q':
        case 'Q':
            board[toRow][toCol][PIECE] = WHITE_QUEEN;
            break;
        case 'r':
        case 'R':
            board[toRow][toCol][PIECE] = WHITE_ROOK + toAdd;
            break;
        case 'n':
        case 'N':
            board[toRow][toCol][PIECE] = WHITE_KNIGHT + toAdd;
            break;
        case 'b':
        case 'B':
            board[toRow][toCol][PIECE] = WHITE_BISHOP + toAdd;
            break;
    }
    clearLine(statusLine);
    clearLine(commandLine);
}

void checkPassant(int fromRow, int fromCol, int toRow, int toCol) {
    printBoard();
    int rightPawn = 0;
    int leftPawn = 0;
    if (abs(fromRow - toRow) == 2) {
        if (board[toRow][toCol][PIECE] == WHITE_PAWN) {
            if (toCol > 0 &&
                board[toRow][toCol - 1][PIECE] == BLACK_PAWN) { //Pregunto si hay un peon negro a la izquierda
                rightPawn = 1;
            }
            if (toCol < 7 &&
                board[toRow][toCol + 1][PIECE] == BLACK_PAWN) { //Pregunto si hay un peon negro a la derecha
                leftPawn = 1;
            }
        } else if (board[toRow][toCol][PIECE] == BLACK_PAWN) {
            if (toCol > 0 &&
                board[toRow][toCol - 1][PIECE] == WHITE_PAWN) { //Pregunto si hay un peon blanco a la izquierda
                rightPawn = 1;
            }
            if (toCol < 7 &&
                board[toRow][toCol + 1][PIECE] == WHITE_PAWN) { //Pregunto si hay un peon blanco a la derecha
                leftPawn = 1;
            }
        }
    }
    if (rightPawn || leftPawn) {
        char c;
        printcFrom("Passant: 'R': Right 'L':Left 'S':Skip", statusLine, 0, 0xfcba03);
        while (!validPassant((c = getChar()), leftPawn, rightPawn)) {
            updateTime();
        }
        switch (c) {
            case 'r':
            case 'R':
                if (toRow == 3) { //la blanca se come la negra
                    board[toRow - 1][toCol][PIECE] = board[toRow][toCol - 1][PIECE];
                    board[toRow - 1][toCol][MOVEMENTS] = board[toRow][toCol - 1][MOVEMENTS];
                    board[toRow][toCol - 1][PIECE] = 0;
                    board[toRow][toCol - 1][MOVEMENTS] = 0;
                    board[toRow][toCol][PIECE] = 0;
                    board[toRow][toCol][MOVEMENTS] = board[toRow][toCol - 1][PIECE];
                } else if (toRow == 4) { //el negro se come a la blanca NEGRO BLANCA
                    board[toRow + 1][toCol][PIECE] = board[toRow][toCol - 1][PIECE];
                    board[toRow + 1][toCol][MOVEMENTS] = board[toRow][toCol - 1][MOVEMENTS];
                    board[toRow][toCol - 1][PIECE] = 0;
                    board[toRow][toCol - 1][MOVEMENTS] = 0;
                    board[toRow][toCol][PIECE] = 0;
                    board[toRow][toCol][MOVEMENTS] = 0;
                }
                passantTurn();
                break;
            case 'l':
            case 'L':
                if (toRow == 3) { //la blanca se come la negra NEGRO BLANCO
                    board[toRow - 1][toCol][PIECE] = board[toRow][toCol + 1][PIECE];
                    board[toRow - 1][toCol][MOVEMENTS] = board[toRow][toCol + 1][MOVEMENTS];
                    board[toRow][toCol + 1][PIECE] = 0;
                    board[toRow][toCol + 1][MOVEMENTS] = 0;
                    board[toRow][toCol][PIECE] = 0;
                    board[toRow][toCol][MOVEMENTS] = 0;

                } else if (toRow == 4) { //el negro se come a la blanca  BLANCO NEGRO
                    board[toRow + 1][toCol][PIECE] = board[toRow][toCol + 1][PIECE];
                    board[toRow + 1][toCol][MOVEMENTS] = board[toRow][toCol + 1][MOVEMENTS];
                    board[toRow][toCol + 1][PIECE] = 0;
                    board[toRow][toCol + 1][MOVEMENTS] = 0;
                    board[toRow][toCol][PIECE] = 0;
                    board[toRow][toCol][MOVEMENTS] = 0;

                }
                passantTurn();
                break;
            case 's':
            case 'S':
                break;
        }
        printBoard();
        clearLine(statusLine);
        clearLine(commandLine);
    }
}

int validPassant(char option, int left, int right) {
    char buffer[2] = {0};
    buffer[0] = option;
    toMayus(buffer);
    option = buffer[0];
    return (option == 'R' && right) || (option == 'L' && left) || (option == 'S');
}