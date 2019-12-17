#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "structures.h"

//copie plateau pour mise � jour
void copierPlateau(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]);
//retourne tous les d�placements possibles pour le pion sur la case c
node* getDeplacementsPion(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau* c, int premierAppel, char pion);
//mise � jour mouvements possibles
int updateListeCoups(node* nextMoves, int newCol, int newLig);
//retourne une liste avec seulement un saut (pas une rafle)
node* getOneMove(int posXDep, int posYDep, int posXArr, int posYArr, int capture);
//retourne un pointeur vers le dernier �l�ment d'une liste chain�e
node* getLastNode(struct node* noeud, struct node* lastNext);
//mise � jour du plateau en fonction du d�placement effectu�
void jouerCoup(deplacement* dep);
//free liste de deplacements
void freeListeDeplacements(node *depList);
