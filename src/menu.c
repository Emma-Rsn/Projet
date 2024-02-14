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
#include "../libs/texte.h"




int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run){

        SDL_RenderClear(renderer);
        Liste *maListe = initialisation();
        insertion(maListe, "Quitter");
        maListe->ec=maListe->premier;

        

        Liste *Liste2 = initialisation();
        insertion(maListe, "continue");
        Liste2->ec=Liste2->premier;

        int *etat2=malloc(sizeof(int));
        *etat2=1;

        SDL_Rect  r_text_C= {10,10,*we,*he};
        SDL_Rect  r_text_Q= {1920/2,1080/2,100,100};

        //r_text_Q.x=*he;
        //r_text_Q.y=we;


        r_text_C.x=((*he-r_text_C.w)/2)+20;
        r_text_C.y=((*we-r_text_C.w)/2)+20;



            if(event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_p){
                int etat=1;

                while(etat){
                    while (SDL_PollEvent(&event) != 0) {

                                        if(event.type == SDL_MOUSEBUTTONDOWN ){
                                            printf("x = %d\n",event.button.x);
                                            printf("y = %d\n",event.button.y);

                                            printf("xre = %d\n",r_text_Q.x);
                                            printf("yre = %d\n",r_text_Q.y);
                                            printf("test2\n");
                                            //pour quitter le jeu
                                            if((r_text_C.x>=event.button.x) && (r_text_C.x<=event.button.x+50) && (r_text_C.y>=event.button.y+50) && (r_text_C.y<=event.button.y)){
                                                printf("test4\n");
                                                free(etat2);
                                                etat=0;
                                                return 0;
                                            }
                                            if((r_text_Q.x<=event.button.x) && (r_text_Q.x+100>=event.button.x) && (r_text_Q.y+100>=event.button.y) && (r_text_Q.y<=event.button.y)){
                                                printf("test5\n");
                                                free(etat2);
                                                etat=0;
                                                *run=0;
                                                return 0;
                                            }  
                                            
                                        }           
                    }
                    
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
                    SDL_RenderDrawRect(renderer, &r_text_Q);
                    affiche_texte(renderer,maListe,*he,*we,etat2,r_text_Q);
                    //affiche_texte(renderer,Liste2,*he,*we,etat2,r_text_C);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
       
                        
                }

        printf("test\n");
        free(etat2);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        }


    return 0;
}