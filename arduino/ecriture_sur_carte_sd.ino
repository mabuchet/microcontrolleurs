/*
Auteur : Marc-Antoine BUCHET

Programme de base permettant d'écrire sur une carte SD.

Dans ce programme : 
- on teste l'existence du répertoire dans lequel on souhaite écrire ;
- s'il existe, on écrit des données fictives dans un fichier `txt`.

Rq : En usage réel, les données proviendront a priori de capteurs., 
ici les données écrites sont fictives.

Pour que le programme s'exécute correctement, il faut donc que le répertoire
dans lequel on souhaite écrire existe sur la carte SD (voir la chaine de caractère 
stockée dans la variable 'dirName').

Le programme crée le fichier `txt' dans lequel il écrit.

ATTENTION : Le programme est conçu pour vérifier la non-existance des fichiers
avant d'écrire dessus (afin de ne pas effacer un fichier déjà existant). 
Cependant, il existe tout de même un risque de pertes de données. Il est 
fortement conseillé de copier dès que possible les données acquises sur un 
support plus sûr que la carte SD.

Pour modifier les données à enregistrer, il faut :
- modifier la chaîne de caractère passée à la fonction 'ecriture_header' ;
- modifier la fonction 'ecriture_donnees' (rajouter des arguments et rajouter des 'myFile.print(...)' ).
*/

/*
Connection du module 'Micro SD card adapter' à l'Arduino : 
Module <-> Arduino
   GND <-> GND
   Vcc <-> 5V
  MISO <-> pin 12
  MOSI <-> pin 11
   SCK <-> pin 13
    CS <-> pin 10

Remarque : L'utilisation des pins 11, 12 et 13 est imposée
par la librairie SD (bus SPI de l'arduino Uno). 
En revanche, le pin CS peut être modifié si besoin.
*/


#include <SD.h> // crée automatiquement un objet racine SD représentant la carte mémoire SD

// Variables utiles pour l'écriture sur la carte SD :
File myFile; // objet file
char dirName[]="/donnees/"; // tableau de caracteres contenant le nom du répertoire
char fileName[] = "acq%05d.txt" ; // nom du fichier court (8 caractères maxi . 3 caractères maxi, format appelé DOS 8.3)
char formattedFileName[22] ;
char pathFile[22]  ; // tableau de caractères pour le nom du fichier
int fileNumber = 0 ;
int test ; //variable mémorisant le résultat renvoyé par certaines fonctions
int existence_fichier = true ; // Booléen utile pour vérifier l'existence des fichiers et ne pas les écraser 
int CSPin = 10 ; // Ce pin peut être modifié (modifier alors le branchement correspondant).

// Variables présentes uniquement pour l'exemple :
// À remplacer en usage normal par les variables contenant les mesures des capteurs
unsigned long t_milli ; // temps en milli secondes (donné par la fonctio 'millis')
unsigned long mesure ; // résultat de mesure, ici calculé à partir de 't_millis' mais en pratique issu d'un capteur.

void setup(){
  // Initialisation de la communication série avec l'ordinateur :
  Serial.begin(115200); // utiliser le meme debit coté Terminal Serie

  // Initialisation de la carte SD :
  Serial.println("Initialisation de la carte SD ...");
  pinMode(CSPin, OUTPUT); // laisser la broche CS en sortie - obligatoire avec librairie SD
  test=SD.begin(CSPin); // initialisation de la carte SD avec broche 10 en tant que CS - renvoie true/false

  // Vérification de l'initialisation :
  if (test!=true) { // si initialisation n'est pas réussie :
    Serial.println("Echec de l'initialisation !") ; // on l'annonce
  }
  else { // si l'initialisation est réussie
    Serial.println("Initialisation reussie !"); // on l'annonce

    // Test de l'existence du répertoire de travail :
    test=SD.exists(dirName);
    if (test!=true) { // Si le répertoire n'existe pas,
      Serial.println("Le répertoire de travail n'existe pas !"); // on l'annonce
      Serial.println(dirName) ;
    }
    else { // Si le répertoire existe,
      Serial.println("Le répertoire de travail existe !") ; // on l'annonce

      // Formattage du nom de fichier :
      while (existence_fichier) {
        strcpy(pathFile,dirName) ; // Première partie de pathFile : le nom du dossier
        sprintf(formattedFileName , fileName , fileNumber) ;
        strcat(pathFile,formattedFileName) ;
        Serial.print("Nom du fichier :") ;
        Serial.println(pathFile) ;
        existence_fichier=SD.exists(pathFile);
        if (existence_fichier) {
          Serial.println("Le fichier existe deja !") ;
          }
        fileNumber += 1 ;
        }
    
      // Et on écrit le header du fichier (ligne contenant des infos sur le contenur du fichier) :
      //ecriture_header("t en ms ; s en u.a.") ;
      // On ouvre le fichier :
  myFile=SD.open(pathFile,FILE_WRITE); // Ouvre le fichier en écriture. ATTENTION risque d'effacement du fichier !
  if (myFile!=true) { // Si l'ouverture échoue, 
    Serial.println("ecriture_header : Echec ouverture fichier !"); // on l'annonce
  }
  else { // Si l'ouverture est réussie,
    Serial.println("Ouverture fichier reussie !"); // on l'annonce
    // On écrit le header :
    myFile.println("t en ms ; s en u.a."); // À MODIFIER en fonction des données effectivement enregistrées 
    myFile.close(); // fermeture du fichier
    Serial.println("Fermeture fichier effectuee!");
      }
    }
  }
}

void loop(){
// Les deux lignes suivantes seront à remplacer par la lecture des capteurs en utilisation normale
t_milli = millis() ;
mesure = t_milli*t_milli ; // simule des données expérimentales, en pratique, proviendra d'un capteur

// Écriture des données sur la carte SD :
if (test==true) { // si les tests de "Setup" n'on pas échoué 
  ecriture_donnees(t_milli, mesure) ; // on peut écrire
  }

delay(100) ; // A priori à retirer en utilisation normale (ici sert à baisser le taux de données à écrire)
}

void ecriture_header(char chaine[]){
  // On ouvre le fichier :
  myFile=SD.open(pathFile,FILE_WRITE); // Ouvre le fichier en écriture. ATTENTION risque d'effacement du fichier !
  if (myFile!=true) { // Si l'ouverture échoue, 
    Serial.println("ecriture_header : Echec ouverture fichier !"); // on l'annonce
  }
  else { // Si l'ouverture est réussie,
    Serial.println("Ouverture fichier reussie !"); // on l'annonce
    // On écrit le header :
    myFile.println(chaine); // ajoute une ligne (avec saut de ligne !)
    myFile.close(); // fermeture du fichier
    Serial.println("Fermeture fichier effectuee!");
  }
}

void ecriture_donnees(int temps, int mesure){
  // On ouvre le fichier :
  myFile=SD.open(pathFile,FILE_WRITE); // Ouvre le fichier en écriture. ATTENTION risque d'effacement du fichier !
  if (myFile!=true) { // Si l'ouverture échoue, 
    Serial.println("ecriture_donnees : Echec ouverture fichier !"); // on l'annonce
  }
  else { // Si l'ouverture est réussie,
    myFile.seek(myFile.size()); // on se positionne à la fin du fichier
    // On écrit les données (la fonction 'print' ne saute pas de ligne !) :
    myFile.print(temps) ;
    myFile.print(";") ;
    myFile.println(mesure) ;
    myFile.close(); // fermeture du fichier
  }
}
