#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

#include "../libs/Pmov.h"
#include "../libs/texte.h"
#include "../libs/printImg.h"
#include "../libs/save.h"

//nombre de frame par secondes voulu
#define FPS 30

int main(){


    /*Liste *maListe = initialisation();

    insertion(maListe, "test");
    insertion(maListe, "8");
    insertion(maListe, "bonjour");
    suppression(maListe);

    afficherListe(maListe);
    
    destruction(maListe);*/
     
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
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *LEcran, *lEcran, SDL_WINDOW_FULLSCREEN);
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
    //SDL_Texture* backgroundTexture = NULL;

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
	int run = 1;

    SDL_Event event;

    //zone declaration objet
    SDL_Rect obj1 = {100, 200, 288, 288};
    SDL_Rect Ecran = {0,0,*LEcran,*lEcran};
    int dia = 0;

    //boucle du programme
    while (run) {
        //zone d'evenement
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)) {
                run = 0;
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_h)){
                pAlex->e=-1;
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_j)){
                pAlex->e=0;
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_f)){
                dia++;
            }
            pinput(pAlex,event);
            col_p(&obj1,pAlex);
            col_p(&Ecran,pAlex);
            
            
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
        SDL_SetRenderDrawColor(renderer, 50, 0, 50, 255);
        SDL_RenderClear(renderer);

        //affiche le bg
        //print_bg(backgroundTexture,renderer,L_Ecran,l_Ecran);

        // Dessiner un cadre(obj1)
        SDL_SetRenderDrawColor(renderer, 0, 50, 200, 255);
        SDL_RenderDrawRect(renderer, &obj1);

		//Affiche un personnage
        affp(pAlex,renderer);

        //afficher dialogue
        char *mess[2]={"The Last Nightmare","Bonjour"};
        SDL_Color blanc = {255, 255, 255};
        affiche_texte(renderer,mess[dia],900,blanc);

        //affiche les fps
        aff_Fps(cmpfps,renderer);

        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/dfps);
    }

    // Libérer les ressources
    free(nfps);
    free(t0);
    free(t1);
    free(lEcran);
    free(LEcran);
    //SDL_DestroyTexture(backgroundTexture);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
