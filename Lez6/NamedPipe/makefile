# Definsico il compilatore e le flag di compilazione
# Che vengono usate dalle regole implicite
CC = gcc
CFALGS = -g -Wall -O -std=c99
LDLIBS = -lm

# Se scriviamo solo make, verrà compilato di defult main
all: scrittore lettore


scrittore: scrittore.o utils.o
	gcc utils.o scrittore.o -o scrittore

scrittore.o: scrittore.c utils.h
	gcc -c scrittore.c


lettore: lettore.o utils.o
	gcc utils.o lettore.o -o lettore

lettore.o: lettore.c utils.h
	gcc -c lettore.c

clean:
	rm -f  lettore scrittore *.o