#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonctions.h"

int affichePlateauSDL(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU],SDL_Surface *ecran){

    SDL_Surface *cases[2] = {NULL};
    SDL_Rect position;
    int i = 1;
    int j = 1;
    ecran = SDL_SetVideoMode(TAILLE_ECRAN, TAILLE_ECRAN, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    //case blanche
    cases[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CASE, TAILLE_CASE, 32, 0, 0, 0, 0);
    SDL_FillRect(cases[0], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    //case noire
    cases[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CASE, TAILLE_CASE, 32, 0, 0, 0, 0);
    SDL_FillRect(cases[1], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    for(j = 0 ; j < TAILLE_PLATEAU ; j++){
        for(i = 0 ; i < TAILLE_PLATEAU  ; i++){
            //TODO : print pions
            position.x = (i) * TAILLE_CASE;
            position.y = (j) * TAILLE_CASE;

            if ( (i+j) % 2 == 1 )
            {
                SDL_BlitSurface(cases[1], NULL, ecran, &position);
            }
            else
            {
                SDL_BlitSurface(cases[0], NULL, ecran, &position);
            }
        }
    }

    affichePions(plateau,ecran);

    SDL_WM_SetCaption("Jeu de dames", NULL);
    /* Mise à jour de l'écran et de tout ce qu'il contient. */
    SDL_Flip(ecran);
    gestionEvenements(ecran);

    SDL_FreeSurface(cases[0]);
    SDL_FreeSurface(cases[1]);

    SDL_Quit();

    return EXIT_SUCCESS;
}

int constructMenu(SDL_Surface* ecran, TTF_Font* font, casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU])
{

	int x, y;
    SDL_Surface  *imageDeFond = NULL;

	const char* labels[NB_ITEMS_MENU] = {"Jouer","Quitter"};
	SDL_Surface* menus[NB_ITEMS_MENU];
	int selected[NB_ITEMS_MENU] = {FALSE,FALSE};

	SDL_Color color[2] = {{218, 225, 237},{146, 170, 212}};

    ecran = SDL_SetVideoMode(TAILLE_ECRAN, TAILLE_ECRAN, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]);
	menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);

	SDL_Rect positionsItems[NB_ITEMS_MENU];
	positionsItems[0].x = ecran->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	positionsItems[0].y = ecran->clip_rect.h/2 - menus[0]->clip_rect.h;
	positionsItems[1].x = ecran->clip_rect.w/2 - menus[1]->clip_rect.w/2;
	positionsItems[1].y = ecran->clip_rect.h/2 + menus[1]->clip_rect.h;

    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;

    imageDeFond = SDL_LoadBMP("./img/ui/fond.bmp");

    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	SDL_Event event;
	int continuer = 1;
	while(continuer)
	{
		SDL_WaitEvent(&event);

			switch(event.type)
			{
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					continuer = 0;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for(int i = 0; i < NB_ITEMS_MENU; i++) {
						if(x>=positionsItems[i].x && x<=positionsItems[i].x+positionsItems[i].w && y>=positionsItems[i].y && y<=positionsItems[i].y+positionsItems[i].h)
						{
							if(selected[i]==FALSE)
							{
								selected[i] = TRUE;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
							}
						}
						else
						{
							if(selected[i]==TRUE)
							{
								selected[i] = FALSE;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
				    //TODO : démarrer le jeu
					x = event.button.x;
					y = event.button.y;
					for(int i = 0; i < NB_ITEMS_MENU; i ++) {
						if(x>=positionsItems[i].x && x<=positionsItems[i].x+positionsItems[i].w && y>=positionsItems[i].y && y<=positionsItems[i].y+positionsItems[i].h)
						{
						    switch(i){

                            case 0 :
                                affichePlateauSDL(plateau,ecran);
                                break;

						    default :
                                SDL_FreeSurface(menus[0]);
                                SDL_FreeSurface(menus[1]);
                                break;
						    }
						}
					}
					break;
			}

		for(int i = 0; i < NB_ITEMS_MENU; i ++) {
			SDL_BlitSurface(menus[i],NULL,ecran,&positionsItems[i]);
		}

		SDL_Flip(ecran);
	}


    SDL_Quit();
}

void afficheMenuJeu(SDL_Surface *ecran, casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU])
{
	ecran = SDL_SetVideoMode(TAILLE_ECRAN,TAILLE_ECRAN,32,SDL_SWSURFACE);
	SDL_WM_SetCaption("Jeu de dames", NULL);

	TTF_Font *font;
	TTF_Init();
	font = TTF_OpenFont("./highland-gothic/HighlandGothicFLF.ttf",30);

	int result;
	result = constructMenu(ecran, font, plateau);
}
