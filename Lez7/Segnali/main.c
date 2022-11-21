#include "utils.h"
#define QUI __LINE__,__FILE__

// esempio base gestione segnali con handler
// ogni processo ha un unico thread



// variabili globali utilizzate da main signal handler 
int tot_segnali = 0;
//La keyword volatile serve per dire al compilatore
//che la variabile continua deve essere testata
//E che non deve fare assunzioni di nessun tipo
volatile bool continua = true;

// funzione che viene invocata quando viene ricevuto 
// un segnale USR1 USR2 o INT (Control-C)

//La fuzione prende come parametro il codice del segnale da trattare
//Non conosce inoltre lo stato del resto del programma quindi
//Ogni tipo di interazione deve essere fatta tramite V.G.
void handler(int s){
  tot_segnali++;
  printf("Segnale %d ricevuto dal processo %d\n", s, getpid());
  if(s==SIGUSR2) {
    // dopo aver fatto girare il programma la prima volta
    // s-commentate l'istruzione kill
    kill(getpid(),SIGUSR1);
    continua = false;
  } 
}

int main(int argc, char *argv[])
{
  // definisce signal handler 
  struct sigaction sa;
  sa.sa_handler = &handler;
	// setta a "insieme vuoto" sa.sa_mask che è la
	// maschera di segnali da bloccare: non una buona idea 
	// quando si usa lo stesso handler per più funzioni
  sigemptyset(&sa.sa_mask);   
  sa.sa_flags = SA_RESTART;     // restart system calls 
  sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
  sigaction(SIGUSR2,&sa,NULL);  // stesso handler per USR2
  sigaction(SIGINT,&sa,NULL);   // stesso handler per Control-C

	fork();
	
  // visualizza il pid
  printf("Se vuoi mandarmi dei segnali il mio pid e': %d\n", getpid());
  // entra in orribile busy waiting attendendo i segnali
  continua = true;
  do { // loop apparentemente senza uscita
    //Non mettendo la keyword volatile alla riga 14
    //Il compilatore cercherà di ottimizzare questo loop
    //Mettendo al posto di while(continua) --> while(true)
    sleep(100);               
  } while(continua);
  printf("Ricevuti: %d segnali\n", tot_segnali);   
  return 0;
}

