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
    int up[2];//Array che conterrà la pipe per la comunicazione figli -> padre
    int down[2];//Array che conterrà la pipe per la comunicazione padre -> figli

    xpipe(up, __LINE__, __FILE__);
    xpipe(down, __LINE__, __FILE__);

    if(argc < 2) termina("USO: ./main nomefile");

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL) termina("Apertura file in fallita");
    int subProc = 2;
    for(int i = 0; i < subProc ; i++){
        /*
        All'interno di questo ciclo vado a creare i figli che si occuperanno di fare le somme
        */
        pid_t pid = xfork(__LINE__, __FILE__);//Eseguo le fork per generare i figli

        if(pid == 0){//Sono il figlio
            int sonSum = 0;
            xclose(up[0], __LINE__, __FILE__);//Chiudo la pipe up in lettura --> uso up per scrivere
            /*
            La pipe up viene usata per la comunicazione dai figli verso il padre.
            Poiché noi vogliamo solo usarla per scrivere al padre le somme calcolate
            chiudiamo la pipe in lettura
            */
            xclose(down[1], __LINE__, __FILE__);//Chiudo down in scrittura --> uso down per leggere
            /*
            La pipe down viene usata per la comunicazione dal padre verso i figli.
            Poiché noi vogliamo solo usarla per leggere i numeri che il padre leggerà
            chiudiamo la pipe in scrittura
            */



            /*=== LETTURA DAL PADRE ===
            L'idea è quella di mettersi in ascolto sulla pipe del padre e iniziare a leggere 
            i vari valori che questo inizierà a scrivere
            */
            while(true){
                int x;//Contiene il valore letto
                ssize_t e = read(down[0],&x, sizeof(int));
                //printf("Sono %d e ho letto: %d\n", getpid(), x);
                if(e == 0) break;
                if(primo(x))
                    sonSum +=  x;
            }

            printf("La somma di %d è: %d\n", getpid(), sonSum);
            //HO LETTO E SOMMATO
            int e = write(up[1], &sonSum, sizeof(int));
            if(e != sizeof(int)) termina("Errore scrittura pipe");
            xclose(up[1], __LINE__, __FILE__);//Chiudo la pipe up in scrittura --> up chiusa completamente
            //Dobbiamo ricordarci di chiudere la pipe dei figli in scrittura così che
            //il padre possa sapere quando i figli sono terminati senza dover fare la wait
            exit(0);
        }
    }
    //Sono il padre
    xclose(down[0], __LINE__, __FILE__);//Chiudo la pipe down in lettura --> uso la pipe per scrivere
    xclose(up[1], __LINE__, __FILE__);//Chiudo la pipe up in scrittura --> uso la pipe in lettura
    
    /*=== SCRITTURA AI FIGLI ===
    Il padre ha il compito di leggere dei nummeri da un file 
    e passarli ai figli. Per farlo usiamo una fscanf e il valore lo passiamo
    all'interno della pipe in scrittura del padre
    */
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

    /*=== LETTURA SOMME  DAI FIGLI ===
    Arrivati a questo punto vogliamo leggere i valori delle somme che i figli hanno calcolato
    e poi usarli per fare la somma totale. Per farlo usiamo la pipe up in lettura così da prendere i 
    vari valori
    */
    while (true){
        int sonSum;
        int e = read(up[0], &sonSum, sizeof(int));
        //printf("sono il padre e ho letto %d\n",  sonSum);
        if(e == 0) break;
        somTot +=  sonSum;
    }

    /*
    A questo punto sappiamo con certezza che i figli sono terminati 
    e possiamo terminare il nostro processo
    */
    xclose(up[0], __LINE__, __FILE__);//Chiudo up in lettura --> up chiusa 

    printf("La somma totale è : %d\n",  somTot);

    if(fclose(fin) != 0) termina("Chiusura file input fallita");
    
    return 0;
}
