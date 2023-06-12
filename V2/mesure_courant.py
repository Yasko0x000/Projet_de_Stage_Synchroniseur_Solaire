# Importation des bibliothèques nécessaires (serial et time)
import serial
import time

# J’établie une connexion série avec le capteur
primo = serial.Serial('/dev/ttyAMA0', 38400) #Je verifie avec stty -echo -F /dev/ttyAMA0 raw speed 38400 et cat /dev/ttyAMA0

#Lecture de la réponse du capteur
def lecture_courant():
    primo.write(b'c')
    reponse = primo.readline().decode().strip()
    ct1 = float(reponse[0:5].replace(' ', ''))/1000
    return ct1

while True:
    Amp_courant = lecture_courant()
    # Affichage du courant mesuré avec deux chiffres aprés la virgule
    print(f'Le courant mesuré est : {Amp_courant:.2f} A')
    time.sleep(1)