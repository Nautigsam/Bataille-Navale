/**
 * \file FichierSauvRes.c
 * \author Benoît Sauvère
 * \date 19/06/2012
 * \brief Controleur du fichier de sauvegarde
 *
 * Contient les implémentations des fonctions utilisées pour la sauvegarde et la restauration d'une partie.
*/

#include "FichierSauvRes.h"

#include "fichierDebug.h"

#include "../model/bateau.h"
#include "../model/grille.h"
#include "../model/partie.h"
#include "../model/pileCoup.h"

#define SAVE_REP "ressources/saves/"

//===============================//
//=         SAUVEGARDE          =//
//===============================//

int sauvegardePartie(TPartie *partie, const char nomSauv[]){

    FILE *fichier;
    char * chemin = malloc( sizeof(char) * (strlen(SAVE_REP) + strlen(nomSauv)));

    //Création du chemin
    strcpy(chemin, "ressources/saves/");
    strcat(chemin, nomSauv);

    //On ouvre le fichier en écrant tout le contenu
    fichier = fopen(chemin, "wb+");

    if(fichier == NULL){
        dgErreur("Impossible d'ouvrir le fichier de sauvegarde.");
        return 0;
    }
    else{
        //On sauvegarde tout

        //Les bateaux
        sauvegardeBateaux(partie, fichier);

        //La grille du joueur
        sauvegardeGrille(partie->grille, fichier);
        sauvegardeGrille(partie->grilleMachine, fichier);

        //On sauvegarde les coups
        sauvegardeCoups(partie, fichier);

        //Les paramètes
        sauvegardeParam(partie, fichier);

        fclose(fichier);

        return 1;
    }

}

int sauvegardeBateaux(TPartie *partie, FILE *fichier){

    int nbBateaux = getNbBat(partie->parametres);
    int i = 0;
    TBateau bat;

    //on écrit le nombre de bateaux par joueurs
    fwrite(&nbBateaux, sizeof(nbBateaux), 1, fichier);

    //On écrit tout les bateaux du joueur
    for(i = 0 ; i < nbBateaux ; i++){
        bat = *(partie->joueur->mesBateaux[i]);
        fwrite(&bat, sizeof(bat), 1, fichier);
    }

    //On écrit tout les bateaux de la machine
    for(i = 0 ; i < nbBateaux ; i++){
        bat = *(partie->machine->mesBateaux[i]);
        fwrite(&bat, sizeof(bat), 1, fichier);
    }

    fwrite(partie->joueur->nomJ, sizeof(partie->joueur->nomJ), 1, fichier);
    fwrite(partie->machine->nomJ, sizeof(partie->machine->nomJ), 1, fichier);

    return 1;
}

int sauvegardeGrille(Grille *grille, FILE *fichier){

    int nbLigne, nbColonne, abs, ord;
    int i, j;
    Coord position;
    CaseGrille *caseGrille;

    nbLigne = grille->NbLin;
    nbColonne = grille->NbCol;
    abs = grille->abscisse;
    ord = grille->ordonnee;

    //On écrit le nombre de ligne et de colonne
    fwrite(&nbLigne, sizeof(nbLigne), 1, fichier);
    fwrite(&nbColonne, sizeof(nbColonne), 1, fichier);

    //On écrit le tableau des CaseGrilles
    //Ligne par ligne
    for(i = 1 ; i <= nbLigne ; i++){
        position.noLin = i;

        for(j = 1 ; j <= nbColonne ; j++){
            position.noCol = j;

            //On récupère la case et on l'écrit
            caseGrille = Consulter(grille, position);
            fwrite(caseGrille, sizeof(CaseGrille), 1, fichier);
        }
    }

    //On écrit l'abscisse et l'ordonnée
    fwrite(&abs, sizeof(abs), 1, fichier);
    fwrite(&ord, sizeof(ord), 1, fichier);

    return 1;
}

