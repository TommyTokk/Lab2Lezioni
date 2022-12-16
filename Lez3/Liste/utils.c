#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include "utils.h"

int max(int *array, int dim){
    int max = array[0];
    for(int i = 1; i < dim; i++){
        if (array[i] > max) max = array[i];
    }

    return max;
}

int min(int *array, int dim){
    int min = array[0];
    for(int i = 1; i < dim; i++){
        if (array[i] < min) min = array[i];
    }

    return min;
}

int *creaArrayInt(int dim, char **argv){
    int *a;

    a = malloc(dim * sizeof(int));
    if(!a) termina("Allocazione fallita");

    for(int i = 0; i < dim; i++){
        a[i] = atoi(argv[i+1]);
    }

    return a;
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

void merge(int a[], int na, int b[], int nb, int c[]) 
{
  int ia, ib;
	ia = ib = 0;

  for(int i=0;i<na+nb;i++) {
		// calcolo c[i]
		if(ia==na) {
			assert(ib<nb);  
			c[i] = b[ib++];
			continue;
		}
    if(ib==nb) {
			assert(ia<na);  
			c[i] = a[ia++];
			continue;
		}
		// nessuno dei due è finito
		assert(ia<na && ib<nb);
    if(a[ia]<b[ib]) {
			c[i] = a[ia++];
		}
		else {
			c[i] = b[ib++];
		}
	}
}

void mergesort(int a[], int n)
{
  assert(a!=NULL);
	assert(n>0);
	if(n==1) return; 

	int n1 = n/2;
	int n2 = n-n1;

	// primo array a[0 .... n1 -1]
	// secondo array a[n1 .... n-1]
	// Esempio n=11 n1 = 5:  a[0....4]  a[5 .... 10]
	// ordino ricorsivamente i due array
	mergesort(a, n1);
	mergesort(&a[n1],n2); // se si vuole si può scrivere  a + n1
	// alloca array temporaneo usato per il merge
	int *b = malloc(n*sizeof(int));
	if(b==NULL) termina("allocazione fallita");
	merge(a,n1,&a[n1],n2,b);
	// copia gli elementi di b[] (ora ordinati)
	// nell'array di input a[]
	for(int i=0;i<n;i++)
	  a[i] = b[i];
	free(b);
}

int *creaArrayFile(FILE *fin, int *inArray){
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

    while(true){
        int num;
        int e = fscanf(fin, "%d", &num); //Leggo dal file
        if(e != 1) break;

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
        assert(actualSize < size);
        arr[actualSize++] = num;
    }

    *inArray = actualSize;
    arr = realloc(arr, actualSize * sizeof(int));
    if(arr == NULL) termina("Realloc fallita");


    return arr;
}

void stampaArrayFile(int *array, int dim, FILE *f){
    for(int i = 0; i < dim; i++){
        /*
        Per scrivere sul file uso la funzione fprintf che vuole:
            - File in cui scrivere 
            - Formato del dato da scrivere
            - Cosa scrivre 
        */
        fprintf(f, "%4d\n", array[i]);
    }
    printf("\n");
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

     if(lis -> lat > lat){
        capitale *tmp = lis -> next;
        capitaleDistruggi(lis);
        return cancellaNordiche(tmp, lat);
     }else{
        lis -> next = cancellaNordiche(lis -> next, lat);
        return lis;
     }
}

capitale *listaCapitaleCrea(FILE *fin){
    capitale *lis = NULL;

    while (true){
        capitale *c = capitaleLeggi(fin);
        if(c == NULL) break;
        lis = listaCapitaleInserisci(lis, c);
    }
    return lis;
}

void listaCapitaleDistruggi(capitale *lis){
    
    if(lis != NULL){
        listaCapitaleDistruggi(lis -> next);
        capitaleDistruggi(lis);
    }
}

capitale *duplica(capitale *lis){
    if(!lis) return lis;

    if(lis -> lat == 20){
        capitale *tmp = lis -> next;
        capitale *dup = capitaleCrea(lis -> nome, lis -> lat, lis -> lon);
        lis -> next = dup;
        dup -> next = duplica(tmp);
        return lis;
    }

    lis -> next = duplica(lis -> next);
    return lis;
}