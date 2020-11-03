#include <apps.h>
#include <syscalls.h>
#include <standardIO.h>
#include <types.h>
#include <string.h>
#include <stdint.h>

#define MEM_BYTES 32
#define BUFFER64_BITS 20

char array[] = {121,27,3,4,5,6,7,8,9,10};

programs commands[] =   {   {"time", time, "    Displays the current system time."}, 
                            {"inforeg", infoReg, " Displays the registers current state."}, 
                            {"printmem", printMem,"Prints on screen the first 32 bytes from the given position."},
                            {"help", showApps,"    Shows a static menu of the differents apps."},
                            {"chess", chess, "   Starts a PVP chess match."},
                            {"clear",clear,"   Clears the current screen."}};

int checkArgs(int args, int expected);

void infoReg(int args, char argv[][25]) {
    if(!checkArgs(args,0)) return;

    char regis[][4]={"R15","R14","R13","R12","R11","R10","R9 ","R8 ","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RIP","CS ","FLG","RSP"};
    uint64_t values[REGISTERS_AMOUNT];
    getRegisters(values);
    char buffer[BUFFER64_BITS]={0};

    for (int i = 0; i < REGISTERS_AMOUNT; i++)
    {
        turnToBaseN(values[i], 16, buffer, BUFFER64_BITS);
        printc(regis[i],0xaa08d0);
        printc(":  ",0xaa08d0);
        print("0x");
        println(buffer);
    }
    
}

void printMem(int args, char argv[][25]){
    if(!checkArgs(args,1)) return;

    char * dir = (char *)stringToInt(argv[1]);
    char  dump[MEM_BYTES];
    memoryDump(dir, dump);
    char buffer[BUFFER64_BITS] = {0};

    for(int i = 0; i < MEM_BYTES; i++) {
        turnToBaseN((uint64_t)(dir + i), 16, buffer, BUFFER64_BITS);
        print(buffer);
        print(":  ");
      // TODO
        turnToBaseN(dump[i], 16, buffer, 3);
        print(buffer);
        print(" ");
        println(" ");
    }
}

void time(int args, char argv[][25]) {
    if(!checkArgs(args, 0)) return;

    dateInfo info;
    getTime(&info);
    char fecha [19] = {0};
    print("Local date at the moment is: ");
    dateToString(&info, fecha, '/', 18);
    print(fecha);
    println("");    
}

void showApps(int args, char argv[][25]) {
    if(!checkArgs(args, 0)) return;
    
    int color = 0xf03fcd;

    for(int i = 0 ; i < PROGRAMS ; i++){
        printc(commands[i].name, color);
        printc(": ", color);
        printcln(commands[i].description, 0xcfd7e6);
    }    
    char toHex[BUFFER64_BITS];
    turnToBaseN(array,16,toHex, BUFFER64_BITS);
    println(toHex);
}
 
void chess(int args, char argv[][25]) {
    
}

void clear(int args, char argv[][25]){
    if(!checkArgs(args, 0)) return;
    clearScreen();
}

int checkArgs(int args, int expected) {
    if(args != expected) {
        println("Invalid number of arguments");
        return 0; 
    }
    return 1; //1 es que esta OK
}

void throwDivZero(){
    int a = 0;
    int b = 5;
    a = b / a;
}

void throwInvOpCode(){
    
}
