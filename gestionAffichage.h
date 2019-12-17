#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"

//Gestion du menu
int constructMenu(SDL_Surface* ecran, TTF_Font* font);
void afficheMenuJeu(SDL_Surface* ecran,casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

//affichage plateau interface graphique
int affichePlateauSDL(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],SDL_Surface *ecran);
//affichage des pions
void affichePions(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],SDL_Surface *ecran) ;
