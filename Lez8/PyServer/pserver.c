/*#include "xerrori.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#define QUI __LINE__,__FILE__

// parametri del server
#define HOST "127.0.0.1"
#define PORT 65432

// dimensione buffer consumatori 
#define Buf_size 20


// prototipi
ssize_t readn(int fd, void *ptr, size_t n);
ssize_t writen(int fd, void *ptr, size_t n);
void *tbody(void *);
bool primo(int n);


// struct contenente i parametri dei thread (tutti uguali)
typedef struct {
  int cindex;  // indice nel buffer
  int *buffer; 
  pthread_mutex_t *cmutex;
  sem_t *sem_free_slots;
  sem_t *sem_data_items; 
} cdati;


// questa versione non permette di scegliere 
// host e port dalla linea di comando
// per cambiarli è necessario ricompilare
int main(int argc, char const* argv[])
{
  if(argc!=2) {
    printf("Uso\n\t%s workers\n", argv[0]);
    exit(1);
  }
  // ========= faccio partire i workers 
  int w = atoi(argv[1]);
  pthread_t t[w];
  int buffer[Buf_size];  // nel buffer metto file descriptor quindi int
  sem_t sem_free_slots, sem_data_items;
  xsem_init(&sem_free_slots,0,Buf_size,__LINE__,__FILE__);
  xsem_init(&sem_data_items,0,0,__LINE__,__FILE__);
  pthread_mutex_t cmutex = PTHREAD_MUTEX_INITIALIZER;
  cdati c;
  c.cindex = 0;
  c.buffer=buffer;
  c.cmutex = &cmutex;
  c.sem_free_slots = &sem_free_slots;
  c.sem_data_items = &sem_data_items;
  for(int i=0;i<w;i++)
    xpthread_create(&t[i],NULL,&tbody,&c,QUI);
    
    
  // ===== faccio partire il server
  int fd_skt = 0;      // file descriptor associato al socket
  // crea socket
  if ((fd_skt = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    xtermina("Errore creazione socket",QUI);
  struct sockaddr_in serv_addr;
  // assegna indirizzo
  serv_addr.sin_family = AF_INET;
  // il numero della porta deve essere convertito in network order 
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = inet_addr(HOST);
  // inizializza socket 
  if(bind(fd_skt, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))<0) 
    xtermina("Errore bind",QUI);
  if(listen(fd_skt, 10)<0)
    xtermina("Errore listen",QUI);
    
  // main loop
  puts("In attesa di connessioni");
  int fdc, pindex = 0;
  while(true) {
    fdc = accept(fd_skt,NULL,0);
    if(fdc<0) xtermina("Errore accept",QUI);
    // metti il file descriptor nel buffer e riparti 
    xsem_wait(&sem_free_slots,QUI);
    buffer[pindex++ % Buf_size] = fdc;
    xsem_post(&sem_data_items,QUI);
  }

  // il server non ha modo di uscire ci vorrebbe un signal handler... 
  puts("Connessione terminata"); 
  return 0;
}

void *tbody(void *arg)
{
  cdati *a = (cdati *)arg; 
  int fd, tot, estremi[2];
  do {
    // --- legge file descriptor da gestire 
    xsem_wait(a->sem_data_items,__LINE__,__FILE__);
    xpthread_mutex_lock(a->cmutex,__LINE__,__FILE__);
    fd = a->buffer[a->cindex % Buf_size];
    a->cindex +=1;
    xpthread_mutex_unlock(a->cmutex,__LINE__,__FILE__);
    xsem_post(a->sem_free_slots,__LINE__,__FILE__);
    if(fd>0) {
      readn(fd,estremi,2*sizeof(int));
      estremi[0] = ntohl(estremi[0]);
      estremi[1] = ntohl(estremi[1]);
      printf("Ho ricevuto: %d %d\n",estremi[0],estremi[1]);
      // molto inefficiente, facciodue volte il conto!!!
      tot = 0;
      for(int i=estremi[0];i<=estremi[1];i++)
        if(primo(i)) tot++;
      printf("Ho trovato %d primi\n",tot);
      tot = htonl(tot);
      writen(fd,&tot,sizeof(tot));
      for(int i=estremi[0];i<=estremi[1];i++)
        if(primo(i)) {int j=htonl(i); writen(fd,&j,sizeof(j));}
      xclose(fd,QUI);
    }
    else // attulamente i thread non terminano mai  
      break;
  } while(true);
  pthread_exit(NULL); 
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


/* Read "n" bytes from a descriptor 
ssize_t readn(int fd, void *ptr, size_t n) {  
   size_t   nleft;
   ssize_t  nread;
 
   nleft = n;
   while (nleft > 0) {
     if((nread = read(fd, ptr, nleft)) < 0) {
        if (nleft == n) return -1; /* error, return -1 
        else break; /* error, return amount read so far 
     } else if (nread == 0) break; /* EOF 
     nleft -= nread;
     ptr   += nread;
   }
   return(n - nleft); /* return >= 0 
}


/* Write "n" bytes to a descriptor 
ssize_t writen(int fd, void *ptr, size_t n) {  
   size_t   nleft;
   ssize_t  nwritten;
 
   nleft = n;
   while (nleft > 0) {
     if((nwritten = write(fd, ptr, nleft)) < 0) {
        if (nleft == n) return -1; /* error, return -1 
        else break; /* error, return amount written so far 
     } else if (nwritten == 0) break; 
     nleft -= nwritten;
     ptr   += nwritten;
   }
   return(n - nleft); /* return >= 0 
}*/

