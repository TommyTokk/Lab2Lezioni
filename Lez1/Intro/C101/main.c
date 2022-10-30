#include <stdio.h>
#include <stdlib.h>

//PROTOTIPI
void caricaArrayV1(int *array, int dim);
void stampaArrayInt(int *array, int dim);
void termina(char *msg);
//PROTOTIPI

/* La funzione prende un intero N e carica i primi numeri < N*/

int main(int argc, char **argv){
    /*
    argc => contiene il numero di elementi passati alla linea di comando
    argv => contiene i valori effettivi
    */

   /*
   ATTENZIONE 
   Esiste una versione più semplice per allocare un array di interi
   La notazione per farlo sarebbe:
   int array[dim]; => Questo dichiara (in modo STATICO) un array di interi di dimensione dim
   Poiché dovremo usare spesso i puntatori e potrebbe capitare di lavorare con insiemi
   di cui non sapete nulla abituatevi ad usare la versione complicata qui sotto.
   */
   int num, e, *array;//Array è dichiarato tramite l'utilizzo di un puntatore
   puts("Inserisci il numero di elementi da caricare: ");
   e = scanf("%d", &num);

   if(e != 1) termina ("Lettura fallita");
   if(num < 1 ) termina("Il tuo array potrebbe essere vuoto");

    array = malloc(num * sizeof(int)); // Chiedo al SO di allocare della memoria per il mio array

    /*
    La funzione malloc cercherà di allocare un numero di byte, quanti?
    Il numero di byte è definito dal suo argomento.
    Poiché dobbiamo caricare degli interi il calcolo da fare è:
    numeroDaCaricare * dimensioneTipoInt, ma quanto pesa un int?
    Per sapere la dimensione di un qualcosa usiamo la funzione sizeof(qualcosa)

    prinf("%ld", sizeof(int)); ---> 4 quindi la dimensione di un int è 4 byte
    */

    /*
    Potrebbe accadere che la memoria richiesta non sia disponibile;
    in quel caso array varrà NULL
    */

    if(array == NULL) termina("Allocazione fallita");//Verifico che la memoria sia allocata

    caricaArrayV1(array, num);
    puts("Array:");
    stampaArrayInt(array, num);

    free(array);//Ovviamente devo liberare la memoria che il SO ha allocato
    return 0;
}

//FUNZIONI

void caricaArrayV1(int *array, int dim){
    for(int i = 0; i < dim; i++){
        array[i] = i; 
    }
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