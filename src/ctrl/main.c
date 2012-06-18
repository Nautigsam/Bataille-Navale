#include "../model/champSaisie.h"
#include "../model/parametre.h"
#include "../model/grille.h"
#include "../model/random.h"
#include "../model/partie.h"

#include "../view/vueUtilsSDL.h"
#include "../view/vueGrille.h"
#include "../view/vueChampSaisie.h"
#include "../view/vueRegles.h"
#include "../view/includeSDL.h"

#include "menu.h"
#include "jeu.h"
#include "utilsSDL.h"
#include "fichierDebug.h"
#include "CtrlGrille.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	SDL_Surface * ecran;

	int choixMenu;
	int continuer = 1;
	int i;
    int partiePrete;

	ecran = DemarrerSDL(1024, 768, "Bataille Navale");

    Tparam * parametrePartie = malloc (sizeof(Tparam));

    init_debug();
    initRandom();
    
    //EcranGrille(NULL);

	AfficherMenuAccueil();

	while (continuer)
	{
	    //On créer un tableau d'entier
	    int * nbType = malloc (sizeof(int) * K_NBTYPEBATEAUX);
	    for(i = 0 ; i < K_NBTYPEBATEAUX ; i++){
            nbType[i]=1;
	    }

        parametrePartie = newTParam(nbType);
		choixMenu = AfficherMenuRacine();

        switch (choixMenu)
        {
            case 1: // Nouvelle Partie
                partiePrete = MenuNouvellePartie(parametrePartie);
                if(partiePrete)
                    jeu(parametrePartie);
                break;

            case 2: // Charger partie

                break;

            case 3: // Meilleurs scores

                break;

            case 4: // Afficher règles
                afficherRegles();
                break;

            case 5: // Quitter
                continuer = 0;
                break;

            default:
                break;
        }
    }
    
    ecranVictoire();

	ArreterSDL();
	detruire_debug();

    libererParam(parametrePartie);


	return 0;
}
