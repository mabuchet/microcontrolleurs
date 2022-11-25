"""
Auteur : Marc-Antoine BUCHET
Date : 19 juillet 2022

BUT :
Contrôler l'intensité d'une LED à l'aide d'un signal PWM dont le
rapport cyclique est réglé par un potentiomètre.

Attention, la LED devra être mise en série avec une résistance
de l'ordre d'une centaine d'ohm sous peine de la griller dans le
cas contraire.
"""

# Imports :
from machine import Pin, PWM, ADC
import time

# Choix des pins :
led_pin = Pin(2)
adc_pin = Pin(26)

# Paramétrage du signal PWM :
pwm = PWM(led_pin)
pwm.freq(1000)

# Paramétrage de l'entrée ADC :
adc = ADC(adc_pin)

# Boucle infinie :
while True:
    rapport_cyclique = adc.read_u16()
    print("Rapport cyclique",rapport_cyclique,"soit {0} %".format(rapport_cyclique/65535*100))
    pwm.duty_u16(rapport_cyclique)
    time.sleep(0.1)