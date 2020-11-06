int abs(int value){
    return value >= 0 ? value: -value; 
}
int floor(double number){
    return number>=0? (int)number :(int) number - 1;
}

void scaleMatrix(char * original, int * matrix, int original_s, int scaled_s, int color, int back) {
    int scaled_factor = scaled_s / original_s;
    for(int i = 0; i < original_s; i++) {
        for(int j = 0; j < original_s; j++) {
            for(int y = i * scaled_factor; y < i * scaled_factor + scaled_factor; y++) {
                for(int x = j * scaled_factor; x < j * scaled_factor + scaled_factor; x++) {
                    if(original[i * original_s + j] == 'X') {
                        matrix[y * scaled_s + x] = color;
                    } else {
                        matrix[y * scaled_s + x] = back;
                    }
                }
            }
        }
    }
}


/**
 * Rotates de the index of a matrix 90° @times times.
 * @param i row index of the matrix
 * @param j col index of the matrix
 * @param dim Dimension of the matrix
 * @param times Do the rotation times times.
 */
void rotateIndex(int * i, int * j, int dim, int times) {
    if(times > 0) {
        for(int k = 0; k < times; k++) {
            int aux = *i;
            *i = *j;
            *j = dim - 1 - aux;

        }
    }
}