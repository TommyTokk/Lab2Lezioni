#include "utils.h"




int main(int argc, char const *argv[]){
    
    Persona *p1 = creaPersona("Tommaso", "Tocchini", 20);
    Persona *p2 = creaPersona("Raffaele", "Cadau", 12345);
    Persona *p3 = creaPersona("Paolo", "Rossi", 12);

    Persona *lis = NULL;

    lis = listaPersoneOrdina(p1, lis);
    lis = listaPersoneOrdina(p2, lis);
    lis = listaPersoneOrdina(p3, lis);

    

    //listaStampa(lis);
    lis = rimuoviPersona(lis);
    listaStampa(lis);
    listaDistruggi(lis);
    return 0;
}
