# Definsico il compilatore e le flag di compilazione
# Che vengono usate dalle regole implicite
CC = gcc
CFALGS = -g -Wall -O -std=c99
LDLIBS = -lm

# Se scriviamo solo make, verrà compilato di defult main
all: main

main: main.o utils.o
	gcc utils.o main.o -o main

main.o: main.c utils.h
	gcc -c main.c


clean:
	rm -f  main pipe *.o