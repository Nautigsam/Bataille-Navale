/**
 * \file SDLMsgBox.h
 * \author Aurélien Bertron
 * \date 19 juin 2012
 * \brief Vue utilitaires SDL
 *
 * Contient les déclarations de fonctions utilisées pour simplifer l'utilisation de la SDL.
*/

#ifndef VUE_UTILS_H
#define VUE_UTILS_H

#include "view/IncludeSDL.h"

#define K_LGMAXMESSAGE 30

/**
 * \brief Permet d'écrire du texte en blanc
 *
 * \param[in] texte Texte à écrire (utiliser \n pour sauter des lignes)
 * \param[in] taille Taille du texte
 * \param[in] positionTexte Coordonnées du texte à l'écran
 * \param[in] cheminPolice Chemin de la police dans le dossier Fonts
 */
void ecrireTexte(char * texte, int taille, SDL_Rect positionTexte, char * cheminPolice);

/**
 * \brief Permet d'écrire une ligne de texte
 *
 * \param[in] texte Le texte à écrire
 * \param[in] taille La taille de la police
 * \param[in] positionTexte Coordonnées du texte sur l'ecran
 * \param[in] cheminPolice Chemin de la police dans le dossier Fonts
 */
void ecrireLigneTexte(char * texte,int taille, SDL_Rect positionTexte, char * cheminPolice);

/**
 * \brief Récupère un événement
 *
 * \param[out] coordClic Coordonnees du clic
 * \param[out] touche Touche pressée
 *
 * Met le programme en pause et attend un clic gauche ou l'appui sur une touche.
 * Si un clic gauche est donné, les coordonnees du clic sont enregistrées et 1 est retourné.
 * Si une touche est pressée, sa valeur est enregistrée et 2 est retourné.
 * Si l'on ne veut utiliser que le clavier ou que la souris, il est possible de mettre l'un des deux paramètres à NULL.
*/
int attendreEvent(SDL_Rect *coordClic, SDL_Keysym *touche);

/**
 * \brief Convertit les couleurs
 *
 * \param[in] pCouleur
 * \return Le type de couleur accepté par SDL_FillRect
 *
 * Pour remplir une surface d'une couleur, SDL_FillRect n'accepte que le type Uint32 or, on ne manipule que des SDL_Color.
 * Il est donc nécessaire de réaliser une conversion
*/
Uint32 convertSDL_Color(SDL_Color pCouleur);

/**
 * \brief Affiche les coordonnees du clic
 *
 * \param[in] pPosClic La position du clic
 * \param[in] pTaille Taille du texte
 * \param[in] pAbs Abscisse du texte
 * \param[in] pOrd Ordonnee du texte
 * \param[in] pPolice Police du texte
*/
void afficherCoordClic(SDL_Rect * pPosClic, int pTaille, int pAbs, int pOrd, char * pPolice);

/**
 * \brief Met le programme en pause et attend qu'une touche soit pressée
*/
void pause(void);

/**
 * \brief Efface l'écran
*/
void effacerEcran(void);

#endif
