#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include"structures.h"
#include"constantes.h"

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

