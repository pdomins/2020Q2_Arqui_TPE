/* sampleCodeModule.c */
#include<lib64.h>
#include<types.h>
#include<string.h>
#include<syscalls.h>
#include<shell.h>
#include<standardIO.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	initShell();
	return 0;
}