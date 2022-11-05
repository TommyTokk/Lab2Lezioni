#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <sys/types.h>
#include <unistd.h>
#include <errno.h> 

int main(int argc, char const *argv[]){
    int pid;
    printf("Inizio\n");
    pid = fork();
    printf("%d: Ho ricevuto: %d\n", getpid(), pid);
    return 0;
}
