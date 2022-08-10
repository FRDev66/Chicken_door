// ###################################################################
// Code permettant ouverture / fermeture d'une porte de poulailler
// selon la luminausité
// Composants : 
// + Arduino UNO
// + Moteur DC
// + Cellule photorésistance
//####################################################################
// Auteur : FRDev66
// Date : 2022-08-10
// version :2.0.1
// 
// ChangeLog :
// + [2.0.1] : Modification du nombre de Tours de rotation Ouvrir / Ferme du moteur --> de 4 à 6 Tours
// 
// ###################################################################

// Inclut la bibliothèque Arduino Stepper.h:
//#include <Stepper.h>

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
//Stepper myStepper = Stepper ( stepsPerRevolution, 8, 10, 9, 11 ) ;

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

  int reading  = analogRead(lightPin); // lecture de la valeur de la Photorésistance (Lumix)
  Serial.println(reading);
  
  //Serial.println(Tour);
  Serial.println(etat); // Affiche l'état initial
  
  if(etat==1){
    if(reading <= 100) // seuil  en-dessous duquel la porte se ferme
    {
      Tour = 0 ; // remise à 0 des Tours
      Fermer_porte();
      //Serial.println("Porte fermée");
      //etat = 0;
      //delay(3600000);
      delay(600000);
    }
    else {
      delay(900000);
    }
  }

  if(etat==0){
    if(reading >= 300) // seuil au-dessus duquel la porte ouvre
    {
      Tour = 0 ; // remise à 0 des Tours
      Ouvrir_porte();
      //Serial.println("Porte ouverte");
      //etat = 1;
      //delay(3600000);
      delay(600000);
    }
    else {
      delay(900000);
    }
  }
}

// Séquence d'alimentation normale des bobines du moteur en Full Step
void Fermer_porte(){
  Serial.println(etat);
  while(Tour <= 3072){ // Equivaut à 6 tours
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
  Serial.println(etat); // Affiche Etat après Fermeture de la Porte (doit être 0)
}


// Séquence d'alimentation inverse des bobines du moteur en Full Step
void Ouvrir_porte(){
  while(Tour <= 3072){ // équivaut à 6 tours
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
  Serial.println(etat); // Affiche Etat après Fermeture de la Porte (doit être 1)
}

// Fonction arrêt du moteur
void Arret(){
digitalWrite(MotorPin1,LOW); // Bobine 1 du moteur pas à pas au repos
digitalWrite(MotorPin2,LOW); // Bobine 2 du moteur pas à pas au repos
digitalWrite(MotorPin3,LOW); // Bobine 3 du moteur pas à pas au repos
digitalWrite(MotorPin4,LOW); // Bobine 4 du moteur pas à pas au repos
}
