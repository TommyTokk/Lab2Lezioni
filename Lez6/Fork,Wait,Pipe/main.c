#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"

int main(int argc, char const *argv[]){
    int n = 3;
    for(int i = 0; i < n; i++){
        pid_t pid = xfork(__LINE__, __FILE__);
        /*
        __LINE__ e __FILE__ sono due costanti di compilazione 
        __LINE__ ==> Specifica la linea dell'istruzione
        __FILE__ ==> Specifica il nome del file compilato in questo momento
        */
        //Sono il processo figlio
        if(pid == 0){
            printf("Sono %d, figlio %d-esimo del processo %d\n", getpid(), i, getppid());
            //sleep(10 * i);
            exit(2*i + 1);
        }
    }
    //Sono il padre

    printf("Sono %d, ovvero il main :D,  figlio di %d, ovvero la linea di comando\n", getpid(), getppid());

    int processiFiniti = 0;

    for (int i = 0; i < n; i++){
        int status;
        pid_t pidFiglio = xwait(&status, __LINE__, __FILE__);
        printf("Figlio %d terminato\n", pidFiglio);

        if(WIFEXITED(status)){
            processiFiniti += WEXITSTATUS(status);
            printf("Valore di cont di questo figlio: %d\n", WEXITSTATUS(status));
        }else{
            printf("Figlio %d non terminato con exit\n", pidFiglio);
        }
    }
    printf("Finito.\n");
    return processiFiniti;
}
