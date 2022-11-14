#! /usr/bin/env python3

# crea un file binario contenente n interi positivi 
# mettendo nel nome del file la somma pesata 
# degli elementi dell'array ordinato 

import random, sys, struct

def main(n):
  a = []
  # crea
  for j in range(n):
    num = random.randint(0, 2000)
    a.append(num)
  # ordina e calcola
  b = sorted(a)
  somma = 0
  for j in range(n):
    somma += j*b[j]
  # scrivi
  nome = f"test_{somma}"
  g = open(nome,"wb")
  for j in range(n):
    g.write(struct.pack("<i",a[j]))
  g.close()
  # fine  
  print("Scritti",n,"interi. Somma pesata array ordinato:",somma)


if len(sys.argv)!=2:
  print("Uso:\n\t %s numero_interi" % sys.argv[0])
else:
  main(int(sys.argv[1]))
