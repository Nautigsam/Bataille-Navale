#include "ctrl/EcransDivers.h"

#include "view/IncludeSDL.h"
#include "view/SDLImage.h"
#include "view/VueUtilsSDL.h"
#include "ctrl/UtilsSDL.h"

void ecranVictoire(void)
{
    int continuer = 1;
    SDL_Keysym touche;
    SDL_Rect * positionClic = malloc(sizeof(SDL_Rect));
    int controleEvent;
    Image * imageCaptain;
    Image * imageClavier;
    SDL_Rect positionTexte;

    imageCaptain = creerImage("captain.png", 446, 389);
    imageClavier = creerImage("clavier.png", 300, 600);

    while (continuer)
    {
        effacerEcran();
        afficherImage(imageCaptain);
        afficherImage(imageClavier);
        positionTexte.x = 278;
        positionTexte.y = 230;
        ecrireTexte("VICTOIRE !", 100, positionTexte, "default.ttf");
        positionTexte.x = 380;
        positionTexte.y = 625;
        ecrireTexte("Espace", 30, positionTexte, "default.ttf");
        UpdateWindow(SDL_TRUE);

        controleEvent = attendreEvent(positionClic, &touche);

        if(controleEvent == 2 && touche.scancode == SDL_SCANCODE_SPACE)
        {
            continuer = 0;
        }
        else if(controleEvent == 1)
        {
            afficherCoordClic(positionClic, 20, 0, 650, "default.ttf");
            UpdateWindow(SDL_TRUE);
        }
    }

    libererImage(imageCaptain);
    free(positionClic);
}

void ecranPerte(void)
{
    int continuer = 1;
    SDL_Keysym touche;
    SDL_Rect * positionClic = malloc(sizeof(SDL_Rect));
    int controleEvent;
    Image * imageCaptain;
    Image * imageClavier;
    SDL_Rect positionTexte;

    imageCaptain = creerImage("pirate.png", 446, 389);
    imageClavier = creerImage("clavier.png", 300, 600);

    while (continuer)
    {
        effacerEcran();
        afficherImage(imageCaptain);
        afficherImage(imageClavier);
        positionTexte.x = 278;
        positionTexte.y = 230;
        ecrireTexte("PERDU !", 100, positionTexte, "default.ttf");
        positionTexte.x = 380;
        positionTexte.y = 625;
        ecrireTexte("Espace", 30, positionTexte, "default.ttf");
        UpdateWindow(SDL_TRUE);

        controleEvent = attendreEvent(positionClic, &touche);

        if(controleEvent == 2 && touche.scancode == SDL_SCANCODE_SPACE)
        {
            continuer = 0;
        }
        else if(controleEvent == 1)
        {
            afficherCoordClic(positionClic, 20, 0, 650, "default.ttf");
            UpdateWindow(SDL_TRUE);
        }
    }

    libererImage(imageCaptain);
    free(positionClic);
}
