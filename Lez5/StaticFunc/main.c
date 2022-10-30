#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include "utils.h"


int main(int argc, char *argv[]) {
	if(argc < 2){
		fprintf(stderr, "Uso:\n\t   %s i1 [i2 i3 i4 ... ]\n", argv[0]);
		fprintf(stderr, "dove i valori  i1 i2 ...  sono interi\n");
		exit(1);
	}
	
	int dim = argc - 1;
	int *a = malloc(sizeof(int)*dim);
	
	if(!a) termina("Allocazione memoria fallita");
	
	for(int i = 0; i < dim; i++){
		a[i] = atoi(argv[i+1]);
	}
	
	int res = sortArray(a,dim);
	
	a = realloc(a, sizeof(int)* res);
	
	if(!a) termina("Aggiornamento memoria non riuscito");
	
	stampaArray(a, res);
	
	free(a);
	return 0;
}

