
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
*\fn combattant_t *init_combattant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse)
*\param nom prenom du combattant
*\param pv les pv du combattant
*\param nomATQ1 nom de l'attaque de base du combattant
*\param vitesse vitesse du combattant
*\param nomATQspe nom de l'attaque special du combattant 
*\param camp comp du personnage (1=ennemi,0=allie)
*\param portrait acces du portrait du combattant
*\brief fonction qui creer le combattant 
*/
combattant_t *init_combattant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp,char * portrait){
    combattant_t * combattant=malloc(sizeof(combattant_t));
    combattant->nom=nom;
    combattant->pv=pv;
    combattant->nomATQ1=nomATQ1;
    combattant->nomATQspe=nomATQspe;
    combattant->vitesse=vitesse;
    combattant->mort=0;
    combattant->camp=camp;
    combattant->po=IMG_Load(portrait);
    return combattant;
}

/**
*\fn void desctruction_p_eq(p_mv * p)
*\param combattant strcuture du combattant 
*\brief fonction qui detruit les personnages de l'equipe
*/
void desctruction_combattant(combattant_t * combattant){
    SDL_FreeSurface(combattant->po);  
    free(combattant);
}

/**
*\fn void desctruction_p_eq(p_mv * p)
*\param combattant strcuture du combattant 
*\brief fonction qui detruit les personnages de l'equipe
*/
void desctruction_combat(combat_t * combat){

    int i;
    for(i=0;i<combat->nb_allie;i++){
        combat->allie[i]=NULL;
    }
    for(i=0;i<combat->nb_ennemi;i++){
        combat->ennemi[i]=NULL;
    }
    for(i=0;i<combat->nb_ennemi+combat->nb_allie;i++){
        combat->combattant[i]=NULL;
    }
    free(combat);

}




