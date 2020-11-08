#ifndef STDIO_H
#define STDIO_H

void println(char *toPrint); //print line

void print(char *toPrint); //print with format

void printc(char *toPrint, int color); //print with color

void printcln(char *toPrint, int color); //print with color and insert a jumpLine

void printcFrom(char *toPrint, int row, int col, int color); //prints with color from a certain position

void printFrom(char *toPrint, int row, int col); //prints from a certain position

char getChar();

void removeChar();

void putChar(char c);

void putCharFrom(char c, int row, int col);

#endif