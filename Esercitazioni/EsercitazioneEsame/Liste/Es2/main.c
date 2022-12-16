#include "utils.h"




int main(int argc, char const *argv[]){
    
    numero *n1 = numeroCrea(5);
    numero *n2 = numeroCrea(1);
    numero *n3 = numeroCrea(13);
    numero *n4 = numeroCrea(10);


    numero *lis = NULL;
    aggiungiVal(lis);

    lis = creaLista(n1, lis);
    lis = creaLista(n4, lis);
    lis = creaLista(n3, lis);
    lis = creaLista(n2, lis);

    listaStampa(lis);
    listaDistruggi(lis);
    return 0;
}
