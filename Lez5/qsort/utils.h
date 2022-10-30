#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>

void termina(char *msg);

int *caricaArray(int dim);
char **caricaArrayStr(char **args, int dim);
int intCmp(const void *a, const void *b);
int strCmp(const void *string1, const void *string2);
void stampaArray(int *array, int dim, FILE *fout);
void stampaArrayStr(char **array, int dim, FILE *fout);