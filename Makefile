CC=gcc
CFLAGS=-Iinclude

all:
	
	gcc src/*.c main.c -Iinclude -o build/compiler

run:
	./build/compiler