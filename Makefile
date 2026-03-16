CC=gcc
CFLAGS=-Iinclude

all:
	$(CC) src/*.c main.c -o build/compiler $(CFLAGS)

run:
	./build/compiler