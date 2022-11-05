#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include <fcntl.h>
#include "utils.h"

int main(int argc, char const *argv[]){
    if(argc!=3) {
        fprintf(stderr, "Uso:\n\t%s n nomefile\n\n",argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    if(n==0) {
        fprintf(stderr, "Inserisci un intero non nullo\n");
        exit(1);
    }
    if(n>0) scrivi1n(n,argv[2]);
    else scrivi1nsc(-n,argv[2]);
    return 0;
}
