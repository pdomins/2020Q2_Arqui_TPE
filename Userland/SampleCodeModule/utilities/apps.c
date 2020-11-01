#include <apps.h>
#include <syscalls.h>
#include <standardIO.h>
#include <types.h>
#include <string.h>
#include <stdint.h>

uint64_t array[4] = {1,2,3,4};

programs commands[] =   {   {"time", time, "    Displays the current system time."}, 
                            {"inforeg", infoReg, " Displays the registers current state."}, 
                            {"printmem", printMem,"Prints on screen the first 32 bits from the given position."},
                            {"help", showApps,"    Shows a static menu of the differents apps."},
                            {"chess", chess, "   Starts a PVP chess match."}};

int checkArgs(int args, int expected);

void infoReg(int args, char argv[][25]) {
    if(!checkArgs(args,0)) return;

    char regis[][4]={"R15","R14","R13","R12","R11","R10","R9 ","R8 ","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RIP","CS ","FLG","RSP"};
    uint64_t values[REGISTERS_AMOUNT];
    getRegisters(values);
    char buffer[10]={0};

    for (int i = 0; i < REGISTERS_AMOUNT; i++)
    {
        turnToBaseN(values[i], 16, buffer, 10);
        printc(regis[i],0xaa08d0);
        printc(":  ",0xaa08d0);
        print("0x");
        println(buffer);
    }
    
}

void printMem(int args, char argv[][25]){
    if(!checkArgs(args,1)) return;

    uint64_t * dir = (uint64_t *)stringToInt(argv[1]);
    uint64_t  dump[4];
    memoryDump(dir, dump);
    char buffer[10] = {0};

    for(int i = 0; i < 4; i++) {
        turnToBaseN((uint64_t)(dir + i), 16, buffer, 10);
        print(buffer);
        print(":  ");
        turnToBaseN(dump[i], 16, buffer, 10);
        print(buffer);
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
    char toHex[10];
    turnToBaseN((uint64_t)argv,16,toHex, 10);
    println(toHex);
}
 
void chess(int args, char argv[][25]) {
    
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