CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L/usr/lib -lSDL2 -lSDL2_image
CC=g++


main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o
InitError.o: src/InitError.cpp
	$(CC) $(CFLAGS) src/InitError.cpp -o obj/InitError.o
Util.o: src/Util.cpp
	$(CC) $(CFLAGS) src/Util.cpp -o obj/Util.o
Menu.o: src/Menu.cpp
	$(CC) $(CFLAGS) src/Menu.cpp -o obj/Menu.o
build: main.o InitError.o Util.o Menu.o
	$(CC) $(LDFLAGS) obj/Util.o obj/InitError.o obj/Menu.o obj/main.o -o bin/sdl
run: build
	./bin/sdl
all: build
