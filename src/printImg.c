#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int print_bg(SDL_Window * w,SDL_Renderer* r){
    SDL_Surface* backgroundSurface = IMG_Load("bg.jpeg");
    if (backgroundSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        return -1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(r, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    SDL_Rect destRect = {0, 0, 800, 600};  // Taille de l'écran
    SDL_RenderCopy(r, backgroundTexture, NULL, &destRect);
    SDL_RenderPresent(r);
    return 0;
    /*SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
    return 0;*/
}

void destroyBg(SDL_Texture* bgTexture){
    SDL_DestroyTexture(bgTexture);
}