#ifndef CHESS_VISUAL_H
#define CHESS_VISUAL_H


//Defines de colores
#define BEIGE 0xe8c99b //240,208,159 | 255,205,190 | 255,220,170 | 232, 201, 155
#define BROWN 0xaa8255 //170,80,40 | 180,110, 80 | 170,130,85
#define WHITE 0xFFFFFF
#define BLACK 0x0000000
#define color_log 0xADADAD
#define color_time 0xFFC32B
#define color_diff 0x38AD34

void printBoard();

void printTime(int whiteSecs, int blackSecs);

void printLog();

void updateLog(char *buffer, int turns);

void rotate();

void printExitMessage(int turns, int exitType);


#endif