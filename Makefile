#file: Makefile
#description: used to build sunspots.c

CC = gcc
CFLAGS = -Wall -pedantic -std=c99
VALFLAGS = --tool=memcheck --leak-check=yes --show-leak-kinds=all 
DEBUG = -g
CFILES = sunspots.c hash.c
ARGS = ./data/
OUTPUT = sun

#creates and runs the executable
sun:	clean $(SOURCES) 
	$(CC) $(CFLAGS) -o $(OUTPUT) $(CFILES)
	./$(OUTPUT) $(ARGS)

#compile and run using gdb 
gdb:	clean $(SOURCES) 
	$(CC) $(CFLAGS) $(DEBUG) -o $(OUTPUT) $(CFILES)
	gdb --args $(OUTPUT) $(ARGS) 

#run using valgrind
valgrind: clean $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(CFILES)
	valgrind $(VALFLAGS)  $(OUTPUT) $(ARGS)

#clean up various executable and .o files
clean:
	rm -f core.*
	rm -f $(OUTPUT)
	rm -f a.out
	rm -f *.o
