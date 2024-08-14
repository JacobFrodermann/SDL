CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L /usr/local/lib/ -L/usr/lib -lsharpyuv -lyuv -lSDL2 -lSDL2_image
CC=g++

setup:
	mkdir -p obj
	mkdir -p bin


main.o: setup src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o
InitError.o: setup src/InitError.cpp
	$(CC) $(CFLAGS) src/InitError.cpp -o obj/InitError.o
Util.o: setup src/Util.cpp
	$(CC) $(CFLAGS) src/Util.cpp -o obj/Util.o
Menu.o: setup src/Menu.cpp
	$(CC) $(CFLAGS) src/Menu.cpp -o obj/Menu.o
State.o: setup src/State.cpp
	$(CC) $(CFLAGS) src/State.cpp -o obj/State.o
Game.o : setup src/Game.cpp
	$(CC) $(CFLAGS) src/Game.cpp -o obj/Game.o
build: setup main.o InitError.o Util.o Menu.o State.o Game.o
	$(CC) $(LDFLAGS) obj/Util.o obj/InitError.o obj/State.o obj/Game.o obj/Menu.o obj/main.o -o bin/AsteroidShooter
link:
	$(CC) $(LDFLAGS) obj/Util.o obj/InitError.o obj/State.o obj/Game.o obj/Menu.o obj/main.o -o bin/AsteroidShooter
run: build
	./bin/AsteroidShooter
all: build

