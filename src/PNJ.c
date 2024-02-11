#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../libs/texte.h"
#include "../libs/printImg.h"
#include "../libs/PNJ.h"

pnj_t init_pnj(char * nom,int x, int y,char * emp_po, char * emp_perso){
    pnj_t pnj;
    pnj.nom = malloc(strlen(nom));
    strcpy(pnj.nom,nom);
    pnj.r.x = x;
    pnj.r.y = y;
    pnj.r.w = 64;
    pnj.r.h = 64;
    pnj.dial = initialisation();
    pnj.po = IMG_Load(emp_po);
    pnj.perso = IMG_Load(emp_perso);
    return pnj;
}

void aff_pnj(pnj_t pnj, SDL_Renderer *renderer){
    SDL_Texture * tperso = SDL_CreateTextureFromSurface(renderer, pnj.perso);
    SDL_RenderCopy(renderer, tperso, NULL, &(pnj.r));
    SDL_DestroyTexture(tperso);
}

void debut_dialogue(SDL_Event event,Liste * liste){
    if(1) dialogue (event,liste);
}

void pnj_dialogue (SDL_Event event,pnj_t * pnj,SDL_Renderer * renderer,int * he,int * we){
    SDL_Texture * targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, *we, *he);
    SDL_RenderCopy(renderer, targetTexture, NULL, NULL);

    while(pnj->dial->etat < 2){
        while (SDL_PollEvent(&event) != 0) {
            dialogue (event,pnj->dial);
        }
        int aff_boite_dia(SDL_Renderer * rendu,Liste *liste,SDL_Surface * po,int le,int LE);
    }
}

void dest_pnj(pnj_t * pnj){
    free(pnj->nom);
    liste_destruction(pnj->dial);
    SDL_FreeSurface(pnj->perso);
    SDL_FreeSurface(pnj->po);
}