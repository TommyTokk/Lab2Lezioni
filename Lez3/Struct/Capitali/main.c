#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

typedef struct{
    char *nome;
    double lat;
    double lon;
} capitale;

/*
Poiché dobbiamo a tutti gli effetti creare un oggetto andiamo a fare due metodi particolari
Il primo serve per la sua costruzione e si chiama costruttore (constructor per gli anglofoni)
Il secondo serve per la sua distruzione
*/

capitale capitaleCrea(char *nome, double lat, double lon);
void capitaleDistruggi(capitale c);

capitale capitaleLeggi(FILE *fin);
capitale *creaArraycapitale(FILE *fin, int *actualIn);
void capitaleStampa(capitale c, FILE *fout);


int main(int argc, char const **argv){
    
    if(argc != 2) termina("Uso: main nomefile");

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen("output.txt", "a");

    if(fin ==  NULL) termina("Apertura file input fallita");
    if(fout ==  NULL) termina("Apertura file output fallita");
    int dim;

    capitale *array = creaArraycapitale(fin, &dim);

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

capitale capitaleCrea(char *nome, double lat, double lon){
    capitale c;

    c.lat = lat;
    c.lon = lon;
    c.nome =strdup(nome);

    


    return c;
}

void capitaleDistruggi(capitale c){
    free(c.nome);
}


capitale capitaleLeggi(FILE *fin){
    char buff[500];
    double lat, lon;

    int e = fscanf(fin, "%499s %lf %lf", buff, &lat, &lon);

    if(e == 3) return capitaleCrea(buff, lat, lon);
    capitale c;
    c.nome = NULL;
    c.lat = 100;//valore illegale
    c.lon = 200;//valore illegale

    return c;
}

capitale *creaArraycapitale(FILE *fin, int *actualIn){

    int size = 5;
    int actualSize = 0;

    capitale *arr = malloc(size * sizeof(capitale));

    if(!arr) termina("Allocazione memoria fallita");

    while(true){
        
        capitale c = capitaleLeggi(fin);

        if(c.nome == NULL) break; 
        if(size == actualSize){
            size *= 2;
                /*
                    Per aumentare la dimensione del mio array uso la funzione realloc
                    Questa prende l'array e la nuova dimensione per fare:
                    - Allocare uno spazio di memoria pari a (size*sizeof(int))
                    - Copiare i valori del vecchio array in quello appena creato
                    - Fare la free del primo array
                */
            arr = realloc(arr, size*sizeof(capitale));
            if(arr == NULL) termina("Realloc fallita");
        }
        assert(actualSize < size);
        arr[actualSize] = c;
        actualSize++;
    }
    
    arr = realloc(arr, actualSize*sizeof(capitale));
    if(!arr) termina("Realloc fallita");
    
    *actualIn = actualSize;
    return arr;
}

void capitaleStampa(capitale c, FILE *fout){
    fprintf(fout, "%s (%lf, %lf)\n", c.nome, c.lat, c.lon);
}