CFLAGS=-c -Wall -I/usr/include/SDL2 -D_REENTRANT -g 
LDFLAGS= -L/usr/lib -lSDL2 -lSDL2_image
CC=g++

setup:
	mkdir -p obj
	mkdir -p bin
compile: setup
	for file in src/*.cpp ; do \
		$(CC) $(CFLAGS) $$file -o obj/$$(echo $$file | cut -c 5- | rev | cut -c 4- | rev)o;\
		echo $$file;\
	done
link: compile
	$(CC) $(LDFLAGS) obj/* -o bin/AsteroidShooter
run: link
	./bin/AsteroidShooter
all: build
