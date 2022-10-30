#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int main(int argc, char const *argv[]){
    
    if(argc < 3) termina("Uso: ./main nomeFile numeroDaTestare");
    
    int n = atoi(argv[2]);
    int *a;
    int actualSize; // => Contiene il numero di el. dentro l'array

    FILE *fout = fopen(argv[1], "w");
    if(fout == NULL) termina("Apertura file fallita");

    a = creaArray(n, &actualSize);

    stampaArrayIntBin(a, actualSize, fout);

    if(fclose(fout) != 0) termina("Chiusura file fallita");
    free(a);
    return 0;
}
