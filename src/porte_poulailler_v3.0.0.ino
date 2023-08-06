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


  /* switch (etat)
  {
    case 1:
      if(reading >= 200) {
      // Fait bouger le bras de 0° à 180°
        //myServo.write(1);
        for (unsigned long position = 1500; position <= 2000; position += 500) {
          myServo.writeMicroseconds(position);
          delay(15);
          Serial.println(position);
        }
        etat = 0;
        
      } else {Serial.println("Pas assez de lumière !!");}
      break;
    
    case 0:
      if(reading <= 50) {
      // Fait bouger le bras de 180° à 0°
        for (unsigned long position = 2500; position >= 1000; position -= 5) {
          myServo.writeMicroseconds(position);
          delay(15);
        }
        etat = 1;
      } else {} 
      break;
  }

  delay(10000); */
}

int actionPorte(int action) {
  switch (action) {
    case 1 :
      myServo.attach(9); 
      myServo.write(180);
      delay(1000);
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


// Séquence d'alimentation normale des bobines du moteur en Full Step
// void Fermer_porte() {
//   Serial.println(etat);
//   myservo.write(0);// move servos to center position -> 90°

//   Serial.println("Porte Fermée"); // Affichage sur le moniteur série
//   //etat=0;
//   Serial.print("Etat = ");
//   Serial.println(etat); // Affiche Etat après Fermeture de la Porte (doit être 0)
// }

// // Séquence d'alimentation inverse des bobines du moteur en Full Step
// void Ouvrir_porte() {
//   Serial.println("Ouverture Porte...");
//   myservo.write(30);// move servos to center position -> 90°
  
//   Serial.println("Porte Ouverte"); // Affichage sur le moniteur série
//   //etat=1;
//   Serial.print("Etat = ");
//   Serial.println(etat); // Affiche Etat après Fermeture de la Porte (doit être 1)
//   Serial.print("Angle = ");
//   Serial.println(angle);
// }

