#include "utils.h"

// creazione di una tabella di numeri primi 
// con thread multipli

/*
Per poter implementare la mutua esclusione utilizziamo le lock.
Questo sistema si basa su due stati in cui potremmo trovarci:
- Locked ==> Qualcun altro è già all'interno della sezione critica quindi resto fuori
- Unlocked ==> Nessun altro thread è all'interno della sezione critica e quindi entro

** ATTENZIONE **
L'operazione di unlock deve essere fatta dallo stesso thread che ha effettuato la lock.
Non rilasciare la lock implica bloccare l'accesso alla sezione critica a tutti gli altri thread
*/

#define DIMTABELLA 10000000

//Prototipi
bool primo(int n);

// struct che uso per passare argomenti ai thread
/*
Voglio che i thread lavorino su alcune variabili condivise
Per tutto quello che devo condividere passo il puntatore
Per le parti "private" passo un valore normale
*/
typedef struct {
	int start;   // intervallo dove cercare i primo 
	int end;
  	int somma;   // somma locale primi del thread
  	int *tabella; // array dei primi condiviso
  	int *messi;   // numero primi in array condiviso
  	pthread_mutex_t *mutex_tab; 
} dati;

void *tbody(void *v) {
	dati *d = (dati *) v;
	// cerco i primi nell'intervallo assegnato
	d->somma = 0;
	for(int j=d->start;j<d->end;j++) {
        if(primo(j)) {
					d->somma += j;
					assert(*(d -> messi) < DIMTABELLA );
					/*
					Sto per entrare all'interno di una sezione critica quindi faccio
					una lock così da poter lavorare in mutua esclusione e in modo che 
					non venga interrotto
					*/
					xpthread_mutex_lock(d->mutex_tab,__LINE__,__FILE__);
					d->tabella[*(d->messi)] = j;
					*(d->messi) += 1;
					/*
					Una volta finita la sezione critica devo ricordarmi di liberare 
					la lock altrimenti nessun altro potrà accedere 
					*/
					xpthread_mutex_unlock(d->mutex_tab,__LINE__,__FILE__);
        }
	}
  fprintf(stderr,"Il thread che partiva da %d ha terminato\n",d->start);
  // segnala al processo padre che questo processo ha finito 
  pthread_exit(NULL);
}


int main(int argc,char *argv[])
{
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s limite num_threads\n", argv[0]);
    exit(1);
  }
  // conversione input
  int m = atoi(argv[1]);
  if(m < 1) termina("limite primi non valido");
  int p = atoi(argv[2]);
  if(p <= 0) termina("numero di thread non valido");

	// creazione tabella inzialmente vuota 
  int *tabella = malloc(DIMTABELLA*sizeof(int));
  if(tabella == NULL)
		xtermina("Errore malloc",__LINE__,__FILE__);
  int messi = 0;
	// creo mutex
	pthread_mutex_t mutabella = PTHREAD_MUTEX_INITIALIZER;

  // creazione thread ausiliari
  pthread_t t[p];   // array di p indentificatori di thread 
	dati d[p];        // array di p struct che passerò alle p thread

  for(int i = 0; i < p; i++) {
    int n = m/p;  // quanti numeri esamina ogni figlio + o - 
    d[i].start = n*i; // inizio range figlio i
    d[i].end = (i == p-1) ? m : n*(i+1);
	d[i].somma = 0; //per permettere ai thread di comunicare la somma
	d[i].tabella = tabella;
	d[i].messi = &messi;
	d[i].mutex_tab = &mutabella;
    if(pthread_create(&t[i], NULL, &tbody, &d[i])!= 0)
			termina("Errore creazione thread"); 
  }
  // aspetta che abbiano finito tutti i figli: 
  for(int i = 0; i < p; i++) {
	  pthread_join(t[i],NULL);
		printf("Terminato il thread %d\n",i);
	}

	// calcola somma dei primi dalla tabella 
	// e attraverso i valori restituiti dai singoli thread
	long somma = 0;
	for(int i = 0;i < messi;i++) {
		fprintf(stderr,"%d\n",tabella[i]);
		somma += tabella[i];
	}
	printf("Somma primi in tabella: %ld\n",somma);
	somma = 0;
	for(int i=0;i<p;i++) 
		somma += d[i].somma;
	printf("Somma primi nelle somme dei thread: %ld\n",somma);
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

