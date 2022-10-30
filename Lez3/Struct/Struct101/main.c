#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

/*
    Potrebbe capitare di dover lavorare con strutture dati complesse.
    Anche in C possiamo creare tipi COMPOSTI, ovvero tipi formati da altri tipi semplici
    Queste strutture dati prendono il nome di struct
*/

/*
Quello che va a fare l'istuzione sotto è creare un nuovo tipo chiamato coppia
formato da due interi

struct coppia{
    int primo;
    int secondo;
};

Portarsi dietro però ogni volta la parola struct è noioso
preferiamo quindi usare la parola magica typedef

Dopo questa istruzione infatti potremo evirtare di dire ogni volta
struct coppia c;

ma dire semplicemente coppia c;

La sintassi è
typedef tipoDaSostiuire{parametri} aliasDelTipo;
*/
typedef struct coppia{
    int primo;
    int secondo;
} coppia;

void coppiastampa(coppia a, FILE *fout);

int main(int argc, char const *argv[]){
    /*
        Nel main possiamo quindi ora andare a creare delle variabili con questo nuovo tipo
        Questo viene fatto tramite l'istruzione 
    
        struct coppia c1;  
    */
    coppia c1;

    /*
    Per accedere pssiamo usare la stessa sintassi usata per gli oggetti in JS quindi
    nomeOggetto.parametroOggetto
    */
    c1.primo = 5;
    c1.secondo = 10;

    coppia *arrayCoppie;
    FILE *fout = fopen("output.txt", "w");

    if(fout == NULL) termina("Apertura file fallita");

    if(argc < 3 || argc % 2 != 1) termina("Uso: main numero positivo pari di interi");

    int dim = (argc - 1)/2;

    arrayCoppie = malloc(dim * sizeof(coppia));

    if(!arrayCoppie) termina("Allocazione fallita");

    for(int i = 0; i < dim; i++){
        arrayCoppie[i].primo = atoi(argv[2*i+1]);
        arrayCoppie[i].secondo = atoi(argv[2*i+2]);
    }

    
    for(int i = 0; i < dim; i++){
        coppiastampa(arrayCoppie[i], fout);
    }

    if(fclose(fout) != 0) termina("Chiusura file fallita");
    free(arrayCoppie);


    return 0;
}

void coppiastampa(coppia a, FILE *fout){
    fprintf(fout, "(%d, %d)\n", a.primo, a.secondo);
}