#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h> 
#include <fcntl.h>
#include "utils.h"

void scrivi1nsc(int n, char *nome){
    int fd = open(nome, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(fd < 0) perror("Errore creazione file");
    
    for(int i = 0; i <= n; i++){
        ssize_t e =write(fd, &i, sizeof(int));

        if(e != sizeof(int)){
            perror("Errore scrittura file");
            exit(1);
        }
    }

    int e = close(fd);
    
    if(e != 0){
        perror("Errore chiusura file");
        exit(1);
    }

}

void scrivi1n(int n, char *nome) 
{
  // apre file in scrittura
  FILE *f = fopen(nome,"wb");
  assert(f!=NULL);
  // scrive valori sul file
  for(int i=1;i<=n;i++) {
    int e = fwrite(&i, sizeof(int), 1, f); // scrive su f il contenuto di i 
    if(e!=1) {
      perror("Errore scrittura file");
      exit(1);
    }
  }
  // chiude file 
  int e = fclose(f);
  if(e!=0) {
    perror("Errore chiusura file");
    exit(1);
  }
}