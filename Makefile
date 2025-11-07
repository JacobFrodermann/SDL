CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L /usr/local/lib/ -L/usr/lib -lsharpyuv -ljxl -lyuv -lSDL2 -lSDL2_image -lspdlog -lfmt -std=c++11
CC=g++

setup:
	mkdir -p obj
	mkdir -p bin
	mkdir -p build/Debug

Asteroids.o:
	$(CC) $(CFLAGS) -g src/Objects/Asteroids.cpp -o obj/Asteroids.o
Beam.o:
	$(CC) $(CFLAGS) -g src/Objects/Beam.cpp -o obj/Beam.o
Ship.o:
	$(CC) $(CFLAGS) -g src/Objects/Ship.cpp -o obj/Ship.o
Game.o:
	$(CC) $(CFLAGS) -g src/Game.cpp -o obj/Game.o
InitError.o:
	$(CC) $(CFLAGS) -g src/Utils/InitError.cpp -o obj/InitError.o
Main.o:
	$(CC) $(CFLAGS) -g src/Main.cpp -o obj/main.o
Menu.o:
	$(CC) $(CFLAGS) -g src/Menu.cpp -o obj/Menu.o
State.o:
	$(CC) $(CFLAGS) -g src/State.cpp -o obj/State.o
Util.o:
	$(CC) $(CFLAGS) -g src/Utils/Util.cpp -o obj/Util.o

compile: setup Asteroids.o Beam.o Game.o InitError.o Main.o Menu.o State.o Util.o Ship.o

link: compile
	$(CC) $(LDFLAGS) obj/* -o bin/AsteroidShooter
run: link
	bin/AsteroidShooter
debug: compile
	$(CC) $(LDFLAGS) obj/* -o build/Debug/outDebug

all: link

clean:
	rm -rf bin obj
