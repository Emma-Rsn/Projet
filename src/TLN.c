#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#include "../libs/truc.h"
#include "../libs/Pmov.h"
#include "../libs/texte.h"
#include "../libs/printImg.h"
#include "../libs/texte.h"

int main(){


     // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    
    int dim=480;
    
    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, dim, SDL_WINDOW_SHOWN);
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
            dialogue(renderer,dim);
            
            pinput(ppoint);
        }

        // Affiche le fond d'ecran
        //print_bg(window,renderer);
        
        // Dessiner un cadre
        SDL_SetRenderDrawColor(renderer, 0, 50, 200, 255);
        SDL_Rect rect = {300, 200, 100, 100};
        SDL_RenderDrawRect(renderer, &rect);

        //test collision
        if(ppoint->x >= 300 && ppoint->x <= 400 && ppoint->y == 200){
            ppoint->x -= 1;
        }if(ppoint->y >= 200 && ppoint->y <= 300 && ppoint->x == 300){
            ppoint->y -= 1;
        }if(ppoint->x >= 300 && ppoint->x <= 400 && ppoint->y == 300){
            ppoint->x -= 1;
        }if(ppoint->y >= 200 && ppoint->y <= 300 && ppoint->x == 400){
            ppoint->y -= 1;
        }
        //fin test collision

		//Affiche un point
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
