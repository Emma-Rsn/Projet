//
//  fenetre.c
//
//  Created by Moreau Enzo on 26/01/2024.
/**
 *  \file fenetre.c
 * \brief Programme qui initialise la fenetre SDL et son rendu
 * \author Enzo Moreau
 * \version 1.0
 * \date 26 janvier 2024
*/




#include <SDL2/SDL.h>

/**
 * \fn int init_window (SDL_Window *window,SDL_Renderer *renderer)
 * \brief Programme qui initialise la fenetre SDL et son rendu
 * \param *window pointeur sur fenetre (type de SDL) *renderer pointeur sur rendu (type de SDL) 
*/
int init_window(SDL_Window *window,SDL_Renderer *renderer){
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Création du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur de création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    return 0;
}