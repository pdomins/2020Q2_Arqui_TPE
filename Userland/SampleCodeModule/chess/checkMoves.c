#include <chess.h>

int isValidCoord(int toX, int toY){
    return toX>=0 && toX <=8 && toY>=0 && toY <=8;
}

/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkPawn(int fromX,int fromY,int toX,int toY){
    if (fromY == toY){ //si se esta moviendo
        if (fromX == toX + 1 /*||(es el primer movimiento && fromX = toX + 2)*/) return 1;
    }else if(fromY == toY+1 || fromY == toY-1){ //si come
        return fromX = fromX + 1;
    }
    return 0;
    /*son validos:
    i + 1
    i + 2 si es la primera vez
    i + 1 && j + 1 || j-1 si come
    */

}

/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkKnight(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
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
    //son validas i+2 && (j+1 || j-1)
    //son validas i-2 && (j+1 || j-1)
    //son validas j+2 && (i+1 || i-1)
    //son validas j-1 && (i+1 || i-1)
}

/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkKing(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
        if (fromX==toX){
            return fromY == toY+1 || fromY == toY-1;
        }else if (fromX==toX+1){
            return fromY == toY+1 || fromY == toY-1 || fromY == toY;
        }else if (fromX==toX-1){
            return fromY == toY+1 || fromY == toY-1 || fromY == toY;
        }
    }
    return 0;
    //alexa play despacito
    // para todas las direcciones una sola vez
    //son validas i && (j+1 || j-1)
    //son validas i+1 && (j+1 || j-1|| j)
    //son validas i-1 && (j+1 || j-1|| j)
}

/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkRook(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
        if (fromX==toX && fromY != toY) return 1; //se mueve verticalmente
        else if (fromY == toY && fromX != toX) return 1; //se mueve horizontalmente
    }
    return 0;
    //son validas i && (j+n|| j-n)
    //son validas j && (i+n|| i-n)

}

/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkBishop(int fromX,int fromY,int toX,int toY){
    if (isValidCoord(toX,toY)){
    return fromX-toX == fromY-toY ? 0:1; //como se mueve en diagonal, se deben mover n lugares de i y j.
    }
    return 0;
    //son validas i+n && (j+n|| j-n)
    //son validas i-n && (j+n|| j-n)
}

/*
Returns 0 if it's a valid move, 1 if not.
*/
int checkQueen(int fromX,int fromY,int toX,int toY){
    return checkBishop(fromX,fromY,toX,toY)==1 && checkRook(fromX,fromY,toX,toY)==1;
}
