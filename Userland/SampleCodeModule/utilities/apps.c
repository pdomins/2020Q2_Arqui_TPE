#include <apps.h>
#include <syscalls.h>
#include <standardIO.h>
#include <types.h>
#include <string.h>


programs commands[] =   {{"time", time, "Displays the current system time."}, 
                            {"inforeg", infoReg, "Displays the registers current state."}, 
                            {"printmem", printMem,"Druck die erste 32 bits von einer Position auf dem Bildschirm."},//"Prints on screen the first 32 bits from the position given"},
                            {"help", showApps,"Shows a static menu of the differents apps."},
                            {"chess", chess, "Starts a PVP chess match."}};

int checkArgs(int args, int expected);

void infoReg(int args, char argv[][25]) {

}

void printMem(int args, char argv[][25]){
    
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