#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int max(int *array, int dim){
    int max = array[0];
    for(int i = 1; i < dim; i++){
        if (array[i] > max) max = array[i];
    }

    return max;
}

int min(int *array, int dim){
    int min = array[0];
    for(int i = 1; i < dim; i++){
        if (array[i] < min) min = array[i];
    }

    return min;
}

int *creaArrayInt(int dim, char **argv){
    int *a;

    a = malloc(dim * sizeof(int));
    if(!a) termina("Allocazione fallita");

    for(int i = 0; i < dim; i++){
        a[i] = atoi(argv[i+1]);
    }

    return a;
}

void stampaArrayInt(int *array, int dim){
    for(int i = 0; i < dim; i++){
        printf("%4d", array[i]);
    }
    printf("\n");
}

void termina(char *msg){
    puts(msg);
    exit(1);
}

void merge(int *leftHalf, int dimLeft, int *rightHalf, int dimRight, int *res){
    int dimTot = dimLeft + dimRight; // Contiene la dimensione totale
    int leftIndex, rightIndex;
    leftIndex = rightIndex = 0;

    for(int i = 0; i < dimTot; i++){

        if(leftIndex == dimLeft){
            assert(rightIndex < dimRight);
            res[i] = rightHalf[rightIndex++];
            continue;
        }

        if(rightIndex == dimRight){
            assert(leftIndex < dimLeft);
            res[i] = leftHalf[leftIndex++];
            continue;
        }
        //Nessuna delle due parti è finita
        assert(leftIndex < dimLeft && rightIndex < dimRight);
        if(leftHalf[leftIndex] < rightHalf[rightIndex]){//L'elemento più piccolo si trova nella parte sinistra
            res[i] = leftHalf[leftIndex++];
        }else{//L'elemento più piccolo si trova nella parte destra
            res[i] = rightHalf[rightIndex++];
        }
    }

}

void mergeSortInt(int *array, int dim){

    assert(array != NULL);
    assert(dim > 0);
    
    if(dim == 1) return;

    int dimLeft = dim / 2;
    int dimRight = dim - dimLeft;


    mergeSortInt(array, dimLeft);
    mergeSortInt(&array[dimRight], dimRight);

    int *res = malloc(dim * sizeof(int));

    if(!res) termina("Allocazione di memoria fallita");

    merge(array, dimLeft , &array[dimRight], dimRight, res);
    for(int i = 0; i < dim; i++){
        array[i] = res[i];
    }

    free(res);
}



int *creaArrayFile(FILE *fin, int *inArray){
    int size = 5; // => contiene una dimensione di partenza per l'array
    int actualSize = 0;
    int *arr = malloc(size*sizeof(int));
    if(arr == NULL) termina("Allocazione fallita");


    /*
    Poiché non so quanti elementi io debba caricare all'interno del mio array
    Prima di fare qualsiasi inserimento confronto le variabili
    size & actualSize; nel caso siano uguali procedo con l'ingrandimento 
    del mio array
    */

    while(true){
        int num;
        int e = fscanf(fin, "%d", &num); //Leggo dal file
        if(e != 1) break;

        if(size == actualSize){
            size *= 2;
                /*
                Per aumentare la dimensione del mio array uso la funzione realloc
                Questa prende l'array e la nuova dimensione per fare:
                - Allocare uno spazio di memoria pari a (size*sizeof(int))
                - Copiare i valori del vecchio array in quello appena creato
                - Fare la free del primo array
                */
            arr = realloc(arr, size*sizeof(int));
            if(arr == NULL) termina("Realloc fallita");
        }
        assert(actualSize < size);
        arr[actualSize++] = num;
    }

    *inArray = actualSize;
    arr = realloc(arr, actualSize * sizeof(int));
    if(arr == NULL) termina("Realloc fallita");


    return arr;
}

void stampaArrayFile(int *array, int dim, FILE *f){
    for(int i = 0; i < dim; i++){
        /*
        Per scrivere sul file uso la funzione fprintf che vuole:
            - File in cui scrivere 
            - Formato del dato da scrivere
            - Cosa scrivre 
        */
        fprintf(f, "%4d\n", array[i]);
    }
    printf("\n");
}