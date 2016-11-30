#include "display.h"

// Tableau contenant les 5 chiffres à afficher
extern int afficheur[5];

// Déclaration du clavier numérique
const byte LIGNES = 4; // 4 lignes
const byte COLONNES = 3; // 3 colonnes
char touches[LIGNES][COLONNES] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte brLignes[LIGNES] = {10, 12, 7, 11}; // Connection vers les broches des lignes du clavier numérique
byte brColonnes[COLONNES] = {8, 6, 9};     // Connection vers les broches des colonnes du clavier numérique
Keypad clavier = Keypad( makeKeymap(touches), brLignes, brColonnes, LIGNES, COLONNES );

/**
 * Affiche une valeur sur l'afficheur
 * @param valeur la valeur à afficher
 */
void Display ( long valeur ) {
  Serial.print("valeur = ");
  Serial.println(valeur);

  // Extraie les cinq chiffres du montant
  byte chiffres[5]={0, 0, 0, 0, 0};
  for ( byte ii = 0; ii < 5 ; ii++ ) {
    byte chiffre = valeur % 10;
    Serial.println(chiffre);
    chiffres[ii] = chiffre;
    valeur /= 10;
  }
  
  // Supprime les zéros non significatifs : les remplace par la valeur 10, qui sera "vide" sur l'afficheur
  Serial.println("------------------------");
  byte chiffre=0;
  byte ii = 4;
  while ( chiffre == 0 && ii > 0) {
    chiffre = chiffres[ii];
    Serial.println(chiffre);
    if (chiffre == 0 ) chiffres[ii] = 10;
    ii--;
  }

  // Affiche les chiffres
  Serial.println("------------------------");
  for ( byte ii = 0; ii < 5 ; ii++ ) {
    Serial.println(chiffres[ii]);
    writeADigit (chiffres[ii], afficheur[ii]);
  }

}

void setup() {
  // Initialise l'afficheur
  digitSetup();

  // Initialise le port série
  Serial.begin(9600);
}

long montant = 0;
byte ii = 0;
bool chiffrePresse = false;

void loop() {
  // Attente de l'appui sur une touche du clavier
  char touche = clavier.getKey();

  // Si la touche est '*' est pressée, on va lire la série de chiffre à suivre jusqu'à ce que :
  //  - on appuie sur la touche '#' => on affiche les chiffres saisis
  //  - on ai saisi chiffres => on affiche les chiffres saisis
  if ( touche == '*' ){
    chiffrePresse = false;
    montant = 0;
    ii = 0;

    // Tant que l'on a pas saisi cinq chiffres, on continue la lecture sur le clavier
    while ( ii < 5 ) {
      touche = clavier.getKey();

      // En cas d'appui sur la touche "#" on sort de la boucle de lecture,
      // quel que soit le nombre de chiffres saisis
      if ( touche == '#' ) {
        break;
      }
      
      if ( touche ) {
        chiffrePresse = true;
        char touches[2];
        touches[0]=touche;
        touches[1]=0;
        montant = 10 * montant + atol(touches);
        ii++;
        Serial.print("montant (");
        Serial.print(ii);
        Serial.print(") = ");
        Serial.print(montant);
        Serial.println(" ");

      }
    }

    
    if (chiffrePresse) {
      // Si on avait saisi des nombres, on les affiche
      Display(montant);
    }
    else {
      // Sinon on efface l'afficheur
      blank(afficheur[0]);
      blank(afficheur[1]);
      blank(afficheur[2]);
      blank(afficheur[3]);
      blank(afficheur[4]);
    }
      
  }
}

