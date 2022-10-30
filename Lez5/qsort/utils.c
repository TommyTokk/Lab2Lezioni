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
        a[i] = rand() % 100;
    }

    return a;
}

char **caricaArrayStr(char **args, int dim){
    char **array = malloc(dim + sizeof(char*));
    if(!array) termina("Allocazione di memoria fallita");
    for(int i = 0; i < dim; i++){
        array[i] = args[i + 1];
    }

    return array;
}

int intCmp(const void *a, const void *b){
    int *n1 = (int *)a;
    int *n2 = (int *)b; 
    if(*n1 < *n2) return -1;
    else if(*n1 > *n2) return 1;
    else return 0;
}

int strCmp(const void *string1, const void *string2){
    char *s1 = (char *) string1;
    char *s2 = (char *) string2;
    return strcmp(s1, s2);
}

void stampaArray(int *array, int dim, FILE *fout){
    for (size_t i = 0; i < dim; i++){
        fprintf(fout, "%3d", array[i]);
    }
    fprintf(fout, "\n");
}

void stampaArrayStr(char **array, int dim, FILE *fout){
    for (size_t i = 0; i < dim; i++){
        fprintf(fout, "%s\n", array[i]);
    }
    fprintf(fout, "\n");
}