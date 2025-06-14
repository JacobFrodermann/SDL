CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L /usr/local/lib/ -L/usr/lib -lsharpyuv -ljxl -lyuv -lSDL2 -lSDL2_image -lspdlog -lfmt -std=c++11
CC=g++

setup:
	mkdir -p obj
	mkdir -p bin

Asteroids.o:
	$(CC) $(CFLAGS) -g src/Asteroids.cpp -o obj/Asteroids.o
Beam.o:
	$(CC) $(CFLAGS) -g src/Beam.cpp -o obj/Beam.o
Game.o:
	$(CC) $(CFLAGS) -g src/Game.cpp -o obj/Game.o
InitError.o:
	$(CC) $(CFLAGS) -g src/InitError.cpp -o obj/InitError.o
Main.o:
	$(CC) $(CFLAGS) -g src/Main.cpp -o obj/main.o
Menu.o:
	$(CC) $(CFLAGS) -g src/Menu.cpp -o obj/Menu.o
State.o:
	$(CC) $(CFLAGS) -g src/State.cpp -o obj/State.o
Util.o:
	$(CC) $(CFLAGS) -g src/Util.cpp -o obj/Util.o
Ship.o:
	$(CC) $(CFLAGS) -g src/Ship.cpp -o obj/Ship.o

compile: setup Asteroids.o Beam.o Game.o InitError.o Main.o Menu.o State.o Util.o Ship.o

link: compile
	$(CC) $(LDFLAGS) obj/* -o bin/AsteroidShooter
run: link
	bin/AsteroidShooter
debug: link
	bin/AsteroidShooter --debug

all: link

clean:
	rm -rf bin obj
