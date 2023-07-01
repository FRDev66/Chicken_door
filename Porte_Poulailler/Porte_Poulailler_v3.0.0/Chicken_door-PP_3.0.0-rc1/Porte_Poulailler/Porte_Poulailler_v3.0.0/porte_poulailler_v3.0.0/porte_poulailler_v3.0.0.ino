// ###################################################################
// Code permettant ouverture / fermeture d'une porte de poulailler
// selon la luminausité
// Composants : 
// + Arduino UNO
// + Moteur DC
// + Cellule photorésistance
//####################################################################
// Auteur : FRDev66
// Date : 2023-07-01
// version :3.0.0
// 
// ChangeLog :
// + [3.0.0 : Modification du type de moteur : Pas à Pas --> Servo
// 
// ###################################################################

// Liste Bibliothèques utiles
#include <Servo.h>

// Déclaration Constantes & Variables
int Tour=0; // Déclaration variable pour gérer le nombre de tours du moteur
int delayTime=5; // Vitesse d'ouverture et fermeture de la porte
int etat = 0; // Initialisation de l'Etat (A voir si utile ?)

// Déclaration des Broches (PIN) utilisés
int lightPin = 0; // Pin de branchement de la cellule Photorésistance = A0

// Déclaration Transverse
Servo myservo; // Déclaration Constante Servo Moteur


void setup() {
  Serial.begin(9600); // Ouverture du port série et debit de communication fixé à 9600 bauds

  myservo.attach(9); // PIN de branchement Digital du Servo Moteur = 9
  myservo.write(0); // move servos to center position -> 90°
}

void loop() {
  
  int reading  = analogRead(lightPin); // Lecture de la PhotoRésistance
  Serial.println(reading);
  delay(10000);
  
  // Si lumière (Lumix) > 300 ==> Ouverture de la Porte
  if(reading >= 300) {
    Ouvrir_porte();
    delay(6000);
  }

  // Si lumière (Lumix) < 50 ==> Fermeture de la Porte
  if(reading <= 50) {
    Fermer_porte();
    delay(9000);
  }
}

// Séquence d'alimentation normale des bobines du moteur en Full Step
void Fermer_porte(){
  Serial.println(etat);
  myservo.write(0);// move servos to center position -> 90°

  Serial.println("Porte Fermée"); // Affichage sur le moniteur série
  etat=0;
  Serial.println(etat); // Affiche Etat après Fermeture de la Porte (doit être 0)
}


// Séquence d'alimentation inverse des bobines du moteur en Full Step
void Ouvrir_porte(){
  myservo.write(180);// move servos to center position -> 90°

  Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
  etat=1;
  Serial.println(etat); // Affiche Etat après Fermeture de la Porte (doit être 1)
}

