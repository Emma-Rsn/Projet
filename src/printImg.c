//
//printImg.c
//Created by Moreau Enzo
//

/**
*\file printImg.c
*\brief programme pour afficher les FPS et le background
*\author Moreau Enzo
*\date  Janvier 2024
*\version 1.0
*
*/


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
*
*\fn int print_bg(SDL_Texture* backgroundTexture,SDL_Renderer* r,int LE, int lE)
*\param backgroundTexture texture 
*\param r rendu de la fenetre
*\param LE Longueur de l'ecran
*\param lE Largeur de l'ecran
*\brief fonction pour afficher le background
*
*/

//fonction pour afficher le background
int print_bg(SDL_Texture* backgroundTexture,SDL_Renderer* r,int LE, int lE){
    SDL_Rect destRect = {0, 0, LE, lE};  // Taille de l'écran
    SDL_Surface* backgroundSurface = IMG_Load("bg.jpeg");
    if (backgroundSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        return -1;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(r, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    SDL_RenderCopy(r, backgroundTexture, NULL, &destRect);
    return 0;
}

/**
*
*\fn int NB_Fps(int *nfps,Uint32 * t0,Uint32 * t1)
*\param nfps ?
*\param t0 ?
*\param t1 ?
*\brief fonction pour calculer le nombre de FPS 
*
*/



//fonction pour calculer le nombre de FPS 
int NB_Fps(int *nfps,Uint32 * t0,Uint32 * t1){
    if(*(t0) == -1){
        *(t0) = SDL_GetTicks();
        *(nfps) = 0;
    }else{
        *(t1) = SDL_GetTicks();
        *(nfps)=*(nfps)+1;
        if((*(t1) - *(t0)) >= 1000){
            *(t0) = -1;
            return 1;
        }
    }
    return 0;
}

/**
*
*\fn int aff_Fps(int cmpfps,SDL_Renderer *renderer)
*\param cmpfps nombre de FPS
*\param renderer rendu de la fenetre
*\brief fonction pour afficher le nombre de FPS 
*
*/



//fonction pour afficher le nombre de FPS 

//optimiser le chargement du font
int aff_Fps(int cmpfps,SDL_Renderer *renderer){
    //chargement de la police d'écriture
    TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 20);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColor = {0, 0, 0};
    char *texte = malloc(12);
    snprintf(texte, 12, "FPS : %d", cmpfps);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font,texte, textColor);
    if (!textSurface) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Position du texte
    SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};

    // Afficher la texture sur le rendu
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    free(texte);
    texte=NULL;
    TTF_CloseFont(font);
    return 0;
}
