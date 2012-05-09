#include <stdlib.h>

#include "grille.h"

Grille * CreerGrille(int nbLin, int nbCol)
{
	Grille * grille;
	int i;
	int j;

	// Controle des paramètres
	if(nbLin > 0 && nbCol > 0)
	{
		// Allocation de la matrice
		Grille * nouvGrille = (Grille*)malloc(sizeof(Grille));
		if(nouvGrille == NULL) return NULL;

		nouvGrille->NbLin = nbLin;
		nouvGrille->NbCol = nbCol;

		// Allocation du tableau de lignes
		nouvGrille->TabLignes = (Ligne*)malloc(nbLin * sizeof(Ligne));
		if(nouvGrille->TabLignes == NULL) return NULL;

		// Parcours des lignes
		for(i=0;i<nbLin;i++)
		{
			// Allocation de chaque ligne (tableau d'entiers)
			nouvGrille->TabLignes[i] = (int*)malloc(nbCol * sizeof(int));
			if(nouvGrille->TabLignes[i] == NULL) return NULL;

			// Et on remplit avec des 0
			for(j=0;j<nbCol;j++)
			{
				nouvGrille->TabLignes[i][j] = GRILLE_CASE_VIDE;
			}
		}

		grille = nouvGrille;
	}
	else
	{
		grille = NULL;
	}

	return grille;
}

int Consulter(Grille * grille, Coord coord)
{
	return grille->TabLignes[coord.noLin-1][coord.noCol-1];
}

Grille * SetVal(Grille * grille, Coord coord, EtatCase etat)
{
	grille->TabLignes[coord.noLin-1][coord.noCol-1] = etat;

	return grille;
}

Grille * EffacerGrille(Grille * grille)
{
	int i,j;

	for(i=0;i<grille->NbLin;i++)
	{
		for(j=0;j<grille->NbCol;j++)
		{
			grille->TabLignes[i][j] = 0;
		}
	}

	return grille;
}

void LibererGrille(Grille * grille)
{
    int i;

    for(i=0;i<grille->NbLin;i++)
        free(grille->TabLignes[i]);

    free(grille->TabLignes);
    free(grille);
}
