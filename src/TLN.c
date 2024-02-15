//
//TLN.c
//Created by Moreau Enzo Rasson Emma Pasquier Lina 
//

/**
*\file TLN.c
*\brief programme principale
*\author Moreau Enzo Rasson Emma Pasquier Lina 
*\date  janvier 2024
*\version 1.0
*
*/






#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../libs/save.h"
#include "../libs/printImg.h"
#include "../libs/Pmov.h"
#include "../libs/texte.h"
#include "../libs/map2.h"
#include "../libs/printImg.h"
#include "../libs/save.h"
#include "../libs/menu.h"
#include "../libs/PNJ.h"
#include "../libs/commun.h"
#include "../libs/combat.h"

//nombre de frame par secondes voulu
#define FPS 30

int main(){
    srand(time(NULL));

    //initialisation variable menu

    int * etat_menu=malloc(sizeof(int));
    int * run=malloc(sizeof(int));
    *run=1;

     
    //resolution de l'ecran
    save_settings();
    int * hEcran = malloc(sizeof(int));
    int * wEcran = malloc(sizeof(int));
    load_settings(wEcran,hEcran);

     // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    // Initialisation de TTF
    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur d'initialisation de TTF : %s\n", SDL_GetError());
        return -1;
    }
    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *wEcran, *hEcran, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
    //mode de transparence
    SDL_BlendMode blend = SDL_BLENDMODE_BLEND;
    SDL_SetRenderDrawBlendMode(renderer, blend);


    //IMG de fond
    //SDL_Texture* backgroundTexture = NULL;
    SDL_Color Blue={0, 204, 203, 255};
    Uint8 br=0;
    Uint8 bg=204;
    Uint8 bb=203;
    Uint8 ba=255;
    SDL_Color Pink={254, 231, 240, 255};
    Uint8 pr=254;
    Uint8 pg=231;
    Uint8 pb=240;
    Uint8 pa=255;
    SDL_Color Green={130, 196, 108, 255};
    Uint8 gr=130;
    Uint8 gg=196;
    Uint8 gb=108;
    Uint8 ga=255;
    
    
    // Initialiser la map
    map_t map=creation_map((*wEcran),(*hEcran));
    //printf("test1\n");
    int ind_map=0;

    /*
    int color_ind,color_ind2;
    for(color_ind=0;color_ind<COLUMNS;color_ind++){
        for(color_ind2=0;color_ind2<ROWS;color_ind2++){
            switch(color_ind){
                case 0 : map.tabMap[color_ind2][color_ind]=color_carte(map.tabMap[color_ind2][color_ind],br,bg,bb,ba);
                case 1 : map.tabMap[color_ind2][color_ind]=color_carte(map.tabMap[color_ind2][color_ind],pr,pg,pb,pa);
                case 2 : map.tabMap[color_ind2][color_ind]=color_carte(map.tabMap[color_ind2][color_ind],gr,gg,gb,ga);
                default : break;
            }
        }
    }  
    */  
   map.tabMap[0][0].r=br;
   map.tabMap[0][0].g=bg;
   map.tabMap[0][0].b=bb;
   map.tabMap[0][0].a=ba;

   map.tabMap[0][1].r=pr;
   map.tabMap[0][1].g=pg;
   map.tabMap[0][1].b=pb;
   map.tabMap[0][1].a=pa;


    //variable FPS
    int cmpfps = 0;
    int dfps = FPS;
    Uint32 * t0 = malloc(sizeof(Uint32));
    Uint32 * t1 = malloc(sizeof(Uint32));
    int * nfps = malloc(sizeof(int));
    *t0 = -1;

    //creation personnage
	p_mv Alex;
	Alex = initp(200,200);
	p_mv * pAlex = &Alex;
    //creation d'un pnj
    pnj_t Alex2;
    Alex2 = init_pnj("Alex2",500, 200,"sprite/alexdial.png", "sprite/alexface2.png",map.tabMap[0][0].grille.tabGrille[14][9]);
    pnj_t * pAlex2 = &Alex2;
    insertion(Alex2.dial, "Bonjour");
    insertion(Alex2.dial, "Test");


    //creation ennemi 

    pnj_t Alex3;
    Alex3 = init_pnj("Alex3",500, 200,"sprite/alexdial.png", "sprite/alexface2.png",map.tabMap[0][0].grille.tabGrille[1][2]);
    pnj_t * pAlex3 = &Alex3;

    //variable indique l'etat du prog

    SDL_Event event;

    //zone declaration objet
    SDL_Rect HUD  = {0,0,*wEcran,56};
    
    SDL_Rect bord = {pAlex2->r.x - 1, pAlex2->r.y - 1,pAlex2->r.w + 2, pAlex2->r.h + 2};

    SDL_Rect bord2 = {pAlex3->r.x - 1, pAlex3->r.y - 1,pAlex3->r.w + 2, pAlex3->r.h + 2};

    SDL_Rect Ecran = {0,0,*hEcran,*wEcran};

    //boucle du programme
    while (*run) {
        //zone d'evenement
        while (SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_h)){
                pAlex->e=-1;
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_j)){
                pAlex->e=0;
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_x)){
                //printf("eee\n");
                
                if(ind_map==0){
                    ind_map=1;
                }
                /*if(ind_map==1){
                    ind_map=2;
                }
                if(ind_map==2){
                    ind_map=3;
                }
                if(ind_map==3){
                    ind_map=0;
                }*/
                //printf("i = %d\n",ind_map);
            }
            
            pinput(pAlex,event);
            col_p(&Ecran,pAlex);

            //menu
            
            menu(wEcran,hEcran,event,renderer,run);
            col_p(&pAlex2->r,pAlex);
            debut_dialogue(event,pAlex2->dial,&bord,pAlex);
            debut_combat(event,pAlex3,&bord2,pAlex);
            col_p(&pAlex3->r,pAlex);
            
        }
        //zone d'affichage
        //ajustement de dfps
        if(NB_Fps(nfps,t0,t1)){
            cmpfps = *nfps;
            if(*nfps < FPS){
                dfps++;
            }else if(*nfps >= FPS){
                dfps--;
            }
        }
        //efface le rendu
        SDL_SetRenderDrawColor(renderer,map.tabMap[0][ind_map].r,map.tabMap[0][ind_map].g,map.tabMap[0][ind_map].b,map.tabMap[0][ind_map].a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 245, 255);
        SDL_RenderFillRect(renderer, &HUD);

        //affiche la grille
        afficher_grille(map.tabMap[0][ind_map].grille,renderer);


		//Affiche un personnage
        affp(pAlex,renderer);

        //Affichage pnj
        aff_pnj(Alex2,renderer);
        aff_pnj(Alex3,renderer);

        //afficher dialogue
        pnj_dialogue (event,pAlex2,renderer,hEcran,wEcran);

        //affiche les fps
        aff_Fps(cmpfps,renderer);

        //Commence une combat
        combat(wEcran,hEcran,event,renderer,pAlex3,pAlex);

    
        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/dfps);
    }

    // Libérer les ressources
    free(nfps);
    free(t0);
    free(t1);
    free(etat_menu);
    free(run);
    

    //SDL_DestroyTexture(backgroundTexture);
    dest_pnj(pAlex2);
    free(wEcran);
    free(hEcran);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
