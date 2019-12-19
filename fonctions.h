#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "structures.h"

//TODO : séparer dans plusieurs fichiers pour éviter le bazar

//affichage plateau de jeu en ligne de commande (debug)
void affichePlateauConsole();
//affichage plateau de jeu en ligne de commande (debug)
void afficheLignePlateauConsole();
//initialisation plateau tour 1
void initPlateau(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

//recuperation clic
casePlateau getCaseCliquee(SDL_Event evenement);

//nécessaire pour gérer les événements SDL
void gestionEvenements(SDL_Surface *ecran);

//mise à jour du plateau à chaque tour
void playPartie();

//retourne TRUE si le joueur ne peut plus jouer, FALSE sinon
int coince(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char couleur);


//retourne tous les déplacements possibles pour un joueur
node* getCoupsJoueur(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char color);

//retourne la rafle maximale
rafle* getMaxRafle(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int profondeur);

//pour obtenir le plateau mis à jour après un déplacement
void copierPlateau(casePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]);

//recuperation du score du plateau selon la couleur
int getScore(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char couleur);



