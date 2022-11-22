#! /usr/bin/env python3
# server che fornisce l'elenco dei primi in un dato intervallo 
# gestisce più clienti contemporaneamente usando i thread
import sys, struct, socket, threading
# modulo che contiene già un server bastao sui socket
import socketserver

# host e porta di default
HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)
 
class ElencaPrimi(socketserver.StreamRequestHandler):
  def handle(self):
    print(f"Gestisco richiesta da {self.client_address}")
    # sostanzialmente stesso codice di gestisci_connessione
    # tranne che usa self.rfile e self.wfile invece del socket
    # ---- attendo due interi da 32 bit
    data = self.rfile.read(8)
    assert len(data)==8
    inizio  = struct.unpack("!i",data[:4])[0]
    fine = struct.unpack("!i",data[4:])[0]
    print(f"Ho ricevuto i valori:", inizio,fine)
    # ---- calcolo elenco dei primi
    primi = elenco_primi(inizio, fine)
    # ---- invio risultato in formato preceduto da lunghezza
    self.wfile.write(struct.pack("!i",len(primi))) #lunghezza
    for p in primi:
      self.wfile.write(struct.pack("!i",p))       # singoli valori 
    print(f"Finito con {self.client_address}")


# classe che specifica che voglio un TCP server gestito con i thread 
class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    daemon_threads = True
    allow_reuse_address = True
    
    
def main(host=HOST,port=PORT):
  with ThreadedTCPServer((host, port), ElencaPrimi) as server:
    print('In attesa dei client...')
    server.serve_forever()



# restituisce lista dei primi in [a,b]
def elenco_primi(a,b):
  ris = []
  for i in range(a,b+1):
    if primo(i):
      ris.append(i);
  return ris


# dato un intero n>0 restituisce True se n e' primo
# False altrimenti
def primo(n):
    assert n>0, "L'input deve essere positivo"
    if n==1:
        return False
    if n==2:
        return True
    if n%2 == 0:
        return False
    assert n>=3 and n%2==1, "C'e' qualcosa che non funziona"
    for i in range(3,n//2,2):
        # fa attendere solamente questo thread 
        # threading.Event().wait(.5)
        if n%i==0:
            return False
        if i*i > n:
            break    
    return True



if len(sys.argv)==1:
  main()
elif len(sys.argv)==2:
  main(sys.argv[1])
elif len(sys.argv)==3:
  main(sys.argv[1], int(sys.argv[2]))
else:
  print("Uso:\n\t %s [host] [port]" % sys.argv[0])



