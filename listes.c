#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void)
{
    cellule_t* newCel;
    newCel = (cellule_t*)malloc(sizeof(cellule_t));
    newCel->suivant = NULL;

    return newCel;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);  
}

void conversion (char *texte, sequence_t *seq)
{
    for (int i =0 ; texte[i] != '\0'; i ++){
        ajout_en_queue(seq, texte[i]);
    }
}

void afficher (sequence_t* seq)
{
	assert(seq); /*pointeur valide*/
	if(seq->tete == NULL){
		printf("Liste d'instruction vide\n");
		return;
	}
	cellule_t * cel = seq-> tete;
	do{
		printf("%c",cel->command);
		cel=cel->suivant;
	}while(cel!=NULL);
}


void ajout_en_tete(sequence_t *seq, char n) {
    cellule_t * cel = (cellule_t *)malloc(sizeof(cellule_t));
    cel -> command = n;
	cel -> suivant = seq -> tete;
	seq -> tete = cel;
    return;
}

void ajout_en_queue(sequence_t *seq, char n) {
	cellule_t * nouv_cel = (cellule_t *)malloc(sizeof(cellule_t)), * cel_cour = seq -> tete;
	nouv_cel -> command = n;
	nouv_cel -> suivant = NULL;
	if (seq -> tete == NULL)
	{
		seq -> tete = nouv_cel;
		return;
	}
	while (cel_cour -> suivant != NULL)
	{
		cel_cour = cel_cour -> suivant;
	}
	cel_cour -> suivant = nouv_cel;
return;}