/**
*
*\fn int affiche_point(int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, combat_t * combat)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de la fenetre
*\param r_basEcran rectangle du bas de l'ecran
*\param combat structure combat
*\brief fonction qui affiche les point de la personnes et le multiplicateur de degat
*/
//fonction qui affiche les point de la personnes et le multiplicateur de degat
int affiche_point(int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, combat_t * combat)
{
	TTF_Font *font = TTF_OpenFont("fonts/alagard.ttf", 50);
	if (!font)
	{
		erreur_sdl( "Erreur lors du chargement de la police \n",NULL,renderer,NULL,NULL);
		return -1;
	}

	SDL_Color textColor = { 255, 255, 255 };

    //creation du texte du multiplicateur
	char *textemult = malloc(20);
	sprintf(textemult, "mult : %.1f", combat->mult);
	SDL_Surface *textSurfacemult = TTF_RenderText_Solid(font, textemult, textColor);

	if (!textSurfacemult)
	{
		erreur_sdl ("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
		TTF_CloseFont(font);
		return -1;
	}

	SDL_Texture *textTexturemult = SDL_CreateTextureFromSurface(renderer, textSurfacemult);

    //creation du texte du nombre de point

	char *point = malloc(20);
	sprintf(point, "nombre de point : %d", combat->nb_point);
	SDL_Surface *textSurfacePoint = TTF_RenderText_Solid(font, point, textColor);
	if (!textSurfacePoint)
	{
		erreur_sdl("Erreur lors de la création de la surface de texte \n",NULL,renderer,textTexturemult,NULL);
		TTF_CloseFont(font);
		return -1;
	}

	SDL_Texture *textTexturePoint = SDL_CreateTextureFromSurface(renderer, textSurfacePoint);

	// Position du texte
	SDL_Rect r_mult = { 50, (r_basEcran.h*3)+r_basEcran.h/2+50, textSurfacemult->w, textSurfacemult->h
	};

	SDL_Rect r_point = {25, (r_basEcran.h*3)+r_basEcran.h/2-50, textSurfacePoint->w, textSurfacePoint->h
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
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de la fenetre
*\param r_GEcran renctangle gauche de l'ecran
*\param r_DEcran renctangle droit de l'ecran
*\param combat structure combat
*\brief fonction qui affiche les allies et les ennemis sue les cotes
*/
//fonction qui affiche les allies et les ennemis sue les cotes
int affiche_pv(int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_GEcran,SDL_Rect r_DEcran,combat_t *combat){
    int i=0;

    TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return -1;
    }
    SDL_Color textColorvivant = {255, 255, 255};
    SDL_Color textColormort = {200, 200, 200};
    SDL_Color couleuractuel=textColorvivant;

    /*
    *
    *AFFICHAGE ENNEMI
    *
    */

    for(i=0;i<combat->nb_ennemi;i++){
        if(combat->ennemi[i]->mort==1){
             couleuractuel=textColormort;
        }
        else{
             couleuractuel=textColorvivant;
        }

        SDL_Surface* textSurface = TTF_RenderText_Blended(font,combat->ennemi[i]->nom, couleuractuel);
        if (!textSurface) {
            erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
            TTF_CloseFont(font);
        return -1;

        }
        
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {10, r_GEcran.y+i*(r_GEcran.h/4), textSurface->w, textSurface->h};
        if(strcmp(combat->ennemi[i]->nom,combat->combattant[combat->indice_combattant]->nom)==0 && combat->combattant[combat->indice_combattant]->mort==0){
            textRect.x = (r_GEcran.x+(100));
        }
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    /*
    *
    *AFFICHAGE ALLIE
    *
    */

    for(i=0;i<combat->nb_allie;i++){

        if(combat->allie[i]->mort==1){
             couleuractuel=textColormort;
        }
        else{
             couleuractuel=textColorvivant;
        }

        SDL_Surface* textSurface = TTF_RenderText_Blended(font,combat->allie[i]->nom, couleuractuel);
        if (!textSurface) {
            erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
            TTF_CloseFont(font);
        return -1;

        
        }
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {r_DEcran.x, r_DEcran.y+i*(r_GEcran.h/4), textSurface->w, textSurface->h};
        if(strcmp(combat->allie[i]->nom,combat->combattant[combat->indice_combattant]->nom)==0 && combat->combattant[combat->indice_combattant]->mort==0){
            textRect.x = (r_DEcran.x+(r_DEcran.w/50));
        }


        

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        

        

    }

    TTF_CloseFont(font);
    return 0;

}

/**
*
*\fn int attaque_ennemi(combattant_t *combattantAt,int nb_combattant,combattant_t *combattant[])
*\param combattantAt structure combattant du personnage qui attaque
*\param nb_combattant nombre de combattant 
*\param combattant tableau de structure de combattant pour avoir les allies
*\brief fonction d'attaque de l'ennemi 
*/
//fonction d'attaque de l'ennemi 
int attaque_ennemi(combattant_t *combattantAt,int nb_combattant,combattant_t *combattant[]){

    //personnage de l'equipe qui va etre attaque
    int perso;
    do{
        perso=(int)1+rand()%(nb_combattant);

    }while(((combattant[perso-1]->camp)==1) || (combattant[perso-1]->pv<=0));  
    

    //enleve des pv au personnages par rapport a ses pv 
    if(combattantAt->pv<=100 && combattantAt->pv>60){
        combattant[perso-1]->pv-=(int)10+rand()%(15+1-10);
    }
    if(combattantAt->pv<=60 && combattantAt->pv>30){
        combattant[perso-1]->pv-=(int)5+rand()%(10+1-5);
    }
    if(combattantAt->pv<=30 && combattantAt->pv>0){
        combattant[perso-1]->pv-=(int)1+rand()%(5+1-1);
    }
    return 0;
}

/**
*
*\fn int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de l'ecran
*\param combat structure de combat
*\brief fonction d'affichage du combat
*/
//fonction d'affichage du combat

int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat){
    
    int j=0;
    //chargement de la police d'écriture
            TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
            if (!font) {
                erreur_sdl("Erreur lors du chargement de la police",NULL,renderer,NULL,NULL);
                return -1;
            }

            /*
            *
            *  BAS DE L'ECRAN
            *
            */

            SDL_Rect r_basEcran={0,(*he)-(*he)/4,(*we),(*he)/4};
            SDL_Color textColor = {255, 255, 255};
            
            //creation du premier texte (Attaque)
            SDL_Surface* textSurfaceATQ1 = TTF_RenderText_Solid(font,"Attaque", textColor);
            if (!textSurfaceATQ1) {
                erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
                TTF_CloseFont(font);
                return -1;
            }

            SDL_Texture* textTextureATQ1 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ1);
            SDL_Rect  r_ATQ1= {(r_basEcran.w*40/100),(r_basEcran.h*3)+r_basEcran.h/2,textSurfaceATQ1->w,textSurfaceATQ1->h};
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
            SDL_Rect  r_ATQ3= {(r_basEcran.w*40/100)+(r_basEcran.w*30/100),(r_basEcran.h*3)+r_basEcran.h/2,textSurfaceATQ3->w,textSurfaceATQ3->h};
            SDL_FreeSurface(textSurfaceATQ3);
            if(SDL_QueryTexture(textTextureATQ3,NULL,NULL,&r_ATQ3.w,&r_ATQ3.h)!=0){
                    erreur_sdl("Impossible de charger le texte",NULL,renderer,textTextureATQ3,NULL);
                    return -1;
            }


            /*
            *
            *ECRAN HAUT
            *
            */

            SDL_Rect  r_hautEcran= {0,0,(*we),56};

            //Nom du personnage selectionne
            SDL_Surface* NomSurface = TTF_RenderText_Blended(font,combat->ennemi[combat->indice_ennemi]->nom, textColor);
            if (!NomSurface) {
                erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
                TTF_CloseFont(font);
            return -1;

            
            }
            SDL_Texture* NomTexture = SDL_CreateTextureFromSurface(renderer, NomSurface);
            SDL_Rect NomRect = {r_hautEcran.w/2-NomSurface->w/2, r_hautEcran.y/2+NomSurface->h/4, NomSurface->w, NomSurface->h};
            SDL_FreeSurface(NomSurface);

            //numero du tour 
            char *NumTour = malloc(12);
            snprintf(NumTour, 12, "Tour : %d", combat->num_tour);

            SDL_Surface* NumTourSurface = TTF_RenderText_Blended(font,NumTour, textColor);
            if (!NumTourSurface) {
                erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
                TTF_CloseFont(font);
            return -1;

            
            }
            SDL_Texture* NumTourTexture = SDL_CreateTextureFromSurface(renderer, NumTourSurface);
            SDL_Rect NumTourRect = {(r_hautEcran.w/4)*3+NumTourSurface->w, r_hautEcran.y/2+NumTourSurface->h/4, NumTourSurface->w, NumTourSurface->h};
            SDL_FreeSurface(NumTourSurface);


            /*
            *
            *ECRAN GAUCHE
            *
            */

            SDL_Rect r_GEcran={0,r_hautEcran.h,(*we)/4,r_basEcran.y};


           /*
            *
            *ECRAN DROIT
            *
            */
            SDL_Rect r_DEcran={(*we)-(*we)/4,r_hautEcran.h,(*we),r_basEcran.y};


            /*
            *
            *AFFICHAGE ENNEMI
            *
            */

            while(combat->allie[j]->mort==1){
                    j++;
            }

            //creation texture de l'ennemi
            SDL_Texture * tperso = SDL_CreateTextureFromSurface(renderer, combat->ennemi[combat->indice_ennemi]->po);
            
            //creation des rectangles pour l'affichage
            SDL_Rect  r_ennemi= {r_GEcran.w+((r_DEcran.x-r_GEcran.w)/2)-300,r_basEcran.y-600,600,600};

           
            /*
            *
            *AFFICHAGE TOUR
            *
            */
            int i,nbMort=0;
            int nb_combattant=combat->nb_allie+combat->nb_ennemi;
            for(j=0;j<(nb_combattant);j++){
                    if(combat->combattant[j]->pv<=0){
                        nbMort++;
                        

                    }
                    
                }

            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,0,150,0,255);
            if((nb_combattant-nbMort)%2==0){

                for(i=0;i<nb_combattant-nbMort;i++){
                    SDL_Rect r1= {r_GEcran.w+((r_DEcran.x-r_GEcran.w)/8)*i+(((r_DEcran.x-r_GEcran.w)/8))*((combat->nb_allie+combat->nb_ennemi)/2),r_hautEcran.h,(r_DEcran.x-r_GEcran.w)/8,100};
                    SDL_RenderDrawRect(renderer, &r1);
                }

            }else{
                for(i=0;i<nb_combattant-nbMort;i++){
                    SDL_Rect r1= {r_GEcran.w+((r_DEcran.x-r_GEcran.w)/8)*i+(((r_DEcran.x-r_GEcran.w)/8))*((combat->nb_allie+combat->nb_ennemi)/2)-(((r_DEcran.x-r_GEcran.w)/8)/2),r_hautEcran.h,(r_DEcran.x-r_GEcran.w)/8,100};
                    SDL_RenderDrawRect(renderer, &r1);
                }

            }






            //fermeture de le police d'ecriture
            TTF_CloseFont(font);
            font=NULL;

                //affichage du combat
                SDL_SetRenderDrawColor(renderer,0,0,0,255);



                SDL_SetRenderDrawColor(renderer,150,150,150,255);
                SDL_RenderFillRect(renderer, &r_GEcran);
                SDL_RenderFillRect(renderer, &r_DEcran);


                SDL_SetRenderDrawColor(renderer,100,100,100,255);
                SDL_RenderFillRect(renderer, &r_basEcran);
                SDL_RenderFillRect(renderer, &r_hautEcran);
     

                SDL_RenderCopy(renderer, textTextureATQ1, NULL, &r_ATQ1);
                SDL_RenderCopy(renderer, textTextureATQ3, NULL, &r_ATQ3);
                SDL_RenderCopy(renderer, NomTexture, NULL, &NomRect);
                SDL_RenderCopy(renderer, NumTourTexture, NULL, &NumTourRect);
            

                affiche_point(we,he,renderer,r_basEcran,combat);
                affiche_pv(we,he,renderer,r_GEcran,r_DEcran,combat);

                SDL_RenderCopy(renderer, tperso, NULL, &r_ennemi);
                SDL_RenderPresent(renderer);
                if(combat->combattant[combat->indice_combattant]->camp==1 && combat->combattant[combat->indice_combattant]->mort==0 ){
                    SDL_Delay(250);
                }
                else{
                    SDL_Delay(100);
                }
                
                                        
                                        
                //destruction des textures
                SDL_DestroyTexture(textTextureATQ1);
                SDL_DestroyTexture(textTextureATQ3);
                SDL_DestroyTexture(tperso);
                SDL_DestroyTexture(NomTexture);
                SDL_DestroyTexture(NumTourTexture);
                free(NumTour);
    return 0;
}

