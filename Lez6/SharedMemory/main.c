
#include "utils.h"


// conteggio dei primi con piu' processi utilizzando
// un array condiviso 


// nome della shared memory 
#define Nome "/contaprimi"

//Prototipi
bool primo(int n);



int main(int argc,char *argv[])
{
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s m num_processi\n", argv[0]);
    exit(1);
  }
  // conversione input
  int m = atoi(argv[1]);
  if(m<1) termina("limite primi non valido");
  int p= atoi(argv[2]);
  if(p<=0) termina("numero di processi non valido");
  pid_t salvapid[p]; // array per salvare i pid dei figli 

  // ---- creazione array memoria condivisa
  /*
  Quello che vogliamo fare è riservare uno spazio in RAM 
  comune per tutti i nostri processi. Praticamente andremo a creare un "file"
  che poi trasformeremo in array condiviso
  */
  int shm_size = p*sizeof(int); // un intero x processo
  int fd = xshm_open(Nome,O_RDWR | O_CREAT, 0660,__LINE__,__FILE__);
  /*
  Con l'operazione xshm_open() andiamo a creare ed aprire un oggetto.
  La funzione restituisce un file descriptor per identificare il file
  Per utlteriori dettagli visitare la pagina man 
  */
  xftruncate(fd, shm_size, __LINE__,__FILE__);
  /*
  ftruncate() ha il compito di settare la dimensione della zona di
  memoria condivisa appena creata. Se l'oggetto è nuovo la sua dimensione è 0.
  Per utlteriori dettagli visitare la pagina man
  */
  int *a = simple_mmap(shm_size,fd, __LINE__,__FILE__);
  /*
  mmap() si occupa di "mappare" (Appunto) l' oggetto condiviso appena creato 
  all'interno dello spazio di indirizzamento virtuale del processo chiamante
  Per utlteriori dettagli visitare la pagina man
  */

  close(fd); // dopo mmap e' possibile chiudere il file descriptor
  xshm_unlink(Nome,__LINE__, __FILE__); // distrugge shm quando finito
  /*
  La funzione unlink() rimuove lo spazio di memoria condiviso.
  La sua particolarità è che attende che tutti abbiano finito di 
  utilizzarla prima di chiuderla
  Per utlteriori dettagli visitare la pagina man
  */

  // creazione processi figlio
  for(int i=0; i<p; i++) {
    pid_t pid= xfork(__LINE__, __FILE__);
    if(pid!=0) 
      salvapid[i] = pid;  // processo padre salva il pid del figlio
    else { //processo figlio
      int n = m/p;  // quanti numeri verifica ogni figlio + o - 
      int start = n*i; // inizio range figlio i
      int end = (i==p-1) ? m : n*(i+1);
			a[i]=0;        
      for(int j=start;j<end;j++)
        if(primo(j)) a[i] += 1;
      fprintf(stderr,"Processo %d terminato dopo avere trovato %d primi\n",i,a[i]);
      // unmap memoria condivisa perchè ho finito di usarla
      xmunmap(a,shm_size,__LINE__, __FILE__);
      exit(0);
    }
  }
  // codice processo padre
  // aspetta che abbiano finito i figli: 
  for(int i=0; i<p; i++)  
     if(waitpid(salvapid[i],NULL,0)<0)
       termina("Errore waitpid");
    
  // calcola e restituisce il risultato 
  int conta = 0;
  for(int i=0; i<p; i++) conta += a[i];
  printf("Numero primi tra 1 e %d (escluso): %d\n",m,conta);
  
  // unmap memoria condivisa e termina
  xmunmap(a,shm_size,__LINE__, __FILE__);
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

