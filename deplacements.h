#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "structures.h"

//copie plateau pour mise à jour
void copierPlateau(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]);
//retourne tous les déplacements possibles pour le pion sur la case c
node* getDeplacementsPion(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau* c, int premierAppel, char pion);
//mise à jour mouvements possibles
int updateListeCoups(node* nextMoves, int newCol, int newLig);
//retourne une liste avec seulement un saut (pas une rafle)
node* getOneMove(int posXDep, int posYDep, int posXArr, int posYArr, int capture);
//retourne un pointeur vers le dernier élément d'une liste chainée
node* getLastNode(struct node* noeud, struct node* lastNext);
//mise à jour du plateau en fonction du déplacement effectué
void jouerCoup(deplacement* dep);
//free liste de deplacements
void freeListeDeplacements(node *depList);
