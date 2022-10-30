#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>

void termina(char *msg);

/*
A volte abbiamo la necessità di considerare i puntatori tutti sotto lo stesso tetto
L'idea di un qualcosa di generico lo abbiamo già incontrato con il valore speciale NULL
NULL infatti, oltre a rappresentare il puntatore non valido, può essere asseganto a qualsiasi 
variabile di qualsiasi tipo.
Lo stesso ragionamento possiamo farlo per un puntatore speciale, ovvero il puntatore a void
void * (in realtà la maggior parte delle funzioni viste fin ora usano già il puntatore a void)
Questo tipo di puntatore viene chiamato puntatore genereico e la sua caratteristica è quella che
può essere asseganto a qualunque tipo senza che il compilatore dia errore
*/

int main(int argc, char const *argv[]){
    int *array = malloc (10 * sizeof(int));
    if(!array) termina ("Allocazione di memoria fallita");

    char *string = malloc (10 * sizeof(char));
    if(!string) termina ("Allocazione di memoria fallita");

    for(int i = 0; i < 10; i++){
        array[i] = i;
    }

    void *p = array;
    /*
    Purtroppo non è tutto oro ciò che luccica, infatti sì, 
    un puntatore a void può essere asseganto a qualsiasi cosa ma 
    un puntatore a void NON può essere deferenziato; 
    Infatti a riga 34 possiamo tranquillamente notare che p ed array siano uguali
    Però provando a fare
    int x = p[0] otterremmo un errore 
    */

    int * newP = (int*)p;
    /*
    Sempre guardando la linea 34 possiamo però notare che p ed array puntano però 
    alla stessa cosa; possiamo quindi in realtà deferenziare un puntatore a void 
    facendo il cast al tipo a cui siamo interessati
    */
    printf("%d\n", newP[0]);

    return 0;
}

void termina(char *msg){
    puts(msg);
    exit(1);
}
