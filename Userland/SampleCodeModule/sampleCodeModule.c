/* sampleCodeModule.c */
#include<lib64.h>
#include<types.h>
#include<string.h>
#include<syscalls.h>
#include<shell.h>
#include<standardIO.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	dateInfo info;
	date myDate = &info;
	getTime(myDate);
	char fecha [19];
	
	dateToString(myDate, fecha, '/', 18);
	initShell();
	return 0;
}