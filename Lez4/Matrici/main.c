#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

int main(int argc, char const *argv[]){
    if(argc != 3) termina("Uso: ./main #righe #colonne");
    int r = atoi(argv[1]);
    int c = atoi(argv[2]);

    /*
    int matrix[r][c];
    La rappresentazione logica di questa matrice è quella canonica
              1 2 3 4 5 6
    matrix = 7 8 9 10 11 12
            13 14 15 16 17 18
    Per ovvi motivi in memoria non può essere così
    le matrici infatti vengono rappresentate in modo lineare in memoria
    matrix = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18]
    Ma quindi come fa il compliatore a capire quando cambiare riga?
    Usa il numero di colonne con cui è stato inizializzato
    */

    int **matrix = creaMatriceDin(r,c);
    caricaMatriceInt(r, c, matrix);
    stampaMatriceDin(r, c, matrix, stdout);

    freeMatrice(r,matrix);


    return 0;
}

