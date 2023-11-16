class Attrazione:
    def __init__(self, nome, lat, long):
        self.nome = nome
        self.lat = lat
        self.long = long

    
    def getAttrazione(self):
        print("====================")
        print(f"Nome: {self.nome}")
        print(f"Latitudine: {self.lat}")
        print(f"Longitudine: {self.long}")

def main():
    attrList = []
    with open("attrazioni.txt", "r") as f:
        lines = f.readlines()

    for line in lines:
        tokens = line.split(",")
        attr = Attrazione(tokens[0], float(tokens[1]), float(tokens[2].strip("\n")))
        attrList.append(attr)

    for attr in attrList:
        attr.getAttrazione()

main()



    #str = "statua della libertà, 61, 28"
    #words = str.split(",")

    #nome = words[0].strip("\n")
    #lat = words[1].strip("\n")
    #long = words[2].strip("\n")

    #attr = Attrazione(nome, lat, long)

    #attr.getAttrazione()
    

        