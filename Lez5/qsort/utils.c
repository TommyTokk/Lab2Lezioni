#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

void termina(char *msg){
    puts(msg);
    exit(1);
}

int *caricaArray(int dim){
    int *a = malloc(dim * sizeof(int));
    if(!a) termina("Allocazione di memoria fallita");

    for(int i = 0; i < dim; i++){
        a[i] = rand() % 35;
    }

    return a;
}
int cmp(int *a, int *b){
    if(*a < *b) return -1;
    else if(*a > *b) return 1;
    else return 0;
}

void stampaArray(int *array, int dim, FILE *fout){
    for (size_t i = 0; i < dim; i++){
        fprintf(fout, "%3d", array[i]);
    }
    fprintf(fout, "\n");
}