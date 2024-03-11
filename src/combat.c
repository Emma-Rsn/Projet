
//
//combat.c
//Created by Pasquier Lina 
//

/**
*\file combat.c
*\brief Programme qui s'occupe du combats
*\author Pasquier Lina 
*\date 15 Fevrier 2024
*\version 0.3
*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "../libs/PNJ.h"
#include "../libs/Pmov.h"


/**
*
*\fn int affiche_point(float mult,int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_basEcran,int *nb_point)
*\param message message a donner
*\param fenetre fenetre du jeu
*\param renderer rendu de la fenetre
*\param Texture une texture
*\param Texture2 une deuxieme texture
*\brief fonction qui gere les erreurs de SDL
*/
//fonction qui gere les erreurs de SDL
void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture,SDL_Texture *Texture2){
    SDL_Log("Erreur %s > %s",message,SDL_GetError());
    

    if(Texture2!=NULL){
        SDL_DestroyTexture(Texture2);
    }
    if(Texture!=NULL){
        SDL_DestroyTexture(Texture);
    }
    if(renderer!=NULL){
        SDL_DestroyRenderer(renderer);
    }
    if(fenetre!=NULL){
        SDL_DestroyWindow(fenetre);
    }
    SDL_Quit();
    exit(EXIT_FAILURE);
}



/**
*
*\fn int affiche_point(float mult,int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_basEcran,int *nb_point)
*\param mult multiplicateur de degat
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de la fenetre
*\param r_basEcran rectangle du bas de l'ecran
*\param nb_point nombre de point qu'a la personne
*\brief fonction qui affiche les point de la personnes et le multiplicateur de degat
*/
//fonction qui affiche les point de la personnes et le multiplicateur de degat
int affiche_point(float mult, int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, int *nb_point)
{
	TTF_Font *font = TTF_OpenFont("fonts/alagard.ttf", 50);
	if (!font)
	{
		erreur_sdl( "Erreur lors du chargement de la police \n",NULL,renderer,NULL,NULL);
		return -1;
	}

	SDL_Color textColor = { 255, 255, 255 };

    //creation du texte du multiplicateur
	char *textemult = malloc(sizeof(mult));

	sprintf(textemult, "mult : %.1f", mult);
	SDL_Surface *textSurfacemult = TTF_RenderText_Solid(font, textemult, textColor);

	if (!textSurfacemult)
	{
		erreur_sdl ("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
		TTF_CloseFont(font);
		return -1;
	}

	SDL_Texture *textTexturemult = SDL_CreateTextureFromSurface(renderer, textSurfacemult);

    //creation du texte du nombre de point

	char *point = malloc(sizeof(nb_point));
	sprintf(point, "nombre de point : %d", *nb_point);
	SDL_Surface *textSurfacePoint = TTF_RenderText_Solid(font, point, textColor);
	if (!textSurfacePoint)
	{
		erreur_sdl("Erreur lors de la création de la surface de texte \n",NULL,renderer,textTexturemult,NULL);
		TTF_CloseFont(font);
		return -1;
	}

	SDL_Texture *textTexturePoint = SDL_CreateTextureFromSurface(renderer, textSurfacePoint);

	// Position du texte
	SDL_Rect r_mult = { r_basEcran.w / 2 - 200, (r_basEcran.h / 2) + r_basEcran.h + 100, textSurfacemult->w, textSurfacemult->h
	};

	SDL_Rect r_point = {*we / 2, 10, textSurfacePoint->w, textSurfacePoint->h
	};

	// Afficher la texture sur le rendu
	SDL_RenderCopy(renderer, textTexturemult, NULL, &r_mult);
	SDL_FreeSurface(textSurfacemult);
	SDL_DestroyTexture(textTexturemult);

	SDL_RenderCopy(renderer, textTexturePoint, NULL, &r_point);
	SDL_FreeSurface(textSurfacePoint);
	SDL_DestroyTexture(textTexturePoint);

	free(point);
	point = NULL;
	free(textemult);
	textemult = NULL;
	TTF_CloseFont(font);
	return 0;

}



/**
*
*\fn int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer)
*\param ennemi structure d'un pnj ennemi
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de la fenetre
*\brief fonction qui affiche les pv des personnages et de l'ennemi
*/
//fonction qui affiche les pv des personnages et de l'ennemi
int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer,p_eq * pp){

    TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }
    SDL_Color textColor = {255, 255, 255};

    char *texte = malloc(15);
    snprintf(texte, 15, "PV : %d", ennemi->pv);

    char *texte2 = malloc(15);
    snprintf(texte2, 15, "%s PV : %d",pp->nom ,pp->pv);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font,texte, textColor);
    if (!textSurface) {
        erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Surface* textSurface2 = TTF_RenderText_Blended(font,texte2, textColor);
    if (!textSurface2) {
        erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,textTexture,NULL);
        TTF_CloseFont(font);
        return -1;
    }

    SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);

    // Position du texte
    SDL_Rect textRect2 = {*we-(textSurface2->w), 10, textSurface2->w, textSurface2->h};
    SDL_Rect textRect = {0, 10, textSurface->w, textSurface->h};

    // Afficher la texture sur le rendu
    SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface2);
    SDL_DestroyTexture(textTexture2);
    free(texte);
    free(texte2);
    texte=NULL;
    TTF_CloseFont(font);
    return 0;

}

