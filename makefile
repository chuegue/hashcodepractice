PROJECT_NAME = hashcode

CC = gcc
CFLAGS = -g#-Wall -pedantic -std=c99 -O3 
OBJECTS = Main.o DynVec.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)
	rm -f *.o

Main.o: Main.c