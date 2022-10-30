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

//STRINGHE
char **creaArrayFileStr(FILE *fin, int *actualInArray){
    int size = 5;
    int actualSize = 0;

    char **array = malloc(size * sizeof(char *));

    if(!array) termina("Allocazione di memoria fallita");

    while (true){
        /*
            char buff[10];

            Per poter leggere una stringa da un file dobbiamo
            confrontarci con il problema dello spazio occupato.
            Potremmo pensare di dichiarare un buffer di una certa dimensione
            ed utilizzare quello.
            
            Ma cosa succede se la stringa è più grande?
            Risposta: Sono str[6] amari

            int e = fscanf(fin, "%9s", buff); <--- NON USARE 
            if(e != 1) break;
        */

        char *buff;// Buffer che conterrà la stringa letta
        
        /*
            Per il risolvere il problema del commento sopra usiamo un altro metodo;
            All'interno della fscanf possiamo passare il modificatore ms.
            Questo ci permetterà di fare la stessa cosa (leggere da un file)
            liberandoci, però, dalla fase di allocazione della memoria.
        */

        int e = fscanf(fin, "%ms", &buff);

        if(e != 1) break;

        if(size == actualSize){
            size *= 2;
            array = realloc(array, size * sizeof(char *));

            if(!array) termina("Realloc fallita");
        }

        assert(actualSize < size);
        /*
            Non ho più bisogno di dover duplicare la stringa
            dato che la fscanf andrà a mettere ogni stringa in un posto diverso
            
            array[actualSize] = strdup(buff);
        */
        array[actualSize] = buff;
        actualSize++;
    }

    array = realloc(array, actualSize * sizeof(char *));
    if(!array) termina("Realloc fallita");

    *actualInArray = actualSize;
    return array;
    
}

void stampaArrayStr(char **array, int dim){
    for(int i = 0; i < dim; i++){
        printf("%s\n", array[i]);
    }
}

//STRINGHE
capitale *capitaleCrea(char *nome, double lat, double lon){
    capitale *c = malloc(sizeof(*c));

    c -> lat = lat;
    c ->lon = lon;
    c -> nome = strdup(nome);
    c -> next = NULL;

    return c;
}

void capitaleDistruggi(capitale *c){
    free(c -> nome);
    free(c);
}


capitale *capitaleLeggi(FILE *fin){
    char buff[500];
    double lat, lon;

    int e = fscanf(fin, "%499s %lf %lf", buff, &lat, &lon);

    if(e == 3) return capitaleCrea(buff, lat, lon);
    if(e != EOF) termina("Errore nei dati di input");
    return NULL;
    
}

capitale **creaArraycapitale(FILE *fin, int *actualIn){

    int size = 5;
    int actualSize = 0;

    capitale **arr = malloc(size * sizeof(*arr));

    if(!arr) termina("Allocazione memoria fallita");

    while(true){
        
        capitale *c = capitaleLeggi(fin);

        if(c == NULL) break;

        if(size == actualSize){
            size *= 2;
                /*
                    Per aumentare la dimensione del mio array uso la funzione realloc
                    Questa prende l'array e la nuova dimensione per fare:
                    - Allocare uno spazio di memoria pari a (size*sizeof(int))
                    - Copiare i valori del vecchio array in quello appena creato
                    - Fare la free del primo array
                */
            arr = realloc(arr, size*sizeof(capitale));
            if(arr == NULL) termina("Realloc fallita");
        }
        assert(actualSize < size);
        arr[actualSize] = c;
        actualSize++;
    }
    
    arr = realloc(arr, actualSize*sizeof(capitale));
    if(!arr) termina("Realloc fallita");

    *actualIn = actualSize;
    return arr;
}


void capitaleStampa(capitale *c, FILE *fout){
    fprintf(fout, "%s (%lf, %lf)\n", c->nome, c->lat, c->lon);
}

void listaCapitaleStampa(capitale *lis, FILE *fout){
    while(lis != NULL){
        capitaleStampa(lis, fout);
        lis = lis -> next;
    }

    /* VERSIONE RISCORSIVA
    if(lis != NULL) capitaleStampa(lis, fout);
    listaCapitaleStampa(lis-next, fout);
    */
}

capitale *listaCapitaleInserisci(capitale *lis, capitale *c){
    assert(c != NULL);
    if(lis == NULL){
        c -> next = NULL;
        return c;
    }

    if(strcmp(c->nome, lis->nome) < 0){//il nome in c è più piccolo
        c->next = lis;
        return c;
    }
    else{
        // Scorro la lista per sapere dove mettere c
        //lis rimane il primo elemento
        lis->next = listaCapitaleInserisci(lis->next, c);
        return lis;
    }

    /*
    
    capitale *t = lis;
    while(p->next != NULL && strcmp(c->nome, t->next-> nome) > 0){
        t = t->next;
    }
    //devo inserire c tra t e t->next
    c->next = p->next;
    p->next = c;
    
    */
}

capitale *cancellaNordiche(capitale *lis, double lat){
     if(lis == NULL) return NULL;
     if(lis->lat > lat){
        capitale *tmp = lis->next;
        capitaleDistruggi(lis);
        cancellaNordiche(tmp, lat);
    }else{
        lis->next = cancellaNordiche(lis->next, lat);
        return lis;
    }
}

/*capitale *listaCapitaleCrea(FILE *fin){
    capitale *lis = NULL;

    while (true){
        capitale *c = capitaleLeggi(fin);
        if(c == NULL) break;
        lis = listaCapitaleInserisci(lis, c);
    }
    return lis;
}*/

void listaCapitaleDistruggi(capitale *lis){
    
    if(lis != NULL){
        listaCapitaleDistruggi(lis -> next);
        capitaleDistruggi(lis);
    }
}