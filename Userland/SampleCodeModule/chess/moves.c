#include <chess.h>
#include <moves.h>
#include <maths.h>

extern int board[8][8][3];
int isWhitePiece(int pieceNumber);
int isValidCoord(int toRow, int toCol);
int isAvailable(int toRow, int toCol);
int isValidPath(int fromRow, int fromCol,int toRow, int toCol);
int checkPawn(int fromRow,int fromCol,int toRow,int toCol);
int checkKnight(int fromRow,int fromCol,int toRow,int toCol);
int checkKing(int fromRow,int fromCol,int toRow,int toCol);
int checkRook(int fromRow,int fromCol,int toRow,int toCol);
int checkBishop(int fromRow,int fromCol,int toRow,int toCol);
int checkQueen(int fromRow,int fromCol,int toRow,int toCol);

/*      B   N
    K = 1 / 7
    Q = 2 / 8
    B = 3 / 9
    K = 4 / 10
    R = 5 / 11
    P = 6 / 12
*/
void checkIfKing(int piece){
    if (piece == WHITE_KING || piece == BLACK_KING)
        kingEaten();
}

void setToMovedPiece(int x,int y){
    board[x][y][MOVEMENTS] = 1;
}

int move(int (*func) (int,int,int,int),int fromRow,int fromCol,int toRow,int toCol){
    if (func(fromRow,fromCol,toRow,toCol)){
        checkIfKing(board[toRow][toCol][PIECE]); //checks if the piece to be eaten is a king
        board[toRow][toCol][PIECE] = board[fromRow][fromCol][PIECE];
        setToMovedPiece(toRow, toCol);
        board[fromRow][fromCol][PIECE] = 0;
        return 1;
    }
    return 0;
}


int movePawn(int fromRow,int fromCol,int toRow,int toCol){
    return move(checkPawn,fromRow,fromCol,toRow,toCol);
}

int moveKnight(int fromRow,int fromCol,int toRow,int toCol){
    return move(checkKnight,fromRow,fromCol,toRow,toCol);   
}

int moveKing(int fromRow,int fromCol,int toRow,int toCol){
     return move(checkKing,fromRow,fromCol,toRow,toCol);
}

int moveRook(int fromRow,int fromCol,int toRow,int toCol){
    return move(checkRook,fromRow,fromCol,toRow,toCol);
}

int moveBishop(int fromRow,int fromCol,int toRow,int toCol){
    return move(checkBishop,fromRow,fromCol,toRow,toCol);
}

int moveQueen(int fromRow,int fromCol,int toRow,int toCol){
    return move(checkQueen,fromRow,fromCol,toRow,toCol);
}

/*
Returns 1 if it's a white piece, 0 if it's black.
*/
int isWhitePiece(int pieceNumber){
    return pieceNumber >= 0 && pieceNumber <= 6;
}

/*
Returns 1 if it's a valid coordinate within the boundaries of the board.
*/
int isValidCoord(int row, int col){
    return row>=0 && row <=7 && col>=0 && col<=7;
}
/*
Returns 1 if it's a free slot.
*/
int isAvailable(int toRow, int toCol){
    return board[toRow][toCol][PIECE] == 0;
}

/*
Returns 1 if it's a valid path, 0 if not.
Also, checks that if a piece is found, its a FOE's one.

creo que no pensamos bien este plan, mis brazo son muy cortos y mi cabeza muy grande
*/

int isValidBishopPath(int fromRow, int fromCol,int toRow, int toCol){
    int i = fromRow, j = fromCol;
    if(fromRow < toRow){ // Baja
        if(fromCol < toCol){ //Derecha
            while( i != toRow){
                if(board[i][j][PIECE] != 0)
                    return 0;
                i++;
                j++;
            }
        } else { //izquierda
            while( i != toRow){
                if(board[i][j][PIECE] != 0)
                    return 0;
                i++;
                j--;
            } 
        }
    } else { //Sube
        if(fromCol < toCol) { //Derecha
            while( i != toRow) {
                if(board[i][j][PIECE] != 0) 
                    return 0;
                i--;
                j++;   
            }
        } else { //Izquierda
            while( i != toRow) {
                if(board[i][j][PIECE] != 0) 
                    return 0;
                i--;
                j--;   
            }
        }
    }

    return 1;
}

