#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

int main(int argc, char **argv){
    /*int dim = argc - 1;
    if(argc < 2) termina("Uso: main s1 s2 ... (dove lgi sk sono stringhe)");*/

    int dim = atoi(argv[1]);

    int *array = caricaArray(dim);
    //char **array = caricaArrayStr(argv, dim);
    stampaArray(array, dim, stdout);
    qsort(array, dim, sizeof(int), &intCmp);
    puts("--- eseguo qsort ---");
    stampaArray(array, dim, stdout);
    free(array);

    return 0;
 }
 