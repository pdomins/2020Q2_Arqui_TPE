#include<shell.h>
#include<string.h>
#include<syscalls.h>
#define CHUNK 200

int hasProgram(char * input);

static char ** programs;
void initShell(){
    char *initGreet="user@TPArqui:~$ ";
    char c;
    while(1 /*|| excepcion*/){
        printColor(initGreet,0x22ab00);
        char content[CHUNK] = {0};
        int contentLength = 0;
        while( (c = getChar()) != '\n'){
            if(c != 0){
                switch(c){
                    case '\b':
                            if(contentLength > 0){
                                print("\b");
                                content[--contentLength] = 0;
                            }
                            break;
                    default:
                       // if (contentLength<30){
                        content[contentLength++] = c;
                        char toPrint[2]={0};
                        toPrint[0]=c;
                        print(toPrint);    
                   // }
                }
            }

            
        }
        if(contentLength > 0){
            if(hasProgram(content)){
                println("");
            }
            else{
                println(content);
                println(": command not found");
            }
        }
        else
        {
            println("");
        }
                      
        contentLength = 0;
    }
}

int hasProgram(char *input){
    //if es llamada al ajedrez
    return 1;
}