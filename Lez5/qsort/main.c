#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

int main(int argc, char const *argv[]){
    int dim = atoi(argv[1]);

    int *array = caricaArray(dim);
    qsort(array, dim, sizeof(int), &cmp);
    stampaArray(array, dim, stdout);
    free(array);

    return 0;
 }
 