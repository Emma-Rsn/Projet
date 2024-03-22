
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

#include "../libs/commun.h"

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
*\fn combatant_t *init_combatant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse)
*\param nom prenom du combatant
*\param pv les pv du combatant
*\param nomATQ1 nom de l'attaque de base du combatant
*\param vitesse vitesse du combatant
*\param nomATQspe nom de l'attaque special du combatant 
*\brief fonction qui creer le combatant 
*/
combatant_t *init_combatant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp){
    combatant_t * combatant=malloc(sizeof(combatant_t));
    combatant->nom=nom;
    combatant->pv=pv;
    combatant->nomATQ1=nomATQ1;
    combatant->nomATQspe=nomATQspe;
    combatant->vitesse=vitesse;
    combatant->mort=0;
    combatant->camp=camp;
    return combatant;
}

/**
*\fn void desctruction_p_eq(p_mv * p)
*\param p strcuture du personnage 
*\brief fonction qui detruit les personnages de l'equipe
*/
/*void desctruction_combatant(combatant_t * combatant,int nb_combatant){
    int i;
    for(i=0;i<nb_combatant;i++){
        free(combatant[i]);
    }
    
}*/


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
int affiche_point(float mult, int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, int nb_point)
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
	sprintf(point, "nombre de point : %d", nb_point);
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
int affiche_pv(combatant_t * ennemi,int *we,int *he,SDL_Renderer * renderer,combatant_t * combatant){

    TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }
    SDL_Color textColor = {255, 255, 255};

    char *texte = malloc(15);
    snprintf(texte, 15, "PV : %d", ennemi->pv);


    char *texte2 = malloc(15);
    snprintf(texte2, 15, "%s PV : %d",combatant->nom ,combatant->pv);

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
int attaque_ennemi(combatant_t *combatantAt,int nb_combatant,int allie,combatant_t *combatant[]){

    //personnage de l'equipe qui va etre attaque
    int perso;
    do{
        perso=(int)1+rand()%(nb_combatant);
        printf("perso attaque : %d\n",perso-1);
        printf("%d\n",combatant[perso-1]->camp);
    }while(((combatant[perso-1]->camp)==1) || (combatant[perso-1]->pv<=0));  //(allie>0)
    

    //enleve des pv au personnages par rapport a ses pv 
    if(combatantAt->pv<=100 && combatantAt->pv>60){
        combatant[perso-1]->pv-=(int)10+rand()%(15+1-10);
    }
    if(combatantAt->pv<=60 && combatantAt->pv>30){
        combatant[perso-1]->pv-=(int)5+rand()%(10+1-5);
    }
    if(combatantAt->pv<=30 && combatantAt->pv>0){
        combatant[perso-1]->pv-=(int)1+rand()%(5+1-1);
    }
    return 0;
}

