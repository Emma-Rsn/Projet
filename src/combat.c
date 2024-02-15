
//
//combat.c
//Created by Pasquier Lina 
//

/**
*\file combat.c
*\brief Programme qui s'occupe des combats
*\author Pasquier Lina 
*\date 15 Fevrier 2024
*\version 0.3
*/


#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "../libs/PNJ.h"


/**
*
*\fn int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer)
*\param ennemi structure d'un pnj ennemi
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de la fenetre
*\brief fonction qui affiche les pv des personnages
*/

//fonction qui affiche les pv des personnages
int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer){

    TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 20);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }
    SDL_Color textColor = {255, 255, 255};

    char *texte = malloc(12);
    snprintf(texte, 12, "PV : %d", ennemi->pv);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font,texte, textColor);
    if (!textSurface) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Position du texte
    SDL_Rect textRect = {*we-200, 10, textSurface->w, textSurface->h};

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
*\fn int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp)
*\param ennemi structure d'un pnj ennemi
*\param event evenement 
*\param obj_r rectangle 
*\param pp structure du pnj jouable
*\brief fonction qui regarde si on peut lancer un combat
*/
//fonction qui regarde si on peut lancer un combat
int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp){
    
    if( boolcolbeta(obj_r,pp) && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_p && ennemi->pv>0){
        ennemi->combat=1;
        
    } 
    return 0;
}

/**
*
*\fn int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp)
*\param ennemi structure d'un pnj ennemi
*\param event evenement 
*\param we Largeur de la fenetre 
*\param he hauteur de la fenetre
*\param renderer rendu de la fenetre
*\brief fonction qui gere le combat avec un ennemi
*/
//fonction qui gere le combat avec un ennemi
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi){

    if(ennemi->combat){
        
        SDL_RenderClear(renderer);


        //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColor = {255, 255, 255};
        char *ATQ1 = "Attaque 1";
        char *ATQ2 ="Attaque 2";
        char *ATQ3 ="Attaque 3";
        
        SDL_Surface* textSurfaceATQ1 = TTF_RenderText_Solid(font,ATQ1, textColor);
        if (!textSurfaceATQ1) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureATQ1 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ1);
        

        SDL_Surface* textSurfaceATQ2 = TTF_RenderText_Solid(font,ATQ2, textColor);
        if (!textSurfaceATQ2) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceATQ1);
            return -1;
        }

        SDL_Texture* textTextureATQ2 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ2);
        

        SDL_Surface* textSurfaceATQ3 = TTF_RenderText_Solid(font,ATQ3, textColor);
        if (!textSurfaceATQ3) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceATQ1);
            SDL_FreeSurface(textSurfaceATQ2);
            return -1;
        }
        
        SDL_Texture* textTextureATQ3 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ3);
        SDL_Texture * tperso = SDL_CreateTextureFromSurface(renderer, ennemi->po);

        TTF_CloseFont(font);
        font=NULL;

        SDL_Rect r_basEcran={0,(*he)-(*he)/2,(*we),(*he)/2};

        SDL_Rect  r_ATQ1= {r_basEcran.w/2+200,(r_basEcran.h/2)+r_basEcran.h-100,textSurfaceATQ1->w,textSurfaceATQ1->h};
        SDL_Rect  r_ATQ2= {r_basEcran.w/2-200,(r_basEcran.h/2)+r_basEcran.h-100,textSurfaceATQ2->w,textSurfaceATQ2->h};
        SDL_Rect  r_ATQ3= {r_basEcran.w/2+200,(r_basEcran.h/2)+r_basEcran.h+100,textSurfaceATQ3->w,textSurfaceATQ3->h};
        SDL_Rect  r_ennemi= {200,200,200,200};

        SDL_FreeSurface(textSurfaceATQ1);
        SDL_FreeSurface(textSurfaceATQ2);
        SDL_FreeSurface(textSurfaceATQ3);


        if(SDL_QueryTexture(textTextureATQ1,NULL,NULL,&r_ATQ1.w,&r_ATQ1.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureATQ2,NULL,NULL,&r_ATQ2.w,&r_ATQ2.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }

         if(SDL_QueryTexture(textTextureATQ3,NULL,NULL,&r_ATQ3.w,&r_ATQ3.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }

        
        while(ennemi->pv>0){

            while (SDL_PollEvent(&event) != 0 ) {

                if(event.type == SDL_MOUSEBUTTONDOWN ){

                    //pour continuer le jeu
                    if((r_ATQ1.x<=event.button.x) && ((r_ATQ1.x+r_ATQ1.w)>=event.button.x) && ((r_ATQ1.y+r_ATQ1.h)>=event.button.y) && (r_ATQ1.y<=event.button.y)){
                        ennemi->pv-=10;
                    }
                    //pour quitter le jeu
                    else if((r_ATQ2.x<=event.button.x) && ((r_ATQ2.x+r_ATQ2.w)>=event.button.x) && ((r_ATQ2.y+r_ATQ2.h)>=event.button.y) && (r_ATQ2.y<=event.button.y)){
                        ennemi->pv-=20;
                    }  
                    else if((r_ATQ3.x<=event.button.x) && ((r_ATQ3.x+r_ATQ3.w)>=event.button.x) && ((r_ATQ3.y+r_ATQ3.h)>=event.button.y) && (r_ATQ3.y<=event.button.y)){
                        ennemi->pv-=30;
                    }
  
                                            
                             
                }
            
                        
            }

            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer,100,100,100,255);
            SDL_RenderFillRect(renderer, &r_basEcran);

            SDL_RenderCopy(renderer, textTextureATQ1, NULL, &r_ATQ1);
            SDL_RenderCopy(renderer, textTextureATQ2, NULL, &r_ATQ2);
            SDL_RenderCopy(renderer, textTextureATQ3, NULL, &r_ATQ3);
            affiche_pv(ennemi,we,he,renderer);

            
            SDL_RenderCopy(renderer, tperso, NULL, &r_ennemi);

            SDL_RenderPresent(renderer);
            SDL_Delay(100);


        
        }
        SDL_DestroyTexture(textTextureATQ1);
        SDL_DestroyTexture(textTextureATQ2);
        SDL_DestroyTexture(textTextureATQ3);
        SDL_DestroyTexture(tperso);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        ennemi->combat=0;



    
    }
    return 0;
}

