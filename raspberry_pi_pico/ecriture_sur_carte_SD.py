"""
Auteur : Marc-Antoine BUCHET
Date : 20/07/2022

BUT :
Créer un fichier csv sur une carte SD et écrire des données dedans.

Ici, les données sont fictives et sont simplement générées par une boucle for.

En situation réelle, les données proviendront a priori d'un capteur.

La carte SD comprend 6 pins :
- GND, la masse ;
- VCC, l'alimentation (normalement, 3.3V, mais certaines cartes possèdent un deuxième pin d'alimentation pouvant recevoir 5V) ;
- CS (également appelée SS pour Slave Select), active le module esclave ;
- MOSI (Master Output, Slave Input) ;
- MISO (Master Input, Slave Output).
- SCK (signal d'horloge)

Ici, on utilise le port SPI numéro 1. On connecte alors
les pins du module de la carte SD comme suit :

- GND à un des pins GND de la carte Pico (par exemple le pin 18) ;
- VCC à la sortie 3V de l'arduino - 3V3(OUT) - pin 36) ;
- CS au pin 17 du Pico (GP13) ;
- MISO au pin 16 du Pico (GP12) ;
- MOSI au pin 15 du Pico (GP11) ;
- SCK au pin 14 du Pico (GP10).

Attention, ce script nécessite l'installation de la librairie 'sdcard.py'
qu'on trouvera sur github, par exemple à l'adresse :
https://raw.githubusercontent.com/micropython/micropython/master/drivers/sdcard/sdcard.py
"""

from machine import Pin, SPI
import sdcard
import os

# Choix des pins :
pin_MISO = Pin(12)
pin_MOSI = Pin(11)
pin_SCK = Pin(10)
pin_CS = Pin(13)

# Initialisation du signal SPI :
port_SPI = 1
baudrate = 40000000 # fréquence de communication
spi=SPI(port_SPI,baudrate=baudrate,sck=pin_SCK,mosi=pin_MOSI,miso=pin_MISO)

# Initialisation de la carte SD :
sd=sdcard.SDCard(spi,pin_CS)
vfs=os.VfsFat(sd)
os.mount(sd,'/sd')

# Création d'un fichier (mode 'w' = mode d'écriture)
# Attention, le mode 'w' crée un nouveau fichier si celui n'existe pas
# mais DÉTRUIT un éventuel fichier existant préalablement
nom_du_fichier = "fichier_de_donnees_fictif.csv"
file = open("/sd/"+nom_du_fichier,"w")

# Écriture de l'en-tête :
en_tete = "t en s;x en m"
file.write(en_tete+"\n")

# Écriture des données :
for i in range(20) :
    ligne = "{0};{1}".format(i,i**2)
    file.write(ligne+"\n")

# Fermeture du fichier :
file.close()

# On peut également ouvrir un fichier en mode 'a' pour ajouter des données
# à la suite de celles préexistantes :
file = open("/sd/"+nom_du_fichier,"a")
file.write("Cette ligne a été ajoutée après une première fermeture du fichier.\n")
file.close()