int sauvegardeCoups(TPartie *partie, FILE *fichier){

    //On compte le combre de coups dans la pile et on l'écrit
    int nbCoups = longueurPile(partie->pileCoups);

    Pile pile = partie->pileCoups;

    fwrite(&nbCoups, sizeof(nbCoups), 1, fichier);

    // on écrit les coups du sommet vers la queue
    while(pile != NULL){
        fwrite(&(pile->Info), sizeof(pile->Info), 1, fichier);
        pile = pile->Lien;
    }


    return 1;
}

int sauvegardeParam(TPartie *partie, FILE *fichier){

    int nbTypeInstances = K_NBTYPEBATEAUX;
    int nbTInfoBateau = getNbBat(partie->parametres);

    int i;

    //On écrit le nombre de type de bateaux
    fwrite(&nbTypeInstances, sizeof(nbTypeInstances), 1, fichier);

    //on écrit le tableau contenant le nombre de bateau pour chaque type
    for(i = 0 ; i < nbTypeInstances ; i++){
        fwrite(&(partie->parametres->nombreInstanceBateaux[i]), sizeof(int), 1, fichier);
    }

    //On écrit les TInfoBateau pour le joueur puis pour la machine
    //On sait que nb(TInfoBateau) = nb(Bateau d'un joueur)

    for(i = 0 ; i < nbTInfoBateau ; i++){
        fwrite(&(partie->parametres->bateauxJoueur[i]), sizeof(partie->parametres->bateauxJoueur[i]), 1, fichier);
    }

    for(i = 0 ; i < nbTInfoBateau ; i++){
        fwrite(&(partie->parametres->bateauxMachine[i]), sizeof(partie->parametres->bateauxJoueur[i]), 1, fichier);
    }


    return 1;
}


//===============================//
//=        RESTAURATION         =//
//===============================//

TPartie* restaurerPartie(const char nomSauv[]){

    TPartie *partie;

    FILE *fichier;
    char * chemin = malloc( sizeof(char) * (strlen(SAVE_REP) + strlen(nomSauv)));

    //Création du chemin
    strcpy(chemin, "ressources/saves/");
    strcat(chemin, nomSauv);

    //On ouvre le fichier en écrant tout le contenu
    fichier = fopen(chemin, "rb");

    if(ferror(fichier)){
        dgErreur("Impossible d'ouvrir le fichier de sauvegarde.");
        return 0;
    }
    else{

        partie = malloc( sizeof(TPartie) );

        //On restaure tout

        //les bateaux
        restaurerBateaux(partie, fichier);

        //On créer les grilles
        restaurerGrilles(partie, fichier);

        restaurerCoups(partie, fichier);

        //Les paramètes
        restaurerParam(partie, fichier);

        fclose(fichier);

        return partie;
    }

}

int restaurerBateaux(TPartie *partie, FILE* fichier){

    //Nombre de bateaux pour chaque joueur
    int nbBat;
    int i;

    //Pour les noms des joueurs
    char nom[KLGNOMJ] = {'\0'};

    //On alloue les structures joueur
    partie->joueur = malloc( sizeof(Joueur) );
    partie->machine = malloc( sizeof(Joueur) );

    partie->joueur->type = HUMAIN;
    partie->machine->type = MACHINE;

    //On lit le nombre de bateaux
    fread(&nbBat, sizeof(int), 1, fichier);

    partie->joueur->mesBateaux = malloc(sizeof(TBateau*) * nbBat);
    partie->machine->mesBateaux = malloc(sizeof(TBateau*) * nbBat);

    //On lit les bateaux du joueur
    for(i = 0 ; i < nbBat ; i++){
        partie->joueur->mesBateaux[i] = malloc(sizeof(TBateau));
        fread(partie->joueur->mesBateaux[i], sizeof(TBateau), 1, fichier);
    }

    //On lit les bateaux de la machine
    for(i = 0 ; i < nbBat ; i++){
        partie->machine->mesBateaux[i] = malloc(sizeof(TBateau));
        fread(partie->machine->mesBateaux[i], sizeof(TBateau), 1, fichier);
    }

    //On lit le nom du joueur
    fread(nom, sizeof(char) * KLGNOMJ, 1, fichier);
    strcpy(partie->joueur->nomJ, nom);

    //On lit le nom de la machine
    fread(nom, sizeof(char) * KLGNOMJ, 1, fichier);
    strcpy(partie->machine->nomJ, nom);

    return 1;
}

