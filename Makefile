CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L/usr/lib -lSDL2 -lSDL2_image
CC=g++


main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o
InitError.o: src/InitError.cpp
	$(CC) $(CFLAGS) src/InitError.cpp -o obj/InitError.o
Util.o: src/Util.cpp
	$(CC) $(CFLAGS) src/Util.cpp -o obj/Util.o
prog: main.o InitError.o Util.o
	$(CC) $(LDFLAGS) obj/Util.o obj/InitError.o obj/main.o -o bin/sdl
run: prog
	./bin/sdl
