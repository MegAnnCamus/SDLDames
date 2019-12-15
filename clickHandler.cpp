#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <SDL/SDL.h>
#include "structures.h"
#include "constantes.h"

casePlateau getCaseCliquee(SDL_Event evenement){

    int x,y;
    casePlateau caseCliquee;
	SDL_Rect positionSouris;

	positionSouris.x = evenement.button.x;
	positionSouris.y = evenement.button.y;
	x = positionSouris.x / TAILLE_CASE + 1;
	y = positionSouris.y / TAILLE_CASE + 1;

    if (x < 1 || x > 10 || y < 1 || y > 10) {
		fprintf(stderr, "Case hors plateau (%i,%i)\n", x, y);
	}
	else{
        fprintf(stdout,"Case cliquee : (%i,%i)\n", x, y);
        caseCliquee.numLig = x;
        caseCliquee.numCol = y;
	}
    return caseCliquee;

}

casePlateau controlPremierClic(joueur joueurEnCours, SDL_Event evenement, casePlateau *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau *oldCase){

    casePlateau caseCliquee;
	caseCliquee = getCaseCliquee(evenement);

	if(plateau[caseCliquee.numLig][caseCliquee.numCol]->type != ' '){ //Si la case n'est pas libre
		if(plateau[caseCliquee.numLig][caseCliquee.numCol]->couleur == joueurEnCours.couleur){ //Si la couleur du pion correspond à celle du joueur en cours
			*oldCase = caseCliquee;
			printf("Premier clic reussi : ligne = %d colonne = %d \n", caseCliquee.numLig, caseCliquee.numCol);
		}
	}
	return caseCliquee;

}

casePlateau controlDeuxiemeClic(SDL_Event evenement,casePlateau *newCase, casePlateau *oldCase, casePlateau *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
	casePlateau caseCliquee;
	casePlateau caseCoup;

	caseCliquee = getCaseCliquee(evenement);

	if(plateau[caseCliquee.numLig][caseCliquee.numCol]->type != ' '){
		//Si la case selectionne correspond a une des cases du tableau des coups possibles
		*newCase = caseCliquee;
        //TODO : deplacer
	}

	return caseCliquee;
}

