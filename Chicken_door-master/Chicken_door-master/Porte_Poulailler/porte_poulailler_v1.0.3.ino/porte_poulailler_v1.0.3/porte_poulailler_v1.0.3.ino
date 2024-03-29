// ###################################################################
// Code permettant ouverture / fermeture d'une porte de poulailler
// selon la luminausité
// Composants : 
// + Moteur pas à pas - Stepper
// + Cellule photorésistance
//####################################################################
// Auteur : FRDev66
// Date : 2022-04-09
// version : 1.0.3
// 
// ChangeLog :
// 
// 
// ###################################################################

// Inclut la bibliothèque Arduino Stepper.h:
#include <Stepper.h>

// Définit le nombre de pas par rotation:
const int stepsPerRevolution = 2048;

int MotorPin1= 8; // Déclaration broche commande Bobine 1 moteur
int MotorPin2= 9; // Déclaration broche commande Bobine 2 moteur
int MotorPin3= 10; // Déclaration broche commande Bobine 3 moteur
int MotorPin4= 11; // Déclaration broche commande Bobine 4 moteur
int Tour=0; // Déclaration variable pour gérer le nombre de tours du moteur
int delayTime=5; // Vitesse d'ouverture et fermeture de la porte

int lightPin = 0;
int etat = 0;

// Créez un objet stepper appelé ‘myStepper’, notez l’ordre des broches:
Stepper myStepper = Stepper ( stepsPerRevolution, 8, 10, 9, 11 ) ;

void setup() {
Serial.begin(9600); // Ouverture du port série et debit de communication fixé à 9600 bauds

// Réglez la vitesse sur 5 tr / min:
//myStepper. setSpeed ( 20 ) ;

pinMode(MotorPin1, OUTPUT); // Pin 8 de l'arduino en sortie digitale
pinMode(MotorPin2, OUTPUT); // Pin 9 de l'arduino en sortie digitale
pinMode(MotorPin3, OUTPUT); // Pin 10 de l'arduino en sortie digitale
pinMode(MotorPin4, OUTPUT); // Pin 11 de l'arduino en sortie digitale
}

void loop() {

  int reading  = analogRead(lightPin);
  Serial.println(reading);
  //Serial.println(Tour);
  Serial.println(etat);
  if(etat==1){
    if(reading <= 300) // seuil  en-dessous duquel la porte se ferme
    {
      Tour = 0 ; // remise à 0 des Tours
      Fermer_porte();
      Serial.println("Fermeture porte");
      etat = 0;
      delay(21600000);
    }
  }

  if(etat==0){
    if(reading >= 300) // seuil au-dessus duquel la porte ouvre
    {
      Tour = 0 ; // remise à 0 des Tours
      Ouvrir_porte();
      Serial.println("Ouverture porte");
      etat = 1;
      delay(25200000);
    }
  }
}

// Séquence d'alimentation normale des bobines du moteur en Full Step
void Fermer_porte(){
  Serial.println(etat);
  while(Tour <= 2048){ // Equivaut à 1 tours
    digitalWrite(MotorPin1,HIGH); // Alimentation A de la Bobine 1 du moteur pas à pas
    digitalWrite(MotorPin2,HIGH); // Alimentation B de la Bobine 2 du moteur pas à pas
    digitalWrite(MotorPin3,LOW); // Bobine 3 du moteur pas à pas au repos
    digitalWrite(MotorPin4,LOW); // Bobine 4 du moteur pas à pas au repos
    delay(delayTime);
    digitalWrite(MotorPin1,LOW); // Bobine 1 du moteur pas à pas au repos
    digitalWrite(MotorPin2,HIGH); // Alimentation B de la Bobine 2 du moteur pas à pas
    digitalWrite(MotorPin3,HIGH); // Alimentation C de la Bobine 3 du moteur pas à pas
    digitalWrite(MotorPin4,LOW); // Bobine 4 du moteur pas à pas au repos
    delay(delayTime);
    digitalWrite(MotorPin1,LOW); // Bobine 1 du moteur pas à pas au repos
    digitalWrite(MotorPin2,LOW); // Bobine 2 du moteur pas à pas au repos
    digitalWrite(MotorPin3,HIGH); // Alimentation C de la Bobine 3 du moteur pas à pas
    digitalWrite(MotorPin4,HIGH); // Alimentation D de la Bobine 4 du moteur pas à pas
    delay(delayTime);
    digitalWrite(MotorPin1,HIGH); // Alimentation A de la Bobine 1 du moteur pas à pas
    digitalWrite(MotorPin2,LOW); // Bobine 2 du moteur pas à pas au repos
    digitalWrite(MotorPin3,LOW); // Bobine 3 du moteur pas à pas au repos
    digitalWrite(MotorPin4,HIGH); // Alimentation D de la Bobine 4 du moteur pas à pas
    delay(delayTime);
    Serial.println("Fermer porte"); // Affichage sur le moniteur série
    Tour++;
  }
  Serial.println("Porte Fermée"); // Affichage sur le moniteur série
  Arret();
  etat=0;
}


// Séquence d'alimentation inverse des bobines du moteur en Full Step
void Ouvrir_porte(){
  while(Tour <= 2048){ // équivaut à 1 tour
    digitalWrite(MotorPin1,LOW); // Bobine 1 du moteur pas à pas au repos
    digitalWrite(MotorPin2,LOW); // Bobine 2 du moteur pas à pas au repos
    digitalWrite(MotorPin3,HIGH); // Alimentation C de la Bobine 3 du moteur pas à pas
    digitalWrite(MotorPin4,HIGH); // Alimentation D de la Bobine 4 du moteur pas à pas
    delay(delayTime);
    
    digitalWrite(MotorPin1,LOW); // Bobine 1 du moteur pas à pas au repos
    digitalWrite(MotorPin2,HIGH); // Alimentation B de la Bobine 2 du moteur pas à pas
    digitalWrite(MotorPin3,HIGH); // Alimentation C de la Bobine 3 du moteur pas à pas
    digitalWrite(MotorPin4,LOW); // Bobine 4 du moteur pas à pas au repos
    delay(delayTime);
    
    digitalWrite(MotorPin1,HIGH); // Alimentation A de la Bobine 1 du moteur pas à pas
    digitalWrite(MotorPin2,HIGH); // Alimentation B de la Bobine 2 du moteur pas à pas
    digitalWrite(MotorPin3,LOW); // Bobine 3 du moteur pas à pas au repos
    digitalWrite(MotorPin4,LOW); // Bobine 4 du moteur pas à pas au repos
    delay(delayTime);
    
    digitalWrite(MotorPin1,HIGH); // Alimentation A de la Bobine 1 du moteur pas à pas
    digitalWrite(MotorPin2,LOW); // Bobine 2 du moteur pas à pas au repos
    digitalWrite(MotorPin3,LOW); // Bobine 3 du moteur pas à pas au repos
    digitalWrite(MotorPin4,HIGH); // Alimentation D de la Bobine 4 du moteur pas à pas
    delay(delayTime);
    Serial.println("Ouvrir porte"); /// Affichage sur le moniteur série du texte
    Tour++;
  }
  Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
  Arret();
  etat=1;
  Serial.println(etat);
}

// Fonction arrêt du moteur
void Arret(){
digitalWrite(MotorPin1,LOW); // Bobine 1 du moteur pas à pas au repos
digitalWrite(MotorPin2,LOW); // Bobine 2 du moteur pas à pas au repos
digitalWrite(MotorPin3,LOW); // Bobine 3 du moteur pas à pas au repos
digitalWrite(MotorPin4,LOW); // Bobine 4 du moteur pas à pas au repos
}
