#include <stdio.h>

int max(int *array, int dim);
int min(int *array, int dim);
int *creaArrayInt(int dim, char **argv);
int *creaArrayFile(FILE *f, int *inArray);
void stampaArrayInt(int *array, int dim);
void stampaArrayFile(int *array, int dim, FILE *f);
void termina(char *msg);
void mergeSortInt(int* array, int dim);
void merge(int *leftHalf, int dimLeft, int *rightHalf, int dimRight, int *res);