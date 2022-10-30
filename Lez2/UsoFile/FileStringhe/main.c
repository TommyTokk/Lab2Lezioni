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
    
    int actualSize;
    char **array;

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

    if(fin == NULL) termina("Apertura file di input non riuscita");

    
    /*int a = 44;
    char buffer[10];
    int b = 33;

    scanf("%s", buffer);

    printf("a = %d, buffer = %s, b = %d", a, buffer, b);*/

    array = creaArrayFileStr(fin, &actualSize);
    stampaArrayStr(array, actualSize);
    


    /*
    Siccome un file occupa della memoria dobbaimo fare come per la malloc
    e quindi liberare lo spazio occupato dal file
    */
    if(fclose(fin) != 0) termina("Chiusura file input fallita");

    for(int i = 0; i < actualSize; i++){
        free(array[i]);
    }
    free(array);


    return 0;
}
