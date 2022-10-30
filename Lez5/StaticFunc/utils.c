#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>
#include "utils.h"

static void shiftEl(int a[], int n);

void stampaArray(int a[], int n){
	for(int i = 0; i < n; i++){
		fprintf(stderr,"%d\n", a[i]);
	}	
}

static void shiftEl(int a[], int n){
	int tmp=0;
	int tail = n-1;
	for(int i = 0; i < n; i++){
		if(a[i] == 0){
			for(int j = tail; j > i; j--){
				if(a[j] != 0){
					tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
				}
			}
		}
	}
}

int sortArray(int a[], int n){
	int dim = 0;
	for(int i = 0; i < n; i++){
		if(a[i] % 5 == 0) a[i] = 0;
	}
	
	shiftEl(a, n);

	for(int k = 0; k < n; k++){
		if(a[k] != 0) dim++;
	}
	return dim;
}

void termina(char *messaggio){// stampa messaggio d'errore su stderr e termina 
  fprintf(stderr,"%s\n", messaggio);
  exit(1);
}