/* sampleCodeModule.c */
#include<lib64.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	sysWrite(1,"a");
	char time[9];
	sysTime(time);
	sysWrite(8,time);

	char text [1];
	while(1){
	sysRead(1, text);
	sysWrite(1, text);
	}
	
	return 0;
}