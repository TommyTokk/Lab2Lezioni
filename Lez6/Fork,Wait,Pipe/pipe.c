#include "utils.h"

// programma per il conteggio di numero dei primi in un
// intervallo usando piu' processi 

// restituisce true/false a seconda che n sia primo o composto
bool primo(int n)
{
  if(n < 2) return false;
  if(n%2 == 0) {
    if(n == 2)  return true;
    else return false; }
  for (int i = 3; i*i <= n; i += 2) 
      if(n%i ==0 ) return false;
  return true;
}

// conta i primi in [a,b)
int contap(int a, int b)
{
  int tot = 0;
  for(int i = a;i < b;i++)
    if(primo(i)) tot++;
  return tot;  
}


// conta quanti sono i primi tra argv[1] (compreso) e argv[2] (escluso)
int main(int argc, char *argv[]) {
  if(argc != 4) {
    printf("Uso:\n\t%s n1 n2 p\n",argv[0]);
    exit(1);
  }
  int n0 = atoi(argv[1]);
  int n1 = atoi(argv[2]);
  int p = atoi(argv[3]);
  assert(n0>0 && n1>=n0 && p>0);

  // creo una pipe di comunicazione tra genitori e figli
  int up[2]; // la chiamo up perchè la uso da figli a genitore
  xpipe(up,__LINE__,__FILE__);

  /*
  La funzione pipe va ad inserire all'interno dell'array up due file descriptor
  che permettono di scrivere in up[1] e di leggerlo da up[0].
  Non essendo dei veri file, se provo a leggere da up[0] senza che nessuno 
  stia scrivendo in up[1] non leggerò nulla.
  In questo caso specifico SOLO i figli scriveranno in up[1] anche se il padre potrebbe
  tranquillamente farlo, tenete sempre conto che più attori usano la pipe
  più controlli voi dovrete fare e più casi dovrete gestire
  */

  // generazione dei processi child
  for(int i = 0;i < p;i++) {
    pid_t pid = xfork(__LINE__,__FILE__);

    if(pid==0) {// figlio
      xclose(up[0],__LINE__,__FILE__);

      int n = (n1-n0)/p;  // quanti numeri verifica ogni figlio + o - 
      int start = n0 + n*i; // inizio range figlio i
      int end = (i == p-1) ? n1 : n0 + n*(i+1);  
      int tot = contap(start,end);

      printf("Figlio %d, cerco tra %d e %d, trovati %d \n",i+1,start,end,tot);

      ssize_t e = write(up[1],&tot,sizeof(int));
      /*
      La scrittura all'interno delle pipe le scritture sono atomiche
      Se p1 sta scrivendo p2 dovrà attendere per scrivere
      */
      if(e!=sizeof(int)) termina("Errore scrittura pipe");
      xclose(up[1],__LINE__,__FILE__);
      exit(0);
    }  
  }
  // qui arriva solo il genitore 
  int tot=0;
  xclose(up[1],__LINE__,__FILE__);
  // leggo fino a quando tutti non hanno chiuso up[1]
  while(true) {
    int x;
    ssize_t e = read(up[0],&x,sizeof(int));
    if(e == 0) break;
    tot += x;
  }
  xclose(up[0],__LINE__,__FILE__);
  printf("Numero primi p tali che  %d <= p < %d è: %d\n",n0,n1,tot);
  return 0;
}