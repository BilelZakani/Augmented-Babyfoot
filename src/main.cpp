// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12,,11, 5, 4, 3, 2;

int capteur_force = 0;  // FSR branché sur pin Analog 0
int lecture_FSR; // Lecture analogique de la tension du pont diviseur du capteur FSR
int pression;
int score = 0;
int score2 = 0;
int capteur_force2 = 1;
int pression2;
int lecture_FSR2;
int ledr = 6;
int ledb = 7;

// paramètre bouton
const int btnPin = A2;
// variable bouton
int btnVal = 0;

void setup() {
  //initialise le nombre de colonnes et de lignes de l'écran LCD
  lcd.begin(16, 2);
  //affiche un message sur l'écran LCD.
  lcd.print("BLUE:        RED:");
  Serial.begin(9600);  // Envoide message de déboggage sur connexion série

  //Initialisation du bouton
  pinMode(btnPin, INPUT_PULLUP);

  //Initialisation des leds
  pinMode(ledr, OUTPUT);
  pinMode(ledb, OUTPUT);
  digitalWrite(ledr,LOW);
  digitalWrite(ledb,LOW);
  
}


void loop() {

  digitalWrite(ledr,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(9,LOW);

  pinMode(9, OUTPUT);

  delay(500);

  // On envoie le signal
  digitalWrite(9,HIGH);

  delayMicroseconds(10);

  digitalWrite(9,LOW);

  // On reçoit le signal
  pinMode(8,INPUT);

  long temps = pulseIn(8, HIGH);

  // On calcule la distance

  float vitesse = 340.0;

  long distance = (vitesse * temps)/1000;

  distance = distance/2;

  Serial.println(distance, DEC);

  lecture_FSR = analogRead(capteur_force);
  Serial.print("Capteur de force = ");
  Serial.println(lecture_FSR);


  pression = map(lecture_FSR, 0, 1023, 0, 255);


  if(pression > 0.5 and distance > 2000)
  {
    score = score +1 ;
    score2 = score2 - 1;
    digitalWrite(ledb,HIGH);
    delay(500);
  }

  else if(distance < 2000)
  {
    score = score + 1;
    digitalWrite(ledb,HIGH);
    delay(500);
  }

  else
  {
    digitalWrite(ledb,LOW);
  }


  // même code mais pour les capteurs de l'autre cage

  digitalWrite(13, LOW);
  pinMode(13, OUTPUT);
  delay(500);
  digitalWrite(13,HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  pinMode(10, INPUT);
  long temps2 = pulseIn(10, HIGH);
  long distance2 = (vitesse * temps2)/1000;
  distance2 = distance2/2;
  Serialprintln(distance2, DEC);
  lecture_FSR2 = analogRead(capteur_force2);
  Serial.print("Capteur de Force2 =  ");
  Serial.println(lecture_FSR2);
  pression2 = map(lecture_FSR, 0, 1023, 0, 255);

  if(pression >0.5 and distance2 > 2000)
  {
    score2 = score2 + 1;
    score = score - 1;
    digitalWrite(ledr,HIGH);
    delay(500);
  }

  else if(distance2 < 2000)
  {
    score2 = score2 + 1;
    digitalWrite(ledr,HIGH);
    delay(500);
  }

  else
  {
    digitalWrite(ledr,LOW);
  }



  // réinitialise les scores quand la partie est finie

  if(score>10)
  {
    score = 0;
    score2 = 0;
    lcd.setCursor(1,2);
    lcd.print("       ");
    lcd.setCursor(12,2);
    lcd.print("       ");
  }
  if(score2 > 10)
  {
    score = 0;
    score2 = 0;
    lcd.setCursor(1,2);
    lcd.print("       ");
    lcd.setCursor(12,2);
    lcd.print("       ");
  }

  // permet d'éviter les erreurs d'affichage lors du passage négatif à positif
  lcd.setCursor(1,2);
  lcd.print("       ");
}
