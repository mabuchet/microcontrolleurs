"""
Auteur : Marc-Antoine BUCHET
Date : 18 juillet 2022

BUT :
Contrôler l'allumage d'une LED externe à l'aide d'un bouton poussoir.

Attention, la LED devra être mise en série avec une résistance
de l'ordre d'une centaine d'ohm sous peine de la griller dans le
cas contraire.
"""

# Imports :
from machine import Pin
import time

# Paramétrage des pins :
pin_led = 2
led = Pin(pin_led, Pin.OUT)

pin_bouton = 14
bouton = Pin(pin_bouton, Pin.IN, Pin.PULL_DOWN)

while True:
    if bouton.value():
        led.toggle()
        time.sleep(0.5)