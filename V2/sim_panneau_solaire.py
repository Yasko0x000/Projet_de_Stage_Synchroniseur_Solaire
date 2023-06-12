import time

def onduleurVirtuel(typeEnsoleillement, heure):
    production_par_type = {
           #1h 2h 3h 4h 5h 6h 7h 8h    9h    10h   11h   12h   13h   14h   15h   16h   17h   18h  19h  20h  21h  22h  23h  24h
        0: [0, 0, 0, 0, 0, 0, 0, 1000, 1000, 2000, 2000, 3000, 3000, 2000, 2000, 1000, 1000, 750, 750, 500, 500, 250, 250, 210], #Un jour de production sans nuage
        1: [0, 0, 0, 0, 0, 0, 0, 500, 500, 1000, 1000, 1500, 1500, 1000, 1000, 500, 500, 250 , 250 , 100 , 100 , 50, 50, 10], #Un jour nuageux de production
        2: [0 , 0 , 0 , 0 , 0 , 0 , 0 ,100 ,100 ,500 ,500 ,100 ,100 ,500 ,500 ,100 ,100 , 50 , 50 , 25 , 25 , 10 , 10, 5] #Un jour pluvieux de production
    }

    if typeEnsoleillement in production_par_type:
        return production_par_type[typeEnsoleillement][heure]
    else:
        return 0

type_ensoleillement = None  # Stock du type d'ensoleillement (pour la question)

while type_ensoleillement is None:
    type_ensoleillement = input("Entrez le type d'ensoleillement (entier entre 0 et 2) : ")
    try:
        type_ensoleillement = int(type_ensoleillement)
        if type_ensoleillement < 0 or type_ensoleillement > 2:
            print("Type d'ensoleillement invalide. Veuillez entrer un entier entre 0 et 2.")
            type_ensoleillement = None
    except ValueError:
        print("Type d'ensoleillement invalide. Veuillez entrer un entier entre 0 et 2.")
        type_ensoleillement = None

while True:
    heure_actuelle = time.localtime().tm_hour
    production = onduleurVirtuel(type_ensoleillement, heure_actuelle)
    print("Heure :", heure_actuelle, "Production d'énergie actuelle :", production, "W")

    time.sleep(10)
