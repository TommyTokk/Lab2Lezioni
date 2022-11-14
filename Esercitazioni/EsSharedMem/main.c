#include "utils.h"

#define SUB_PROC 2

int *creaArrayFile(FILE *fin, int *dimTot);
int confronta(const void *n1, const void *n2);
void merge(int *pipe1, int *pipe2, int *array);

int main(int argc, char const *argv[]){
    if(argc != 2) termina("Uso: ./main nomeFile");

    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL) termina("Apertura file non risucita");

    int up1[2], up2[2], down1[2], down2[2];

    xpipe(up1, __LINE__, __FILE__);
    xpipe(up2, __LINE__, __FILE__);
    xpipe(down1, __LINE__, __FILE__);
    xpipe(down2, __LINE__, __FILE__);

    int dimTot;
    //Funzione per creazione array
    int *array = creaArrayFile(fin, &dimTot);

    int dim1 = dimTot/2;
    int dim2 = dimTot - dim1;

    //Creo processi figli

    for(int i = 0; i < SUB_PROC ;i++){
        pid_t pid = xfork(__LINE__, __FILE__);
        
        if(pid == 0){//SONO IL FIGLIO
            if(i == 0){ //SONO IL FIGLIO 1
                xclose(up1[0], __LINE__, __FILE__);//Chiudo up1 in lettura
                xclose(up2[0], __LINE__, __FILE__);//Chiudo up2 in lettura
                xclose(up2[1], __LINE__, __FILE__);//Chiudo up2 in scrittura
                xclose(down1[1], __LINE__, __FILE__);//chiudo down1 in scrittura
                xclose(down2[0] , __LINE__, __FILE__);//Chiudo down2 in lettura
                xclose(down2[1] , __LINE__, __FILE__);//CHiudo down in scrittura

                int *array1 = malloc(dim1 * sizeof(int));
                if(!array1) termina("Allocazione figlio1 fallita");
                int messi = 0;
                //LEGGO DA DOWN1[0]
                while(messi < dim1){
                    int x;//Contiene il valore letto
                    ssize_t e = read(down1[0],&x, sizeof(int));
                    if(e == 0) break;
                    //printf("Ho letto %d\n", x);
                    array1[messi] = x;
                    messi++;
                }

                //HO LETTO E CARICATO
                qsort(array1, dim1, sizeof(int), &confronta);


                //HO ORDINATO E DEVO SCRIVERE
                for(int i = 0; i < dim1; i++){
                    int e = write(up1[1], &array1[i], sizeof(int));
                    if(e != sizeof(int)) termina("Errore scrittura pipe");
                }

                //HO SCRITTO SU UP1[1]
                xclose(up1[1], __LINE__, __FILE__);//Chiudo up1 in scrittura
                xclose(down1[0], __LINE__, __FILE__);
                /* ---- PIPE CHIUSE DA 1 ----
                - up1
                - up2
                - down1
                - down2
                */
                //Dobbiamo ricordarci di chiudere la pipe dei figli in scrittura così che
                //il padre possa sapere quando i figli sono terminati senza dover fare la wait
                free(array1);
                exit(0);
            }else{
                xclose(up2[0], __LINE__, __FILE__);
                xclose(up1[0], __LINE__, __FILE__);
                xclose(up1[1], __LINE__, __FILE__);
                xclose(down2[1], __LINE__, __FILE__);
                xclose(down1[0] , __LINE__, __FILE__);
                xclose(down1[1] , __LINE__, __FILE__);

                int *array2 = malloc(dim2 * sizeof(int));
                if(!array2) termina("Allocazione figlio1 fallita");
                int messi2 = dim1;
                int cont = 0;
                //LEGGO DA DOWN1[0]
                while(messi2 < dimTot){
                    int x;//Contiene il valore letto
                    ssize_t e = read(down2[0],&x, sizeof(int));
                    if(e == 0) break;
                    //printf("Ho letto %d\n", x);
                    array2[cont] = x;
                    messi2++;
                    cont++;
                }
                //HO LETTO E CARICATO
                qsort(array2, dim2, sizeof(int), &confronta);

                //HO ORDINATO E DEVO SCRIVERE
                for(int i = 0; i < dim2; i++){
                    int e = write(up2[1], &array2[i], sizeof(int));
                    if(e != sizeof(int)) termina("Errore scrittura pipe");
                }

                //HO SCRITTO SU UP1[1]
                xclose(up2[1], __LINE__, __FILE__);//Chiudo la pipe up in scrittura --> up chiusa completamente
                xclose(down2[0], __LINE__, __FILE__);
                //Dobbiamo ricordarci di chiudere la pipe dei figli in scrittura così che
                //il padre possa sapere quando i figli sono terminati senza dover fare la wait
                free(array2);
                exit(0);
            }
        }
    }
    //SONO IL PADRE
    xclose(up1[1], __LINE__, __FILE__);//up1 chiusa in scrittura
    xclose(up2[1], __LINE__, __FILE__);//up2 chiusa in scrittura
    xclose(down1[0], __LINE__, __FILE__);//down1 chiusa in lettura
    xclose(down2[0] , __LINE__, __FILE__);//down2 chiusa in lettura


    for(int i = 0; i < dim1; i++){
        int e = write(down1[1], &array[i], sizeof(int));
        if(e != sizeof(int)) termina("Errore scrittura pipe");
    }

    for(int i = dim1; i < dimTot; i++){
        int e = write(down2[1], &array[i], sizeof(int));
        if(e != sizeof(int)) termina("Errore scrittura pipe");
    }
    //FACCIO IL MERGE
    int sum = 0;
    merge(up1, up2, array);
    puts("---- ARRAY ----");
    for(int i = 0; i < dimTot; i++){
        sum += i * array[i];
        printf("%d\n", array[i]);
    }

    printf("La somma finale dell'array è: %d\n", sum);

    xclose(up1[0], __LINE__, __FILE__);
    xclose(up2[0], __LINE__, __FILE__);
    xclose(down1[1], __LINE__, __FILE__);
    xclose(down2[1] , __LINE__, __FILE__);


    if(fclose(fin) != 0) termina("Chiusura file fallita");
    free(array);
    return 0;
}

