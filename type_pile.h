#include "listes.h"

#define TAILLE_MAX 100

typedef struct {
  int n;
  sequence_t tab[TAILLE_MAX];
} PileEntiers;

/* Constructeurs */

/* Créer une pile vide */
void creer_pile(PileEntiers * p);

/* Opérations d'accès */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers p);

/* Renvoie l'entier en haut de la pile */
/* Précondition : p doit être non vide */
sequence_t sommet(PileEntiers p);

/* Renvoie le nombre d'éléments dans la pile */
int taille(PileEntiers p);

/* Afficher les éléments de la pile */
void print(PileEntiers p);

/* Opérations de modification */

/* Vider la pile p */
void vider(PileEntiers * p);

/* Empiler un entier x */
/* Précondition : taille(p) < TAILLE_MAX */
void empiler(PileEntiers * p, sequence_t x);

/* Supprimer l'entier en haut de la pile */
/* Précondition : p non vide */
void depiler(PileEntiers * p, sequence_t *resultat);


void afficherP (PileEntiers* pile);
