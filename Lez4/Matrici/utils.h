#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>

void termina (char *msg);
void stampaMatrice(int r, int c, int m[][c], FILE *fout);
void freeMatrice(int r, int **m);
void stampaMatriceDin(int r, int c, int **m, FILE *fout);
void caricaMatriceInt(int r, int c, int **m);
int **creaMatriceDin(int r, int c);