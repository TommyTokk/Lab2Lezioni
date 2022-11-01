from tokenize import Name

#In python esistono 4 tipi di strutture dati
#1) Sets
#2) Dictionaries
#3) Lists
#4)Tuples
#Alcune potrebbero sembrarvi molto simili ma sono tutte MOLTO diverse

# SETS: Sono uno delle 4 strutture dati disponibili
#I set sono strutture dati NON ordinate, immutabili (possono essere solo aggiunti/rimossi elementi) e non indicizzate

#DICTIONARIES: Strutture dati per lo storing di informazioni key : value
#Sono strutture dati ordinate, mutabili e non ammettono duplicati

#LISTS: strutture dati per lo storing di più informazioni in una singola variabile
#Le liste sono ordinate, mutabili e ammettono duplicati
#Sono strutture dati indicizzate ed è possibile accedere ai valori tramite la notazione [index]

#TUPLES: strutture dati per lo storing di più informazioni in una singola variabile
#Sono strutture dati ordinate e immutabili e ammettono duplicati
#Sono indicizzate ed è possibile accedere ai valori tramite la notazione [index]




list = [
    {
        "id" : 132749357,
        "Name" : "Tommaso",
        "Surname" : "Tocchini",
        "Age" : 21
    },
    {
        "id" : 267842874,
        "Name" : "Pietro",
        "Surname" : "Battini",
        "Age" : 21
    },
    {
        "id" : 3263942594,
        "Name" : "Agnese",
        "Surname" : "Bertoncini",
        "Age" : 21
    },
    {
        "id" : 3263942594,
        "Name" : "Federica",
        "Surname" : "Zocco",
        "Age" : 21
    }
]

tupleList = []
idSets = {}
idSets = set()


for dicts in list:
    tupleList.append((dicts["id"], dicts["Age"]))


print("---- Set ----")


for tuples in tupleList:
    idSets.add(tuples[0])

print(f"idSets:{idSets}")

print("---- Tuples ----")

print("Tuples:")
for tuples in tupleList:
    print(tuples)
