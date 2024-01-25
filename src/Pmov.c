#include <SDL2/SDL.h>




//structure du point
 typedef struct point point_mv;
    struct point{
        //coordonées du point
        int x;
        int y;
        //vitesse du point
        int xV;
        int yV;

    }


point_mv init_point(){
    point_mv p;
    p.x=0;
    p.y=0;
    p.xV=0;
    p.yV=0;
    return p;
}



int point(void){
     // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
// Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_FULLSCREEN);
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


}