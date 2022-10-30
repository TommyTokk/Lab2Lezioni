#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int primo(int num){
    for(int i = 2; i < num; i++){
        if(num % i == 0) return 0;
    }

    return 1;
}

int *creaArray(int n,int *in){
    int size = 5; // => contiene una dimensione di partenza per l'array
    int actualSize = 0;
    int *arr = malloc(size*sizeof(int));
    if(arr == NULL) termina("Allocazione fallita");
    for(int i = 2; i <= n; i++){
        if(primo(i)){
            if(size == actualSize){
                size *= 2;

                arr = realloc(arr, size*sizeof(int));
                if(arr == NULL) termina("Realloc fallita");
            }
            arr[actualSize] = i;
            actualSize++;
        }
    }

    *in = actualSize;
    arr = realloc(arr, actualSize * sizeof(int));
    if(arr == NULL) termina("Realloc fallita");


    return arr;
}

void stampaArrayIntBin(int *array, int dim, FILE *fout){
    /*for(int i = 0; i < dim; i++){
        fprintf(fout, "%4d", array[i]);
    }
    fprintf(fout,"\n");*/
    int e = fwrite(array, sizeof(int), dim, fout);
    if(e != dim) termina("Scrittura file fallita");
}

void termina(char *msg){
    puts(msg);
    exit(1);

}