/**
*
*\fn int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,combattant_t *combattant,int Nbennemi,combat_t * combat)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param event evenement
*\param renderer rendu de la fenetre
*\param ennemi structure d'un pnj ennemi
*\param combattant structure du combattant
*\param Nbennemi nombre d'ennemie vivant
*\param combat struture de combat
*\brief fonction d'attaque d'un allie
*/
//fonction d'attaque d'un allie
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,combattant_t *combattant,int Nbennemi,combat_t * combat){
         while (SDL_PollEvent(&event) != 0 );
        if(combattant->mort==0){
        SDL_Rect r_basEcran={0,(*he)-(*he)/4,(*we),(*he)/4};
        SDL_Rect  r_ATQ1= {(r_basEcran.w*40/100),(r_basEcran.h*3)+r_basEcran.h/2,175,48};
        SDL_Rect  r_ATQ3= {(r_basEcran.w*40/100)+(r_basEcran.w*30/100),(r_basEcran.h*3)+r_basEcran.h/2,373,48};
        SDL_Rect r_mult = { 50, (r_basEcran.h*3)+r_basEcran.h/2+50, 206, 47};
            int jouer=1;
            int nb_point_deb=combat->nb_point;


            while(jouer){
                

                while(ennemi->combattant[combat->indice_ennemi]->mort==1){
                        combat->indice_ennemi++;
                }
                affichage_combat(we,he,renderer,combat);
                while (SDL_PollEvent(&event) != 0 ) {

                        if(event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_a){
                            if(combat->indice_ennemi>=(Nbennemi-1)){
                                combat->indice_ennemi=0;
                                }
                                else{
                                    combat->indice_ennemi++;
                                }
                            }
                    //enleve des pv au monstre avec les attaques
                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        if((r_ATQ1.x<=event.button.x) && (r_ATQ1.x+r_ATQ1.w>=event.button.x) && ((r_ATQ1.y+r_ATQ1.h)>=event.button.y) && (r_ATQ1.y<=event.button.y)){
                            ennemi->combattant[combat->indice_ennemi]->pv-=10*combat->mult;
                            jouer=0;
                        }
                        else if((r_ATQ3.x<=event.button.x) && ((r_ATQ3.x+r_ATQ3.w)>=event.button.x) && ((r_ATQ3.y+r_ATQ3.h)>=event.button.y) && (r_ATQ3.y<=event.button.y)){
                            ennemi->combattant[combat->indice_ennemi]->pv-=30*combat->mult;
                            jouer=0;
                        }
                        else if((r_mult.x<=event.button.x) && ((r_mult.x+r_mult.w)>=event.button.x) && ((r_mult.y+r_mult.h)>=event.button.y) && (r_mult.y<=event.button.y)){
                            
                            if (combat->mult<2.5 && combat->nb_point>0){
                                combat->mult+=0.5;
                                (combat->nb_point)--;
                                
                            }
                            else{
                                
                                combat->nb_point=nb_point_deb;
                                combat->mult=1;
                            }
                            
                        }
                        
                    }
                    
                            

                }


            }
            


        }
        combat->indice_ennemi=0;
        while(combat->ennemi[combat->indice_ennemi]->mort==1){
            combat->indice_ennemi++;
        }
        
     return 0;
}
                
   