int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat){
    
    int i=0;
    int j=0;
    //chargement de la police d'écriture
            TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
            if (!font) {
                erreur_sdl("Erreur lors du chargement de la police",NULL,renderer,NULL,NULL);
                return -1;
            }


            SDL_Rect r_basEcran={0,(*he)-(*he)/4,(*we),(*he)/4};
            SDL_Rect r_coteDroitEcran={(*we)/4,(*he)-(*he)/4,(*we),(*he)/4};
            SDL_Color textColor = {255, 255, 255};
            
            //creation du premier texte (Attaque 1)
            SDL_Surface* textSurfaceATQ1 = TTF_RenderText_Solid(font,"Attaque", textColor);
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



            //creation du troisieme texte (Attaque speciale)
            SDL_Surface* textSurfaceATQ3 = TTF_RenderText_Solid(font,"Attaque speciale", textColor);
            if (!textSurfaceATQ3) {
                erreur_sdl("Erreur lors de la création de la surface de texte",NULL,renderer,textTextureATQ1,NULL);
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
            while(combat->ennemi[i]->mort==1){
                    i++;
            }
            while(combat->allie[j]->mort==1){
                    j++;
            }

            //creation texture de l'ennemi
            SDL_Texture * tperso = SDL_CreateTextureFromSurface(renderer, combat->ennemi[i]->po);
            
            //fermeture de le police d'ecriture
            TTF_CloseFont(font);
            font=NULL;

            //creation des rectangles pour l'affichage
            SDL_Rect  r_point= {r_basEcran.w/2-200,(r_basEcran.h/2)+r_basEcran.h+100,textSurfaceATQ3->w,textSurfaceATQ3->h};
            SDL_Rect  r_ennemi= {200,200,200,200};

                //affichage du combat
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer,100,100,100,255);
                SDL_RenderFillRect(renderer, &r_basEcran);

                SDL_RenderCopy(renderer, textTextureATQ1, NULL, &r_ATQ1);
                SDL_RenderCopy(renderer, textTextureATQ3, NULL, &r_ATQ3);

                affiche_point(combat->mult,we,he,renderer,r_basEcran,combat->nb_point);
                affiche_pv(combat->ennemi[i],we,he,renderer,combat->allie[j]);

                SDL_RenderCopy(renderer, tperso, NULL, &r_ennemi);
                SDL_RenderPresent(renderer);
                SDL_Delay(100);
                                        
                                        
                //destruction des textures
                SDL_DestroyTexture(textTextureATQ1);
                SDL_DestroyTexture(textTextureATQ3);
                SDL_DestroyTexture(tperso);
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
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,int *nb_point,combatant_t *combatant,int Nbennemi){
        if(combatant->mort==0){
        
            int jouer=1;
            int nb_point_deb=*nb_point;
            float mult=1;
            int i=0;

            while(jouer){
                while(ennemi->combatant[i]->mort==1){
                        i++;
                }
                while (SDL_PollEvent(&event) != 0 ) {

                        if(event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_a){
                            if(i>=(Nbennemi-1)){
                                i=0;
                                }
                                else{
                                    i++;
                                }
                            }


                        
                    //aff(ennemi->combatant[i]);

                    //enleve des pv au monstre avec les attaques
                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        if((1700<=event.button.x) && (1760>=event.button.x) && ((1010)>=event.button.y) && (1000<=event.button.y)){
                            ennemi->combatant[i]->pv-=10*mult;
                            jouer=0;
                        }
                        else if((1500<=event.button.x) && ((1560)>=event.button.x) && ((1010)>=event.button.y) && (1000<=event.button.y)){
                            ennemi->combatant[i]->pv-=30*mult;
                            jouer=0;
                        }
                        else if((1300<=event.button.x) && ((1360)>=event.button.x) && ((1010)>=event.button.y) && (1000<=event.button.y)){
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

int compare_vitesse(const combatant_t * const combatant1,const combatant_t * const combatant2){

  /*if(combatant1->mort==1){
    return(1);
  }*/
  if( combatant1->vitesse == combatant2->vitesse ) {
    return(0) ; 
  }
  if( combatant1->vitesse > combatant2->vitesse){
    return(-1) ; 
  }  
  return(1) ;   
}

int compare_vitesse_enc( const void * const combatant1 , const void * const combatant2 ) {
    const combatant_t *comb1e = *(const combatant_t**)combatant1;
  const combatant_t *comb2e = *(const combatant_t**)combatant2;
  return compare_vitesse(   comb1e ,comb2e );
}


void aff(combatant_t * combatant){
    if(combatant==NULL){
        printf("vide\n");
    }else{
printf("nom:%s\n",combatant->nom);
printf("pv:%d\n",combatant->pv);

    }
    
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
        int nb_ennemi=0;
        int nb_combatant=0;
        int j;
        int Nennemi=0;

        combat_t * combat=malloc(sizeof(combat_t));

        //compte le nombre d'allie dans l'equipe
        for (i=0;i<4;i++){
            if(pp->equipe[i]!=NULL){
                nb_allie++;
                allie++;
                combat->allie[i]=pp->equipe[i];
            }
        }

        //compte le nombre d'ennemi
        for (i=0;i<4;i++){
            if(ennemi->combatant[i]!=NULL){
                nb_ennemi++;
                Nennemi++;
                combat->ennemi[i]=ennemi->combatant[i];
            }
        }
        
        nb_combatant=nb_allie+nb_ennemi;
        for(i=0;i<8;i++){
            combat->combatant[i]=NULL;
        }

        for(i=0;i<nb_allie;i++){
            combat->combatant[i]=pp->equipe[i];
        }
        for(i=nb_allie,j=0;i<nb_combatant;i++,j++){
            combat->combatant[i]=ennemi->combatant[j];
        }
       
        while(Nennemi>0 && allie>0){
            //trie vitesse

            qsort(combat->combatant,nb_combatant,sizeof(void *),compare_vitesse_enc);

            for(i=0;i<nb_combatant && Nennemi>0 ;i++){
                
                if(combat->combatant[i]->camp==0 && combat->combatant[i]->mort==0){
                    attaque_allie(we,he,event,renderer,ennemi,nb_point,combat->combatant[i],Nennemi);
                }
                
                else if(combat->combatant[i]->camp==1 && combat->combatant[i]->mort==0){
                    attaque_ennemi(combat->combatant[i],nb_combatant,allie,combat->combatant);
                }
                 
                //compte le nombre d'allie dans l'equipe
                for(j=0;j<nb_combatant;j++){
                    //printf("allie av:%d\n",allie);
                    if(combat->combatant[j]->pv<=0 && combat->combatant[j]->mort==0){
                        combat->combatant[j]->mort=1;
                        if(combat->combatant[j]->camp==0){
                            allie--;
                        }
                        if(combat->combatant[j]->camp==1){
                            Nennemi--;
                        }
                    }

                    
                }
                printf("ennemi :%d\n",Nennemi);
                affichage_combat(we,he,renderer,combat);

            }

            SDL_Delay(100);
            if(*nb_point<6){
                (*nb_point)++;
            }
            
        }

        SDL_RenderPresent(renderer);
        ennemi->combat=0;
        free(combat);
    }

    return 0;
}




