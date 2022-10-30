#include <stdio.h>
#include <stdlib.h>

/*
Funzione che prende in ingresso un intero N e calcola i numeri primi <= N
*/

//PROTOTIPI
int *creaArray(int n, int *actualSize);
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
    int actualSize; // => Contiene il numero di el. dentro l'array

    a = creaArray(n, &actualSize);

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

int *creaArray(int n,int *in){
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
                arr = realloc(arr, size*sizeof(int));
                if(arr == NULL) termina("Realloc fallita");
            }
            arr[actualSize] = i;
            actualSize++;
        }
    }

    *in = actualSize;
    arr = realloc(arr, actualSize * sizeof(int));
    if(arr == NULL) termina("Realloc fallita");


    return arr;
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