CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L/usr/lib -lSDL2 
CC=g++


main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o
InitError.o: src/InitError.cpp
	$(CC) $(CFLAGS) src/InitError.cpp -o obj/InitError.o
prog: main.o InitError.o
	$(CC) $(LDFLAGS) obj/InitError.o obj/main.o -o sdl
run: prog
	./sdl
