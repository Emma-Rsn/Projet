//
//menu.c
//Created by Moreau Enzo
//

/**
 *\file menu.c
 *\brief programme pour afficher tous les menus
 *\author Moreau Enzo Pasquier Lina
 *\date Janvier 2024
 *\version
 *
 */

#include "../libs/commun.h"


/**
 *\fn int menu_option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,int * etatoption)
 *\param we Largeur de l'ecran
 *\param he Longueur de l'ecran
 *\param event permet de savoir si il y a un evenement
 *\param renderer rendu de la fenetre
 *\param run pointeur pour continuer le programme
 *\param etatoption etat du menu des options
 *\brief fonction qui affiche le menu dans le jeu
 */

//fonction qui affiche le menu dans le jeu
int menu_option(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * run, int * etatoption) {

    SDL_RenderClear(renderer);
    SDL_Color textColor = {
        255,
        255,
        255
    };

    //chargement de la police d'écriture
    TTF_Font * fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
    if (!fontT) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColorT = {
        43,
        27,
        85
    };

    SDL_Surface * textSurfaceT = TTF_RenderText_Solid(fontT, "The Last Nightmare", textColorT);
    if (!textSurfaceT) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(fontT);
        return -1;
    }

    SDL_Texture * textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

    SDL_Rect r_text_T = {
        (( * we) / 2) - ((textSurfaceT -> w) / 2),
        10,
        textSurfaceT -> w,
        textSurfaceT -> h
    };
    SDL_FreeSurface(textSurfaceT);

    if (SDL_QueryTexture(textTextureT, NULL, NULL, & r_text_T.w, & r_text_T.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;

    }

    TTF_CloseFont(fontT);
    fontT = NULL;

    //chargement de la police d'écriture
    TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 50);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Surface * textSurfaceQ = TTF_RenderText_Solid(font, "Quitter", textColor);
    if (!textSurfaceQ) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture * textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);

    SDL_Surface * textSurfaceC = TTF_RenderText_Solid(font, "Continuer", textColor);
    if (!textSurfaceC) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(textSurfaceQ);
        return -1;
    }

    SDL_Texture * textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);

    SDL_Surface * textSurfaceO = TTF_RenderText_Solid(font, "Options", textColor);
    if (!textSurfaceO) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceC);
        return -1;
    }

    SDL_Texture * textTextureO = SDL_CreateTextureFromSurface(renderer, textSurfaceO);

    TTF_CloseFont(font);
    font = NULL;

    //creation rectangle pour les textes
    SDL_Rect r_text_C = {
        (( * we) / 2) - ((textSurfaceC -> w) / 2),
        (( * he) / 3) * 1 - textSurfaceC -> h,
        textSurfaceC -> w,
        textSurfaceC -> h
    };
    SDL_Rect r_text_Q = {
        (( * we) / 2) - ((textSurfaceQ -> w) / 2),
        (( * he) / 3) * 2 - textSurfaceQ -> h,
        textSurfaceQ -> w,
        textSurfaceQ -> h
    };
    SDL_Rect r_text_O = {
        (( * we) / 2) - ((textSurfaceO -> w) / 2),
        (( * he) / 3) * 3 - textSurfaceO -> h - 50,
        textSurfaceO -> w,
        textSurfaceO -> h
    };

    SDL_FreeSurface(textSurfaceC);
    SDL_FreeSurface(textSurfaceQ);
    SDL_FreeSurface(textSurfaceO);

    if (SDL_QueryTexture(textTextureQ, NULL, NULL, & r_text_Q.w, & r_text_Q.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;
    }

    if (SDL_QueryTexture(textTextureC, NULL, NULL, & r_text_C.w, & r_text_C.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;
    }

    if (SDL_QueryTexture(textTextureO, NULL, NULL, & r_text_O.w, & r_text_O.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;

    }

    if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || ( * etatoption == 2)) {
        int etat = 1;
        while (etat) {

            while (SDL_PollEvent( & event) != 0) {

                if (event.type == SDL_MOUSEBUTTONDOWN) {

                    //pour continuer le jeu
                    if ((r_text_C.x <= event.button.x) && ((r_text_C.x + r_text_C.w) >= event.button.x) && ((r_text_C.y + r_text_C.h) >= event.button.y) && (r_text_C.y <= event.button.y)) {
                        etat = 0;
                        * etatoption = 0;
                    }
                    //pour quitter le jeu
                    else if ((r_text_Q.x <= event.button.x) && ((r_text_Q.x + r_text_Q.w) >= event.button.x) && ((r_text_Q.y + r_text_Q.h) >= event.button.y) && (r_text_Q.y <= event.button.y)) {
                        etat = 0;
                        * etatoption = 0;
                        * run = 0;
                    } else if ((r_text_O.x <= event.button.x) && ((r_text_O.x + r_text_O.w) >= event.button.x) && ((r_text_O.y + r_text_O.h) >= event.button.y) && (r_text_O.y <= event.button.y)) {
                        etat = 0;
                        * etatoption = 1;
                    }

                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, textTextureQ, NULL, & r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, & r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, & r_text_T);
            SDL_RenderCopy(renderer, textTextureO, NULL, & r_text_O);

            SDL_RenderPresent(renderer);
            SDL_Delay(100);

        }

    }
    SDL_DestroyTexture(textTextureQ);
    SDL_DestroyTexture(textTextureC);
    SDL_DestroyTexture(textTextureT);
    SDL_DestroyTexture(textTextureO);

    return 0;
}

/**
 *\fn int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,int * etatoption,int * toucheDeplacement)
 *\param we Largeur de l'ecran
 *\param he Longueur de l'ecran
 *\param event permet de savoir si il y a un evenement
 *\param renderer rendu de la fenetre
 *\param run pointeur pour continuer le programme
 *\param etatoption etat du menu des options
 *\param toucheDeplacement variable pour savoir quel touche de deplacement le joueur a choisis
 *\brief fonction qui affiche l'ecran titre
 */

//fonction qui affiche l'ecran titre
int menu(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * run, int * etatoption, int * toucheDeplacement,map_t * map) {
    SDL_RenderClear(renderer);
    SDL_Color textColor = {
        255,
        255,
        255
    };

    //chargement de la police d'écriture
    TTF_Font * fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
    if (!fontT) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColorT = {
        43,
        27,
        85
    };

    SDL_Surface * textSurfaceT = TTF_RenderText_Solid(fontT, "The Last Nightmare", textColorT);
    if (!textSurfaceT) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(fontT);
        return -1;
    }

    SDL_Texture * textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

    SDL_Rect r_Bouton_T = {
        (( * we) / 2) - ((*we)*45/100 / 2),
        (( * he) / 6) * 1 - (((*he)*15/100)/2),
        (*we)*45/100,
         (*he)*15/100
    };

    SDL_Rect r_text_T = {
        (r_Bouton_T.x+(r_Bouton_T.w)/2-textSurfaceT -> w/2),
        (r_Bouton_T.y+(r_Bouton_T.h)/2-textSurfaceT -> h /2),
        textSurfaceT -> w,
        textSurfaceT -> h
    };


    SDL_FreeSurface(textSurfaceT);

    if (SDL_QueryTexture(textTextureT, NULL, NULL, & r_text_T.w, & r_text_T.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;

    }

    TTF_CloseFont(fontT);
    fontT = NULL;

    //chargement de la police d'écriture
    TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 50);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Surface * textSurfaceQ = TTF_RenderText_Solid(font, "Quitter", textColor);
    if (!textSurfaceQ) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture * textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);

    SDL_Surface * textSurfaceC = TTF_RenderText_Solid(font, "Continuer", textColor);
    if (!textSurfaceC) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(textSurfaceQ);
        return -1;
    }

    SDL_Texture * textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);

    SDL_Surface * textSurfaceO = TTF_RenderText_Solid(font, "Options", textColor);
    if (!textSurfaceO) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceC);
        return -1;
    }

    SDL_Texture * textTextureO = SDL_CreateTextureFromSurface(renderer, textSurfaceO);

    SDL_Surface * textSurfaceN = TTF_RenderText_Solid(font, "Nouvelle partie", textColor);
    if (!textSurfaceN) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceO);
        return -1;
    }

    SDL_Texture * textTextureN = SDL_CreateTextureFromSurface(renderer, textSurfaceN);

    TTF_CloseFont(font);
    font = NULL;

    //creation rectangle pour les textes

    SDL_Rect r_Bouton_C = {
        (( * we) / 2) - ((*we)*15/100 / 2),
        (( * he) / 6) * 2 - (((*he)*8/100)/2),
        (*we)*15/100,
         (*he)*8/100
    };
    SDL_Rect r_text_C = {
        (r_Bouton_C.x+(r_Bouton_C.w)/2-textSurfaceC -> w/2),
        (r_Bouton_C.y+(r_Bouton_C.h)/2-textSurfaceC -> h /2),
        textSurfaceC -> w,
        textSurfaceC -> h
    };
    SDL_Rect r_Bouton_Q = {
        (( * we) / 2) - ((*we)*15/100 / 2),
        (( * he) / 6) * 5 - (((*he)*8/100)/2),
        (*we)*15/100,
         (*he)*8/100
    };
    SDL_Rect r_text_Q = {
        (r_Bouton_Q.x+(r_Bouton_Q.w)/2-textSurfaceQ -> w/2),
        (r_Bouton_Q.y+(r_Bouton_Q.h)/2-textSurfaceQ -> h /2),
        textSurfaceQ -> w,
        textSurfaceQ -> h
    };

    SDL_Rect r_Bouton_O = {
        (( * we) / 2) - ((*we)*15/100 / 2),
        (( * he) / 6) * 4 - (((*he)*8/100)/2),
        (*we)*15/100,
         (*he)*8/100
    };
    SDL_Rect r_text_O = {
        (r_Bouton_O.x+(r_Bouton_O.w)/2-textSurfaceO -> w/2),
        (r_Bouton_O.y+(r_Bouton_O.h)/2-textSurfaceO -> h /2),
        textSurfaceO -> w,
        textSurfaceO -> h
    };
    SDL_Rect r_Bouton_N = {
        (( * we) / 2) - ((*we)*25/100 / 2),
        (( * he) / 6) * 3 - (((*he)*8/100)/2),
        (*we)*25/100,
         (*he)*8/100
    };

    SDL_Rect r_text_N = {
        (r_Bouton_N.x+(r_Bouton_N.w)/2-textSurfaceN -> w/2),
        (r_Bouton_N.y+(r_Bouton_N.h)/2-textSurfaceN -> h /2),
        textSurfaceN -> w,
        textSurfaceN -> h
    };


    SDL_FreeSurface(textSurfaceC);
    SDL_FreeSurface(textSurfaceQ);
    SDL_FreeSurface(textSurfaceO);
    SDL_FreeSurface(textSurfaceN);

    if (SDL_QueryTexture(textTextureQ, NULL, NULL, & r_text_Q.w, & r_text_Q.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;
    }

    if (SDL_QueryTexture(textTextureC, NULL, NULL, & r_text_C.w, & r_text_C.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;
    }

    if (SDL_QueryTexture(textTextureO, NULL, NULL, & r_text_O.w, & r_text_O.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;

    }

    if (SDL_QueryTexture(textTextureN, NULL, NULL, & r_text_N.w, & r_text_N.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;

    }
            SDL_Rect r_ecran = {
        0,
        0,
        (*we),
        (*he)
        };

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderCopy(renderer, map -> tabTexture[38], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[37], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[36], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[35], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[34], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[33], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[32], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[31], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[39], NULL, & r_Bouton_C);
        SDL_RenderCopy(renderer, map -> tabTexture[39], NULL, & r_Bouton_O);
        SDL_RenderCopy(renderer, map -> tabTexture[39], NULL, & r_Bouton_Q);
        SDL_RenderCopy(renderer, map -> tabTexture[40], NULL, & r_Bouton_N);
        SDL_RenderCopy(renderer, map -> tabTexture[40], NULL, & r_Bouton_T);


        SDL_RenderCopy(renderer, textTextureQ, NULL, & r_text_Q);
        SDL_RenderCopy(renderer, textTextureC, NULL, & r_text_C);
        SDL_RenderCopy(renderer, textTextureT, NULL, & r_text_T);
        SDL_RenderCopy(renderer, textTextureO, NULL, & r_text_O);
        SDL_RenderCopy(renderer, textTextureN, NULL, & r_text_N);

        SDL_RenderPresent(renderer);

    int etat = 1;
    while (etat) {

        while (SDL_PollEvent( & event) != 0) {

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                //pour continuer le jeu
                if ((r_text_C.x <= event.button.x) && ((r_text_C.x + r_text_C.w) >= event.button.x) && ((r_text_C.y + r_text_C.h) >= event.button.y) && (r_text_C.y <= event.button.y)) {
                    etat = 0;
                }

                //pour quitter le jeu
                else if ((r_text_Q.x <= event.button.x) && ((r_text_Q.x + r_text_Q.w) >= event.button.x) && ((r_text_Q.y + r_text_Q.h) >= event.button.y) && (r_text_Q.y <= event.button.y)) {
                    etat = 0;
                    * run = 0;
                }
                //Pour aller au menu option
                else if ((r_text_O.x <= event.button.x) && ((r_text_O.x + r_text_O.w) >= event.button.x) && ((r_text_O.y + r_text_O.h) >= event.button.y) && (r_text_O.y <= event.button.y)) {
                    * etatoption = 3;
                    option(we, he, event, renderer, etatoption, toucheDeplacement);
                }
                //Pour creer une nouvelle partie
                else if ((r_text_N.x <= event.button.x) && ((r_text_N.x + r_text_N.w) >= event.button.x) && ((r_text_N.y + r_text_N.h) >= event.button.y) && (r_text_N.y <= event.button.y)) {
                    etat = 0;
                }

            }
        }


        SDL_Delay(100);

    }

    SDL_DestroyTexture(textTextureQ);
    SDL_DestroyTexture(textTextureC);
    SDL_DestroyTexture(textTextureT);
    SDL_DestroyTexture(textTextureO);
    SDL_DestroyTexture(textTextureN);

    SDL_RenderPresent(renderer);

    return 0;
}

/**
 *\fn int option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * etatoption,int * toucheDeplacement)
 *\param we Largeur de l'ecran
 *\param he Longueur de l'ecran
 *\param event permet de savoir si il y a un evenement
 *\param renderer rendu de la fenetre
 *\param etatoption etat du menu des options
 *\param toucheDeplacement variable pour savoir quel touche de deplacement le joueur a choisis
 *\brief fonction qui affiche les options
 */

//fonction qui affiche les options
int option(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * etatoption, int * toucheDeplacement) {

    if ( * etatoption == 1 || * etatoption == 3) {

        SDL_Color textColor = {
            255,
            255,
            255
        };

        //chargement de la police d'écriture
        TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Surface * textSurfaceQ = TTF_RenderText_Solid(font, "Retour", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);

        SDL_Surface * textSurfaceQwerty = TTF_RenderText_Solid(font, "Qwerty", textColor);
        if (!textSurfaceQwerty) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTextureQwerty = SDL_CreateTextureFromSurface(renderer, textSurfaceQwerty);

        SDL_Surface * textSurfaceAzerty = TTF_RenderText_Solid(font, "Azerty", textColor);
        if (!textSurfaceAzerty) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTextureAzerty = SDL_CreateTextureFromSurface(renderer, textSurfaceAzerty);

        SDL_Surface * textSurfacefleches = TTF_RenderText_Solid(font, "fleches", textColor);
        if (!textSurfacefleches) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTexturefleches = SDL_CreateTextureFromSurface(renderer, textSurfacefleches);

        TTF_CloseFont(font);
        font = NULL;

        //creation rectangle pour les textes
        SDL_Rect r_text_Q = {
            (( * we) / 2) - ((textSurfaceQ -> w) / 2),
            ( * he / 4) * 4 - textSurfaceQ -> h - 100,
            textSurfaceQ -> w,
            textSurfaceQ -> h
        };
        SDL_Rect r_text_Qwerty = {
            (( * we) / 4) * 1 - ((textSurfaceQwerty -> w) / 2),
            ( * he / 2),
            textSurfaceQwerty -> w,
            textSurfaceQwerty -> h
        };
        SDL_Rect r_text_Azerty = {
            (( * we) / 2) * 1 - ((textSurfaceAzerty -> w) / 2),
            ( * he / 2),
            textSurfaceAzerty -> w,
            textSurfaceAzerty -> h
        };
        SDL_Rect r_text_fleches = {
            (( * we) / 4) * 3 - ((textSurfacefleches -> w) / 2),
            ( * he / 2),
            textSurfacefleches -> w,
            textSurfacefleches -> h
        };

        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceQwerty);
        SDL_FreeSurface(textSurfaceAzerty);
        SDL_FreeSurface(textSurfacefleches);

        if (SDL_QueryTexture(textTextureQ, NULL, NULL, & r_text_Q.w, & r_text_Q.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }
        if (SDL_QueryTexture(textTextureQwerty, NULL, NULL, & r_text_Qwerty.w, & r_text_Qwerty.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }
        if (SDL_QueryTexture(textTextureAzerty, NULL, NULL, & r_text_Azerty.w, & r_text_Azerty.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }
        if (SDL_QueryTexture(textTexturefleches, NULL, NULL, & r_text_fleches.w, & r_text_fleches.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }

        int etat = 1;
        while (etat) {

            while (SDL_PollEvent( & event) != 0) {

                if (event.type == SDL_MOUSEBUTTONDOWN) {

                    //pour quitter les options
                    if ((r_text_Q.x <= event.button.x) && ((r_text_Q.x + r_text_Q.w) >= event.button.x) && ((r_text_Q.y + r_text_Q.h) >= event.button.y) && (r_text_Q.y <= event.button.y)) {
                        etat = 0;
                        //retour au menu option
                        if ( * etatoption == 1) {
                            * etatoption = 2;
                        }
                        //retour a l'ecran titre
                        else {
                            * etatoption = 0;
                        }
                    }

                    if ((r_text_Qwerty.x <= event.button.x) && ((r_text_Qwerty.x + r_text_Qwerty.w) >= event.button.x) && ((r_text_Qwerty.y + r_text_Qwerty.h) >= event.button.y) && (r_text_Qwerty.y <= event.button.y)) {
                        * toucheDeplacement = 1;

                    }

                    if ((r_text_Azerty.x <= event.button.x) && ((r_text_Azerty.x + r_text_Azerty.w) >= event.button.x) && ((r_text_Azerty.y + r_text_Azerty.h) >= event.button.y) && (r_text_Azerty.y <= event.button.y)) {
                        * toucheDeplacement = 0;

                    }

                    if ((r_text_fleches.x <= event.button.x) && ((r_text_fleches.x + r_text_fleches.w) >= event.button.x) && ((r_text_fleches.y + r_text_fleches.h) >= event.button.y) && (r_text_fleches.y <= event.button.y)) {
                        * toucheDeplacement = 2;

                    }

                }

            }

            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawRect(renderer, & r_text_Azerty);
            SDL_RenderDrawRect(renderer, & r_text_Qwerty);
            SDL_RenderDrawRect(renderer, & r_text_fleches);
            if ( * toucheDeplacement == 0) {
                SDL_RenderFillRect(renderer, & r_text_Azerty);

            }
            if ( * toucheDeplacement == 1) {
                SDL_RenderFillRect(renderer, & r_text_Qwerty);

            }
            if ( * toucheDeplacement == 2) {
                SDL_RenderFillRect(renderer, & r_text_fleches);

            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderCopy(renderer, textTextureQ, NULL, & r_text_Q);

            SDL_RenderCopy(renderer, textTextureQwerty, NULL, & r_text_Qwerty);
            SDL_RenderCopy(renderer, textTextureAzerty, NULL, & r_text_Azerty);
            SDL_RenderCopy(renderer, textTexturefleches, NULL, & r_text_fleches);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);

        }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureQwerty);
        SDL_DestroyTexture(textTextureAzerty);
        SDL_DestroyTexture(textTexturefleches);

    }
    return 0;

}

/**
 *\fn int menu_gameOver(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,p_mv* personnage,map_t * map)
 *\param we Largeur de l'ecran
 *\param he Longueur de l'ecran
 *\param event permet de savoir si il y a un evenement
 *\param renderer rendu de la fenetre
 *\param run pointeur pour continuer le programme
 *\param personnage structure du personnage jouer
 *\param map structure de la map
 *\brief fonction qui affiche l'ecran game over
 */

//fonction qui affiche l'ecran game over
int menu_gameOver(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * run, p_mv * personnage, map_t * map) {
    if ( * personnage -> equipe[0] -> pv <= 0) {

        SDL_RenderClear(renderer);
        SDL_Color textColor = {
            255,
            255,
            255
        };

        //chargement de la police d'écriture
        TTF_Font * fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
        if (!fontT) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColorT = {
            150,
            0,
            0
        };

        SDL_Surface * textSurfaceT = TTF_RenderText_Solid(fontT, "Game Over", textColorT);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(fontT);
            return -1;
        }

        SDL_Texture * textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

        SDL_Rect r_text_T = {
            (( * we) / 2) - ((textSurfaceT -> w) / 2),
            (( * he) / 3),
            textSurfaceT -> w,
            textSurfaceT -> h
        };
        SDL_FreeSurface(textSurfaceT);

        if (SDL_QueryTexture(textTextureT, NULL, NULL, & r_text_T.w, & r_text_T.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;

        }

        TTF_CloseFont(fontT);
        fontT = NULL;

        //chargement de la police d'écriture
        TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Surface * textSurfaceQ = TTF_RenderText_Solid(font, "Quitter", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);

        SDL_Surface * textSurfaceC = TTF_RenderText_Solid(font, "Rejouer", textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture * textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);

        SDL_Surface * textSurfaceN = TTF_RenderText_Solid(font, "Magasin", textColor);
        if (!textSurfaceN) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }

        SDL_Texture * textTextureN = SDL_CreateTextureFromSurface(renderer, textSurfaceN);

        TTF_CloseFont(font);
        font = NULL;

        //creation rectangle pour les textes

        SDL_Rect r_text_Q = {
            (( * we) / 2) - ((textSurfaceQ -> w) / 2),
            ( * he / 4) * 4 - textSurfaceQ -> h - 100,
            textSurfaceQ -> w,
            textSurfaceQ -> h
        };
        SDL_Rect r_text_N = {
            (( * we) / 2) - ((textSurfaceN -> w) / 2),
            ( * he / 4) * 2 - textSurfaceN -> h + 50,
            textSurfaceN -> w,
            textSurfaceN -> h
        };
        SDL_Rect r_text_C = {
            (( * we) / 2) - ((textSurfaceC -> w) / 2),
            ( * he / 4) * 3 - textSurfaceC -> h,
            textSurfaceC -> w,
            textSurfaceC -> h
        };

        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceN);

        if (SDL_QueryTexture(textTextureQ, NULL, NULL, & r_text_Q.w, & r_text_Q.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }

        if (SDL_QueryTexture(textTextureC, NULL, NULL, & r_text_C.w, & r_text_C.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }

        if (SDL_QueryTexture(textTextureN, NULL, NULL, & r_text_N.w, & r_text_N.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;

        }

        int etat = 1;
        while (etat) {

            while (SDL_PollEvent( & event) != 0) {

                if (event.type == SDL_MOUSEBUTTONDOWN) {

                    //pour continuer le jeu
                    if ((r_text_C.x <= event.button.x) && ((r_text_C.x + r_text_C.w) >= event.button.x) && ((r_text_C.y + r_text_C.h) >= event.button.y) && (r_text_C.y <= event.button.y)) {
                        etat = 0;
                    }

                    //pour quitter le jeu
                    else if ((r_text_Q.x <= event.button.x) && ((r_text_Q.x + r_text_Q.w) >= event.button.x) && ((r_text_Q.y + r_text_Q.h) >= event.button.y) && (r_text_Q.y <= event.button.y)) {
                        etat = 0;
                        * run = 0;
                    }
                    //Pour aller au magasin
                    else if ((r_text_N.x <= event.button.x) && ((r_text_N.x + r_text_N.w) >= event.button.x) && ((r_text_N.y + r_text_N.h) >= event.button.y) && (r_text_N.y <= event.button.y)) {
                        etat = 0;
                        magasin(we, he, event, renderer, personnage, map);
                    }

                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderClear(renderer);
            SDL_Rect r_ecran = {
                0,
                0,
                ( * we),
                ( * he)
            };
            SDL_RenderCopy(renderer, map -> tabTexture[44], NULL, & r_ecran);

            SDL_RenderCopy(renderer, textTextureQ, NULL, & r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, & r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, & r_text_T);
            SDL_RenderCopy(renderer, textTextureN, NULL, & r_text_N);

            SDL_RenderPresent(renderer);
            SDL_Delay(100);

        }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);
        SDL_DestroyTexture(textTextureN);

        SDL_RenderPresent(renderer);

    }
    return 0;
}

/**
 *\fn int magasin(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,p_mv* personnage,map_t * map)
 *\param we Largeur de l'ecran
 *\param he Longueur de l'ecran
 *\param event permet de savoir si il y a un evenement
 *\param renderer rendu de la fenetre
 *\param run pointeur pour continuer le programme
 *\param personnage structure du personnage jouer
 *\param map structure de la map
 *\brief fonction qui affiche et gere le magasin
 */

//fonction qui affiche et gere le magasin
int magasin(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, p_mv * personnage, map_t * map) {

    SDL_RenderClear(renderer);
    SDL_Color textColor = {
        255,
        255,
        255
    };
    SDL_Color textColorGris = {
        50,
        50,
        50
    };
    SDL_Color couleuractuel = textColor;
    int i, j, k;

    /*
     *
     *HAUT DE L'ECRAN
     *
     */

    SDL_Rect r_HEcran = {
        0,
        0,
        ( * we),
        ( * he) / 8
    };
    SDL_Rect r_ecran = {
        0,
        0,
        ( * we),
        ( * he)
    };
    SDL_Rect r_Mecran = {
        0,
        r_HEcran.h,
        ( * we),
        ( * he) - (r_HEcran.h - ( * he) - (( * he / 8) * 7))
    };

    //chargement de la police d'écriture
    TTF_Font * fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
    if (!fontT) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColorT = {
        43,
        27,
        85
    };

    SDL_Surface * textSurfaceT = TTF_RenderText_Solid(fontT, "Magasin", textColorT);
    if (!textSurfaceT) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(fontT);
        return -1;
    }

    SDL_Texture * textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

    SDL_Rect r_text_T = {
        (( * we) / 2) - ((textSurfaceT -> w) / 2),
        (r_HEcran.h / 2) - (textSurfaceT -> h / 2),
        textSurfaceT -> w,
        textSurfaceT -> h
    };
    SDL_FreeSurface(textSurfaceT);

    if (SDL_QueryTexture(textTextureT, NULL, NULL, & r_text_T.w, & r_text_T.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;

    }

    TTF_CloseFont(fontT);
    fontT = NULL;

    /*
     *
     *BAS ECRAN
     *
     */
    SDL_Rect r_BEcran = {
        0,
        ( * he / 8) * 7,
        ( * we),
        ( * he) - (( * he / 8) * 7)
    };

    //chargement de la police d'écriture
    TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 50);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Surface * textSurfaceQ = TTF_RenderText_Solid(font, "Retour", textColor);
    if (!textSurfaceQ) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture * textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);

    //creation rectangle pour les textes

    SDL_Rect r_text_Q = {
        (( * we) / 2) - ((textSurfaceQ -> w) / 2),
        (r_BEcran.y + r_BEcran.h / 2) - (textSurfaceQ -> h / 2),
        textSurfaceQ -> w,
        textSurfaceQ -> h
    };

    SDL_FreeSurface(textSurfaceQ);

    if (SDL_QueryTexture(textTextureQ, NULL, NULL, & r_text_Q.w, & r_text_Q.h) != 0) {
        printf("Impossible de charger le texte\n");
        return -1;
    }

    TTF_CloseFont(font);
    font = NULL;
    SDL_RenderCopy(renderer, map -> tabTexture[44], NULL, & r_ecran);
    SDL_RenderFillRect(renderer, & r_Mecran);

    int etat = 1;
    while (etat) {
        SDL_RenderClear(renderer);
        SDL_Rect r_Mecran = {
            0,
            r_HEcran.h,
            ( * we),
            r_BEcran.y - r_HEcran.h
        };
        //affichage du rectangle du haut et du bas
        SDL_SetRenderDrawColor(renderer, 112, 114, 110, 255);
        SDL_Rect r_ecran = {
            0,
            0,
            ( * we),
            ( * he)
        };
        SDL_RenderCopy(renderer, map -> tabTexture[44], NULL, & r_ecran);
        SDL_RenderCopy(renderer, map -> tabTexture[56], NULL, & r_HEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[56], NULL, & r_BEcran);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, & r_Mecran);

        /*
         *
         *ARGENT
         *
         */
        //chargement de la police d'écriture
        font = TTF_OpenFont("fonts/alagard.ttf", 30);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        char * texte = malloc(20);
        snprintf(texte, 20, "Argents : %d", map -> argent);

        SDL_Surface * textSurface = TTF_RenderText_Blended(font, texte, textColor);
        if (!textSurface) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect r_text_A = {
            10,
            r_HEcran.h / 2 - textSurface -> h / 2,
            textSurface -> w,
            textSurface -> h
        };
        SDL_FreeSurface(textSurface);

        if (SDL_QueryTexture(textTexture, NULL, NULL, & r_text_A.w, & r_text_A.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;

        }

        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);

        /*
         *
         *AFFICHAGE CARRE EMPLACEMENT
         *
         */

        SDL_Rect r_emplacement1 = {
            (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 1)) - (10 * 1) - (( * we) * 3 / 100),
            (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
            r_HEcran.h - (r_HEcran.h / 4),
            r_HEcran.h - (r_HEcran.h / 4)
        };
        SDL_Rect r_emplacement2 = {
            (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 2)) - (10 * 2) - (( * we) * 3 / 100),
            (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
            r_HEcran.h - (r_HEcran.h / 4),
            r_HEcran.h - (r_HEcran.h / 4)
        };
        SDL_Rect r_emplacement3 = {
            (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 3)) - (10 * 3) - (( * we) * 3 / 100),
            (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
            r_HEcran.h - (r_HEcran.h / 4),
            r_HEcran.h - (r_HEcran.h / 4)
        };
        SDL_Rect r_emplacement4 = {
            (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 4)) - (10 * 4) - (( * we) * 3 / 100),
            (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
            r_HEcran.h - (r_HEcran.h / 4),
            r_HEcran.h - (r_HEcran.h / 4)
        };

        SDL_RenderFillRect(renderer, & r_emplacement1);
        SDL_RenderFillRect(renderer, & r_emplacement2);
        SDL_RenderFillRect(renderer, & r_emplacement3);
        SDL_RenderFillRect(renderer, & r_emplacement4);

        TTF_CloseFont(font);
        font = NULL;
        font = TTF_OpenFont("fonts/alagard.ttf", 20);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        char * prix_emplacement = malloc(20);
        snprintf(prix_emplacement, 20, "Prix : %d", map -> prix_emplacement);
        for (k = 4, i = 1; k > 0; k--, i++) {

            if (i > map -> nb_emplacement) {

                //afficher le descriptif des artefacts de droite
                SDL_Surface * textSurfaceEmp = TTF_RenderText_Solid(font, prix_emplacement, couleuractuel);
                if (!textSurfaceEmp) {
                    fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                    TTF_CloseFont(font);
                    return -1;
                }

                SDL_Texture * textTextureEmp = SDL_CreateTextureFromSurface(renderer, textSurfaceEmp);

                SDL_Rect r_text_Emp = {
                    (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * k)) - (10 * k) + (r_emplacement4.w / 2) - (textSurfaceEmp -> w / 2),
                    (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2 + (r_emplacement4.h / 2) - (textSurfaceEmp -> h / 2),
                    textSurfaceEmp -> w,
                    textSurfaceEmp -> h
                };

                SDL_FreeSurface(textSurfaceEmp);
                if (SDL_QueryTexture(textTextureEmp, NULL, NULL, & r_text_Emp.w, & r_text_Emp.h) != 0) {
                    printf("Impossible de charger le texte\n");
                    return -1;
                }
                SDL_RenderCopy(renderer, textTextureEmp, NULL, & r_text_Emp);
                SDL_DestroyTexture(textTextureEmp);

            }
        }

        /*
         *
         *AFFICHAGE RELIQUES
         *
         */

        TTF_CloseFont(font);
        font = NULL;

        font = TTF_OpenFont("fonts/alagard.ttf", 30);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        //afficher les carres des artefacts adegauche
        SDL_Rect r_artefactGauche1 = {
            ( * we) / 8,
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 0 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactGauche2 = {
            ( * we) / 8,
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 1 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactGauche3 = {
            ( * we) / 8,
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 2 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactGauche4 = {
            ( * we) / 8,
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 3 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactGauche5 = {
            ( * we) / 8,
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 4 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };

        //SDL_RenderFillRect(renderer, &r_artefactGauche);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[0] -> indice_texture], NULL, & r_artefactGauche1);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[1] -> indice_texture], NULL, & r_artefactGauche2);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[2] -> indice_texture], NULL, & r_artefactGauche3);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[3] -> indice_texture], NULL, & r_artefactGauche4);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[4] -> indice_texture], NULL, & r_artefactGauche5);

        //afficher les carres des artefacts de droite
        SDL_Rect r_artefactDroit1 = {
            ( * we) - (( * we) / 8 * 3),
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 0 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactDroit2 = {
            ( * we) - (( * we) / 8 * 3),
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 1 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactDroit3 = {
            ( * we) - (( * we) / 8 * 3),
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 2 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactDroit4 = {
            ( * we) - (( * we) / 8 * 3),
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 3 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };
        SDL_Rect r_artefactDroit5 = {
            ( * we) - (( * we) / 8 * 3),
            r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 4 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
            ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
        };

        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[5] -> indice_texture], NULL, & r_artefactDroit1);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[6] -> indice_texture], NULL, & r_artefactDroit2);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[7] -> indice_texture], NULL, & r_artefactDroit3);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[8] -> indice_texture], NULL, & r_artefactDroit4);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[9] -> indice_texture], NULL, & r_artefactDroit5);

        //((*we)-(((*we)-(r_artefactGauche.w+r_artefactGauche.x))/2))-(((r_BEcran.y-r_HEcran.h)/5)-((r_BEcran.y-r_HEcran.h)/5)*10/100)/2 Le X

        //SDL_RenderFillRect(renderer, &r_artefactDroit);
        SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[i] -> indice_texture], NULL, & r_artefactDroit1);

        for (j = 0, k = 5; j < 5 && k < 10; j++, k++) {
            if (map -> listeArtefact[j] -> possession == 1) {
                couleuractuel = textColorGris;
            } else {
                couleuractuel = textColor;
            }
            /*
             *
             *NOM DES ARTEFACTS
             *
             */

            //afficher le nom des artefacts de gauche
            SDL_Surface * textSurfaceArtG = TTF_RenderText_Solid(font, map -> listeArtefact[j] -> nom, couleuractuel);
            if (!textSurfaceArtG) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            SDL_Texture * textTextureArtG = SDL_CreateTextureFromSurface(renderer, textSurfaceArtG);

            SDL_Rect r_text_ArtG = {
                ((r_artefactDroit1.x) - ((r_artefactDroit1.x) - (r_artefactGauche1.x + r_artefactGauche1.w)) / 2) - textSurfaceArtG -> w / 2,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                textSurfaceArtG -> w,
                textSurfaceArtG -> h
            };

            SDL_FreeSurface(textSurfaceArtG);
            if (SDL_QueryTexture(textTextureArtG, NULL, NULL, & r_text_ArtG.w, & r_text_ArtG.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;
            }
            SDL_RenderCopy(renderer, textTextureArtG, NULL, & r_text_ArtG);
            SDL_DestroyTexture(textTextureArtG);

            if (map -> listeArtefact[k] -> possession == 1) {
                couleuractuel = textColorGris;
            } else {
                couleuractuel = textColor;
            }

            //afficher le nom des artefacts de droite
            SDL_Surface * textSurfaceArtD = TTF_RenderText_Solid(font, map -> listeArtefact[k] -> nom, couleuractuel);
            if (!textSurfaceArtD) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            SDL_Texture * textTextureArtD = SDL_CreateTextureFromSurface(renderer, textSurfaceArtD);

            SDL_Rect r_text_ArtD = {
                (( * we) - (( * we) - (r_artefactDroit1.x + r_artefactDroit1.w)) / 2) - textSurfaceArtD -> w / 2,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                textSurfaceArtD -> w,
                textSurfaceArtD -> h
            };

            SDL_FreeSurface(textSurfaceArtD);
            if (SDL_QueryTexture(textTextureArtD, NULL, NULL, & r_text_ArtD.w, & r_text_ArtD.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;
            }
            SDL_RenderCopy(renderer, textTextureArtD, NULL, & r_text_ArtD);
            SDL_DestroyTexture(textTextureArtD);

            /*
             *
             *DESCRPTIF DES ARTEFACTS
             *
             */
            if (map -> listeArtefact[j] -> possession == 1) {
                couleuractuel = textColorGris;
            } else {
                couleuractuel = textColor;
            }
            //afficher le descrptif des artefacts de gauche
            textSurfaceArtG = TTF_RenderText_Solid(font, map -> listeArtefact[j] -> descriptif, couleuractuel);
            if (!textSurfaceArtG) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            textTextureArtG = SDL_CreateTextureFromSurface(renderer, textSurfaceArtG);

            SDL_Rect r_text_ArtGD = {
                ((r_artefactDroit1.x) - ((r_artefactDroit1.x) - (r_artefactGauche1.x + r_artefactGauche1.w)) / 2) - textSurfaceArtG -> w / 2,
                (r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2) + r_text_ArtG.h,
                textSurfaceArtG -> w,
                textSurfaceArtG -> h
            };

            SDL_FreeSurface(textSurfaceArtG);
            if (SDL_QueryTexture(textTextureArtG, NULL, NULL, & r_text_ArtGD.w, & r_text_ArtGD.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;
            }
            SDL_RenderCopy(renderer, textTextureArtG, NULL, & r_text_ArtGD);
            SDL_DestroyTexture(textTextureArtG);

            if (map -> listeArtefact[k] -> possession == 1) {
                couleuractuel = textColorGris;
            } else {
                couleuractuel = textColor;
            }

            //afficher le descriptif des artefacts de droite
            textSurfaceArtD = TTF_RenderText_Solid(font, map -> listeArtefact[k] -> descriptif, couleuractuel);
            if (!textSurfaceArtD) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            textTextureArtD = SDL_CreateTextureFromSurface(renderer, textSurfaceArtD);

            SDL_Rect r_text_ArtDD = {
                (( * we) - (( * we) - (r_artefactDroit1.x + r_artefactDroit1.w)) / 2) - textSurfaceArtD -> w / 2,
                (r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2) + r_text_ArtD.h,
                textSurfaceArtD -> w,
                textSurfaceArtD -> h
            };

            SDL_FreeSurface(textSurfaceArtD);
            if (SDL_QueryTexture(textTextureArtD, NULL, NULL, & r_text_ArtDD.w, & r_text_ArtDD.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;
            }
            SDL_RenderCopy(renderer, textTextureArtD, NULL, & r_text_ArtDD);
            SDL_DestroyTexture(textTextureArtD);

            /*
             *
             *PRIX DES ARTEFACTS
             *
             */

            if (map -> listeArtefact[j] -> possession == 1) {
                couleuractuel = textColorGris;
            } else {
                couleuractuel = textColor;
            }

            char * texte = malloc(12);
            snprintf(texte, 12, "Prix : %d", map -> listeArtefact[j] -> prix);

            //afficher le descrptif des artefacts de gauche
            textSurfaceArtG = TTF_RenderText_Solid(font, texte, couleuractuel);
            if (!textSurfaceArtG) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            textTextureArtG = SDL_CreateTextureFromSurface(renderer, textSurfaceArtG);

            SDL_Rect r_text_ArtGP = {
                ((r_artefactDroit1.x) - ((r_artefactDroit1.x) - (r_artefactGauche1.x + r_artefactGauche1.w)) / 2) - textSurfaceArtG -> w / 2,
                (r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2) + r_text_ArtG.h + r_text_ArtGD.h,
                textSurfaceArtG -> w,
                textSurfaceArtG -> h
            };

            SDL_FreeSurface(textSurfaceArtG);
            if (SDL_QueryTexture(textTextureArtG, NULL, NULL, & r_text_ArtGP.w, & r_text_ArtGP.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;
            }
            SDL_RenderCopy(renderer, textTextureArtG, NULL, & r_text_ArtGP);
            SDL_DestroyTexture(textTextureArtG);

            char * texte2 = malloc(12);
            snprintf(texte2, 12, "Prix : %d", map -> listeArtefact[k] -> prix);

            if (map -> listeArtefact[k] -> possession == 1) {
                couleuractuel = textColorGris;
            } else {
                couleuractuel = textColor;
            }

            //afficher le descriptif des artefacts de droite
            textSurfaceArtD = TTF_RenderText_Solid(font, texte2, couleuractuel);
            if (!textSurfaceArtD) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            textTextureArtD = SDL_CreateTextureFromSurface(renderer, textSurfaceArtD);

            SDL_Rect r_text_ArtDP = {
                (( * we) - (( * we) - (r_artefactDroit1.x + r_artefactDroit1.w)) / 2) - textSurfaceArtD -> w / 2,
                (r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2) + r_text_ArtD.h + r_text_ArtDD.h,
                textSurfaceArtD -> w,
                textSurfaceArtD -> h
            };

            SDL_FreeSurface(textSurfaceArtD);
            if (SDL_QueryTexture(textTextureArtD, NULL, NULL, & r_text_ArtDP.w, & r_text_ArtDP.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;
            }
            SDL_RenderCopy(renderer, textTextureArtD, NULL, & r_text_ArtDP);
            SDL_DestroyTexture(textTextureArtD);

            free(texte2);
            free(texte);

        }
        while (SDL_PollEvent( & event) != 0) {

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                //pour quitter le jeu
                if ((r_text_Q.x <= event.button.x) && ((r_text_Q.x + r_text_Q.w) >= event.button.x) && ((r_text_Q.y + r_text_Q.h) >= event.button.y) && (r_text_Q.y <= event.button.y)) {
                    etat = 0;

                }
                if ((r_artefactGauche1.x <= event.button.x) && ((r_artefactGauche1.x + r_artefactGauche1.w) >= event.button.x) && ((r_artefactGauche1.y + r_artefactGauche1.h) >= event.button.y) && (r_artefactGauche1.y <= event.button.y) && map -> argent >= map -> listeArtefact[0] -> prix && map -> listeArtefact[0] -> possession == 0) {
                    map -> listeArtefact[0] -> possession = 1;
                    map -> argent -= map -> listeArtefact[0] -> prix;

                }
                if ((r_artefactGauche2.x <= event.button.x) && ((r_artefactGauche2.x + r_artefactGauche2.w) >= event.button.x) && ((r_artefactGauche2.y + r_artefactGauche2.h) >= event.button.y) && (r_artefactGauche2.y <= event.button.y) && map -> argent >= map -> listeArtefact[1] -> prix && map -> listeArtefact[1] -> possession == 0) {
                    map -> listeArtefact[1] -> possession = 1;
                    map -> argent -= map -> listeArtefact[1] -> prix;

                }
                if ((r_artefactGauche3.x <= event.button.x) && ((r_artefactGauche3.x + r_artefactGauche3.w) >= event.button.x) && ((r_artefactGauche3.y + r_artefactGauche3.h) >= event.button.y) && (r_artefactGauche3.y <= event.button.y) && map -> argent >= map -> listeArtefact[2] -> prix && map -> listeArtefact[2] -> possession == 0) {
                    map -> listeArtefact[2] -> possession = 1;
                    map -> argent -= map -> listeArtefact[2] -> prix;

                }
                if ((r_artefactGauche4.x <= event.button.x) && ((r_artefactGauche4.x + r_artefactGauche4.w) >= event.button.x) && ((r_artefactGauche4.y + r_artefactGauche4.h) >= event.button.y) && (r_artefactGauche4.y <= event.button.y) && map -> argent >= map -> listeArtefact[3] -> prix && map -> listeArtefact[3] -> possession == 0) {
                    map -> listeArtefact[3] -> possession = 1;
                    map -> argent -= map -> listeArtefact[3] -> prix;

                }
                if ((r_artefactGauche5.x <= event.button.x) && ((r_artefactGauche5.x + r_artefactGauche5.w) >= event.button.x) && ((r_artefactGauche5.y + r_artefactGauche5.h) >= event.button.y) && (r_artefactGauche5.y <= event.button.y) && map -> argent >= map -> listeArtefact[4] -> prix && map -> listeArtefact[4] -> possession == 0) {
                    map -> listeArtefact[4] -> possession = 1;
                    map -> argent -= map -> listeArtefact[4] -> prix;

                }
                if ((r_artefactDroit1.x <= event.button.x) && ((r_artefactDroit1.x + r_artefactDroit1.w) >= event.button.x) && ((r_artefactDroit1.y + r_artefactDroit1.h) >= event.button.y) && (r_artefactDroit1.y <= event.button.y) && map -> argent >= map -> listeArtefact[5] -> prix && map -> listeArtefact[5] -> possession == 0) {
                    map -> listeArtefact[5] -> possession = 1;
                    map -> argent -= map -> listeArtefact[5] -> prix;

                }
                if ((r_artefactDroit2.x <= event.button.x) && ((r_artefactDroit2.x + r_artefactDroit2.w) >= event.button.x) && ((r_artefactDroit2.y + r_artefactDroit2.h) >= event.button.y) && (r_artefactDroit2.y <= event.button.y) && map -> argent >= map -> listeArtefact[6] -> prix && map -> listeArtefact[6] -> possession == 0) {
                    map -> listeArtefact[6] -> possession = 1;
                    map -> argent -= map -> listeArtefact[6] -> prix;

                }
                if ((r_artefactDroit3.x <= event.button.x) && ((r_artefactDroit3.x + r_artefactDroit3.w) >= event.button.x) && ((r_artefactDroit3.y + r_artefactDroit3.h) >= event.button.y) && (r_artefactDroit3.y <= event.button.y) && map -> argent >= map -> listeArtefact[7] -> prix && map -> listeArtefact[7] -> possession == 0) {
                    map -> listeArtefact[7] -> possession = 1;
                    map -> argent -= map -> listeArtefact[7] -> prix;

                }
                if ((r_artefactDroit4.x <= event.button.x) && ((r_artefactDroit4.x + r_artefactDroit4.w) >= event.button.x) && ((r_artefactDroit4.y + r_artefactDroit4.h) >= event.button.y) && (r_artefactDroit4.y <= event.button.y) && map -> argent >= map -> listeArtefact[8] -> prix && map -> listeArtefact[8] -> possession == 0) {
                    map -> listeArtefact[8] -> possession = 1;
                    map -> argent -= map -> listeArtefact[8] -> prix;

                }
                if ((r_artefactDroit5.x <= event.button.x) && ((r_artefactDroit5.x + r_artefactDroit5.w) >= event.button.x) && ((r_artefactDroit5.y + r_artefactDroit5.h) >= event.button.y) && (r_artefactDroit5.y <= event.button.y) && map -> argent >= map -> listeArtefact[9] -> prix && map -> listeArtefact[9] -> possession == 0) {
                    map -> listeArtefact[9] -> possession = 1;
                    map -> argent -= map -> listeArtefact[9] -> prix;

                }
                if ((r_emplacement1.x <= event.button.x) && ((r_emplacement1.x + r_emplacement1.w) >= event.button.x) && ((r_emplacement1.y + r_emplacement1.h) >= event.button.y) && (r_emplacement1.y <= event.button.y) && map -> argent >= map -> prix_emplacement && map -> nb_emplacement == 3) {
                    map -> nb_emplacement++;
                    map -> argent -= map -> prix_emplacement;

                }
                if ((r_emplacement2.x <= event.button.x) && ((r_emplacement2.x + r_emplacement2.w) >= event.button.x) && ((r_emplacement2.y + r_emplacement2.h) >= event.button.y) && (r_emplacement2.y <= event.button.y) && map -> argent >= map -> prix_emplacement && map -> nb_emplacement == 2) {
                    map -> nb_emplacement++;
                    map -> argent -= map -> prix_emplacement;

                }
                if ((r_emplacement3.x <= event.button.x) && ((r_emplacement3.x + r_emplacement3.w) >= event.button.x) && ((r_emplacement3.y + r_emplacement3.h) >= event.button.y) && (r_emplacement3.y <= event.button.y) && map -> argent >= map -> prix_emplacement && map -> nb_emplacement == 1) {
                    map -> nb_emplacement++;
                    map -> argent -= map -> prix_emplacement;

                }

            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderCopy(renderer, textTextureQ, NULL, & r_text_Q);
        SDL_RenderCopy(renderer, textTextureT, NULL, & r_text_T);
        SDL_RenderCopy(renderer, textTexture, NULL, & r_text_A);
        SDL_DestroyTexture(textTexture);
        free(texte);
        free(prix_emplacement);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }
    TTF_CloseFont(font);
    font = NULL;
    //destruction des texture
    SDL_DestroyTexture(textTextureQ);
    SDL_DestroyTexture(textTextureT);

    SDL_RenderPresent(renderer);

    return 0;
}

/**
 *\fn int inventaire(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,map_t * map)
 *\param we Largeur de l'ecran
 *\param he Longueur de l'ecran
 *\param event permet de savoir si il y a un evenement
 *\param renderer rendu de la fenetre
 *\param map structure de la map
 *\brief fonction qui affiche et gere l'inventaire
 */

//fonction qui affiche et gere l'inventaire
int inventaire(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, map_t * map) {

    if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)) {

        int i, j, k;
        int indice_art_emp[4];
        int nb_artefact_equipe = 0;

        for (i = 0; i < 10; i++) {
            if (map -> listeArtefact[i] -> equipe == 1) {
                nb_artefact_equipe++;
            }
        }

        SDL_RenderClear(renderer);
        SDL_Color textColor = {
            255,
            255,
            255
        };
        SDL_Color textColorGrisFonce = {
            56,
            62,
            66
        };
        SDL_Color couleuractuel = textColor;

        /*
         *
         *HAUT DE L'ECRAN
         *
         */

        SDL_Rect r_HEcran = {
            0,
            0,
            * we,
            ( * he) / 8
        };

        //chargement de la police d'écriture
        TTF_Font * fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
        if (!fontT) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColorT = {
            43,
            27,
            85
        };

        SDL_Surface * textSurfaceT = TTF_RenderText_Solid(fontT, "Inventaire", textColorT);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(fontT);
            return -1;
        }

        SDL_Texture * textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

        SDL_Rect r_text_T = {
            (( * we) / 2) - ((textSurfaceT -> w) / 2),
            (r_HEcran.h / 2) - (textSurfaceT -> h / 2),
            textSurfaceT -> w,
            textSurfaceT -> h
        };
        SDL_FreeSurface(textSurfaceT);

        if (SDL_QueryTexture(textTextureT, NULL, NULL, & r_text_T.w, & r_text_T.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;

        }

        TTF_CloseFont(fontT);
        fontT = NULL;

        /*
         *
         *BAS ECRAN
         *
         */
        SDL_Rect r_BEcran = {
            0,
            ( * he / 8) * 7,
            * we,
            ( * he) - (( * he / 8) * 7)
        };

        //chargement de la police d'écriture
        TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Surface * textSurfaceQ = TTF_RenderText_Solid(font, "Retour", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture * textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);

        //creation rectangle pour les textes

        SDL_Rect r_text_Q = {
            (( * we) / 2) - ((textSurfaceQ -> w) / 2),
            (r_BEcran.y + r_BEcran.h / 2) - (textSurfaceQ -> h / 2),
            textSurfaceQ -> w,
            textSurfaceQ -> h
        };

        SDL_FreeSurface(textSurfaceQ);

        if (SDL_QueryTexture(textTextureQ, NULL, NULL, & r_text_Q.w, & r_text_Q.h) != 0) {
            printf("Impossible de charger le texte\n");
            return -1;
        }

        TTF_CloseFont(font);
        font = NULL;

        int etat = 1;
        while (etat) {
            SDL_RenderClear(renderer);
            SDL_Rect r_Mecran = {
                0,
                r_HEcran.h,
                ( * we),
                r_BEcran.y - r_HEcran.h
            };
            //affichage du rectangle du haut et du bas
            SDL_SetRenderDrawColor(renderer, 112, 114, 110, 255);
            SDL_Rect r_ecran = {
                0,
                0,
                ( * we),
                ( * he)
            };
            SDL_RenderCopy(renderer, map -> tabTexture[44], NULL, & r_ecran);
            SDL_RenderCopy(renderer, map -> tabTexture[56], NULL, & r_HEcran);
            SDL_RenderCopy(renderer, map -> tabTexture[56], NULL, & r_BEcran);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, & r_Mecran);

            /*
             *
             *ARGENT
             *
             */
            //chargement de la police d'écriture
            font = TTF_OpenFont("fonts/alagard.ttf", 30);
            if (!font) {
                //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
                return -1;
            }

            char * texte = malloc(20);
            snprintf(texte, 20, "Argents : %d", map -> argent);

            SDL_Surface * textSurface = TTF_RenderText_Blended(font, texte, textColor);
            if (!textSurface) {
                fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                TTF_CloseFont(font);
                return -1;
            }

            SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_Rect r_text_A = {
                10 + (( * we) * 3 / 100),
                r_HEcran.h / 2 - textSurface -> h / 2,
                textSurface -> w,
                textSurface -> h
            };
            SDL_FreeSurface(textSurface);

            if (SDL_QueryTexture(textTexture, NULL, NULL, & r_text_A.w, & r_text_A.h) != 0) {
                printf("Impossible de charger le texte\n");
                return -1;

            }

            /*
             *
             *AFFICHAGE CARRE EMPLACEMENT
             *
             */

            for (i = 0, k = 0; i < 10; i++) {
                if (map -> listeArtefact[i] -> equipe == 1) {
                    indice_art_emp[k] = map -> listeArtefact[i] -> indice;
                    k++;

                }
            }

            SDL_Rect r_emplacement1 = {
                (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 1)) - (10 * 1) - (( * we) * 3 / 100),
                (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
                r_HEcran.h - (r_HEcran.h / 4),
                r_HEcran.h - (r_HEcran.h / 4)
            };
            SDL_Rect r_emplacement2 = {
                (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 2)) - (10 * 2) - (( * we) * 3 / 100),
                (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
                r_HEcran.h - (r_HEcran.h / 4),
                r_HEcran.h - (r_HEcran.h / 4)
            };
            SDL_Rect r_emplacement3 = {
                (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 3)) - (10 * 3) - (( * we) * 3 / 100),
                (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
                r_HEcran.h - (r_HEcran.h / 4),
                r_HEcran.h - (r_HEcran.h / 4)
            };
            SDL_Rect r_emplacement4 = {
                (( * we) - ((r_HEcran.h - (r_HEcran.h / 4)) * 4)) - (10 * 4) - (( * we) * 3 / 100),
                (r_HEcran.h / 4) - (r_HEcran.h / 4) / 2,
                r_HEcran.h - (r_HEcran.h / 4),
                r_HEcran.h - (r_HEcran.h / 4)
            };

            SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);

            if (nb_artefact_equipe > 0) {
                SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[indice_art_emp[0]] -> indice_texture], NULL, & r_emplacement4);
            } else {
                SDL_RenderFillRect(renderer, & r_emplacement4);
            }
            if (nb_artefact_equipe > 1) {
                SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[indice_art_emp[1]] -> indice_texture], NULL, & r_emplacement3);
            } else {
                if (map -> nb_emplacement < 2) {
                    SDL_SetRenderDrawColor(renderer, 56, 62, 66, 255);
                }
                SDL_RenderFillRect(renderer, & r_emplacement3);
            }
            if (nb_artefact_equipe > 2) {
                SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[indice_art_emp[2]] -> indice_texture], NULL, & r_emplacement2);
            } else {
                if (map -> nb_emplacement < 3) {
                    SDL_SetRenderDrawColor(renderer, 56, 62, 66, 255);
                }
                SDL_RenderFillRect(renderer, & r_emplacement2);
            }

            if (nb_artefact_equipe > 3) {
                SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[indice_art_emp[3]] -> indice_texture], NULL, & r_emplacement1);
            } else {
                if (map -> nb_emplacement < 4) {
                    SDL_SetRenderDrawColor(renderer, 56, 62, 66, 255);
                }
                SDL_RenderFillRect(renderer, & r_emplacement1);
            }

            /*
             *
             *AFFICHAGE RELIQUES
             *
             */

            //afficher les carres des artefacts adegauche
            SDL_Rect r_artefactGauche1 = {
                ( * we) / 8,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 0 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactGauche2 = {
                ( * we) / 8,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 1 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactGauche3 = {
                ( * we) / 8,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 2 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactGauche4 = {
                ( * we) / 8,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 3 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactGauche5 = {
                ( * we) / 8,
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 4 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };

            //SDL_RenderFillRect(renderer, &r_artefactGauche);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[0] -> indice_texture], NULL, & r_artefactGauche1);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[1] -> indice_texture], NULL, & r_artefactGauche2);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[2] -> indice_texture], NULL, & r_artefactGauche3);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[3] -> indice_texture], NULL, & r_artefactGauche4);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[4] -> indice_texture], NULL, & r_artefactGauche5);

            //afficher les carres des artefacts de droite
            SDL_Rect r_artefactDroit1 = {
                ( * we) - (( * we) / 8 * 3),
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 0 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactDroit2 = {
                ( * we) - (( * we) / 8 * 3),
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 1 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactDroit3 = {
                ( * we) - (( * we) / 8 * 3),
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 2 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactDroit4 = {
                ( * we) - (( * we) / 8 * 3),
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 3 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };
            SDL_Rect r_artefactDroit5 = {
                ( * we) - (( * we) / 8 * 3),
                r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * 4 + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100,
                ((r_BEcran.y - r_HEcran.h) / 5) - ((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100
            };

            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[5] -> indice_texture], NULL, & r_artefactDroit1);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[6] -> indice_texture], NULL, & r_artefactDroit2);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[7] -> indice_texture], NULL, & r_artefactDroit3);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[8] -> indice_texture], NULL, & r_artefactDroit4);
            SDL_RenderCopy(renderer, map -> tabTexture[map -> listeArtefact[9] -> indice_texture], NULL, & r_artefactDroit5);

            //((*we)-(((*we)-(r_artefactGauche.w+r_artefactGauche.x))/2))-(((r_BEcran.y-r_HEcran.h)/5)-((r_BEcran.y-r_HEcran.h)/5)*10/100)/2 Le X

            //SDL_RenderFillRect(renderer, &r_artefactDroit);

            for (j = 0, k = 5; j < 5 && k < 10; j++, k++) {
                if (map -> listeArtefact[j] -> possession == 0) {
                    couleuractuel = textColorGrisFonce;
                } else {
                    couleuractuel = textColor;
                }
                /*
                 *
                 *NOM DES ARTEFACTS
                 *
                 */

                //afficher le nom des artefacts de gauche
                SDL_Surface * textSurfaceArtG = TTF_RenderText_Solid(font, map -> listeArtefact[j] -> nom, couleuractuel);
                if (!textSurfaceArtG) {
                    fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                    TTF_CloseFont(font);
                    return -1;
                }

                SDL_Texture * textTextureArtG = SDL_CreateTextureFromSurface(renderer, textSurfaceArtG);

                SDL_Rect r_text_ArtG = {
                    ((r_artefactDroit1.x) - ((r_artefactDroit1.x) - (r_artefactGauche1.x + r_artefactGauche1.w)) / 2) - textSurfaceArtG -> w / 2,
                    r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                    textSurfaceArtG -> w,
                    textSurfaceArtG -> h
                };

                SDL_FreeSurface(textSurfaceArtG);
                if (SDL_QueryTexture(textTextureArtG, NULL, NULL, & r_text_ArtG.w, & r_text_ArtG.h) != 0) {
                    printf("Impossible de charger le texte\n");
                    return -1;
                }
                SDL_RenderCopy(renderer, textTextureArtG, NULL, & r_text_ArtG);
                SDL_DestroyTexture(textTextureArtG);

                //afficher le descrptif des artefacts de gauche
                textSurfaceArtG = TTF_RenderText_Solid(font, map -> listeArtefact[j] -> descriptif, couleuractuel);
                if (!textSurfaceArtG) {
                    fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                    TTF_CloseFont(font);
                    return -1;
                }

                textTextureArtG = SDL_CreateTextureFromSurface(renderer, textSurfaceArtG);

                SDL_Rect r_text_ArtGD = {
                    ((r_artefactDroit1.x) - ((r_artefactDroit1.x) - (r_artefactGauche1.x + r_artefactGauche1.w)) / 2) - textSurfaceArtG -> w / 2,
                    (r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2) + r_text_ArtG.h,
                    textSurfaceArtG -> w,
                    textSurfaceArtG -> h
                };

                SDL_FreeSurface(textSurfaceArtG);
                if (SDL_QueryTexture(textTextureArtG, NULL, NULL, & r_text_ArtGD.w, & r_text_ArtGD.h) != 0) {
                    printf("Impossible de charger le texte\n");
                    return -1;
                }
                SDL_RenderCopy(renderer, textTextureArtG, NULL, & r_text_ArtGD);
                SDL_DestroyTexture(textTextureArtG);

                if (map -> listeArtefact[k] -> possession == 0) {
                    couleuractuel = textColorGrisFonce;
                } else {
                    couleuractuel = textColor;
                }

                //afficher le nom des artefacts de droite
                SDL_Surface * textSurfaceArtD = TTF_RenderText_Solid(font, map -> listeArtefact[k] -> nom, couleuractuel);
                if (!textSurfaceArtD) {
                    fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                    TTF_CloseFont(font);
                    return -1;
                }

                SDL_Texture * textTextureArtD = SDL_CreateTextureFromSurface(renderer, textSurfaceArtD);

                SDL_Rect r_text_ArtD = {
                    (( * we) - (( * we) - (r_artefactDroit1.x + r_artefactDroit1.w)) / 2) - textSurfaceArtD -> w / 2,
                    r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2,
                    textSurfaceArtD -> w,
                    textSurfaceArtD -> h
                };

                SDL_FreeSurface(textSurfaceArtD);
                if (SDL_QueryTexture(textTextureArtD, NULL, NULL, & r_text_ArtD.w, & r_text_ArtD.h) != 0) {
                    printf("Impossible de charger le texte\n");
                    return -1;
                }
                SDL_RenderCopy(renderer, textTextureArtD, NULL, & r_text_ArtD);
                SDL_DestroyTexture(textTextureArtD);

                //afficher le descriptif des artefacts de droite
                textSurfaceArtD = TTF_RenderText_Solid(font, map -> listeArtefact[k] -> descriptif, couleuractuel);
                if (!textSurfaceArtD) {
                    fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                    TTF_CloseFont(font);
                    return -1;
                }

                textTextureArtD = SDL_CreateTextureFromSurface(renderer, textSurfaceArtD);

                SDL_Rect r_text_ArtDD = {
                    (( * we) - (( * we) - (r_artefactDroit1.x + r_artefactDroit1.w)) / 2) - textSurfaceArtD -> w / 2,
                    (r_HEcran.h + ((r_BEcran.y - r_HEcran.h) / 5) * j + (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) - (((r_BEcran.y - r_HEcran.h) / 5) * 10 / 100) / 2) + r_text_ArtD.h,
                    textSurfaceArtD -> w,
                    textSurfaceArtD -> h
                };

                SDL_FreeSurface(textSurfaceArtD);
                if (SDL_QueryTexture(textTextureArtD, NULL, NULL, & r_text_ArtDD.w, & r_text_ArtDD.h) != 0) {
                    printf("Impossible de charger le texte\n");
                    return -1;
                }
                SDL_RenderCopy(renderer, textTextureArtD, NULL, & r_text_ArtDD);
                SDL_DestroyTexture(textTextureArtD);

            }

            while (SDL_PollEvent( & event) != 0) {

                if (event.type == SDL_MOUSEBUTTONDOWN) {

                    //pour quitter le jeu
                    if ((r_text_Q.x <= event.button.x) && ((r_text_Q.x + r_text_Q.w) >= event.button.x) && ((r_text_Q.y + r_text_Q.h) >= event.button.y) && (r_text_Q.y <= event.button.y)) {
                        etat = 0;

                    }
                    if ((r_artefactGauche1.x <= event.button.x) && ((r_artefactGauche1.x + r_artefactGauche1.w) >= event.button.x) && ((r_artefactGauche1.y + r_artefactGauche1.h) >= event.button.y) && (r_artefactGauche1.y <= event.button.y) && map -> listeArtefact[0] -> equipe == 0 && map -> listeArtefact[0] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[0] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactGauche2.x <= event.button.x) && ((r_artefactGauche2.x + r_artefactGauche2.w) >= event.button.x) && ((r_artefactGauche2.y + r_artefactGauche2.h) >= event.button.y) && (r_artefactGauche2.y <= event.button.y) && map -> listeArtefact[1] -> equipe == 0 && map -> listeArtefact[1] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[1] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactGauche3.x <= event.button.x) && ((r_artefactGauche3.x + r_artefactGauche3.w) >= event.button.x) && ((r_artefactGauche3.y + r_artefactGauche3.h) >= event.button.y) && (r_artefactGauche3.y <= event.button.y) && map -> listeArtefact[2] -> equipe == 0 && map -> listeArtefact[2] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[2] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactGauche4.x <= event.button.x) && ((r_artefactGauche4.x + r_artefactGauche4.w) >= event.button.x) && ((r_artefactGauche4.y + r_artefactGauche4.h) >= event.button.y) && (r_artefactGauche4.y <= event.button.y) && map -> listeArtefact[3] -> equipe == 0 && map -> listeArtefact[3] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[3] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactGauche5.x <= event.button.x) && ((r_artefactGauche5.x + r_artefactGauche5.w) >= event.button.x) && ((r_artefactGauche5.y + r_artefactGauche5.h) >= event.button.y) && (r_artefactGauche5.y <= event.button.y) && map -> listeArtefact[4] -> equipe == 0 && map -> listeArtefact[4] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[4] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactDroit1.x <= event.button.x) && ((r_artefactDroit1.x + r_artefactDroit1.w) >= event.button.x) && ((r_artefactDroit1.y + r_artefactDroit1.h) >= event.button.y) && (r_artefactDroit1.y <= event.button.y) && map -> listeArtefact[5] -> equipe == 0 && map -> listeArtefact[5] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[5] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactDroit2.x <= event.button.x) && ((r_artefactDroit2.x + r_artefactDroit2.w) >= event.button.x) && ((r_artefactDroit2.y + r_artefactDroit2.h) >= event.button.y) && (r_artefactDroit2.y <= event.button.y) && map -> listeArtefact[6] -> equipe == 0 && map -> listeArtefact[6] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[6] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactDroit3.x <= event.button.x) && ((r_artefactDroit3.x + r_artefactDroit3.w) >= event.button.x) && ((r_artefactDroit3.y + r_artefactDroit3.h) >= event.button.y) && (r_artefactDroit3.y <= event.button.y) && map -> listeArtefact[7] -> equipe == 0 && map -> listeArtefact[7] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[7] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactDroit4.x <= event.button.x) && ((r_artefactDroit4.x + r_artefactDroit4.w) >= event.button.x) && ((r_artefactDroit4.y + r_artefactDroit4.h) >= event.button.y) && (r_artefactDroit4.y <= event.button.y) && map -> listeArtefact[8] -> equipe == 0 && map -> listeArtefact[8] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[8] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_artefactDroit5.x <= event.button.x) && ((r_artefactDroit5.x + r_artefactDroit5.w) >= event.button.x) && ((r_artefactDroit5.y + r_artefactDroit5.h) >= event.button.y) && (r_artefactDroit5.y <= event.button.y) && map -> listeArtefact[9] -> equipe == 0 && map -> listeArtefact[9] -> possession == 1 && nb_artefact_equipe < map -> nb_emplacement) {
                        map -> listeArtefact[9] -> equipe = 1;
                        nb_artefact_equipe++;

                    }
                    if ((r_emplacement1.x <= event.button.x) && ((r_emplacement1.x + r_emplacement1.w) >= event.button.x) && ((r_emplacement1.y + r_emplacement1.h) >= event.button.y) && (r_emplacement1.y <= event.button.y) && map -> nb_emplacement >= 4 && nb_artefact_equipe > 3) {
                        nb_artefact_equipe--;
                        map -> listeArtefact[indice_art_emp[3]] -> equipe = 0;

                    }
                    if ((r_emplacement2.x <= event.button.x) && ((r_emplacement2.x + r_emplacement2.w) >= event.button.x) && ((r_emplacement2.y + r_emplacement2.h) >= event.button.y) && (r_emplacement2.y <= event.button.y) && map -> nb_emplacement >= 3 && nb_artefact_equipe > 2) {
                        nb_artefact_equipe--;
                        map -> listeArtefact[indice_art_emp[2]] -> equipe = 0;

                    }
                    if ((r_emplacement3.x <= event.button.x) && ((r_emplacement3.x + r_emplacement3.w) >= event.button.x) && ((r_emplacement3.y + r_emplacement3.h) >= event.button.y) && (r_emplacement3.y <= event.button.y) && map -> nb_emplacement >= 2 && nb_artefact_equipe > 1) {
                        nb_artefact_equipe--;
                        map -> listeArtefact[indice_art_emp[1]] -> equipe = 0;

                    }
                    if ((r_emplacement4.x <= event.button.x) && ((r_emplacement4.x + r_emplacement4.w) >= event.button.x) && ((r_emplacement4.y + r_emplacement4.h) >= event.button.y) && (r_emplacement4.y <= event.button.y) && map -> nb_emplacement >= 1 && nb_artefact_equipe > 0) {
                        nb_artefact_equipe--;
                        map -> listeArtefact[indice_art_emp[0]] -> equipe = 0;

                    }

                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderCopy(renderer, textTextureQ, NULL, & r_text_Q);
            SDL_RenderCopy(renderer, textTextureT, NULL, & r_text_T);
            SDL_RenderCopy(renderer, textTexture, NULL, & r_text_A);
            SDL_DestroyTexture(textTexture);
            free(texte);

            SDL_RenderPresent(renderer);
            SDL_Delay(100);

        }

        TTF_CloseFont(font);
        font = NULL;
        //destruction des texture
        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureT);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);

    }

    return 0;
}

