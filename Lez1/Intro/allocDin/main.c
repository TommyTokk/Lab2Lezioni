#include <stdio.h>
#include <stdlib.h>

/*
Funzione che prende in ingresso un intero N e calcola i numeri primi <= N
*/

//PROTOTIPI
void stampaArrayInt(int *array, int dim);
void termina(char *msg);
int primo(int num);
//PROTOTIPI

int main(int argc, char const **argv)
{
    int n, e;
    puts("Inserisci un numero da testare");
    e = scanf("%d", &n);

    if(e != 1) termina("Lettura fallita");

    int *a;
    int size = 5; // => contiene una dimensione di partenza per l'array
    int actualSize = 0; // => Contiene il numero di el. dentro l'array

    a = malloc(size * sizeof(int));

    if(a == NULL) termina("Allocazione fallita");

    /*
    Poiché non so quanti elementi io debba caricare all'interno del mio array
    Prima di fare qualsiasi inserimento confronto le variabili
    size & actualSize; nel caso siano uguali procedo con l'ingrandimento 
    del mio array
    */
    for(int i = 2; i <= n; i++){
        if(primo(i)){
            if(size == actualSize){
                size *= 2;
                /*
                Per aumentare la dimensione del mio array uso la funzione realloc
                Questa prende l'array e la nuova dimensione per fare:
                - Allocare uno spazio di memoria pari a (size*sizeof(int))
                - Copiare i valori del vecchio array in quello appena creato
                - Fare la free del primo array
                */
                a = realloc(a, size*sizeof(int));
                if(a == NULL) termina("Realloc fallita");
            }
            a[actualSize] = i;
            actualSize++;
        }
    }

    a = realloc(a, actualSize * sizeof(int));
    if(a == NULL) termina("Realloc fallita");

    stampaArrayInt(a, actualSize);
    free(a);
    return 0;
}
//FUNZIONI
int primo(int num){
    for(int i = 2; i < num; i++){
        if(num % i == 0) return 0;
    }

    return 1;
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
//FUNZIONI