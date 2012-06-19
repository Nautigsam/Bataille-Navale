#ifndef PILE_COUP_H
#define PILE_COUP_H

#include "grille.h"
#include "joueur.h"
#include "Coups.h"

struct Cellule
{
	Coup * Info;            /**< Pointeur vers coups **/
	struct Cellule * Lien;  /**< Pointeur vers la cellule suivante **/
};

typedef struct Cellule * Pile;

/*
 N : CreerPile
 E : -
 S : -
 R : retourne une pile initialisee
 Prec : -
 */
Pile CreerPile(void);

/*
 N : PileVide
 E : pPile
 S : -
 R : retourne 1 si la pile est vide et 0 sinon
 Prec : -
 */
int PileVide(Pile pPile);

/*
 N : Empiler
 E : pPile, pElem
 S : -
 R : retourne la pile modifiee
 Prec : -
 */
Pile Empiler(Pile pPile, Coup * pElem);

/*
 N : Depiler
 E : pPile
 S : -
 R : retourne la pile modifiee
 Prec : la liste ne doit pas etre vide
 */
Pile Depiler(Pile pPile);

/*
 N : Sommet
 E : pPile
 S : -
 R : retourne le premier element de la pile
 Prec : la pile ne doit pas etre vide
 */
Coup * Sommet(Pile pPile);

#endif
