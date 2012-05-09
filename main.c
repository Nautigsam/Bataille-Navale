#include <stdio.h>
#include <stdlib.h>

// Permet la portabilité du programme
#ifdef __APPLE__
	#include <SDL/SDL.h>
	#include <SDL_image/SDL_image.h>
	#include <SDL_ttf/SDL_ttf.h>
#else
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
#endif

#include "utilsSDL.h"
#include "vueUtilsSDL.h"

#include "menu.h"

#include "parametre.h"

#include "grille.h"
#include "vueGrille.h"

#include "champSaisie.h"
#include "vueChampSaisie.h"
#include "regles.h"

void pause()
{
	int continuer = 1;
	SDL_Event event;

	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				exit(EXIT_FAILURE);
			break;

			case SDL_KEYDOWN:
				continuer = 0;
			break;
        }
    }

}

void controleurParametreVersionTest(Tparam *param)
{
	newTParam(1 , param);

	// boucles avec void newTParam(int pIdBateau , Tparam * pP, char pNom[], int pCouleur , EType pType) doit remplacer ce qui suit
	setIemeInfoBateauTParam(0 , param, "redon", 0 , REMORQUEUR);
	setIemeInfoBateauTParam(1 , param, "peninou", 1 , PORTEAVION);
	setIemeInfoBateauTParam(2 , param, "canut", 2 , SOUSMARIN);
	setIemeInfoBateauTParam(3, param , "caplain", 3 , CARGOT);
	setIemeInfoBateauTParam(4 , param , "bruel", 4 , REMORQUEUR);
	setIemeInfoBateauTParam(5 , param , "inglebert", 5 , PORTEAVION);
	setIemeInfoBateauTParam(6 , param , "verdier", 0 , SOUSMARIN);
	setIemeInfoBateauTParam(7 , param , "nonne", 1 , CARGOT);
}

int main(int argc, char ** argv)
{
	printf("\n== Test du module de paramétrage ==\n");
    
    

	return 0;
}
