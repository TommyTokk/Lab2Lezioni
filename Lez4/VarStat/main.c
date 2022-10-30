#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>

int funct(int x);

int main(int argc, char const *argv[]){
    for (int i = 1; i < argc; i++){
        printf("Funct su %d, con risultato: %d\n",atoi(argv[i]), funct(atoi(argv[i])));
    }
    return 0;
}
int funct(int x){
    /*
    Le variabili statiche hanno un ciclo di vita diverso dalle altre variabili
    Esse infatti non vengono allocate nello stack e quindi non vengono perse al termine della funzione
    */
    static int y  = 0;//Questa inizializzazione avviene solo alla prima allocazione

    int res = x + y;
    printf("Valore di y: %d\n", y);

    y++;
    return res;
}