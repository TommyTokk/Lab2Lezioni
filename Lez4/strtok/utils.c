#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

void termina(char *msg){
    puts(msg);
    exit(1);
}

citta *cittaCrea(char *name, int population){
    citta *c = malloc(sizeof(*c));

    if(!c) termina("Allocazione di memoria fallita");

    c -> name = strdup(name);
    c -> population = population;
    c-> next = NULL;

    return c;
}


citta *listaCittaInserisci(citta *lis, citta *c){
    assert(c != NULL);
    if(lis == NULL){
        c -> next = NULL;
        return c;
    }

    if(strcmp(c->name, lis->name) < 0){//il nome in c è più piccolo
        c->next = lis;
        return c;
    }
    else{
        // Scorro la lista per sapere dove mettere c
        //lis rimane il primo elemento
        lis->next = listaCittaInserisci(lis->next, c);
        return lis;
    }

}
void cittaStampa(citta *c, FILE *fout){
    fprintf(fout, "%s (%d)\n", c -> name, c -> population);
}

void cittaListaStampa(citta *lis, FILE *fout){
    while(lis != NULL){
        cittaStampa(lis, fout);
        lis = lis -> next;
    }
}

void cittaDistruggi(citta *c){
    free(c -> name);
    free(c);
}

void cittaListaDistruggi(citta *lis){
    if(lis != NULL) {cittaListaDistruggi(lis -> next);cittaDistruggi(lis);}
}