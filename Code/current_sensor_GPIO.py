import time
import pigpio

# GPIO utilise pour mesurer la sortie analogique du SCT-013
GPIO = 17

# Coefficient de calibration pour convertir la tension en courant
COEFF = 50

# Initialisation de pigpio et du GPIO
pi = pigpio.pi()
pi.set_mode(GPIO, pigpio.INPUT)

# Fonction pour mesurer le courant
def measure_current():
    value = pi.read(GPIO)
    voltage = value * 3.3 / 4095  # Conversion de la valeur lue en tension
    current = voltage / COEFF    # Conversion de la tension en courant
    return current

# Boucle principale
try:
    while True:
        current = measure_current()
        print(f"Courant: {current:.2f} A")
        time.sleep(1)

except KeyboardInterrupt:
    print("Arrêt de la mesure.")
    pi.stop()