/*
Returns 1 if it's a valid path, 0 if not.
Also, checks that if a piece is found, its a FOE's one.
*/
int isValidRookPath(int fromRow, int fromCol,int toRow, int toCol){
    int i = fromRow, j = fromCol;
    //Creo que el i y el j estan vinculados al reves con el fromRow y fromCol
    if (fromRow == toRow){ //Te moves horizontal
        if(fromCol < toCol){ //Te moves para la derecha
            while( j != toCol ){
                if(board[i][j][PIECE] != 0)
                    return 0;
                j++;
            }
        }
        else{ //fromCol > toCol  Te moves para la izquierda
            while( j != toCol ) {
                if(board[i][j][PIECE] != 0)
                    return 0;
                j--;
            }
        }
    }
    else{ //Te moves vertical
        if(fromRow < toRow){ //Te moves para abajo
            while( i != toRow ){
                if (board[i][j][PIECE]!=0) 
                    return 0;
                i++;
            }
        }else{
            while( i != toRow ) //Te moves para arriba
                if (board[i][j][PIECE]!=0) 
                    return 0;
                i--;
        }
    }

    return 1;
}

/*
Returns 1 if the piece has not been moved yet.
*/
int isFirstMove(int fromRow, int fromCol){
    return board[fromRow][fromCol][MOVEMENTS] == 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkPawn(int fromRow,int fromCol,int toRow,int toCol){
    if (!isValidCoord(toRow,toCol))return 0;
    if (!isWhitePiece(board[fromRow][fromCol][PIECE])){ //Si es negra se mueve para abajo
        if (fromCol == toCol && isAvailable(toRow,toCol)){       //si se esta moviendo
            if (fromRow +1 == toRow || (fromRow + 2 == toRow && isFirstMove(fromRow,fromCol)))
                return 1;
        }else if(fromRow + 1 == toRow && (fromCol + 1 == toCol || fromCol-1 == toCol))//si come
            return board[toRow][toCol][PIECE] != 0;  //la pieza que se comeria exista 
    }else{ //Si es blanca se mueve para arriba
        if (fromCol == toCol && isAvailable(toRow,toCol)){ 
            if (fromRow - 1 == toRow || (fromRow - 2 == toRow && isFirstMove(fromRow,fromCol)))
                return 1; 
        }else if(fromRow - 1 == toRow && (fromCol+1 == toCol || fromCol-1 == toCol))
            return board[toRow][toCol][PIECE] != 0; 
    }
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkKnight(int fromRow,int fromCol,int toRow,int toCol){
    if(isValidCoord(toRow,toCol)){ //no chequeo que sea un path valido dado que el caballo puede saltar
        if(fromRow+2==toRow || fromRow - 2 ==toRow){
            return fromCol + 1 == toCol || fromCol - 1 == toCol;
        }else if(fromCol + 2== toCol || fromCol - 2 == toCol){
            return fromRow + 1  == toRow || fromRow -1 == toRow;
        }
    } 
    return 0;
}

/*
alexa play despacito
Returns 1 if it's a valid move, 0 if not.
*/
int checkKing(int fromRow,int fromCol,int toRow,int toCol){
    if (isValidCoord(toRow,toCol)){
        if (fromRow==toRow)
            return fromCol + 1 == toCol || fromCol - 1 == toCol;
        else if (fromRow + 1 == toRow || fromRow - 1 == toRow)
            return fromCol + 1 == toCol || fromCol - 1 == toCol || fromCol == toCol;
    }
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkRook(int fromRow,int fromCol,int toRow,int toCol){
    if (isValidCoord(toRow,toCol))
        if((fromRow==toRow && fromCol != toCol) || (fromCol == toCol && fromRow != toRow) )
            return isValidRookPath(fromRow,fromCol,toRow, toCol);
    return 0;
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkBishop(int fromRow,int fromCol,int toRow,int toCol){
    if (isValidCoord(toRow,toCol))
        if (abs(fromRow-toRow) == abs(fromCol-toCol))  //como se mueve en diagonal, se deben mover n lugares de i y j.
            return isValidBishopPath(fromRow,fromCol,toRow,toCol);
    return 0; 
}

/*
Returns 1 if it's a valid move, 0 if not.
*/
int checkQueen(int fromRow,int fromCol,int toRow,int toCol){
    return checkBishop(fromRow,fromCol,toRow,toCol) || checkRook(fromRow,fromCol,toRow,toCol);
}