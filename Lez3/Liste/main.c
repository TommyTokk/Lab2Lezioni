#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int main(int argc, char const **argv){
    
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen("outputN.txt", "w");
    if(fin == NULL) termina("Errore apertura file input");
    if(fout == NULL) termina("Errore apertura file output");
    capitale *lis = NULL;

    lis = listaCapitaleCrea(fin);    
    cancellaNordiche(lis, 20);
    listaCapitaleStampa(lis, fout);
    listaCapitaleDistruggi(lis);

    if(fclose(fin) != 0) termina("Errore chiusura file input");
    if(fclose(fout) != 0) termina("Errore chiusura file output");
    return 0;
}
