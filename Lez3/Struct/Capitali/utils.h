#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 


int max(int *array, int dim);
int min(int *array, int dim);
int *creaArrayInt(int dim, char **argv);
int *creaArrayFile(FILE *f, int *inArray);
void stampaArrayInt(int *array, int dim);
void stampaArrayFile(int *array, int dim, FILE *f);
void termina(char *msg);
void mergeSortInt(int* array, int dim);
void merge(int *leftHalf, int dimLeft, int *rightHalf, int dimRight, int *res);

//STRINGHE
char **creaArrayFileStr(FILE *fin, int *actualInArray);
void stampaArrayStr(char **array, int dim);
//STRINGHE