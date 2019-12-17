#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "structures.h"

//TODO : s�parer dans plusieurs fichiers pour �viter le bazar

//affichage plateau de jeu en ligne de commande (debug)
void affichePlateauConsole();
//affichage plateau de jeu en ligne de commande (debug)
void afficheLignePlateauConsole();
//initialisation plateau tour 1
void initPlateau();

//recuperation clic
casePlateau getCaseCliquee(SDL_Event evenement);

//n�cessaire pour g�rer les �v�nements SDL
void gestionEvenements(SDL_Surface *ecran);

//mise � jour du plateau � chaque tour
void playPartie();

//retourne TRUE si le joueur ne peut plus jouer, FALSE sinon
int coince(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char couleur);


//retourne tous les d�placements possibles pour un joueur
node* getCoupsJoueur(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char color);

//retourne la rafle maximale
rafle* getMaxRafle(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int profondeur);

//pour obtenir le plateau mis � jour apr�s un d�placement
void copierPlateau(casePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]);

//recuperation du score du plateau selon la couleur
int getScore(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char couleur);



