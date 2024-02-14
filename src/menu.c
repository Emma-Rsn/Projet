//
//menu.c
//Created by Moreau Enzo
//

/**
*\file menu.c
*\brief programme pour afficher le menu
*\author Moreau Enzo Pasquier Lina
*\date  Janvier 2024
*\version 
*
*/


#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "../libs/texte.h"


/**
*\fn int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run)
*\param we Largeur de l'ecran
*\param he Longueur de l'ecran
*\param event permet de savoir si il y a un evenement
*\param renderer rendu de la fenetre
*\param run pointeur pour continuer le programme
*\brief fonction qui affiche et gere les texte cliquable du menu 
*/

//fonction qui affiche et gere les texte cliquable du menu 
int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run){

        SDL_RenderClear(renderer);


        //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColor = {255, 255, 255};
        char *Quit = "Quitter";
        char *Cont ="Continuer";
        char *Titre ="The Last Nightmare";
        
        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,Quit, textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);
        SDL_FreeSurface(textSurfaceQ);

        SDL_Surface* textSurfaceC = TTF_RenderText_Solid(font,Cont, textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture* textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);
        SDL_FreeSurface(textSurfaceC);

        SDL_Surface* textSurfaceT = TTF_RenderText_Solid(font,Titre, textColor);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }
        
        SDL_Texture* textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);
        SDL_FreeSurface(textSurfaceT);

        TTF_CloseFont(font);
        font=NULL;

        
        
        
        
        
        

        SDL_Rect  r_text_C= {((*we)/2)-(textSurfaceC->w)/2,(*he)/2,textSurfaceC->w,textSurfaceC->h};
        SDL_Rect  r_text_Q= {((*we)/2)-(textSurfaceQ->w)/2,(*he)/2+200,textSurfaceQ->w,textSurfaceQ->h};
        SDL_Rect  r_text_T= {((*we)/2)-(textSurfaceT->w)/2,10,textSurfaceT->w,textSurfaceT->h};

        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureC,NULL,NULL,&r_text_C.w,&r_text_C.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }

         if(SDL_QueryTexture(textTextureT,NULL,NULL,&r_text_T.w,&r_text_T.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }

        
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE){
            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        //pour continuer le jeu
                        if((r_text_C.x<=event.button.x) && ((r_text_C.x+100)>=event.button.x) && ((r_text_C.y+100)>=event.button.y) && (r_text_C.y<=event.button.y)){
                            etat=0;
                        }
                        //pour quitter le jeu
                        else if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+100)>=event.button.x) && ((r_text_Q.y+100)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            *run=0;
                        }  
                                            
                    }           
                }
        
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, &r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, &r_text_T);

            SDL_SetRenderDrawColor(renderer,0,0,255,255);

            SDL_RenderPresent(renderer);

            
       
                        
            }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        
        }



    return 0;
}