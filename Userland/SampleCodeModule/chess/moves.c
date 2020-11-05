#include <chess.h>
#include <moves.h>

extern int board[8][8];
int isWhitePiece(int pieceNumber);
int isValidCoord(int toX, int toY);
int isAvailable(int toX, int toY);
int isValidPath(int fromX, int fromY,int toX, int toY);
int checkPawn(int fromX,int fromY,int toX,int toY, int playNum);
int checkKnight(int fromX,int fromY,int toX,int toY);
int checkKing(int fromX,int fromY,int toX,int toY);
int checkRook(int fromX,int fromY,int toX,int toY);
int checkBishop(int fromX,int fromY,int toX,int toY);
int checkQueen(int fromX,int fromY,int toX,int toY);

void checkIfKing(int piece){
    if (piece == 1 || piece == 7) kingEaten();
}

int move(int (*func) (int,int,int,int),int fromX,int fromY,int toX,int toY){
    if (func(fromX,fromY,toX,toY)){
        checkIfKing(board[toX][toY]);
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY] = 0;
        return 1;
    }
    return 0;
}


int movePawn(int fromX,int fromY,int toX,int toY, int playNum){
    if (checkPawn(fromX,fromY,toX,toY,playNum)){
        checkIfKing(board[toX][toY]); //chequea que no este comiendo un rey
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY] = 0;
        return 1;
    }
    return 0;
}

int moveKnight(int fromX,int fromY,int toX,int toY){
    return move(checkKnight,fromX,fromY,toX,toY);   
}

int moveKing(int fromX,int fromY,int toX,int toY){
     return move(checkKing,fromX,fromY,toX,toY);
}

int moveRook(int fromX,int fromY,int toX,int toY){
    return move(checkRook,fromX,fromY,toX,toY);
}

int moveBishop(int fromX,int fromY,int toX,int toY){
    return move(checkBishop,fromX,fromY,toX,toY);
}

int moveQueen(int fromX,int fromY,int toX,int toY){
    return move(checkQueen,fromX,fromY,toX,toY);
}


/*
Returns 0 if it's a white piece, 1 if nigger.
*/
int isWhitePiece(int pieceNumber){
    if ( pieceNumber >= 0 && pieceNumber <=6){
        return 1;
    }
    return 0;
}

int isValidCoord(int toX, int toY){

    return toX>=0 && toX <=7 && toY>=0 && toY <=7 && isAvailable(toX,toY);
}
int isAvailable(int toX, int toY){
    return board[toX][toY] == 0;
}

/*
Returns 0 if it's a valid path, 1 if not.
Also, checks that if a piece is found, its a FOEs one.
*/
int isValidPath(int fromX, int fromY,int toX, int toY){
    return 0;
    //TODO
}

/*
son validos:
    i + 1
    i + 2 si es la primera vez
    i + 1 && j + 1 || j-1 si come

Returns 0 if it's a valid move, 1 if not.
*/
int checkPawn(int fromX,int fromY,int toX,int toY,int playNum){
    if (!isValidCoord(toX,toY))return 0;
    if (fromY == toY && isAvailable(toX,toY)){ //si se esta moviendo
        if (fromX == toX + 1 ||(fromX = toX + 2 /*primer mov de cada peon*/)) return 1;
    }else if(fromY == toY+1 || fromY == toY-1){ //si come
        int piece = board[toX][toY];//la pieza que se comeria
        if (piece != 0 && isValidPath(fromX,fromY,toX,toY)){
            return toX == fromX+1 || toX == fromX-1; //si hay una pieza en esa posicion y se la puede comer
        }
    } 
    return 0;
}

/*
    son validas i+2 && (j+1 || j-1)
    son validas i-2 && (j+1 || j-1)
    son validas j+2 && (i+1 || i-1)
    son validas j-1 && (i+1 || i-1)

Returns 0 if it's a valid move, 1 if not.
*/
int checkKnight(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){ //no chequeo que sea un path valido dado que el caballo puede saltar
        if (fromX==toX+2){
            return fromY == toY+1 || fromY == toY-1;
        }else if (fromX==toX-2){
            return fromY == toY+1 || fromY == toY-1;
        }else if (fromY==toY+2){
            return fromX == toX+1 || fromX == toX-1;
        }else if (fromY==toY-2){
            return fromX == toX+1 || fromX== toX-1;
        }
    }
    return 0;
}

/*
    alexa play despacito
    para todas las direcciones una sola vez
    son validas i && (j+1 || j-1)
    son validas i+1 && (j+1 || j-1|| j)
    son validas i-1 && (j+1 || j-1|| j)

Returns 0 if it's a valid move, 1 if not.
*/
int checkKing(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
        if (isValidPath(fromX,fromY,toX,toY)){
            if (fromX==toX){
                return fromY == toY+1 || fromY == toY-1;
            }else if (fromX==toX+1){
                return fromY == toY+1 || fromY == toY-1 || fromY == toY;
            }else if (fromX==toX-1){
                return fromY == toY+1 || fromY == toY-1 || fromY == toY;
            }
        }
    }
    return 0;
}

/*
    son validas i && (j+n|| j-n)
    son validas j && (i+n|| i-n)

Returns 0 if it's a valid move, 1 if not.
*/
int checkRook(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
        if (isValidPath(fromX,fromY,toX,toY)){
            if (fromX==toX && fromY != toY) return 1; //se mueve verticalmente
            else if (fromY == toY && fromX != toX) return 1; //se mueve horizontalmente
        }
    }
    return 0;
}

/*
    son validas i+n && (j+n|| j-n)
    son validas i-n && (j+n|| j-n)

Returns 0 if it's a valid move, 1 if not.
*/
int checkBishop(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
        if (isValidPath(fromX,fromY,toX,toY))
            return /*abs*/fromX-toX == fromY-toY ? 0:1; //como se mueve en diagonal, se deben mover n lugares de i y j.
    }
    return 0; 
}
/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkQueen(int fromX,int fromY,int toX,int toY){
            return checkBishop(fromX,fromY,toX,toY)==1 || checkRook(fromX,fromY,toX,toY)==1;
}
