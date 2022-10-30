#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>


typedef struct citta{
    char *name;
    int population;
    struct citta  *next;
}citta;


void termina(char *msg);
citta *cittaCrea(char *nome, int popolazione);
citta *listaCittaInserisci(citta *lis, citta *c);

void cittaStampa(citta *c, FILE *fout);
void cittaListaStampa(citta *lis, FILE *fout);
void cittaListaDistruggi(citta *lis);
void cittaDistruggi(citta *c);