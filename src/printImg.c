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


#include "../libs/commun.h"



/**
*
*\fn int NB_Fps(int *nfps,Uint32 * t0,Uint32 * t1)
*\param nfps nombre de fps actuelle
*\param t0 debut de la mesure des fps
*\param t1 quand la difference t1-t0 vaut 1s on a fini de mesurer les fps
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
    SDL_Rect textRect = {300, 10, textSurface->w, textSurface->h};

    // Afficher la texture sur le rendu
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    free(texte);
    texte=NULL;
    TTF_CloseFont(font);
    return 0;
}

/**
*
*\fn void ajDFPS(int * dfps,int * cmpfps,int *nfps,Uint32 * t0,Uint32 * t1)
*\param dfps diviseur des fps pour s'approcher de la limite de 60 FPS
*\param cmpfps max de fps en 1s
*\param nfps nombre de fps actuelle
*\param t0 debut de la mesure des fps
*\param t1 quand la difference t1-t0 vaut 1s on a fini de mesurer les fps
*\brief fonction qui ajuste les fps
*/
void ajDFPS(int * dfps,int * cmpfps,int *nfps,Uint32 * t0,Uint32 * t1){
    if(NB_Fps(nfps,t0,t1)){
        *cmpfps = *nfps;
        if(*nfps < FPS){
            (*dfps)++;
        }else if(*nfps >= FPS){
            (*dfps)--;
        }
    }
}

/**
*
*\fn void  affHud(SDL_Renderer * renderer,int * he,int * we,map_t map,p_mv pmv)
*\param renderer rendu SDL
*\param he pointeur sur la longeur de l'écran
*\param we pointeur sur la hauteur de l'écran
*\param map structure map du jeu
*\param pmv personnage jouable
*\brief fonction qui affiche le hud
*/

void  affHud(SDL_Renderer * renderer,int * he,int * we,map_t map,p_mv pmv){
    //Variable PV
    int x = 10;
    int y = -5;
    if(*(pmv.equipe[0]->pv)<0){
        *(pmv.equipe[0]->pv)=0;
    }
    else if (*(pmv.equipe[0]->pv)>pmv.equipe[0]->pvMax){
        *(pmv.equipe[0]->pv)=pmv.equipe[0]->pvMax;
    }
    int p = (144*(*pmv.equipe[0]->pv))/pmv.equipe[0]->pvMax;

    //Variable Night
    int xn = 1000;
    int yn = -5;
    int pn = (144*(*pmv.NightP))/pmv.NightMax;

    SDL_Rect HUD  = {0,0,*we,56};
    SDL_Rect PV_bar= {x,y,256,64};
    SDL_Rect PV_barVide= {x+81,y+19,144,26};
    SDL_Rect PV_barPleine= {x+81,y+19,p,26}; //144 = pleine

    SDL_Rect Night_bar= {xn,yn,256,64};
    SDL_Rect Night_barVide = {xn+81,yn+19,144,26};
    SDL_Rect Night_barPleine= {xn+81,yn+19,pn,26}; //144 = pleine


    //chargement de la police d'écriture
        SDL_Color textColor = {
        0,
        0,
        0};
        TTF_Font * font = TTF_OpenFont("fonts/alagard.ttf", 30);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return ;
        }

        char * texte = malloc(20);
        snprintf(texte, 20, "Niveau Equipe : %d", map . nvEquipe);

        SDL_Surface * textSurface = TTF_RenderText_Blended(font, texte, textColor);
        if (!textSurface) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return ;
        }

        SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_Rect r_text_A = {
                (( * we/6) * 5 )-(textSurface -> w/2),
                HUD.h / 2 - textSurface -> h / 2,
                textSurface -> w,
                textSurface -> h
            };
        SDL_FreeSurface(textSurface);

        if (SDL_QueryTexture(textTexture, NULL, NULL, & r_text_A.w, & r_text_A.h) != 0) {
            printf("Impossible de charger le texte\n");
            return ;

        }
    SDL_RenderCopy(renderer, map.tabTexture[184], NULL, & HUD);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &PV_barVide);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &PV_barPleine);

    SDL_RenderCopy(renderer, map.tabTexture[199], NULL, &PV_bar);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &Night_barVide);

    SDL_SetRenderDrawColor(renderer, 43,27,85,255);
    SDL_RenderFillRect(renderer, &Night_barPleine);

    SDL_RenderCopy(renderer, map.tabTexture[170], NULL, &Night_bar);
    SDL_RenderCopy(renderer, textTexture, NULL, & r_text_A);
            SDL_DestroyTexture(textTexture);




    TTF_CloseFont(font);
    font = NULL;
}
