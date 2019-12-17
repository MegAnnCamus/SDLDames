#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <SDL/SDL.h>

#include"structures.h"
#include"constantes.h"

//TODO : séparer dans plusieurs fichiers si possible...
//mettre gestion mémoire dans un seul cpp
//mettre getmoves dans un seul cpp

extern casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];

void jouerCoup(deplacement* dep){

	casePlateau* caseDep = (*dep).depart;
	char pion = plateau[(*caseDep).numLig][(*caseDep).numCol].type;
	node* destination = (*dep).arrivee;

	while (destination != NULL){
		casePlateau* nextCase = (casePlateau*)(*destination).data;
		//si un pion est mangé pendant le deplacement
		if (abs((*nextCase).numLig - (*caseDep).numLig) > 1){
			int xPionMange, yPionMange;
			//direction prise
			if ((*nextCase).numCol > (*caseDep).numCol)
				xPionMange = (*nextCase).numCol - 1;
			else
                xPionMange = (*nextCase).numCol + 1;

			if ((*nextCase).numLig > (*caseDep).numLig)
				yPionMange = (*nextCase).numLig - 1;
			else
                yPionMange = (*nextCase).numLig + 1;

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

void copierPlateau(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau copie[TAILLE_PLATEAU][TAILLE_PLATEAU]){

	for (int i = 0; i < TAILLE_PLATEAU; i++){
		for (int j = 0; j < TAILLE_PLATEAU; j++){
			copie[i][j] = plateau[i][j];
		}
	}
}

node* getOneMove(int posXDep, int posYDep, int posXArr, int posYArr, int capture){
	node* temp = (node*)malloc(sizeof(node));
	(*temp).next = NULL;
	(*temp).data = (deplacement*)malloc(sizeof(deplacement));

	if (capture==TRUE)
		(*(deplacement*)((*temp).data)).nbPrise = 1;
	else
        (*(deplacement*)((*temp).data)).nbPrise = 0;

	(*(deplacement*)((*temp).data)).depart = (casePlateau*)malloc(sizeof(casePlateau));
	(*(*(deplacement*)((*temp).data)).depart).numCol = posXDep;
	(*(*(deplacement*)((*temp).data)).depart).numLig = posYDep;
	(*(deplacement*)((*temp).data)).arrivee = (node*)malloc(sizeof(node));

	(*(*(deplacement*)((*temp).data)).arrivee).next = NULL;
	(*(*(deplacement*)((*temp).data)).arrivee).data = (casePlateau*)malloc(sizeof(casePlateau));

	(*(casePlateau*)(*(*(deplacement*)((*temp).data)).arrivee).data).numCol = posXArr;
	(*(casePlateau*)(*(*(deplacement*)((*temp).data)).arrivee).data).numLig = posYArr;

	return temp;
}
int updateListeCoups(node* nextMoves, int newCol, int newLig){

	node *temp = nextMoves;

	while (temp != NULL){
		(*(deplacement*)(*temp).data).nbPrise++;
		node* firstDest = (node*)malloc(sizeof(node));

		(*firstDest).data = (*(deplacement*)(*temp).data).depart;
		(*firstDest).next = (*(deplacement*)(*temp).data).arrivee;
		(*(deplacement*)(*temp).data).arrivee = firstDest;
		(*(deplacement*)(*temp).data).depart = NULL;
		casePlateau* nouvelleCase = (casePlateau*)malloc(sizeof(casePlateau));

		(*nouvelleCase).numCol = newCol;
		(*nouvelleCase).numLig = newLig;
		(*(deplacement*)(*temp).data).depart = nouvelleCase;
		temp = (*temp).next;
	}
	return (1);
}

node* getLastNode(node* noeud, node* lastNext){
	node* temp = noeud;
	while ((*temp).next != lastNext)
		temp = (*temp).next;
	return temp;
}

void freeListeCases(node *casesList){
	if (casesList != NULL){
		freeListeCases((*casesList).next);
		free((*casesList).data);
		free(casesList);
	}
}

void freeDeplacement(deplacement *deplacement){
	if (deplacement != NULL){
		if ((*deplacement).depart != NULL)
			free((*deplacement).depart);
		freeListeCases((*deplacement).arrivee);
		free(deplacement);
	}
}

void freeListeDeplacements(node *depList){
	if (depList != NULL){
		freeListeDeplacements((*depList).next);
		freeDeplacement((deplacement*)(*depList).data);
		free(depList);
	}
}

//TODO : ajout dans .h
void allocDeplacement(node* temp, node* result){
    if ((*result).data == NULL){
        freeListeDeplacements(result);
        result = temp;
    }
    else{
        (*temp).next = result;
        result = temp;
    }
}

//TODO : séparer pions des dames...
//TODO : factoriser (deplacements dames)
//TODO : separer capture de mouvement simple
//Renvoie la liste des déplacements possibles
node* getDeplacementsPion(casePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], casePlateau* c, int premierAppel, char pion){

	int x = (*c).numCol;
	int y = (*c).numLig;
	free(c);

	node* result = (node*)malloc(sizeof(node));
	(*result).data = NULL;
	(*result).next = NULL;

	if (premierAppel){
        //mouvements pions classiques
		if (pion == PION_BLANC || pion == PION_NOIR){
            //diagonale bas droite
			if ((x + 1 < TAILLE_PLATEAU) && (y + 1 < TAILLE_PLATEAU) && (plateau[y + 1][x + 1].type == CASE_VIDE)){
				node* temp = getOneMove(x, y, x + 1, y + 1, FALSE);
                if (temp == NULL){
                    freeListeDeplacements(result);
                    return (NULL);
                }
                else{
                    allocDeplacement(temp,result);
                }
			}
			//diagonale bas gauche
			if ((x - 1 >= 0) && (y + 1 < TAILLE_PLATEAU) && (plateau[y - 1][x + 1].type == CASE_VIDE)){
				node* temp = getOneMove(x, y, x - 1, y + 1, FALSE);
				if (temp == NULL){
                    freeListeDeplacements(result);
                    return (NULL);
                }
                else{
                    allocDeplacement(temp,result);
                }
			}
			//diagonale haut droite
			if ((x + 1 < TAILLE_PLATEAU) && (y - 1 >= 0) && (plateau[y + 1][x - 1].type == CASE_VIDE)){
				node* temp = getOneMove(x, y, x + 1, y - 1, FALSE);
                if (temp == NULL){
                    freeListeDeplacements(result);
                    return (NULL);
                }
                else{
                    allocDeplacement(temp,result);
                }
			}
			//diagonale haut gauche
			if ((x - 1 >= 0) && (y - 1 >= 0) && (plateau[y - 1][x - 1].type == CASE_VIDE)){
				node* temp = getOneMove(x, y, x - 1, y - 1, FALSE);
				if (temp == NULL){
                    freeListeDeplacements(result);
                    return (NULL);
                }
                else{
                    allocDeplacement(temp,result);
                }
			}
		}
		//mouvements dames
		if ((pion == DAME_BLANC) || (pion == DAME_NOIR)){
			//verif diagonale haut gauche
			int i = x - 1;
			int j = y - 1;
			int stop = 0;

			while ((i >= 0) && (j >= 0) && (!stop)){
				if (plateau[j][i].type == CASE_VIDE){
					node* temp = getOneMove(x, y, i, j, FALSE);
					if (temp == NULL){
						freeListeDeplacements(result);
						return (NULL);
					}
                    else{
                        allocDeplacement(temp,result);
                    }
				}
				else{
					stop = 1;
                    //verif si on peut prendre dans cette direction
                    //verif si on ne sort pas du plateau à la fin du mouvement
					if ((((pion == DAME_BLANC) && ((plateau[j][i].type == PION_NOIR) || (plateau[j][i].type == DAME_NOIR))) ||
						((pion == DAME_NOIR) && ((plateau[j][i].type == PION_BLANC) || (plateau[j][i].type == DAME_BLANC))))
						&& (j - 1 >= 0) && (i - 1 >= 0) && (plateau[j - 1][i - 1].type == CASE_VIDE)
						&& (i != x - 1) && (j != y - 1)){

						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = i - 1;
						(*nextStep).numLig = j - 1;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau,copiePlateau);
						copiePlateau[j][i].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[j - 1][i - 1].type = pion;
						//recursivite
						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);

                        //pas de nouveau mouvement possible
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, i - 1, j - 1, TRUE);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							else{
                                allocDeplacement(temp,result);
							}
						}
						//nouveaux mouvements possibles
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
				i--;
				j--;
			}
			//verif diagonale haut gauche
			i = x + 1;
			j = y - 1;
			stop = 0;

			while ((i < TAILLE_PLATEAU) && (j >= 0) && (!stop)){
				if (plateau[j][i].type == CASE_VIDE){
					node* temp = getOneMove(x, y, i, j, 0);
					if (temp == NULL){
						freeListeDeplacements(result);
						return (NULL);
					}
					else{
                        allocDeplacement(temp,result);
					}
				}
				else{
					stop = 1;
					if ((((pion == DAME_BLANC) && ((plateau[j][i].type == PION_NOIR) || (plateau[j][i].type == DAME_NOIR))) ||
						((pion == DAME_NOIR) && ((plateau[j][i].type == PION_BLANC) || (plateau[j][i].type == DAME_BLANC))))
						&& (i + 1 < TAILLE_PLATEAU) && (j - 1 >= 0) && (plateau[j - 1][i + 1].type == CASE_VIDE)
						&& (i != x + 1) && (j != y - 1)){

						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = i + 1;
						(*nextStep).numLig = j - 1;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau, copiePlateau);
						copiePlateau[j][i].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[j - 1][i + 1].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, i + 1, j - 1, TRUE);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
				i++;
				j--;
			}
			//verif diagonale bas gauche
			i = x - 1;
			j = y + 1;
			stop = 0;

			while ((i >= 0) && (j < TAILLE_PLATEAU) && (!stop)){
				if (plateau[j][i].type == CASE_VIDE){
					node* temp = getOneMove(x, y, i, j, FALSE);
					if (temp == NULL){
						freeListeDeplacements(result);
						return (NULL);
					}
					else{
                        allocDeplacement(temp,result);
					}
				}
				else{
					stop = 1;
					if ((((pion == DAME_BLANC) && ((plateau[j][i].type == PION_NOIR) || (plateau[j][i].type == DAME_NOIR))) ||
						((pion == DAME_NOIR) && ((plateau[j][i].type == PION_BLANC) || (plateau[j][i].type == DAME_BLANC))))
						&& (i - 1 >= 0) && (j + 1 < TAILLE_PLATEAU) && (plateau[j + 1][i - 1].type == CASE_VIDE)
						&& (i != x - 1) && (j != y + 1)){

						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = i - 1;
						(*nextStep).numLig = j + 1;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau, copiePlateau);
						copiePlateau[j][i].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[j + 1][i - 1].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}

						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, i - 1, j + 1, TRUE);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
				i--;
				j++;
			}
			//verif diagonale bas droite
			i = x + 1;
			j = y + 1;
			stop = 0;

			while ((i < TAILLE_PLATEAU) && (j < TAILLE_PLATEAU) && (!stop)){
				if (plateau[j][i].type == CASE_VIDE){
					node* temp = getOneMove(x, y, i, j, 0);
					if (temp == NULL){
						freeListeDeplacements(result);
						return (NULL);
					}
					else{
                        allocDeplacement(temp,result);
					}
				}
				else{
					stop = 1;
					if ((((pion == DAME_BLANC) && ((plateau[j][i].type == PION_NOIR) || (plateau[j][i].type == DAME_NOIR))) ||
						((pion == DAME_NOIR) && ((plateau[j][i].type == PION_BLANC) || (plateau[j][i].type == DAME_BLANC))))
						&& (i + 1 < TAILLE_PLATEAU) && (j + 1 < TAILLE_PLATEAU) && (plateau[j + 1][i + 1].type == CASE_VIDE)
						&& (i != x + 1) && (j != y + 1)){

						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = i + 1;
						(*nextStep).numLig = j + 1;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau, copiePlateau);
						copiePlateau[j][i].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[j + 1][i + 1].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, i + 1, j + 1, 1);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
				i++;
				j++;
			}
		}
	}
	//verif captures
	if ((!((pion == PION_BLANC) && (y == TAILLE_PLATEAU - 1))) && ((!((pion == PION_NOIR) && (y == 0))))){
		//verif capture haut gauche
		if ((x - 1 >= 0) && (y - 1 >= 0)){
			if ((((pion == DAME_BLANC) || (pion == PION_BLANC)) && ((plateau[y - 1][x - 1].type == PION_NOIR) || (plateau[y - 1][x - 1].type == DAME_NOIR))) ||
				(((pion == DAME_NOIR) || (pion == PION_NOIR)) && ((plateau[y - 1][x - 1].type == PION_BLANC) || (plateau[y - 1][x - 1].type == DAME_BLANC)))){
				if ((x - 2 >= 0) && (y - 2 >= 0)){
					if (plateau[y - 2][x - 2].type == CASE_VIDE){
						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = x - 2;
						(*nextStep).numLig = y - 2;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau,copiePlateau);
						copiePlateau[y - 1][x - 1].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[y - 2][x - 2].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, x - 2, y - 2, TRUE);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}

			}
		}
		//verif capture haut droite
		if ((x + 1 < TAILLE_PLATEAU) && (y - 1 >= 0)){
			if ((((pion == DAME_BLANC) || (pion == PION_BLANC)) && ((plateau[y - 1][x + 1].type == PION_NOIR) || (plateau[y - 1][x + 1].type == DAME_NOIR))) ||
				(((pion == DAME_NOIR) || (pion == PION_NOIR)) && ((plateau[y - 1][x + 1].type == PION_BLANC) || (plateau[y - 1][x + 1].type == DAME_BLANC)))){
				if ((x + 2 < TAILLE_PLATEAU) && (y - 2 >= 0)){
					if (plateau[y - 2][x + 2].type == CASE_VIDE){
						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = x + 2;
						(*nextStep).numLig = y - 2;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau,copiePlateau);
						copiePlateau[y - 1][x + 1].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[y - 2][x + 2].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, x + 2, y - 2, 1);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
			}
		}
		//verif capture bas gauche
		if ((x - 1 >= 0) && (y + 1 < TAILLE_PLATEAU)){
			if ((((pion == DAME_BLANC) || (pion == PION_BLANC)) && ((plateau[y + 1][x - 1].type == PION_NOIR) || (plateau[y + 1][x - 1].type == DAME_NOIR))) ||
				(((pion == DAME_NOIR) || (pion == PION_NOIR)) && ((plateau[y + 1][x - 1].type == PION_BLANC) || (plateau[y + 1][x - 1].type == DAME_BLANC)))){
				if ((x - 2 >= 0) && (y + 2 < TAILLE_PLATEAU)){
					if (plateau[y + 2][x - 2].type == CASE_VIDE){
						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = x - 2;
						(*nextStep).numLig = y + 2;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau,copiePlateau);
						copiePlateau[y + 1][x - 1].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[y + 2][x - 2].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, x - 2, y + 2, 1);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
			}
		}
		//verif capture bas droite
		if ((x + 1 < TAILLE_PLATEAU) && (y + 1 < TAILLE_PLATEAU)){
			if ((((pion == DAME_BLANC) || (pion == PION_BLANC)) && ((plateau[y + 1][x + 1].type == PION_NOIR) || (plateau[y + 1][x + 1].type == DAME_NOIR))) ||
				(((pion == DAME_NOIR) || (pion == PION_NOIR)) && ((plateau[y + 1][x + 1].type == PION_BLANC) || (plateau[y + 1][x + 1].type == DAME_BLANC)))){
				if ((x + 2 < TAILLE_PLATEAU) && (y + 2 < TAILLE_PLATEAU)){
					if (plateau[y + 2][x + 2].type == CASE_VIDE){
						casePlateau* nextStep = (casePlateau*)malloc(sizeof(casePlateau));
						(*nextStep).numCol = x + 2;
						(*nextStep).numLig = y + 2;

						casePlateau copiePlateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
						copierPlateau(plateau,copiePlateau);
						copiePlateau[y + 1][x + 1].type = CASE_VIDE;
						copiePlateau[y][x].type = CASE_VIDE;
						copiePlateau[y + 2][x + 2].type = pion;

						node* nextMoves = getDeplacementsPion(copiePlateau, nextStep, FALSE, pion);
						if (nextMoves == NULL){
							freeListeDeplacements(result);
							return (NULL);
						}
						if ((*nextMoves).data == NULL){
							freeListeDeplacements(nextMoves);
							node* temp = getOneMove(x, y, x + 2, y + 2, 1);
							if (temp == NULL){
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = temp;
							}
							else{
								(*temp).next = result;
								result = temp;
							}
						}
						else{
							int res = updateListeCoups(nextMoves, x, y);
							if (res == -1){
								freeListeDeplacements(nextMoves);
								freeListeDeplacements(result);
								return (NULL);
							}
							if ((*result).data == NULL){
								freeListeDeplacements(result);
								result = nextMoves;
							}
							else{
								node* temp = getLastNode(result, NULL);
								(*temp).next = nextMoves;
							}
						}
					}
				}
			}
		}
	}


	return result;
}

