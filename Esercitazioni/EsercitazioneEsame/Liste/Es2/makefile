# Definsico il compilatore e le flag di compilazione
# Che vengono usate dalle regole implicite
CC=gcc
CFLAGS=-g -Wall -O -std=gnu99
LDLIBS=-lm -lrt -pthread

EXEC = main
OUT = output

# Se scriviamo solo make, verrà compilato di defult main
all: ${EXEC}

${EXEC}: ${EXEC}.o utils.o


clean:
	rm -f  ${OUT} ${EXEC} *.o