/**
*
*\fn int attaque_ennemi(pnj_t * ennemi,p_mv * pp)
*\param ennemi structure d'un pnj ennemi
*\param pp structure du pnj jouer
*\brief fonction d'attaque de l'ennemi 
*/
//fonction d'attaque de l'ennemi 
int attaque_ennemi(pnj_t * ennemi,p_mv * p,int nb_allie,int allie){

    //personnage de l'equipe qui va etre a ttaquer
    int perso;
    do{
        perso=(int)1+rand()%(nb_allie+1-1);
        printf("%d\n",perso-1);
    }while(p->equipe[perso-1]->pv<=0 && allie>0);
    

    //enleve des pv au personnages par rapport a ses pv 
    if(ennemi->pv<=100 && ennemi->pv>60){
        p->equipe[perso-1]->pv-=200;
        //(int)10+rand()%(15+1-10);
    }
    if(ennemi->pv<=60 && ennemi->pv>30){
        p->equipe[perso-1]->pv-=(int)5+rand()%(10+1-5);
    }
    if(ennemi->pv<=30 && ennemi->pv>0){
        p->equipe[perso-1]->pv-=(int)1+rand()%(5+1-1);
    }
    return 0;
}

/**
*
*\fn int attaque_ennemi(pnj_t * ennemi,p_mv * pp)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param event evenement
*\param renderer rendu de la fenetre
*\param ennemi structure d'un pnj ennemi
*\param pp structure du pnj jouer
*\param nb_allie nombre de personnage dans l'equipe
*\brief fonction d'attaque des allie 
*/
//fonction d'attaque des allie 
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,p_mv * pp,int nb_allie,int *nb_point,int allie){
            

    int j=0;
    printf("j:%d\n",j);
    for(j=0;(j<nb_allie) && (ennemi->pv>0) && allie>0;j++){
        printf("j2:%d\n",j);
        if(pp->equipe[j]!=NULL){
            printf("pv %d :%d\n",j,pp->equipe[j]->pv);
        
            int jouer=1;
            int nb_point_deb=*nb_point;
            float mult=1;


            //chargement de la police d'écriture
            TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
            if (!font) {
                erreur_sdl("Erreur lors du chargement de la police",NULL,renderer,NULL,NULL);
                return -1;
            }


            SDL_Rect r_basEcran={0,(*he)-(*he)/2,(*we),(*he)/2};
            SDL_Color textColor = {255, 255, 255};
            
            //creation du premier texte (Attaque 1)
            SDL_Surface* textSurfaceATQ1 = TTF_RenderText_Solid(font,pp->equipe[j]->nomATQ1, textColor);
            if (!textSurfaceATQ1) {
                erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
                TTF_CloseFont(font);
                return -1;
            }

            SDL_Texture* textTextureATQ1 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ1);
            SDL_Rect  r_ATQ1= {r_basEcran.w/2+200,(r_basEcran.h/2)+r_basEcran.h-100,textSurfaceATQ1->w,textSurfaceATQ1->h};
            SDL_FreeSurface(textSurfaceATQ1);

                if(SDL_QueryTexture(textTextureATQ1,NULL,NULL,&r_ATQ1.w,&r_ATQ1.h)!=0){
                    erreur_sdl("Impossible de charger le texte",NULL,renderer,textTextureATQ1,NULL);
                    return -1;          
            }


            //creation du deuxieme texte (Attaque 2)
            SDL_Surface* textSurfaceATQ2 = TTF_RenderText_Solid(font,pp->equipe[j]->nomATQ2, textColor);
            if (!textSurfaceATQ2) {
                erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,textTextureATQ1,NULL);
                TTF_CloseFont(font);
                return -1;
            }
            SDL_Texture* textTextureATQ2 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ2);
            SDL_Rect  r_ATQ2= {r_basEcran.w/2-200,(r_basEcran.h/2)+r_basEcran.h-100,textSurfaceATQ2->w,textSurfaceATQ2->h};
            SDL_FreeSurface(textSurfaceATQ2);

                    if(SDL_QueryTexture(textTextureATQ2,NULL,NULL,&r_ATQ2.w,&r_ATQ2.h)!=0){
                    erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,textTextureATQ2,NULL);
                
                    return -1;
            }

            //creation du troisieme texte (Attaque speciale)
            SDL_Surface* textSurfaceATQ3 = TTF_RenderText_Solid(font,pp->equipe[j]->nomATQspe, textColor);
            if (!textSurfaceATQ3) {
                erreur_sdl("Erreur lors de la création de la surface de texte",NULL,renderer,textTextureATQ1,textTextureATQ2);
                TTF_CloseFont(font);
                return -1;
            }
            
            SDL_Texture* textTextureATQ3 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ3);
            SDL_Rect  r_ATQ3= {r_basEcran.w/2+200,(r_basEcran.h/2)+r_basEcran.h+100,textSurfaceATQ3->w,textSurfaceATQ3->h};
            SDL_FreeSurface(textSurfaceATQ3);
            if(SDL_QueryTexture(textTextureATQ3,NULL,NULL,&r_ATQ3.w,&r_ATQ3.h)!=0){
                    erreur_sdl("Impossible de charger le texte",NULL,renderer,textTextureATQ3,NULL);
                    return -1;
            }


            //creation texture de l'ennemi
            SDL_Texture * tperso = SDL_CreateTextureFromSurface(renderer, ennemi->po);
            
            //fermeture de le police d'ecriture
            TTF_CloseFont(font);
            font=NULL;

            //creation des rectangles pour l'affichage
            SDL_Rect  r_point= {r_basEcran.w/2-200,(r_basEcran.h/2)+r_basEcran.h+100,textSurfaceATQ3->w,textSurfaceATQ3->h};
            SDL_Rect  r_ennemi= {200,200,200,200};


            while(jouer){
                while (SDL_PollEvent(&event) != 0 ) {
                    //enleve des pv au monstre avec les attaques
                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        if((r_ATQ1.x<=event.button.x) && ((r_ATQ1.x+r_ATQ1.w)>=event.button.x) && ((r_ATQ1.y+r_ATQ1.h)>=event.button.y) && (r_ATQ1.y<=event.button.y)){
                            ennemi->pv-=10*mult;
                            jouer=0;
                        }
                        else if((r_ATQ2.x<=event.button.x) && ((r_ATQ2.x+r_ATQ2.w)>=event.button.x) && ((r_ATQ2.y+r_ATQ2.h)>=event.button.y) && (r_ATQ2.y<=event.button.y)){
                            ennemi->pv-=20*mult;
                            jouer=0;
                        }  
                        else if((r_ATQ3.x<=event.button.x) && ((r_ATQ3.x+r_ATQ3.w)>=event.button.x) && ((r_ATQ3.y+r_ATQ3.h)>=event.button.y) && (r_ATQ3.y<=event.button.y)){
                            ennemi->pv-=30*mult;
                            jouer=0;
                        }
                        else if((r_point.x<=event.button.x) && ((r_point.x+r_ATQ3.w)>=event.button.x) && ((r_point.y+r_ATQ3.h)>=event.button.y) && (r_point.y<=event.button.y)){
                            if (mult<2.5 && *nb_point>0){
                                mult+=0.5;
                                (*nb_point)--;
                                
                            }
                            else{
                                *nb_point=nb_point_deb;
                                mult=1;
                            }
                            
                        }
                        
                    }
                            
                }

                //affichage du combat
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer,100,100,100,255);
                SDL_RenderFillRect(renderer, &r_basEcran);

                SDL_RenderCopy(renderer, textTextureATQ1, NULL, &r_ATQ1);
                SDL_RenderCopy(renderer, textTextureATQ2, NULL, &r_ATQ2);
                SDL_RenderCopy(renderer, textTextureATQ3, NULL, &r_ATQ3);

                affiche_point(mult,we,he,renderer,r_basEcran,nb_point);
                affiche_pv(ennemi,we,he,renderer,pp->equipe[j]);

                SDL_RenderCopy(renderer, tperso, NULL, &r_ennemi);
                SDL_RenderPresent(renderer);
                SDL_Delay(100);

            }

            //destruction des textures
            SDL_DestroyTexture(textTextureATQ1);
            SDL_DestroyTexture(textTextureATQ2);
            SDL_DestroyTexture(textTextureATQ3);

            SDL_DestroyTexture(tperso);

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);

        }

    }
                
    return 0;

}

