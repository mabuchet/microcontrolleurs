"""
Auteur : Marc-Antoine BUCHET
Date : 19 juillet 2022

BUT :
Contrôler l'intensité d'une LED à l'aide d'un signal PWM.

On utilise une boucle et on augmente le rapport cyclique à chaque
tour de boucle de sorte à visualiser l'augmentation de l'intensité 
de la LED.

Attention, la LED devra être mise en série avec une résistance
de l'ordre d'une centaine d'ohm sous peine de la griller dans le
cas contraire.
"""

# Imports :
from machine import Pin, PWM
import time

# Paramétrage des pins :
pin_led = 2
led = Pin(pin_led, Pin.OUT)

# Paramétrage du signal PWM :
pwm = PWM(led)
pwm.freq(1000)

N_pas = 10
duree_pas = 1
for i in range(N_pas) :
    rapport_cyclique = i*65535//(N_pas-1)  # nombre entre 0 et 65535
    print("Rapport cyclique",rapport_cyclique,"soit {0} %".format(i/(N_pas-1)*100))
    pwm.duty_u16(rapport_cyclique)
    time.sleep(duree_pas)