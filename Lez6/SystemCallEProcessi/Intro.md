# SystemCall VS Library function
- Le SC per come le abbiamo viste noi sono delle funzioni all'interno delle librerie del C
    - Sono funzioni che hanno un rapporto 1:1 con le kernel SC

- In realtà sono funzioni indipendenti dal C 
    - Sono più difficili da usare 
    - Offrono più controllo

Alcuni esempi sono:
----- ----- ----- -----
*LibFunc*     *Kernel SC*
fopen           open
fprintf         /
fread           read
fwrite          write

## **ATTENZIONE**
Non esiste una kernel SC specifica per la *fprintf* in quanto le SC lavorano a livello macchina e quindi lavorano con informazioni sotto forma di byte e non di caratteri testuali. Quindi la funzione di libreria *fprintf* farà prima la conversione $byte\;\Leftrightarrow\;testo$ e poi chiamerà la kernel SC *write*.

## **ATTENZIONE**
Le kernel SC danno poche informazioni riguardo a cosa fanno quindi *USATELE SOLO SE SAPETE COSA STATE FACENDO*

# System call e processi
A differenza delle SC che operano sui file non abbiamo delle funzioni di libreria che operano sui processi, quindi dobbiamo affidarci al kernel. 

## Process ID
Prima di iniziare con le SC facciamo un piccolo ripasso sui processi.
Ogni processo all'interno del sistema è memorizzato all'interno di una tabella chiamata *Process Table* contenente delle strutture dati chiamate *PCB* (o *Process Control Block*) aventi il compito di memorizzare tutte le informazioni del processo. Per accedere ai vari processi usiamo il *PID* (o *Process ID*) ovvero un numero che rappresenta il processo all'interno della PT.

- *pid*: Indice del processo all'interno della tabella dei processi
- *ppid*: Indice del processo padre all'interno della tabella dei processi
- Possiamo ottenerli tramite ```#include <unistd.h>```

E i metodi sono:
```C
pid_t getpid(void);
/*Ritorna il PID (Nessun codice di errore)*/
pid_t getppid(void);
/*Ritorna il PID del padre (Nessun codice di errore)*/
```



