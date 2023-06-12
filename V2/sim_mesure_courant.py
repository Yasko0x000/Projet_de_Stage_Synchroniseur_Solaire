#avant de commencer, il faut utiliser les port virtuel socat, sinon modifier la ligne 7 par le port sur lequel est branché le capteur

import time
import serial

# Config du port série virtuel grace a socat
ser = serial.Serial('/dev/pts/5', 38400)

while True:
    # Lecture des mesures
    data = ser.readline().decode().strip()

    if data:
        try:
            # On conevrtie les donnée en float pour pourvoir avoir des donnée aprés la virgule
            mesure = float(data)

            courant = mesure

            # J'affiche la mesure recu sur le port
            print("Mesure de courant : {:.3f} A".format(courant))

        except ValueError:
            # Si probleme
            print("Erreur de conversion des données")

    time.sleep(1)