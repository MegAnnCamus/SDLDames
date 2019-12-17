#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/*case du plateau*/
typedef struct casePlateau
{
	int numLig;
	int numCol;
	char type;
	char couleur;
} casePlateau;

/*joueur*/
typedef struct joueur
{
    char* nom;
    char couleur;
} joueur;

/*element d'une liste chainee*/
typedef struct node
{
    //data : une case du plateau
	void* data;
	struct node* next;
} node;

/*deplacement d'un pion*/
typedef struct deplacement
{
	casePlateau *depart;
    node *arrivee;
	int nbPrise;
} deplacement;

/*liste chainee*/
typedef struct rafle
{
    int score;
	struct deplacement *dep;
	node *parent;
	node *child;
} rafle;



