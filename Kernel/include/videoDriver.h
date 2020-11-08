#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

void drawPixel(int row, int col, int color);

int drawCharFrom(int character, int row, int col, int color);

int drawChar(int character, int color);

int drawMatrix(int *matrix, int row, int col, int rows, int columns);

void clearScreen();

int screenHeight();

int screenWidth();

#endif