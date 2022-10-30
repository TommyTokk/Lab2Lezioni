#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int main(int argc, char **argv){

    if(argc != 2) termina("Uso: main nomeFile");
    
    int *arr, actualSize;

    /*
    Dichiaro un puntatore al file;
    Per farlo usiamo la funzione fopen() che prende come parametri:
    - Nome del file da aprire
    - Modalità di apertura del file
        - w -> write
        - r -> read
        - a -> append
        .
        .
        .
        Ce ne sono altri recuperabili tranquillamente su google 
    */
    
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen("numeri.txt", "w");

    if(fin == NULL) termina("Apertura file di input non riuscita");
    if(fout == NULL) termina("Apertura file di output non risucita");// Controllo se il file è stato aperto correttamente

    arr = creaArrayFile(fin, &actualSize);
    stampaArrayFile(arr, actualSize, fout);

    /*
    Siccome un file occupa della memoria dobbaimo fare come per la malloc
    e quindi liberare lo spazio occupato dal file
    */
    if(fclose(fin) != 0) termina("Chiusura file input fallita");
    if(fclose(fout) != 0) termina("Chiusura file output fallita");

    free(arr);


    return 0;
}
