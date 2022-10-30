#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

/*void mergeSortInt(int* array, int dim){

    assert(array);
    assert(dim > 0);

    int dimLeft = dim /2;
    int dimRight = dim - dimLeft;

    if(dim == 1) return;

    mergeSortInt(array, dimLeft);
    mergeSortInt(&array[dimRight], dimRight);

    int *res = malloc(dim * sizeof(int));

    if(!res) termina("Allocazione di memoria fallita");

    merge(array, dimLeft , &array[dimRight], dimRight, res);
    for(int i = 0; i < dim; i++){
        array[i] = res[i];
    }

    free(res);
}

void merge(int *leftHalf, int dimLeft, int *rightHalf, int dimRight, int *res){

    int dimTot = dimLeft + dimRight;
    int leftIndex, rightIndex;
    leftIndex = rightIndex = 0;

    for(int i = 0; i < dimTot; i++){

        if(leftIndex == dimLeft){
            assert(rightIndex < dimRight);
            res[i] = rightHalf[rightIndex++];
            continue;
        }

        if(rightIndex == dimRight){
            assert(leftIndex < dimLeft);
            res[i] = leftHalf[leftIndex++];
            continue;
        }
        //Nessuna delle due parti è finita
        assert(leftIndex < dimLeft && rightIndex < dimRight);
        if(leftHalf[leftIndex] < rightHalf[rightIndex]){//L'elemento più piccolo si trova nella parte sinistra
            res[i] = leftHalf[leftIndex++];
        }else{//L'elemento più piccolo si trova nella parte destra
            res[i] = rightHalf[rightIndex++];
        }
    }

}*/