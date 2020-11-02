#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

void drawPixel(int row, int col, int color);
int draw_char_from(int character, int row, int col, int color);
int draw_char(int character, int color);
void drawMatrix(int** matrix, int row, int col, int rows, int columns);
void clearScreen();

#endif