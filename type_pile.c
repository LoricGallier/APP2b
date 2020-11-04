#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "type_pile.h"


/* Créer une pile vide */
void creer_pile(PileEntiers * p){
	p->n = 0;

}

/* Opérations d'accès */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers p){
	return (p.n == 0);

}

/* Renvoie l'entier en haut de la pile */
/* Précondition : p doit être non vide */
sequence_t sommet(PileEntiers p){
	return p.tab[p.n -1];
 
}

/* Renvoie le nombre d'éléments dans la pile */
int taille(PileEntiers p){
	return p.n;
}

/* Afficher les éléments de la pile */
void print(PileEntiers p){
	for(int i=0; i<p.n; i++){
		afficher (&p.tab[i]);
	}
}

/* Opérations de modification */

/* Vider la pile p */
void vider(PileEntiers * p){
	p->n=0;
}

/* Empiler un entier x */
/* Précondition : taille(p) < TAILLE_MAX */
void empiler(PileEntiers * p, sequence_t x){
	p->tab[p->n]=x;
	p->n++;
}

/* Supprimer l'entier en haut de la pile */
/* Précondition : p non vide */
void depiler(PileEntiers * p, sequence_t *resultat){
	*resultat = p->tab[p->n -1];
	p->n--;
}


void afficherP (PileEntiers* pile)
{
	printf("pile : ");
	for(int i=0;i< pile->n;i++){
		afficher (&pile->tab[i]);
	}
	printf("\n");
}