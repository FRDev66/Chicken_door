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
//int Tour=0; // Déclaration variable pour gérer le nombre de tours du moteur
//int delayTime=5; // Vitesse d'ouverture et fermeture de la porte
//int etat = 9; // Initialisation de l'Etat (A voir si utile ?)
int action = 9;
int etat = 0;
int etatPorte = 9;
//int angle = 0;
//int temps = 1500; // censée être à mi-chemin entre 1000 et 2000, un bon point de départ
//unsigned long delayTime;
unsigned long tempoDepart = 0;

//#define servoPin 9
#define tempoMesures 10000 // Délai entre 2 Mesures Statiques (temp / humidité / presssion - en millisecondes - 15 minutes)

// Déclaration des Broches (PIN) utilisés
int lightPin = 0; // Pin de branchement de la cellule Photorésistance = A0

// Déclaration Transverse
Servo myServo; // Déclaration Constante Servo Moteur

void setup() {
  Serial.begin(115200); // Ouverture du port série et debit de communication fixé à 9600 bauds

  //myServo.attach(9, 400, 2550); // PIN de branchement Digital du Servo Moteur = 9
  //myServo.attach(9);
  //myServo.write(0);
  //delay(1000);
  //myServo.detach();
}

void loop() {
  
  //Serial.println("tempoDepart =");
  //Serial.print(tempoDepart);

  // Toutes les 30 minutes ==> Lancer une phase de Mesures Statiques
  if ( millis() - tempoDepart >= tempoMesures ) {
    int reading = niveauLumix();
    afficherLumix(reading);
    //int etat = valeurEtat();
    //afficherEtat(etat);
    

    int action = choixActionPorte(reading,etat); // Détermine quelle action sera effectuée
    Serial.print("Valeur action = ");
    Serial.println(action);

    int etatPorte = actionPorte(action); // Définition des différentes actions
    Serial.print("Etat Porte = ");
    Serial.println(etatPorte);

    etat = etatPorte;

    tempoDepart = millis();
    
  }

}

int actionPorte(int action) {
  switch (action) {
    case 1 :
      myServo.attach(9); 
      myServo.write(180);
      delay(900);
      myServo.detach();
      etatPorte = 1;
      return etatPorte;
      break;
    case 2 :
      myServo.attach(9); 
      myServo.write(0);
      delay(1000);
      myServo.detach();
      etatPorte = 0;
      return etatPorte;
      break;
    case 3 :
      etatPorte = 1;
      return etatPorte;
      break;
    default :
      etatPorte = 9;
      return etatPorte; 
      break;
  }
}

int choixActionPorte(int lumix, int etat) {
  switch (etat) {
    case 0:
      if(lumix >= 200) {
        Serial.println("Ouvrir Porte !!");
        int action = 1;
        return action;
      } else {
        Serial.println("NE RIEN FAIRE !! - Laisser Porte fermée");
        int action = 0;
        return action;
      }
      break;
    case 1:
      if(lumix <= 50) {
        Serial.println("Fermer Porte !!");
        action = 2;
        return action;
      } else {
        Serial.println("NE RIEN FAIRE !! - Porte reste Ouverte");
        int action = 3;
        return action;
      }
      break;
    default:
      Serial.println("MESSAGE : la valeur etat ne correspond pas à une valeur attentdue !");
      action = 0;
      return action;
      break;
  }
}

int niveauLumix() {
  int reading = analogRead(lightPin); // Lecture de la PhotoRésistance
  return reading;
}

void afficherLumix(int lumix) {
  Serial.print("Lumix = ");
  Serial.println(lumix);
}

int valeurEtat() {
  if(!etat) {
    return etat;
  } else {
    etat = 0;
    return etat;
  }
}

void afficherEtat(int etat) {
  Serial.print("Etat = ");
  Serial.println(etat); 
}

int modifierEtat(int etat) {
  if(etat==0) {
    etat = 1;
    return etat;
  } else {
    etat = 0;
    return etat;
  }
  
}
