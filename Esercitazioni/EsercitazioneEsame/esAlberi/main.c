#include "utils.h"

int main(int argc, char const *argv[]){

    bTree *r = malloc(sizeof(*r));

    bTree *n1 = malloc(sizeof(*n1));//
    bTree *n2 = malloc(sizeof(*n2));//
    bTree *n3 = malloc(sizeof(*n3));//
    bTree *n4 = malloc(sizeof(*n4));//
    bTree *n5 = malloc(sizeof(*n5));//
    bTree *n6 = malloc(sizeof(*n6));//
    bTree *n7 = malloc(sizeof(*n7));//
    bTree *n8 = malloc(sizeof(*n8));//
    bTree *n9 = malloc(sizeof(*n9));//

    r -> val = 2;
    n1 -> val = -13;
    n2 -> val = 22;
    n3 -> val = 31;
    n4 -> val = 18;
    n5 -> val = 54;
    n6 -> val = 55;
    n7 -> val = 74;
    n8 -> val = -11;
    n9 -> val = 99;

    r -> sx = n1;
    r -> dx = n2;

    n1 -> sx = n3;
    n1 -> dx = n4;

    n2 -> sx = n9;
    n2 -> dx = NULL;

    n3 -> sx = NULL;
    n3 -> dx = n5;

    n4 -> sx = n6;
    n4 -> dx = n7;

    n5 -> sx = NULL;
    n5 -> dx = NULL;

    n6 -> sx = NULL;
    n6 -> dx = NULL;

    n7 -> sx = NULL;
    n7 -> dx = n8;

    n8 -> sx = NULL;
    n8 -> dx = NULL;

    n9 -> sx = NULL;
    n9 -> dx = NULL;


    //visitaAlbero(r);
    printf("Il numero di foglie è: %d\n", contaFoglie(r));
    visitaAlbero(r);

    alberoDistruggi(r);
    return 0;
}
