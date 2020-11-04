#include <apps.h>
#include <chess.h>
#include <syscalls.h>
#include <standardIO.h>
#include <types.h>
#include <string.h>
#include <stdint.h>
#include <lib64.h>

#define MEM_BYTES 32
#define BUFFER64_BITS 20

char array[] = {121,27,3,4,5,6,7,8,9,10};

programs commands[] =   {   {"about",about,"      Information about the O.S and authors."},
                            {"help", showApps,"       Menu of the differents apps."},
                            {"time", time, "       Displays the systems current time."}, 
                            {"inforeg", infoReg, "    Displays the registers current state."}, 
                            {"printmem", printMem,"   Prints on screen the first 32 bytes from a given position."},
                            {"chess", chess, "      Starts a PVP chess match. Try chess help for aditional info."},
                            {"clear",clear,"      Clears the current screen."},
                            {"exceptionZ",throwDivZero," Throws a divide by zero exception"},
                            {"exceptionOP",throwInvOpCode,"Throws an invalid Operation Code Exception"}
                        };

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
   // char toHex[BUFFER64_BITS];
   // turnToBaseN(array,16,toHex, BUFFER64_BITS);
   // println(toHex);
}
 
void chess(int args, char argv[][25]) {
    if (args == 0 || strcmp(argv[1],"new")== 0 ||strcmp(argv[1],"-n")==0|| strcmp(argv[1],"start")== 0 ||strcmp(argv[1],"-s")== 0){
        println("You're about to start a new chess game. Are you sure? [Y/n]");
        char ans;
        while ((ans != 'n' )&& ans != 'Y'){
            while((ans = getChar())){
                if (ans!=0){
                    if (ans == 'n'){
                        println("Need help? Enter chess help or chess -h to display a menu of the different options from which you can choose");
                        break;
                    }else if(ans == 'Y'){
                        println("Starting a new chess game...");
                        runChess(0);
                        break;
                    }else{
                        println("Invalid option. Please enter 'Y' if you want to start a new chess game. If not, enter 'n'.");
                        break;
                    }  
                }
            }
        }
    }else if (strcmp(argv[1],"resume")== 0 ||strcmp(argv[1],"-r")== 0||strcmp(argv[1],"continue")== 0 ||strcmp(argv[1],"-c")== 0){
        // aca habria que chequear que haya un juego previo inicializado, sino que pregunte si quiere empezar uno nuevo
        println("Please wait! The game will resume just from where you left it!");
    }else if (strcmp(argv[1],"help")== 0 ||strcmp(argv[1],"-h")== 0||strcmp(argv[1],"menu")== 0 ||strcmp(argv[1],"-m")== 0){
        int color = 0xf03fcd;
        printc("chess new, -n", color);printc(": ", color); printcln("   Starts a new chess game.", 0xcfd7e6);
        printc("chess resume, -r", color);printc(": ", color); printcln("Resumes last loaded game.", 0xcfd7e6);

    }else{
        print(argv[1]);println(": command not found");
    } 
    return;  
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
    invalidOpCode();
}

void about(){
    printcln("Clifford 1.0 by Arce Julian, Lombardi Matias & Domingues Paula.", 0xcfd7e6);
}