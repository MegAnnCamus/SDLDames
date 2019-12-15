#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <SDL/SDL.h>

#include"structures.h"
#include"constantes.h"

extern casePlateau plateau[TAILLE_ECRAN][TAILLE_PLATEAU];

void jouerTour(deplacement* dep){

	casePlateau* caseDep = (*dep).depart;
	char pion = plateau[(*caseDep).numLig][(*caseDep).numCol].type;
	node* destination = (*dep).arrivee;

	while (destination != NULL){
		casePlateau* nextCase = (casePlateau*)(*destination).data;
		//si un pion est mangé pendant le deplacement
		if (abs((*nextCase).numLig - (*caseDep).numLig) > 1){
			int xPionMange, yPionMange;
			//direction prise
			if ((*nextCase).numLig > (*caseDep).numLig)
				xPionMange = (*nextCase).numLig - 1;
			else
                xPionMange = (*nextCase).numLig + 1;

			if ((*nextCase).numCol > (*caseDep).numCol)
				yPionMange = (*nextCase).numCol - 1;
			else
                yPionMange = (*nextCase).numCol + 1;

            //on remplace le pion mangé par une case vide
			plateau[xPionMange][yPionMange].type = CASE_VIDE;
		}

		//la case de départ devient vide
		//la case d'arrivee est le pion que l'on a déplacé
		plateau[(*caseDep).numLig][(*caseDep).numCol].type = CASE_VIDE;
		plateau[(*caseDep).numLig][(*caseDep).numCol].type = pion;

		//si rafle on doit passer à la case suivante
		caseDep = nextCase;
		destination = (*destination).next;
	}

	//promotion en dame
	if (((*caseDep).numCol == 9) && (pion == PION_BLANC))
		plateau[(*caseDep).numLig][(*caseDep).numCol].type = DAME_BLANC;
	if (((*caseDep).numCol == 0) && (pion == PION_NOIR))
		plateau[(*caseDep).numLig][(*caseDep).numCol].type = DAME_NOIR;
}
