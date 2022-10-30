#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//PROTOTIPI

void caricaArrayStr(char **array, char **arg, int dim);
char *duplica(char *string);
void termina(char *msg);
void stampaArrayStr(char **array, int dim);

int main(int argc, char **argv)
{
    int dim = argc - 1;
    char *strings[dim];

    caricaArrayStr(strings, argv, dim);

    char *s = duplica(strings[0]);

    /*
        Usare il metodo duplica però potrebbe portare ad alcuni errori
        Per evitarli sfruttiamo le funzioni di libreria.
        In particolare esiste il metodo strdup che esegue proprio la duplicazione della stringa.

        strdup(char *s) -> Prende come parametro la stringa da duplicare e ritorna il puntatore della copia;
        Utilizza malloc per la preparazione dello spazio di memoria quindi dobbiamo ricordarci di liberare
        Lo spazio da lei allocato.
    */

    char *string = strdup(strings[0]);
    printf("%s\n", s);

    free(s);
    free(string);
    return 0;
}

//FUNZIONI

void caricaArrayStr(char **array, char **arg, int dim){
    for(int i = 0; i < dim; i++){
        array[i] = arg[i + 1];
    }
}

char *duplica(char *string){
    char *cpy;
    int len = strlen(string);// Calcolo la lunghezza della stringa passata per riferimento
    cpy = malloc(sizeof(char) * (len + 1));//Alloco lo spazio di memoria per ospitare la prossima stringa
    /*
        Uso len + 1 poiché devo ricordarmi che le stringhe terminano con il carattere speciale 0
        infatti la stringa cane in realtà viene vista come "cane\0"
        Quindi la sua lunghezza non è 4 ma bensì 5
     */

    if(!cpy) termina("Allocazione memoria fallita");

    /*
        Inoltre, siccome la nostra stringa è un array e l'abbiamo allocata con malloc
        Se ritornassimo direttamente cpy avremmo un problema con valgrind.
        I blocchi di memoria riferiti a cpy infatti non verrebbero mai liberati.
        Per ovviare a ciò non ritorniamo l'array creato con malloc ma il puntatore alla sua posizione.
    */
    char *res = cpy;

    while((*cpy = *string)){
        cpy++; string++;
    }

    return res;
}

void stampaArrayStr(char **array, int dim){
    for(int i = 0; i < dim; i++){
        printf("%s\n", array[i]);
    }
}

void termina(char *msg){
    puts(msg);
    exit(1);
}