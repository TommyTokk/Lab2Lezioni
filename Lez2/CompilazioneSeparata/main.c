#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char **argv){
    if(argc < 2) termina("Uso: ./main i1 i2 ... in dove ik sono interi");

    int dim = argc - 1;
    int *array = creaArrayInt(dim, argv);

    //mergeSortInt(array, dim); <-- IGNORATELO NON FUNZIONA

    stampaArrayInt(array, dim);

    free(array);
    return 0;
}
