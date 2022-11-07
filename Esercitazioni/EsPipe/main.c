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
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"


bool primo(int n){
  if(n < 2) return false;
  if(n%2 == 0) {
    if(n == 2)  return true;
    else return false; }
  for (int i = 3; i*i <= n; i += 2) 
      if(n%i ==0 ) return false;
  return true;
}

int main(int argc, char const *argv[]){
    int up[2];
    int down[2];

    xpipe(up, __LINE__, __FILE__);
    xpipe(down, __LINE__, __FILE__);

    if(argc < 2) termina("USO: ./main nomefile");

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL) termina("Apertura file in fallita");

    for(int i = 0; i < 2 ; i++){
        
        pid_t pid = xfork(__LINE__, __FILE__);

        if(pid == 0){//Sono il figlio
            long sonSum = 0;
            xclose(up[0], __LINE__, __FILE__);//Chiudo la pipe up in lettura --> uso up per scrivere
            xclose(down[1], __LINE__, __FILE__);//Chiudo down in scrittura --> uso down per leggere
            
            while(true){
                int x;//Contiene il valore letto
                ssize_t e = read(down[0],&x, sizeof(int));
                printf("Sono %d e ho letto: %d\n", getpid(), x);
                if(e == 0) break;
                if(primo(x))
                    sonSum += (long) x;
            }

            //HO LETTO E SOMMATO

            int e = write(up[1], &sonSum, sizeof(int));
            if(e != sizeof(int)) termina("Errore scrittura pipe");
            xclose(up[1], __LINE__, __FILE__);//Chiudo la pipe up in scrittura --> up chiusa completamente
            exit(0);
        }
    }
    //Sono il padre
    xclose(down[0], __LINE__, __FILE__);//Chiudo la pipe down in lettura --> uso la pipe per scrivere
    xclose(up[1], __LINE__, __FILE__);
    while(true){
        int num;
        int e = fscanf(fin, "%d", &num); //Leggo dal file
        if(e != 1) break;
        if(ferror(fin)) termina("Errore file");
        
        int err = write(down[1], &num, sizeof(int));
        if (err != sizeof(int)) termina("Errore scrittura pipe padre");
    }

    xclose(down[1], __LINE__, __FILE__);//Chiudo down in scrittura --> down chiusa

    int somTot = 0;

    while (true){
        long sonSum;
        int e = read(up[0], &sonSum, sizeof(long));
        //printf("sono il padre e ho letto %d\n",  sonSum);
        if(e == 0) break;
        somTot +=  sonSum;
    }

    xclose(up[0], __LINE__, __FILE__);//Chiudo up in lettura --> up chiusa 

    printf("La somma totale è : %d\n",  somTot);

    if(fclose(fin) != 0) termina("Chiusura file input fallita");
    
    return 0;
}
