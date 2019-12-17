#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "gestionAffichage.h"

casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU];

char userColor;
int minimaxDepth;
rafle* root;
int debugCounter;

int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    afficheMenuJeu(ecran,plateau);
    //affichePlateauSDL(plateau,ecran);
    return 0;
}
