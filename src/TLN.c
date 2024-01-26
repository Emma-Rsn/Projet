#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>


#include "truc.h"
#include "Pmov.h"



int main(){
     // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Création du rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur de création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

	test();

	point_mv point;
	point = initpoint();
	point_mv * ppoint = &point;
	int run = 1;
    
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                run = 0;
            }
            pinput(ppoint);
        }

        // Ecran en rouge
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Dessiner un cadre
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
        SDL_Rect rect = {100, 100, 100, 100};
        SDL_RenderDrawRect(renderer, &rect);

		//Affiche un point et actualise sa pos
        affp(ppoint,renderer);

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    // Libérer les ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}