/**
*
*\fn int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp)
*\param ennemi structure d'un pnj ennemi
*\param event evenement 
*\param obj_r rectangle 
*\param pp structure du pnj jouer
*\brief fonction qui regarde si on peut lancer un combat
*/

//fonction qui regarde si on peut lancer un combat
int debut_combat(SDL_Event event,pnj_t * ennemi,p_mv * pp){
    
    if( boolcol(ennemi->c,pp) && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_p && ennemi->pv>0){
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
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,p_mv * pp){
    

    if(ennemi->combat){

        int i,point=2,allie=0;
        int *nb_point=&point;
        int nb_allie=0;

        //compte le nombre d'allie dans l'equipe
        for (i=0;i<3;i++){
            if(pp->equipe[i]!=NULL){
                nb_allie++;
                allie++;
            }
        }

        while(ennemi->pv>0 && allie>0){
            attaque_allie(we,he,event,renderer,ennemi,pp,nb_allie,nb_point,allie);
            printf("test\n");
            attaque_ennemi(ennemi,pp,nb_allie,allie);
            SDL_Delay(100);
            if(*nb_point<=6){
                (*nb_point)++;
            }
            //compte le nombre d'allie dans l'equipe
            printf("allie av:%d\n",allie);
            for (i=0;i<nb_allie;i++){
                if( pp->equipe[i]!=NULL ){
                    if(pp->equipe[i]->pv<=0){
                            pp->equipe[i]=NULL;
                        allie--;
                    }
                    
                }
            }
            printf("allie ap:%d\n",allie);

        }

        SDL_RenderPresent(renderer);
        ennemi->combat=0;
    }
    return 0;
}