/*int console_command(SDL_Event event,char * command){
if(command == NULL){
command = malloc(80);
}
if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_j)){
scanf("%s",command);
}
return 0;
}

int console_aff(SDL_Renderer * renderer,int we,int he,char * command){
TTF_Font * police = TTF_OpenFont("fonts/alagard.ttf", 20);
SDL_Color blanc = {255, 255, 255};
if (police == NULL){
TTF_CloseFont(police);
TTF_Quit();
fprintf(stderr,"probleme a l'ouverture de la police\n");
return -1;
}
SDL_Rect r = {0,we-32,he,32};
SDL_SetRenderDrawColor(renderer, 0,0,0,120);
SDL_RenderFillRect(renderer, &r);
SDL_Surface * texte = TTF_RenderText_Solid(police, command, blanc);
if (!texte){
SDL_FreeSurface(texte);
TTF_CloseFont(police);
police = NULL;
TTF_Quit();
printf("probleme de texte\n");
return -1;
}
SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer,texte);
SDL_Rect textRect = {r.x+5, r.y+5, texte->w, texte->h};
if(!text_texture){
printf("Impossible de creeer la texture\n");
TTF_CloseFont(police);
police = NULL;
TTF_Quit();
return -1;
}
SDL_RenderCopy(renderer, text_texture, NULL, &textRect);
return 0;
}*/