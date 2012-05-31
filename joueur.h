#ifndef JOUEUR_H
#define JOUEUR_H

#define KLGNOMJ 25

/**
 * \enum ETypeBat
 * \brief Types de bateaux
 *
 * D�finit � la fois le type et la taille du bateau
*/
typedef enum {HUMAIN,MACHINE,UNDEF} ETypeJoueur;

/**
 * \struct TInfoBateau
 * \brief Contient les informations sur un bateau
 *
 * Ces informations seront stock�es dans un tableau (voir Tparam)
*/
typedef struct
{
	ETypeJoueur type;
	char nomJ[KLGNOMJ];
}Joueur;


Joueur * nouvJoueur(void);

int getTypeJoueur(const Joueur * pJoueur);

char * getNomJoueur(Joueur * pJoueur);

void LibererJoueur(Joueur * pJoueur);


#endif