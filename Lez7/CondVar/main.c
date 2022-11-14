/*
Le condition variables sono un'altro dei tanti sistemi di sincronizzazione tra thread.
La differenza dagli altri meccanismi che abbiamo visto è che le 
CV eliminano l'attesa attiva all'interno dell' esecuzione.

Per esempio, supponiamo che un thread debba aspettare che una variabile v diventi >= 10
Un'idea per farlo è:
while(true){
    if(v >= 10) break;
}
Questa però è un'implementazione poco furba; il thread in questione sta occupando cicli di CPU
senza fare ASSOLUTAMENTE nulla. Un'idea sicuramente migliore è testare la condizione nell'if solo 
quando qualcuno modifica la variabile v mettendo in attesa il thread fino ad un risveglio.
*/


#include "utils.h"
// abbreviamo la chiamata alle funzione x...
#define QUI __LINE__,__FILE__


// gestione di heap mediante condition variable
// per fare si che le stampe riflettano l'effetivo ordine
// delle operazioni queste sono effettuate quando il 
// mutex è sempre bloccato 


typedef struct {
  pthread_cond_t  *cv; // condition variable
  pthread_mutex_t *mu; // mutex
  int MB;       // memoria disponibile 
} heap;

// simula allocazione con spazio limitato
void richiedi(heap *h, int n) {
    /*
    Tutte le operazioni di modifica devono essere fatte in modo atomico
    Per garantire che nessuno ci interrompa eseguiamo tutto con una lock acquisita
    */
	xpthread_mutex_lock(h->mu,QUI);
	fprintf(stderr,"Richiesti: %4d\n", n);

    /*
    Poiché stiamo simulando un heap, nel caso in cui non avessimo
    memoria a disposizione dobbiamo far sospendere il thread richiedente. 
    Per farlo usiamo la SC wait passando la CV che stiamo utilizzando.

    OSSERVAZIONE: Notate che alla wait passiamo anche la mutex come secondo parametro
    Questo perché, nel caso in cui il thread si dovesse sospendere, dobbiamo rilasciare la mutex
    perché altrimenti nessun altro thread riuscirebbe ad entrare
    */
	while(n > h->MB)
		xpthread_cond_wait(h->cv,h->mu,QUI);
	h -> MB -= n;
	fprintf(stderr,"Assegnati: %4d. Rimanenti: %4d\n\n",n,h->MB);
    /*
    Nel caso fossi uscito dal ciclo e abbia concluso le mie operazioni
    rilascio la mutex
    */
	xpthread_mutex_unlock(h->mu,QUI);
}

// deallocazione
void libera(heap *h, int n) {
    /*
    Tutte le operazioni di modifica devono essere fatte in modo atomico
    Per garantire che nessuno ci interrompa eseguiamo tutto con una lock acquisita
    */
	xpthread_mutex_lock(h->mu,QUI);
	h->MB += n;
    /*
    Una volta finite le operazioni, SEMPRE IN MUTUA ESCLUSIONE, devo
    risvegliare il/i thread in sospeso sulla CV.

    ATTENZIONE:
    - pthread_cond_broadcast --> Invia un segnale a TUTTI i thread in sospeso sulla CV
    - pthread_cond_signal --> Invia un segnale ad UN SOLO thread tra quelli sospesi sulla CV
    */
	xpthread_cond_broadcast(h->cv,QUI);
    fprintf(stderr,"Restituiti: %3d. Rimanenti: %4d\n\n",n,h->MB);
	xpthread_mutex_unlock(h->mu,QUI);	
}


// codice thread tipo 1
void *tipo1(void *v) {
	heap *h = (heap *) v;
	for(int i=1;i<=5;i++) {
		int m = 10*i;
		richiedi(h,m);
		sleep(1);
		libera(h,m);
	}
	return NULL;
}

// codice thread tipo 2
void *tipo2(void *v) {
	heap *h = (heap *) v;
	for(int i=1;i<=5;i++) {
		int m = 10*i+5;
		richiedi(h,m);
		sleep(1);
		libera(h,m);
	}
	return NULL;
}


int main(int argc, char *argv[])
{
  // controlla numero argomenti
  if(argc!=3) {
      printf("Uso: %s mem numT\n",argv[0]);
      return 1;
  }
	int mem = atoi(argv[1]);
	int nt = atoi(argv[2]);
	assert(nt>1);

  // inizializza heap 
	pthread_cond_t c = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	heap h;
	h.cv = &c; h.mu = &m;
	h.MB = mem;
	
	// esegue i thread
	pthread_t t[nt];
	xpthread_create(&t[0],NULL,&tipo1,&h,QUI);
	for(int i=1;i<nt;i++)
		xpthread_create(&t[i],NULL,&tipo2,&h,QUI);

	for(int i=0;i<nt;i++)
		xpthread_join(t[i],NULL,QUI);
	xpthread_cond_destroy(&c,QUI);
	xpthread_mutex_destroy(&m,QUI);
	
  fprintf(stderr,"Terminato con memoria: %d\n",h.MB);
	return 0;
}
