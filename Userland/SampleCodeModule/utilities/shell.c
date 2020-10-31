#include<shell.h>
#include<string.h>
#include<syscalls.h>
#define CHUNK 200

static char ** programs;
static int prueba = 0;
void initShell(){
    char *initGreet="user@TPArqui:~$ ";
    char c;
    int contentLength = 0, contentSize = CHUNK;
    while(1 /*|| excepcion*/){
        printColor(initGreet,0x22ab00);
        char *content = {0};
        while( (c = getChar()) != '\n'){
            if(c != 0){
                content[contentLength++] = c;

                char toPrint[2]={0};
                toPrint[0]=c;
                print(toPrint);
            }
        }
        if(hasProgram(content)){
            println("");
        }
        else{
            println(content);
            println(": command not found");
        }              
        contentLength = 0;
    }
}

int hasProgram(char * input){
    //if es llamada al ajedrez
    return prueba ? 0:1;
}