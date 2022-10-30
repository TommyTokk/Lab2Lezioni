#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"


//Stesso esempio di prima soltanto ch ora lavoriamo con i puntatori


int main(int argc, char const **argv){
    
    if(argc != 2) termina("Uso: main nomefile");

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen("output.txt", "w");

    if(fin ==  NULL) termina("Apertura file input fallita");
    if(fout ==  NULL) termina("Apertura file output fallita");
    int dim;

    //Voglio leggere un array di puntatori a capitale
    capitale **array = creaArraycapitale(fin, &dim);

    for(int i = 0; i < dim; i++){
        capitaleStampa(array[i], fout);
    }

    for(int i = 0; i < dim; i++){
        capitaleDistruggi(array[i]);
    }

    if(fclose(fin) != 0) termina("Chiusura file input fallita");
    if(fclose(fout) != 0) termina("Chiusura file output fallita");
    free(array);

    return 0;
}

