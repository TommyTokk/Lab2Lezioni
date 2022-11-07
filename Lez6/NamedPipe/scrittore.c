#include "utils.h"

// esempio in cui 2 processi figli scrivono interi 
// in una named pipe 


int main(int argc, char *argv[]){ 
  if(argc!=2) {
    printf("Uso:\n\t%s nome_pipe\n",argv[0]);
    exit(1);
  }
  
  // crea la named pipe da usare per le comunicazioni
  if(mkfifo(argv[1],0666)!=0) 
    termina("Errore creazione named pipe");
  sleep(1);   // questo non dovrebbe servire ma è necessario su alcune macchine

  // faccio partire il lettore
  /*if(xfork(__LINE__,__FILE__)==0) {
     if(execl("lettore", "lettore", argv[1],(char *)NULL)==-1)
        termina("exec fallita");
  }*/
  
  // crea processi ausiliari
  int n=2; 
  for(int i=0;i<n;i++) {
    pid_t p = xfork(__LINE__,__FILE__);
    if(p==0) {// figlio
      // apre file descriptor associato alla named pipe
      // se il file non esiste termina con errore  
      int fd = open(argv[1],O_WRONLY);
      if(fd<0) termina("Errore apertura named pipe");
      for(int j=0;j<10000 ;j++) {
        int val = j*n + i;
        ssize_t e = write(fd,&val,sizeof(val));
        if(e!=sizeof(val))
          termina("Errore scrittura pipe");
        if(j%1000==0)
           printf("%d (figlio di %d): scritti %d interi\n",getpid(),getppid(),j);
      }
      printf("Io figlio %d ho finito.\n",getpid());
      exit(0);
    }  
  }
  // padre
  printf("Io %d ho finito.\n",getpid());
  return 0;
}

// mkfifo
  //if(mkfifo(argv[1],0666)!=0) 
  //  termina("Errore creazione named pipe");
  // sleep(1);   // questo non dovrebbe servire ma è necessario

// execl
  // faccio partire il lettore
  // if(xfork(__LINE__,__FILE__)==0) {
  //   if(execl("lettore", "lettore", argv[1], (char *) NULL)==-1)
  //     termina("exec fallita");
  // }