int restaurerGrilles(TPartie *partie, FILE* fichier){

    int nbLin, nbCol;
    int i, j;
    int abs, ord;
    Coord pos;

    //
    // JOUEUR
    //

    //On lit le nombre de ligne
    fread(&nbLin, sizeof(int), 1, fichier);
    //On lit le nombre de colonnes
    fread(&nbCol, sizeof(int), 1, fichier);

    partie->grille = CreerGrille(nbLin, nbCol);

    //Pour chaque case écrite (ligne par ligne)
    for(i = 1; i <= nbLin ; i++){
        pos.noLin = i;
        for(j = 1 ; j <= nbCol ; j++){
            pos.noCol = j;

            //On lit une case
            fread(Consulter(partie->grille, pos), sizeof(CaseGrille), 1, fichier);
        }
    }

    fread(&abs, sizeof(int), 1, fichier);
    fread(&ord, sizeof(int), 1, fichier);

    partie->grille->abscisse = abs;
    partie->grille->ordonnee = ord;

    //
    // MACHINE
    //

    //On lit le nombre de ligne
    fread(&nbLin, sizeof(int), 1, fichier);
    //On lit le nombre de colonnes
    fread(&nbCol, sizeof(int), 1, fichier);

    partie->grilleMachine = CreerGrille(nbLin, nbCol);

    //Pour chaque case écrite (ligne par ligne)
    for(i = 1; i <= nbLin ; i++){
        pos.noLin = i;
        for(j = 1 ; j <= nbCol ; j++){
            pos.noCol = j;

            //On lit une case
            fread(Consulter(partie->grilleMachine, pos), sizeof(CaseGrille), 1, fichier);
        }
    }

    fread(&abs, sizeof(int), 1, fichier);
    fread(&ord, sizeof(int), 1, fichier);

    partie->grilleMachine->abscisse = abs;
    partie->grilleMachine->ordonnee = ord;

    return 1;
}

int restaurerCoups(TPartie *partie, FILE* fichier){

    int nbCoups;
    int i;
    Coup *coup;
    struct Cellule *cell = NULL;
    struct Cellule *cellPrec = NULL;

    //On lit le nombre de coups
    fread(&nbCoups, sizeof(int), 1, fichier);

    partie->pileCoups = CreerPile();

    //On lit les coups
    for(i = 0 ; i < nbCoups ; i++){

        coup = malloc(sizeof(Coup));
        fread(&coup, sizeof(Coup), 1, fichier);

        cell = malloc(sizeof(struct Cellule));

        cell->Info = coup;

        cell->Lien = cellPrec;
        cellPrec = cell;
    }

    //On fait pointer le sommet de pile
    partie->pileCoups = cell;

    return 1;
}

int restaurerParam(TPartie *partie, FILE* fichier){

    int nbType;
    int nbBateau;
    int i;

    //On lit le nombre de type de bateaux
    fread(&nbType, sizeof(int), 1, fichier);

    //On alloue les paramètes
    partie->parametres = malloc( sizeof(Tparam));
    partie->parametres->nombreInstanceBateaux = malloc(sizeof(int)*nbType);
    
    nbBateau = getNbBat(partie->parametres);

    nbBateau = getNbBat(partie->parametres);

    //On lit le tableau contenant le nombre de bateau pour chaque type
    for(i = 0 ; i < nbType ; i++){
        fread(&(partie->parametres->nombreInstanceBateaux[i]), sizeof(int), 1, fichier);
    }

    partie->parametres->bateauxJoueur = malloc(sizeof(TInfoBateau)*nbBateau);
    partie->parametres->bateauxMachine = malloc(sizeof(TInfoBateau)*nbBateau);

    for(i = 0 ; i < nbBateau ; i++){
        fread(&(partie->parametres->bateauxJoueur[i]), sizeof(TInfoBateau), 1, fichier);
    }

    for(i = 0 ; i < nbBateau ; i++){
        fread(&(partie->parametres->bateauxMachine[i]), sizeof(TInfoBateau), 1, fichier);
    }

    return 1;
}
