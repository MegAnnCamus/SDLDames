#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"

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
//allocation
void allocDeplacement(node* temp, node* result);
