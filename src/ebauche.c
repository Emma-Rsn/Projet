#include <SDL2/SDL.h>

int ebauche(void) {
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

    // Boucle principale
    SDL_Event event;
    int running = 1;
    int isPointRed = 0;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    isPointRed = !isPointRed; // Inverser la couleur du point
                }
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 10, 20, 100, 255);
        SDL_RenderClear(renderer);

        // Dessiner un cadre
        SDL_SetRenderDrawColor(renderer, 0, 50, 0, 255);
        SDL_Rect rect = {100, 100, 440, 280};
        SDL_RenderDrawRect(renderer, &rect);

        // Dessiner un point noir ou rouge au centre
        SDL_SetRenderDrawColor(renderer, isPointRed ? 255 : 0, 50, 0, 255);
        SDL_RenderDrawPoint(renderer, 320, 240);

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }

    // Libérer les ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
