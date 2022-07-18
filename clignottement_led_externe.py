"""
Auteur : Marc-Antoine BUCHET
Date : 18 juillet 2022

BUT :
Faire clignoter N fois une LED externe.

Dans l'exemple qui suit, on a choisi de connecter la LED au pin 2.
Si l'on souhaite la connecter à un autre pin, il faudra modifier
en conséquence la valeur de la variable pin_choisi.

Attention, la LED devra être mise en série avec une résistance
de l'ordre d'une centaine d'Ohm sous peine de la griller dans le
cas contraire.
"""

# Imports :
from machine import Pin
import time

# Paramètres du clignotement :
N = 10 # Nombre de cycles 
duree_on = 1. # s
duree_off = 1. # s

# Paramétrage des pins :
pin_choisi = 2
led = Pin(pin_choisi, Pin.OUT)

# Boucle :
for i in range(N) :
    print(i) # Pour suivre le nombre de clignottements
    led.value(1)
    time.sleep(duree_on)
    led.value(0)
    time.sleep(duree_off)
