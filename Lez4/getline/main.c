#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int main(int argc, char const *argv[]){
    
    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL) termina("Errore apertura file input");

    size_t n = 0;
    char *buff = NULL;

    while (true){
        
        int e = getline(&buff, &n, fin);
        if(e < 0) break;

        printf("%s", buff);
    }
    free(buff);
    printf("\n");
    
    if(fclose(fin) != 0) termina("Errore chiusura file input");

    return 0;
}
