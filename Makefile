CFLAGS=-std=c99 -Wall -g
CC=gcc

all: game

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
	rm game

game: main.o game.o world.o snake.o
	$(CC) main.o game.o world.o snake.o -ltermbox -lm -o game

