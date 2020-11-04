include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
LIBRARIES=$(wildcard libraries/*.c)
UTILITIES=$(wildcard utilities/*.c)
CHESS=$(wildcard chess/*.c)
SOURCES_ASM=$(wildcard asm/*.asm) 
OBJECTS=$(SOURCES:.c=.o)
LIBRARIES_OBJECTS=$(LIBRARIES:.c=.o)
UTILITIES_OBJECTS=$(UTILITIES:.c=.o)
CHESS_OBJECTS=$(CHESS:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=_loader.c

LOADEROBJECT=_loader.o
STATICLIBS=

all: $(MODULE)

$(MODULE): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(LIBRARIES_OBJECTS) $(UTILITIES_OBJECTS) $(CHESS_OBJECTS)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(LIBRARIES_OBJECTS) $(UTILITIES_OBJECTS) $(CHESS_OBJECTS)
	
%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(GCC) $(GCCFLAGS) $(LOADERSRC) -c -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin libraries/*.o utilities/*.o chess/*.o

.PHONY: all clean
