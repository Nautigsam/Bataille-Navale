#include "model/Couleurs.h"

#include "view/IncludeSDL.h"

#include <string.h>

const Couleur tableCouleurs[KCOULEURS_NBCOULMAX] = {
    {'b',"BLANC", {255,255,255} },
    {'F',"FUSHIA", {255,0,255} } ,
    {'R',"ROUGE", {255,0,0} },
    {'B', "BLEU", {0,0,255} },
    {'C', "CYAN", {0,255,255} },
    {'M',"MARRON", {91,59,17} },
    {'J', "JAUNE" , {255,255,0} },
    {'V',"VERT", {0,255,0} }
};

// à quoi ça sert?
int getNbCouleurs (void)
{
    return KCOULEURS_NBCOULMAX ;
}

Couleur lettreToCouleur (char pLettre  )
{
    int i = 0;

    while (i < getNbCouleurs() && tableCouleurs[i].lettre != pLettre)
    {
        i++;
    }

    return tableCouleurs[i];
}

Couleur getCouleurFromNum (int pI)
{
    return tableCouleurs[pI];
}


SDL_Color getColor (Couleur pCouleur)
{
    return pCouleur.rgb;
}

char getChar (Couleur pCouleur)
{
    return pCouleur.lettre;
}

void getNom (Couleur pCouleur, char pNom[])
{
    strcpy(pNom,pCouleur.nom);
}

int getNumFromColor(Couleur color){

    int i = 0, trouve;
    int result = -1;
    trouve = 0;

    //On parcourt les couleurs
    while(!trouve && i < KCOULEURS_NBCOULMAX){

        //Si la lettre correspond
        if(tableCouleurs[i].lettre == color.lettre){
            trouve = 1;
            result = i;
        }

        i++;
    }

    return result;
}
