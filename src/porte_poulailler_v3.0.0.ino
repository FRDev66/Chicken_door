// ###################################################################
// Code permettant ouverture / fermeture d'une porte de poulailler
// selon la luminausité
// Composants : 
// + Arduino UNO
// + Servo Moteur MG996R
// + Cellule photorésistance
//####################################################################
// Auteur : FRDev66
// Date : 2023-08-06
// version :3.0.0
// 
// ChangeLog :
// + [3.0.0 : Modification du type de moteur : Pas à Pas --> Servo Moteur
// 
// ###################################################################

// Liste Bibliothèques utiles
#include <Servo.h>

// Déclaration Constantes & Variables
int action = 9; // Initialisation de la Variable liée au Type d'Action à effectuer (3 = Rien / 1 = Ouverture Porte / 2 = Fermeture Porte)
int etat = 0; // Initialisation de la Variable liée au déclenchement des Actions Porte (0 = Ouverture / 1 = Fermeture)
int etatPorte = 9; // Initalisation de la Variable de l'Etat Actuel de la Porte (0 = Porte Fermée / 1 = Porte Ouverte / 9 = défaut)

unsigned long tempoDepart = 0; // Définition de la Variable de déclenchement d'une mesure

#define tempoMesures 10000 // Délai entre 2 Mesures Statiques de luminosité (lumix)

// Déclaration des Broches (PIN) utilisés
int lightPin = 0; // Pin de branchement de la cellule Photorésistance = A0

// Déclaration Transverse
Servo myServo; // Déclaration Constante Servo Moteur

void setup() {
  Serial.begin(115200); // Ouverture du port série et debit de communication fixé à 9600 bauds

}

void loop() {
  
  // Toutes les 30 minutes ==> Lancer une phase de Mesures Statiques
  if ( millis() - tempoDepart >= tempoMesures ) {
    int reading = niveauLumix();
    afficherLumix(reading);
   

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
      myServo.write(0);
      delay(1000);
      myServo.detach();
      etatPorte = 1;
      return etatPorte;
      break;
    case 2 :
      myServo.attach(9); 
      myServo.write(180);
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
