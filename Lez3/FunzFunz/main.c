#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int somma(int n1, int n2);
int prodotto(int n1, int n2);
int applica(int n1, int n2, int (*f)(int, int));

int main(int argc, char const *argv[]){
    int a,b;
    if(argc != 3) termina("Uso: ./main I1 I2 (dove Ik sono interi");

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    printf("Somma: %d\nProdotto: %d\n", applica(a,b,&somma), applica(a,b,&prodotto));

    return 0;
}

int somma(int n1, int n2){return n1 + n2;}
int prodotto(int n1, int n2){return n1 * n2;}
int applica(int n1, int n2, int (*f)(int,int)){return f(n1,n2);}
