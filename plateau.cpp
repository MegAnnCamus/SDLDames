#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "deplacements.h"

extern casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];

void initPlateau(){
	int lig, col;
	for (lig = 0; lig < TAILLE_PLATEAU; lig++){
		for (col = 0; col < TAILLE_PLATEAU; col++){
			if ((lig + col) % 2 == 1){
				if (col <= 3){
					plateau[lig][col] = casePlateau{.numLig = lig,.numCol = col, .type = PION_BLANC, .couleur = BLANC};
				}
				else if (col >= 6){
					plateau[lig][col] = casePlateau{.numLig = lig,.numCol = col, .type = PION_NOIR, .couleur = NOIR};
				}
				else{
					plateau[lig][col] = casePlateau{.numLig = lig,.numCol = col, .type = CASE_VIDE, .couleur = CASE_VIDE};
				}
			}
			else{
				plateau[lig][col] = casePlateau{.numLig = lig,.numCol = col, .type = CASE_VIDE, .couleur = CASE_VIDE};
			}
		}
	}
}

void afficheLignePlateauConsole(){
	int i;
	printf("  |");
	for (i = 1; i < TAILLE_PLATEAU * 4; i++){
		printf("-");
	}
	printf("|\n");
}

void affichePlateauConsole(){
	int i, j;
	afficheLignePlateauConsole();
	for (j = TAILLE_PLATEAU - 1; j >= 0; j--)
	{
		printf((j < 9 ? "  " : "  "));
		for (i = 0; i < TAILLE_PLATEAU; i++){
			fprintf(stdout,"| %c ", plateau[i][j].type);
		}
		fprintf(stdout,"|\n");
		afficheLignePlateauConsole();
	}
	printf("   ");
	printf("\n");
}


casePlateau getCaseCliquee(SDL_Event evenement){

    int x,y;
    casePlateau caseCliquee;
	SDL_Rect positionSouris;

	positionSouris.x = evenement.button.x;
	positionSouris.y = evenement.button.y;
	x = positionSouris.x / TAILLE_CASE + 1;
	y = positionSouris.y / TAILLE_CASE + 1;

    if (x < 1 || x > 10 || y < 1 || y > 10) {
		fprintf(stderr, "Case hors plateau (%i,%i)\n", y, x);
	}
	else{
        fprintf(stdout,"Case cliquee : (%i,%i)\n", y, x);
        caseCliquee.numLig = y;
        caseCliquee.numCol = x;
        fprintf(stdout,"Case cliquee : (%i,%i)\n", caseCliquee.numLig, caseCliquee.numCol);
	}
    return caseCliquee;

}

casePlateau controlPremierClic(joueur joueurEnCours, SDL_Event evenement, casePlateau *oldCase){

    casePlateau caseCliquee;
	caseCliquee = getCaseCliquee(evenement);

	if(plateau[caseCliquee.numLig][caseCliquee.numCol].type != ' '){ //Si la case n'est pas libre
		if(plateau[caseCliquee.numLig][caseCliquee.numCol].couleur == joueurEnCours.couleur){ //Si la couleur du pion correspond à celle du joueur en cours
			*oldCase = caseCliquee;
			printf("Premier clic reussi : ligne = %d colonne = %d \n", caseCliquee.numLig, caseCliquee.numCol);
		}
	}
	return caseCliquee;

}

casePlateau controlDeuxiemeClic(SDL_Event evenement,casePlateau *newCase, casePlateau *oldCase){
	casePlateau caseCliquee;
	casePlateau caseCoup;

	caseCliquee = getCaseCliquee(evenement);

	if(plateau[caseCliquee.numLig][caseCliquee.numCol].type != ' '){
		//Si la case selectionne correspond a une des cases du tableau des coups possibles
		*newCase = caseCliquee;
        //TODO : deplacer
	}

	return caseCliquee;
}

void gestionEvenements(SDL_Surface *ecran)
{
    int continuer = 1;
    SDL_Event event;
    casePlateau test;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                //recupération la case cliquée
                test = getCaseCliquee(event);
                //node* listeDeplacementsPossibles = getDeplacementsPion(plateau, *test, TRUE, test.type);
                //liste de liste chainee
                //chaque liste chainee = liste de déplacements
                //recupérer la case d'arrivée du premier déplacement de chaque ligne
                //(la champ data de chaque premier élément de chaque liste)

                break;
        }

        SDL_Flip(ecran);
    }
}
