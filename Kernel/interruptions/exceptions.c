#include <library.h>
#include <stdint.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception, uint64_t * rsp) {
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division();
			break;
		case INVALID_OPCODE_ID:
			invalid_opcode();
			break;
	}
	printRegisters(rsp);
	//resetState();
}

static void zero_division() {
	printError("Cannot divide by 0.");
	// Handler para manejar excepcíon
}

static void invalid_opcode() {
	printError("Invalid operation code.");
	// Handler para manejar excepcíon
}
/*
static void resetState(){
	return ;
}*/