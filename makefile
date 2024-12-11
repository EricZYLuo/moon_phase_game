
CC = g++
CFLAGS = -Wall -g

main: main.o map.o game.o player.o card.o
	$(CC) $(CFLAGS) -o main main.o map.o game.o player.o card.o

main.o: main.cpp card.h
	$(CC) $(CFLAGS) -c main.cpp

map.o: map.h card.h

game.o: game.h map.h

player.o: player.h

card.o: card.h


clean: $(RM) main