/**
*
*\fn int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp)
*\param ennemi structure d'un pnj ennemi
*\param event evenement 
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
*\fn int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2)
*\param combattant2 structure d'un combattant 
*\param combattant1 structure du pnj jouer
*\brief fonction pour comparer la vitesse des personnages
*/

//fonction pour comparer la vitesse des personnages
int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2){

  if( combattant1->vitesse == combattant2->vitesse ) {
    return(0) ; 
  }
  if( combattant1->vitesse > combattant2->vitesse){
    return(-1) ; 
  }  
  return(1) ;   
}

//encapsulation de la fonction compare_vitesse
int compare_vitesse_enc( const void * const combattant1 , const void * const combattant2 ) {
    const combattant_t *comb1e = *(const combattant_t**)combattant1;
  const combattant_t *comb2e = *(const combattant_t**)combattant2;
  return compare_vitesse(   comb1e ,comb2e );
}


void aff(combattant_t * combattant){
    if(combattant==NULL){
        printf("vide\n");
    }else{
printf("nom:%s\n",combattant->nom);
printf("pv:%d\n",combattant->pv);

    }
    
}

combat_t * init_combat(){
    combat_t * combat=malloc(sizeof(combat_t));
    combat->nb_allie=0;
    combat->nb_ennemi=0;
    combat->mult=0;
    combat->nb_point=0;
    combat->indice_ennemi=0;
    combat->indice_combattant=0;
    combat->num_tour=0;
    return combat;

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

        int i,allie=0;
        int nb_combattant=0;
        int j;
        int Nennemi=0;

        combat_t * combat=init_combat();

        //compte le nombre d'allie dans l'equipe
        for (i=0;i<4;i++){
            if(pp->equipe[i]!=NULL){
                combat->nb_allie++;
                allie++;
                combat->allie[i]=pp->equipe[i];
            }
        }
        
        combat->indice_ennemi=0;

        //compte le nombre d'ennemi
        for (i=0;i<4;i++){
            if(ennemi->combattant[i]!=NULL){
                combat->nb_ennemi++;
                Nennemi++;
                combat->ennemi[i]=ennemi->combattant[i];
            }
        }
        
        nb_combattant=combat->nb_ennemi+combat->nb_allie;
        for(i=0;i<8;i++){
            combat->combattant[i]=NULL;
        }

        for(i=0;i<combat->nb_allie;i++){
            combat->combattant[i]=pp->equipe[i];
        }
        
        for(i=combat->nb_allie,j=0;i<nb_combattant;i++,j++){
            combat->combattant[i]=ennemi->combattant[j];
        }

       combat->nb_point=2;
       combat->num_tour=1;

        while(Nennemi>0 && allie>0){
            //trie vitesse

            qsort(combat->combattant,nb_combattant,sizeof(void *),compare_vitesse_enc);

            for(i=0;i<nb_combattant && Nennemi>0 ;i++){
                
                combat->mult=1;

                if(combat->combattant[i]->camp==0 && combat->combattant[i]->mort==0){
                    attaque_allie(we,he,event,renderer,ennemi,combat->combattant[i],Nennemi,combat);
                
                }
                
                else if(combat->combattant[i]->camp==1 && combat->combattant[i]->mort==0){
                    attaque_ennemi(combat->combattant[i],nb_combattant,combat->combattant);
                }
                 affichage_combat(we,he,renderer,combat);
                 SDL_Delay(500);

                //compte le nombre d'allie dans l'equipe
                for(j=0;j<nb_combattant;j++){
                    if(combat->combattant[j]->pv<=0 && combat->combattant[j]->mort==0){
                        combat->combattant[j]->mort=1;
                        if(combat->combattant[j]->camp==0){
                            allie--;
                        }
                        if(combat->combattant[j]->camp==1){
                            Nennemi--;
                        }
                    }
                    
                }
                combat->indice_combattant++;
                
            }
            combat->indice_combattant=0;
            combat->num_tour++;

            SDL_Delay(100);
            if(combat->nb_point<6){
                (combat->nb_point)++;
            }
            
        }
        SDL_RenderPresent(renderer);
        ennemi->combat=0;
        free(combat);
    }

    return 0;
}




