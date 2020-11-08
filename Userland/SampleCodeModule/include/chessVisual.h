#ifndef CHESS_VISUAL_H
#define CHESS_VISUAL_H

#define BEIGE 0xe8c99b
#define BROWN 0xaa8255
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