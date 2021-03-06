/**
* \file VueGrille.h
* \author Aurélien Bertron
* \date 21 avril 2012
* \brief Vue Grille
*
* Contient les en-têtes des fonctions d'entrée-sortie du module de grille
*
*/

#ifndef VUEGRILLE_H
#define VUEGRILLE_H

#include "view/IncludeSDL.h"

#include "model/Grille.h"

/**
* \brief Affiche la grille à l'écran
*
* \param[in] grille Grille à afficher
* \param[in] abscisse Abscisse de la grille sur l'écran
* \param[in] ordonnee Ordonnée de la grille sur l'écran
*
* Affiche la grille à l'écran aux abscisse et ordonnee données.
* Attention la grille doit être initialisée.
*
**/
void afficherGrille(Grille * grille, int abscisse, int ordonnee);

/**
* \brief Met à jour la grille
*
* \param[in] grille Grille à mettre à jour
* \param[in] coord Coordonnées de la case à mettre à jour
*
* Met à jour l'affichage de la grille à une case donnée.
* Attention la grille doit être initialisée et les coordonnées doivent correspondre aux dimensions de la grille
*
*/
void updateGrille(Grille * grille, Coord coord);

/**
* \brief Coordonnées d'un clic dans la grille
*
* \param[in] grille Grille cliquée
* \param[in] positionClic Position du clic sur l'écran (type défini par la SDL)
*
* \return Les coordonnées du clic dans la grille si le clic est dans la grille et des coordonées nulles sinon
*
*/
Coord clicCaseGrille(Grille * grille, SDL_Rect * positionClic);

/**
* \brief Détermine si un clic est dans la grille
*
* \param[in] grille Grille où l'on cherche le clic
* \param[in] positionClic Position du clic sur l'écran (type défini par la SDL)
*
* \return 1 si le clic est est dans la grille et 0 sinon
*
*/
int clicDansGrille(Grille * grille, SDL_Rect * positionClic);


#endif
