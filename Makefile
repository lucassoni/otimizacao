CFLAGS = -Wall
LDFLAGS = -lm -ldl
DEBUG_FLAGS = -g -DDEBUG
COMPILER = -std=gnu99

all: bb

bb: bb.c bblib.o
	gcc -o bb bb.c bblib.o $(CFLAGS) $(LDFLAGS)

bblib.o: bblib.c bblib.h
	gcc -c bblib.c -o bblib.o

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f bb