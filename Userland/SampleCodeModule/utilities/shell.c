#include <shell.h>
#include <string.h>
#include <standardIO.h>
#include <syscalls.h>
#include <stdint.h>
#include <apps.h>

#define CHUNK 200
#define PROGRAMS 1

int hasProgram(char * input);
typedef struct{
    char name[10];
    void(*f)(uint64_t *);
}programs;

programs commands[PROGRAMS] = {{"time", time}};
void initShell(){
    char *initGreet="user@TPArqui:~$ ";
    char c;
    while(1){
        printc(initGreet,0x22ab00);
        char content[CHUNK] = {0};
        int contentLength = 0;
        while( (c = getChar()) != '\n'){
            if(c != 0){
                switch(c){
                    case '\b':
                            if(contentLength > 0){
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
        if(contentLength > 0){
            println("");
            uint64_t vec[2] = {0};
            if(hasProgram(content)){
                commands[0].f(vec);
            }
            else{
                print(content);
                println(": command not found");
            }
        }
        else{
            println("");
        }
                    
        contentLength = 0;
    }
}
int tokenizeArguments(char* toToken){
    char tokens[10][25];
	return strtoks(toToken,' ',tokens);
}

int hasProgram(char *input){
    //int amountArgs = tokenizeArguments(input) - 1; //-1 dado que el 1token es el nombre del programa
    /*for (int i = 0; i < PROGRAMS; i++)
    {
        if (strcmp(input,commands[i].name)==0)
        {
            dateInfo myDate;
            commands[i].f(&myDate);
        }
        
    }*/
    

    if(strcmp(input,"time") == 0)
        return 1;
    return 0;
}