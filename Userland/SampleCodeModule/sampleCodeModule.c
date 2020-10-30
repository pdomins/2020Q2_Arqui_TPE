/* sampleCodeModule.c */
#include<lib64.h>
#include<types.h>
#include<string.h>
#include<syscalls.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	dateInfo info;
	date myDate = &info;
	getTime(myDate);
	char fecha [19];
	
	dateToString(myDate, fecha, '/', 18);
	/*print(fecha);
	print("QUE PASA MAESTRO");
	print(" ah re troll sos USTEDES TAMBIEN QUe PRETENDEN JAJA");
	print(" Todas? ");
	print(" Estamos probando el salta dee linea automatico, si no funciona me mato xdxdxd");
	print("Todas.");*/
	char letra [2];
	letra[1]= 0;
	while(1){
		char i = getChar();
		if(i != 0){
			*letra = i;
			print(letra);
		}
	}
	return 0;
}