int *creaArrayFile(FILE *fin, int *dimTot){
    int e;
    int *a;

    e = fseek(fin, 0, SEEK_END);
    if( e != 0) termina("Seek fallita");

    long t = ftell(fin);
    if(t < 0) termina("ftell fallita");

    int dim = t/sizeof(int);

    a = malloc(dim * sizeof(int));
    if(!a) termina("Malloc fallita");

    rewind(fin);

    //Carico l'array

    e = fread(a, sizeof(int), dim, fin);

    if(e != dim) termina("Lettura fallita");
    *dimTot = dim;
    return a;
}

int confronta(const void *a, const void *b){
    int *n1 = (int *)a;
    int *n2 = (int *)b; 
    if(*n1 < *n2) return -1;
    else if(*n1 > *n2) return 1;
    else return 0;
}

void merge(int *pipe1, int *pipe2, int *array){

    int e1, e2, num1, num2;
    e1 = read(pipe1[0],&num1, sizeof(int));
    e2 = read(pipe2[0],&num2, sizeof(int));


    int i = 0;
    while(e1 != 0 && e2 != 0){
        
        if(num1 > num2) {
            array[i] = num2;
            e2 = read(pipe2[0],&num2, sizeof(int));
        }else{
            array[i] = num1;
            e1 = read(pipe1[0],&num1, sizeof(int));
        }

        i++;
    }

    while(e1 != 0 && e2 == 0){
        array[i] = num1;
        i++;
        e1 = read(pipe1[0],&num1, sizeof(int));
    }

    while(e2 != 0 && e1 == 0){
        array[i] = num2;
        i++;
        e2 = read(pipe2[0],&num2, sizeof(int));
    }
}
