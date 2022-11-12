#include "utils.h"


/*
Per poter implementare la mutua esclusione utilizziamo le lock.
Questo sistema si basa su due stati in cui potremmo trovarci:
- Locked ==> Qualcun altro è già all'interno della sezione critica quindi resto fuori
- Unlocked ==> Nessun altro thread è all'interno della sezione critica e quindi entro

** ATTENZIONE **
L'operazione di unlock deve essere fatta dallo stesso thread che ha effettuato la lock.
Non rilasciare la lock implica bloccare l'accesso alla sezione critica a tutti gli altri thread
*/

#define BUFF_SIZE  30

//Prototipi
bool primo(int n);

// struct che uso per passare argomenti ai thread
/*
Voglio che i thread lavorino su alcune variabili condivise
Per tutto quello che devo condividere passo il puntatore
Per le parti "private" passo un valore normale
*/
typedef struct {
	int quanti;   // output 
	long somma;
	int *cIndex;
	int *buffer;
	pthread_mutex_t *cMutex;
	sem_t *semFreeSlots;
	sem_t *semDataItems;
} dati;


//Funzione eseguita dal thread consumatore
void *consumerBody(void *v) {
	dati *d = (dati *) v;
	d -> quanti = 0;
	d -> somma = 0;
	int n;
	do{
		//Devo leggere dal buffer ==> Sezione critica
		xsem_wait(d -> semDataItems, __LINE__, __FILE__);//Nel caso il semaforo sia 0 mi sospendo
		xpthread_mutex_lock(d -> cMutex, __LINE__, __FILE__);
		//Leggo dal buffer
		n = d -> buffer[*(d -> cIndex) % BUFF_SIZE];
		*(d -> cIndex) += 1;

		//Finisco la sessione critica ==> Rilascio la lock e incremento il semaforo
		xpthread_mutex_unlock(d -> cMutex, __LINE__, __FILE__);
		xsem_post(d -> semFreeSlots, __LINE__, __FILE__);

		if(n > 0 && primo(n)){
			(d -> quanti) += 1;
			(d -> somma) += n;
		}
	}while(n != -1);

	pthread_exit(NULL);
}


int main(int argc,char *argv[]){
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s cons file\n", argv[0]);
    exit(1);
  }

  int p = atoi(argv[1]);
  assert(p>=0);
  int tot_primi = 0;
  long tot_somma = 0;
  int e,n; 

  //Inizializzazione thread
  int buffer[BUFF_SIZE];
  int pIndex = 0, cIndex = 0;
  pthread_mutex_t cMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_t t[p]; //Array dei thread
  dati d[p];
  sem_t semFreeSlot, semDataItems;
  xsem_init(&semFreeSlot, 0, BUFF_SIZE, __LINE__, __FILE__);
  xsem_init(&semDataItems, 0, 0, __LINE__, __FILE__);

  //Creazione dei thread
  for(int i = 0; i < p; i++){
	  d[i].buffer = buffer;
	  d[i].cIndex = &cIndex;
	  d[i].cMutex = &cMutex;
	  d[i].semDataItems = &semDataItems;
	  d[i].semFreeSlots = &semFreeSlot;

	  xpthread_create(&t[i],NULL,consumerBody,d+i,__LINE__,__FILE__);
  }

  FILE *f = fopen(argv[2],"r");
  if(f == NULL) {perror("Errore apertura file"); return 1;}
  while(true) {
    e = fscanf(f,"%d", &n);
    if(e != 1) break; // se il valore e' letto correttamente e==1
    assert(n>0);    // i valori del file devono essere positivi
    /*
    Controllo che ci sia spazio all'interno del buffer.
    Per farlo faccio una wait su semFreeSlots in quanto
    se non ci fosse posto il producer verrebbe interrotto
    */
    xsem_wait(&semFreeSlot,__LINE__,__FILE__);
    buffer[pIndex++ % BUFF_SIZE]= n;
    xsem_post(&semDataItems,__LINE__,__FILE__);
  }

  //Terminazione dei thread
  for(int i = 0; i < p; i++){
    xsem_wait(&semFreeSlot, __LINE__, __FILE__);
    buffer[pIndex++ % BUFF_SIZE] = -1; //Inserisco un valore non valido per il consumatore
    xsem_post(&semDataItems, __LINE__, __FILE__);
  }

  //Join threads e calcolo del risultato
  for(int i = 0; i < p;i ++){
    xpthread_join(t[i], NULL, __LINE__, __FILE__);
    tot_somma += d[i].somma;
    tot_primi += d[i].quanti;
  }

  fprintf(stderr,"Trovati %d primi con somma %ld\n",tot_primi,tot_somma);
  return 0;

}



// restituisce true/false a seconda che n sia primo o composto
bool primo(int n)
{
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)  return true;
    else return false; }
  for (int i=3; i*i<=n; i += 2) 
      if(n%i==0) return false;
  return true;
}

