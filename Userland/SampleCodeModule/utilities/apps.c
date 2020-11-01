#include <apps.h>
#include <syscalls.h>
#include <standardIO.h>
#include <types.h>
#include <string.h>

void infoReg(uint64_t* vec) {

}

void printMem(uint64_t* vec) {

}

void time(uint64_t*vec) {
    dateInfo info;
    getTime(&info);
    char fecha [19] = {0};
    print("Local date at the moment is: ");
    dateToString(&info, fecha, '/', 18);
    print(fecha);
    println("");    
}

void help(uint64_t* vec) {

}
 
void chess(uint64_t* vec) {
    
}