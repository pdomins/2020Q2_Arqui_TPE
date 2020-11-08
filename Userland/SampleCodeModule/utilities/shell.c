#include <shell.h>
#include <string.h>
#include <standardIO.h>
#include <syscalls.h>
#include <stdint.h>
#include <apps.h>

#define CHUNK 200

//-------------------------------------------
//                  SHERNELL
//-------------------------------------------

int hasProgram(char *input);

int tokenizeArguments(char *toToken, char tokens[10][25]);

char *initGreet = "user@TPArqui:~$ ";

void initShell() {
    char c;
    while (1) {
        printc(initGreet, 0x22ab00);
        char content[CHUNK] = {0};
        int contentLength = 0;
        while ((c = getChar()) != '\n') {
            if (c != 0) {
                switch (c) {
                    case '\b':
                        if (contentLength > 0) {
                            content[--contentLength] = 0;
                            removeChar();
                        }
                        break;
                    default:
                        content[contentLength++] = c;
                        putChar(c);
                }
            }
        }
        content[contentLength] = 0;
        if (contentLength > 0) {
            println("");
            char tokens[10][25] = {{0}}; //time param1
            int args = tokenizeArguments(content, tokens) - 1;// 1 es el nombre del programa
            int progAvail = hasProgram(tokens[0]);
            if (progAvail != -1) {
                commands[progAvail].f(args, tokens);

            } else {
                print(content);
                println(": command not found, try 'help' for help.");
            }
        } else {
            println("");
        }

        contentLength = 0;

    }
}

int tokenizeArguments(char *toToken, char tokens[10][25]) {
    return strtoks(toToken, ' ', tokens);
}

int hasProgram(char *input) {
    for (int i = 0; i < PROGRAMS; i++) {
        if (strcmp(input, commands[i].name) == 0) {
            return i;
        }
    }
    return -1;
}