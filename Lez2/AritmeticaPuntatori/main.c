#include <stdio.h>
#include <stdlib.h>

//PROTOTIPI
int lengthStrBella(char *string);
int lengthStrBrutta(char *string);
//PROTOTIPI

int main(int argc, char const **argv){

/*
    Sappiamo che le stringhe sono array di caratteri
    Quindi possiamo accedere agli elementi di una stringa tramite la notazione str[i] dove:
    - str è ovviamente la stringa
    - i è l'indice corrente.
*/

    char *s = "CIAO";

    printf("%c\n", s[0]);
    printf("%c\n", *s);

    /*
    Eseguendo il codice notiamo che le istruzioni alle righe 20-21
    stampano lo stesso identico risultato:
        - s[0] = 'C'
        - *s = 'C'
    Da qui deduciamo che *s = s[0]
    Potenzialmente quindi possiamo scorrere l'array con s e basta (PERICOLOSO).
    */

    printf("%d\n", lengthStrBrutta(s));
    return 0;
}
//FUNZIONI
int lengthStrBella(char *string){
    int dim = 0;

    while(string[dim] != '\0'){
        dim++;
    }

    return dim;
}

int lengthStrBrutta(char *string){
    int dim = 0;
    while(*string != '\0'){
       dim++;
       /*
       Sappiamo che string -> primo carattere della stringa
       Come facciamo però a scorrere per poter simulare s[i]?
       Semplice, incrementiamo string di 1.
       Però C è infame; in realtà fare pointer++ (pointer = pointer + 1)
       somma al valore attuale di pointer la dimensione del tipo di pointer.
       */
       string++;
    }

    return dim;
}
//FUNZIONI
