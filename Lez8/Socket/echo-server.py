#! /usr/bin/env python3
# echo-server.py

import socket

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)



# creazione del server socket
try:
    #Vado ad creare ed aprire la socket
    #Per farlo uso il metodo .socket() passando come parametri:
        #- AF_INET: Famiglia di indirizzi con cui la 
        #           socket può comunicare (IPv4)
        #- SOCK_STREAM: Indica che stiamo usando il protocollo TCP (Transport control protocol)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT)) #collego la socket appena creata all'HOST e alla porta dichiarate sopra
        s.listen() #Mi metto in attesa che un client chieda di collegarsi
        #ATTENZIONE
        #Con il metodo listen non creiamo la connessione ma ci mettiamo solo in attesa
        #La connessione verrà creata alla riga 25 con il metodo .accept()
        while True:
            print("In attesa di un client...")
            # mi metto in attesa di una connessione
            conn, addr = s.accept()
            # lavoro con la connessione appena ricevuta 
            with conn:  
                print(f"Contattato da {addr}")
                while True:
                    lenMsg = conn.recv(64) # leggo la dimensione del messaggio
                    if(b'a' in lenMsg):
                        tmpStr = lenMsg.replace(b'a', b'')
                        lenMsg = tmpStr
                    print(f"Ricevuto: {lenMsg}")
                    if(lenMsg == b''): break
                    data = conn.recv(int(lenMsg))
                    print(f"Data: {data}\n")
                    print(f"Ricevuti {len(data)} bytes") 
                    if not data:           # se ricevo 0 bytes 
                        break              # la connessione è terminata
                    conn.sendall(data)           
                    #conn.sendall(data)     # altrimenti echo
                print("Connessione terminata")
        #Una volta chiusa una connessione il server si rimette in attesa
except KeyboardInterrupt:
    print('\nConnessione terminata')






