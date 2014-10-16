EXECUTABLE=mini_cpu
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=
SOURCES=$(wildcard src/*.c src/*.h)
OBJECTS=$(wildcard src/*.o, $(SOURCES))

all: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o bin/$(EXECUTABLE)

debug: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -DDEBUG -o bin/$(EXECUTABLE)


clean:
	rm -vf bin/*
	rm -vf src/*.o
	rm -vf src/*.gch 
