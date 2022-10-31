#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int main(int argc, char const *argv[]){
    
    //if(argc < 3) termina("Uso: ./main nomeFile numeroDaTestare");
    
    int n = atoi(argv[2]);
    int *a;
    int actualSize; // => Contiene il numero di el. dentro l'array

    FILE *fin = fopen("Input.txt", "r");
    FILE *fout = fopen(argv[1], "w");

    if(fout == NULL) termina("Apertura file output fallita");
    if(fin == NULL) termina("Apertura file input fallita");

    a = creaArray(n, &actualSize);//array di primi
    stampaArrayIntBin(a, actualSize, fout);
//------ Stampo --------
    int e = fseek(fin, 0, SEEK_END);
    if(e != 0 ) termina("Errore fseek");

    long t = ftell(fin);
    if(t < 0 ) termina("Errore ftell");

    int dim = t/sizeof(int);

    int *array = malloc(dim*sizeof(int));
    if(!array) termina("Allocazione memoria fallita");

    rewind(fin);

    e = fread(array, sizeof(int), dim, fin);
    if(e != dim) termina("Errore fread");

    stampaArrayInt(array, dim, stdout);

    if(fclose(fout) != 0) termina("Chiusura file outpu fallita");
    free(a);
    return 0;
}
