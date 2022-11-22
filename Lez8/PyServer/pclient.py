#! /usr/bin/env python3
# pclient.py

import sys,struct,socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 65432        # The port used by the server


def main(a,b,host=HOST,port=PORT):
  # inizializzazione socket client 
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # la prossima chiamata è blocking 
    s.connect((host, port))
    print("Connesso a", s.getpeername())
    # pronto per inviare la richiesta
    s.sendall(struct.pack("!i",a))
    s.sendall(struct.pack("!i",b))
    # chiedo quanti primi mi verranno restituiti
    data = recv_all(s,4)
    n = struct.unpack("!i",data)[0]
    print("Devo ricevere", n, "primi")
    for i in range(n):
      data = recv_all(s,4)
      p = struct.unpack("!i",data)[0]
      print("  ", p)
    print("finito")


# Riceve esattamente n byte dal socket conn e li restituisce
# il tipo restituto è "bytes": una sequenza immutabile di valori 0-255
# Questa funzione è analoga alla readn che abbiamo visto nel C
def recv_all(conn,n):
  chunks = b''
  bytes_recd = 0
  while bytes_recd < n:
    chunk = conn.recv(min(n - bytes_recd, 1024))
    if len(chunk) == 0:
      raise RuntimeError("socket connection broken")
    chunks += chunk
    bytes_recd = bytes_recd + len(chunk)
  return chunks


if len(sys.argv)==3:
  main(int(sys.argv[1]),int(sys.argv[2]))
elif len(sys.argv)==4:
  main(int(sys.argv[1]),int(sys.argv[2]),sys.argv[3])
elif len(sys.argv)==5:
  main(int(sys.argv[1]),int(sys.argv[2]), sys.argv[3], int(sys.argv[4]))
else:
  print("Uso:\n\t %s min max [host] [port]" % sys.argv[0])
