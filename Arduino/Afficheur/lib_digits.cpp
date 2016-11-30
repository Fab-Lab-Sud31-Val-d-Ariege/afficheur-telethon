//
// $Id$

#include "display.h"

// Broches BCD
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;

 // Sélection des chiffres
const int ch0 = A1;
const int ch1 = A2;
const int ch2 = A3;
const int ch3 = A4;
const int ch4 = A5;
int afficheur[5] = {ch0, ch1, ch2, ch3, ch4};

// Blanking input (vide l'afficheur, ne fonctionne que tant qu'appliqué)
const int BI = A0;

/** 
 * Efface l'afficheur globalement via la fonction de "blanking input" du décodeur 7 segments 
 */
void blank()
{
  digitalWrite(BI, LOW);
  delay(1);
}

/** 
 *  Efface un chiffre en y envoyant une valeur supérieure à 9
 *  @param ch le chiffre à effacer
 */
void blank(int ch)
{
  writeADigit(15, ch);
}

/**
 * Affiche une valeur sur un chiffre
 * @param valeur la valeur à afficher (entre 0 et 9)
 * @param ch le chiffre sur lequel afficher la valeur
 */
void writeADigit (int valeur, int ch)
{
  // Désactive Blank input
  digitalWrite(BI, HIGH);

  // Envoi le chiffre bit par bit sur l'entrée BCD du décodeur 7 segments
  digitalWrite(pinA, bitRead(valeur, 0));
  digitalWrite(pinB, bitRead(valeur, 1));
  digitalWrite(pinC, bitRead(valeur, 2));
  digitalWrite(pinD, bitRead(valeur, 3));

  // Déclenche la gachette d'affichage
  digitalWrite(ch, LOW);
  delay(1);
  digitalWrite(ch, HIGH);
  delay(1);
}

/**
 * Initialise l'afficheur
 */
void digitSetup() {
  // Positionne les broches BCD en mode OUTPUT
  for ( int ii = 2; ii <=5; ++ii ) {
    pinMode(ii, OUTPUT); 
  }

  // Positionne les broches "blank input" et gachettes en mode OUTPUT
  pinMode(BI, OUTPUT);
  pinMode(ch0, OUTPUT);
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(ch3, OUTPUT);
  pinMode(ch4, OUTPUT);

  // Relache les gachettes
  digitalWrite(ch0, HIGH);
  digitalWrite(ch1, HIGH);
  digitalWrite(ch2, HIGH);
  digitalWrite(ch3, HIGH);
  digitalWrite(ch4, HIGH);

  // Efface l'ensemble des chiffres
  blank(ch0);
  blank(ch1);
  blank(ch2);
  blank(ch3);
  blank(ch4);
}


