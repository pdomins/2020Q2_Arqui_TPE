/* sampleCodeModule.c */
#include<lib64.h>
#include<types.h>
#include<string.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	dateInfo info;
	date myDate = &info;
	sysTime(myDate);
	char fecha [19];
	
	dateToString(myDate, fecha, '/', 18);
	sysWrite(18, fecha);


	//char text [1];
	//sysRead(1, text);
	//sysWrite(1, text);
	
	return 0;
}