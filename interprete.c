#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "type_pile.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

int interprete (sequence_t* seq, bool debug)
{
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.
    char /*num, cont1, cont2,*/ num1, num2;
    int nb1, nb2, nb3;
    sequence_t val1 , val2;
    char commande, x;
    PileEntiers p, p2;
    creer_pile (&p);
    debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */
    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();
    cellule_t * cel = seq-> tete;
    cellule_t * cel1;
    cellule_t * cel2;

    commande = cel ->command; 


    int ret;         //utilisée pour les valeurs de retour

    while ( cel != NULL) { //à modifier: condition de boucle
        sequence_t sequence ;
        cellule_t * init = nouvelleCellule();
        /*sequence.tete = init;*/
        printf("%c \n", commande);
        switch (commande) {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

            case 'A':
                ret = avance();
                if (ret == VICTOIRE){
                    cel = NULL;
                    seq->tete = cel;
                 return VICTOIRE;} /* on a atteint la cible */
                if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
                break; /* à ne jamais oublier !!! */
            case 'G':
                gauche();
                if (ret == VICTOIRE){
                    cel = NULL;
                    seq->tete = cel;
                 return VICTOIRE;} /* on a atteint la cible */
                if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
                break; /* à ne jamais oublier !!! */
            case 'D':
                droite();
                if (ret == VICTOIRE){
                    cel = NULL;
                    seq->tete = cel;
                 return VICTOIRE;} /* on a atteint la cible */
                if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
                break; /* à ne jamais oublier !!! */
            case '0' :
                x = 0;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '1' :
                x = 1;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '2' :
                x =2;
                init->command = x;
                init->suivant = NULL;
                sequence.tete = init;
                empiler( &p , sequence);
                break;
            case '3' :
                x =3;
                init->command = x;
                init->suivant = NULL;
                sequence.tete->suivant = init;
                cel1 = sequence.tete;
                do{
                    printf("val :");
		            printf("%c",cel1->command);
                    printf("\n");
		            cel1=cel1->suivant;
	            }while(cel1!=NULL);
                printf("\n");

                cel1 = sequence.tete;
                printf("cmd : %c \n",cel1->command);
                /*
                ajout_en_tete(&sequence, x);
                conversion(&x, &sequence);*/
                empiler( &p , sequence);
                break;
            case '4' :
                x = 4;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '5' :
                x = 5;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '6' :
                x = 6;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '7' :
                x = 7;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '8' :
                x = 8;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '9' :
                x = 9;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '+':
                depiler(&p ,&val1);
                cel1 = val1.tete;
                depiler(&p, &val2);
                cel2 = val2.tete;



                printf("cel1 : \n");
                do{
                    printf("val :");
		            printf("%c",cel1->command);
                    printf("\n");
		            cel1=cel1->suivant;
	            }while(cel1!=NULL);
                printf("\n");


                printf("cel2 : \n");
                do{
                    printf("val :");
		            printf("%c",cel2->command);
                    printf("\n");
		            cel2=cel2->suivant;
	            }while(cel2!=NULL);
                printf("\n");
                
                cel1=cel1->suivant;
                cel1=cel1->suivant;
                cel2=cel2->suivant;
                cel2=cel2->suivant;
                num1 = cel1->command;
                num2 = cel2->command;
                printf("num1 :%c num2:%c \n",num1, num2);
                nb2 = atoi(&num2);
                nb1 = atoi(&num1);
                printf("nb1 :%d nb2:%d \n",nb1, nb2);
                nb3 = nb1 +nb2;
                printf("%d",nb3);
                x = nb3;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '-':
                depiler(&p ,&val1);
                cel1 = val1.tete;
                depiler(&p, &val2);
                cel2 = val2.tete;
                num1 = cel1->command;
                num2 = cel2->command;
                x = num1-num2;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case '*':
                depiler(&p ,&val1);
                cel1 = val1.tete;
                depiler(&p, &val2);
                cel2 = val2.tete;
                num1 = cel1->command;
                num2 = cel2->command;
                x = num1*num2;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
            case 'P':
                depiler(&p ,&val1);
                cel1 = val1.tete;
                num1 = cel1->command;
                pose(num1);
                break;
              case 'M':
                depiler(&p,&val1);
                cel1 = val1.tete;
                num1 = cel1->command;                
                int m = mesure(num1);
                x = m;
                conversion(&x, &sequence);
                empiler( &p , sequence);
                break;
/*
            case '{':
                cont1 = 1;
                cont2 = 0;
                empiler( &p , commande);
                while (cont1 != cont2){
                    cel=cel->suivant;
                    commande = cel ->command;
                    switch (commande){
                        case '{':
                            cont1 += 1 ;
                            break;
                        case '}':
                            cont2+= 1 ;
                            break;   
                    }
                    empiler( &p , commande);
                }
                break;

            case '?':
                cont1 = 1;
                cont2 = 0;
                while (cont1 != cont2){
                    depiler(&p ,&val1);
                    switch (val1){
                        case '{':
                            cont1 += 1;
                            break;
                        case '}':
                            cont2+= 1;
                            break;   
                    }
                    if (cont1 != cont2){
                        inter[0] = val1;
                        strcat(inter, com1);
                        strcpy(com1, inter);
                    }
                }
                cont1 = 1;
                cont2 = 0;
                while (cont1 != cont2){
                    depiler(&p ,&val1);
                    switch (val1){
                        case '{':
                            cont1 += 1 ;
                            break;
                        case '}':
                            cont2+= 1 ;
                            break;   
                    }
                    if (cont1 != cont2){
                        inter[0] = val1;
                        strcat(inter, com1);
                        strcpy(com2, inter);
                    }
                }



                if (val1){
                    conversion(com1,&prog_seq2);
                    interprete (&prog_seq2, debug);
                }
                else{
                    conversion(com2,&prog_seq2);
                    interprete (&prog_seq2, debug);
                }
                break;
            */
            default:
                eprintf("Caractère inconnu: '%c'\n", commande);
        }

        cel=cel->suivant;
        commande = cel ->command;
        p2 = p;
        afficherP(&p);
        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }
    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */
    

    return CIBLERATEE;
}
