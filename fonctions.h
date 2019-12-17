#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include "constantes.h"
#include "structures.h"

//TODO : séparer dans plusieurs fichiers pour éviter le bazar

//affichage plateau de jeu en ligne de commande (debug)
void affichePlateauConsole();
//affichage plateau de jeu en ligne de commande (debug)
void afficheLignePlateauConsole();
//affichage plateau interface graphique
int affichePlateauSDL(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],SDL_Surface *ecran);
//initialisation plateau tour 1
void initPlateau();
//copie plateau pour mise à jour
void copierPlateau(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]);
//recuperation clic
casePlateau getCaseCliquee(SDL_Event evenement);

//nécessaire pour gérer les événements SDL
void gestionEvenements();

//mise à jour du plateau à chaque tour
void playPartie();

//retourne TRUE si le joueur ne peut plus jouer, FALSE sinon
int coince(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char couleur);

//mise à jour mouvements possibles
int updateListeCoups(node* nextMoves, int newCol, int newLig);
//retourne tous les déplacements possibles pour un joueur
node* getCoupsJoueur(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char color);
//retourne tous les déplacements possibles pour le pion sur la case c
node* getDeplacementsPion(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau* c, int premierAppel, char pion);

//retourne une liste avec seulement un saut (pas une rafle)
node* getOneMove(int posXDep, int posYDep, int posXArr, int posYArr, int capture);
//retourne la rafle maximale
rafle* getMaxRafle(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int profondeur);

//pour obtenir le plateau mis à jour après un déplacement
//casePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU] copierPlateau(casePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]);
//mise à jour du plateau en fonction du déplacement effectué
void jouerTour(deplacement* dep);

//retourne un pointeur vers le dernier élément d'une liste chainée
node* getLastNode(struct node* noeud, struct node* lastNext);
//recuperation du score du plateau selon la couleur
int getScore(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], char couleur);

//GESTION MEMOIRE
//free liste de cases
void freeListeCases(node *casesList);
//free deplacement
void freeDeplacement(deplacement *deplacement);
//free liste de deplacements
void freeListeDeplacements(node *depList);
//free rafle
void freeRafle(rafle* rafle);
//free une liste de rafles
void freeListeRafle(rafle *rafleList);


