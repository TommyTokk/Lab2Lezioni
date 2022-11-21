#! /usr/bin/env python3
# echo-client.py

import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 65432        # The port used by the server

# creazione del socket per la connesssione al server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
      try:
        n = int(input("Quanti byte? "))
      except KeyboardInterrupt:
        n = 0
        print()
      if n <= 0:
        break
      # invio stringa di n a e attendo la risposta   
      msg = "a"*n  
      # converte il messaggio in sequenza di byte
      s.sendall(str(n).encode()) #Dico al server quanto voglio inviare
      s.sendall(msg.encode())
      #Al posto di sendall avrei potuto dcrivere send
      #Il problema è che, volendo inviare n bytes, non è detto che vengano
      #inviati tutti in una volta. Mettendo la send avremmo dovuto metterci e 
      #ciclare fino a quando i bytes da inviare non sarebbero terminati.
      #La sendall lo fa per noi

      data = s.recv(n) #Ricevo la lunghezza del prossimo messaggio
      print(f"Ricevuto {data}, bytes: {len(data)}")

      if len(data)==0:
        break

    #data = s.recv(64)
    #print(f"Ricevuto {data}, bytes: {len(data)}")


    # all'uscita dal blocco with viene eseguito s.close()
    # ma per uscire in maniera più pulita dobbiamo
    # usare prima anche shutdown()
    # SHUT_RDWR indica che terminiamo sia lettura che scrittura     
    s.shutdown(socket.SHUT_RDWR) 

