"""
Auteur : Marc-Antoine BUCHET
Date : 18 juillet 2022

BUT :
Faire clignoter N fois la LED incluse sur le Raspberry Pi Pico.
La LED interne est connectée au pin 25.
"""

# Imports :
from machine import Pin
import time

# Paramètres du clignotement :
N = 10 # Nombre de cycles
duree_on = 1. # s
duree_off = 1. # s

# Paramétrage des pins :
led = Pin(25, Pin.OUT)

# Boucle :
for i in range(N) :
    print(i) # Pour suivre le nombre de clignottements
    led.value(1)
    time.sleep(duree_on)
    led.value(0)
    time.sleep(duree_off)