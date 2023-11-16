#define _GNU_SOURCE   // permette di usare estensioni GNU
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione ass
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */


typedef struct bTree{
    int val;
    struct bTree *sx;
    struct bTree *dx;
} bTree;

void visitaAlbero(bTree *t);
void nodoDistruggi(bTree *t);
void alberoDistruggi(bTree *t);
bTree *pota(bTree *t);
int valoreAlbero(bTree *t);
int contaPari(bTree *tree);
bTree *posAlbero(bTree *t);
int contaFoglie(bTree *t);
