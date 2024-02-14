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

#include "../libs/Pmov.h"
#include "../libs/texte.h"
#include "../libs/map.h"
#include "../libs/printImg.h"
#include "../libs/save.h"
#include "../libs/menu.h"

//nombre de frame par secondes voulu
#define FPS 30

int main(){

    //creation liste chaine des dialogues
    Liste *maListe = initialisation();

    insertion(maListe, "The last Nightmare");
    insertion(maListe, "Test");
    insertion(maListe, "bonjour");

    maListe->ec=maListe->premier;
    int * etat = malloc(sizeof(int));
    SDL_Rect r_text={10,10,0,0};

    //initialisation variable menu

    int * etat_menu=malloc(sizeof(int));
    int * run=malloc(sizeof(int));
    *run=1;

     
    //resolution de l'ecran
    save_settings();
    int * lEcran = malloc(sizeof(int));
    int * LEcran = malloc(sizeof(int));
    load_settings(LEcran,lEcran);


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
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *LEcran, *lEcran, SDL_WINDOW_FULLSCREEN_DESKTOP);
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
    
    //IMG de fond
   /* //SDL_Texture* backgroundTexture = NULL;
    SDL_Color Blue={0, 204, 203, 255};
    SDL_Color Pink={254, 231, 240, 255};
    SDL_Color Green={130, 196, 108, 255};

    //création map
    carte_t * p_map;
    carte_t map[ROW][COLUMN];
    creation_matrice(map);
    p_map=&(map[0][0]);
    lien_carte(map);
    int color_ind,color_ind2;
    for(color_ind=0;color_ind<COLUMN;color_ind++){
        for(color_ind2=0;color_ind2<ROW;color_ind2++){
            switch(color_ind){
                case 0 : color_carte(&(map[color_ind2][color_ind]),Blue);
                case 1 : color_carte(&(map[color_ind2][color_ind]),Pink);
                case 2 : color_carte(&(map[color_ind2][color_ind]),Green);
                default : break;
            }
        }
    }*/


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
    //variable indique l'etat du prog

    SDL_Event event;

    //zone declaration objet
    SDL_Rect obj1 = {100, 200, 288, 288};

    SDL_Rect Ecran = {0,0,*LEcran,*lEcran};

   

   


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
            /*if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_k)){
                p_map=p_map->est;
            }*/
            
            pinput(pAlex,event);
            col_p(&obj1,pAlex);
            col_p(&Ecran,pAlex);
            dialogue(event,etat,maListe);

            //menu
            menu(LEcran,lEcran,event,renderer,run);
            
            
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
        //SDL_SetRenderDrawColor(renderer,p_map->bgColor.r,p_map->bgColor.g,p_map->bgColor.b,p_map->bgColor.a);
        SDL_RenderClear(renderer);

        //affiche le bg
        //print_bg(backgroundTexture,renderer,L_Ecran,l_Ecran);

        // Dessiner un cadre(obj1)
        SDL_SetRenderDrawColor(renderer, 0, 50, 200, 255);
        SDL_RenderDrawRect(renderer, &obj1);

		//Affiche un personnage
        affp(pAlex,renderer);

        //afficher dialogue

        affiche_texte(renderer,maListe,900,900,etat,r_text);

        //affiche les fps
        aff_Fps(cmpfps,renderer);

        

        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/dfps);
    }

    // Libérer les ressources
    //destroy_map(map);
    free(nfps);
    free(t0);
    free(t1);
    liste_destruction(maListe);
    free(etat);
    free(etat_menu);
    free(run);
    

    free(lEcran);
    free(LEcran);
    //SDL_DestroyTexture(backgroundTexture);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
