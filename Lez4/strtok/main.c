#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"


int main(int argc, char const *argv[]){

    if(argc < 2) termina("Uso: main nomefile");
    
    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL) termina("Errore apertura file input");

    size_t n = 0;
    char *buff = NULL;
    citta *lis = NULL;
    

    while (true){
        
        int e = getline(&buff, &n, fin);
        if(e < 0) break;

        //printf("%s (%p)\n", buff, buff);

        char *name = strtok(buff, ";");
        
        if(name == NULL) termina("Errore file di input (1)");

        char *pop = strtok(NULL, ";");

        if(pop == NULL) termina ("Errore file input (2)");

        citta *c = cittaCrea(name, atoi(pop));
        lis = listaCittaInserisci(lis, c);

        /*
        char *token = strtok(buff, ";");

        while (token != NULL){
            printf("%s (%p)\n", token, token);
            token = strtok(NULL, ";");
        }

        printf("=================\n");
        */
    }
    free(buff);
    
    if(fclose(fin) != 0) termina("Errore chiusura file input");
    cittaListaStampa(lis, stdout);
    cittaListaDistruggi(lis);

    return 0;
}

