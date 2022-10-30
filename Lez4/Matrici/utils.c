#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

void termina (char *msg){
    puts(msg);
    exit(1);
}
/*
Quando scriviamo delle funzioni con parametro delle matrici 
dobbiamo quindi indicare al compilatore quale sia il numero di colonne 

ATTENZIONE
Il compilatore non fa alcun tipo di controllo sul numero passato come # di colonne
nel parametro della funzione, quindi valore sbagliato ---> comportamento sbagliato
*/
void caricaMatriceInt(int r, int c, int **m){
    int cont = 1;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            m[i][j] = cont;
            cont++;
        }
    }
}

int **creaMatriceDin(int r, int c){
    int **m = malloc(r * sizeof(int *));
    if(!m) termina("Allocazione di memoria fallita");
    for(int i = 0; i < r; i++){
        /*
        m[i] = malloc(c * sizeof(int *));
        Usando malloc però quello che ci viene restituito dalla funzione 
        è totalmente imprevedibile visto che il SO potrebbe averci dato
        della memoria sporca. Per ovviare a ciò possiamo usare la funzione 
        calloc. Il funzionamento è simile alla malloc solo che inizializza
        lo spazio di memoria allocato con tutti 0
        */
        m[i] = calloc(c, sizeof(int *));
        if(!m[i]) termina("Allocazione di memoria fallita");
    }

    return m; 
}

void stampaMatrice(int r, int c, int m[][c], FILE *fout){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            fprintf(fout, "%4d", m[i][j]);
        }
        fprintf(fout, "\n");
    }
}

void stampaMatriceDin(int r, int c, int **m, FILE *fout){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            fprintf(fout, "%4d", m[i][j]);
        }
        fprintf(fout, "\n");
    }
}

void freeMatrice(int r, int **m){
    for(int i = 0; i < r; i++){
        free(m[i]);
    }

    free(m);
}
