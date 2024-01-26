#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "../libs/truc.h"
#include "../libs/Pmov.h"
#include "../libs/fenetre.h"



int main(){
	test();
	SDL_Window *window;
	SDL_Renderer *renderer;
	point_mv point;
	point = initpoint();
	point_mv * ppoint = &point;
	int run = 1;
	init_window(window,renderer);
    while (run) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                run = 0;
            }
        }

        // Ecran en rouge
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        /*
        // Dessiner un cadre
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
        SDL_Rect rect = {100, 100, 100, 100};
        SDL_RenderDrawRect(renderer, &rect);

		//Affiche un point et actualise sa pos
		pinput(ppoint);
		affp(ppoint,renderer);
        */

       // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }

    // Libérer les ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}