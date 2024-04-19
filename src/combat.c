
//
//combat.c
//Created by Pasquier Lina 
//

/**
*\file combat.c
*\brief Programme qui s'occupe du combat
*\author Pasquier Lina Moreau Enzo
*\date 15 Fevrier 2024
*\version 1.0
*/


#include "../libs/commun.h"

/**
*
*\fn void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture,SDL_Texture *Texture2)
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

combattant_t * pre_init_combattant(){
    combattant_t * combattant=malloc(sizeof(combattant_t));
    combattant->nom=malloc(5);
    combattant->pv=malloc(sizeof(int));
    return combattant;
}

void remplir_combattant(combattant_t * combattant,char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme){
    strcpy(combattant->nom,nom);
    *combattant->pv=pv;
    combattant->pvMax=pv;
    combattant->vitesse=vitesse;
    combattant->puissance=puissance;
    combattant->mort=0;
    combattant->camp=camp;
    combattant->temps_recharge=0;
    combattant->temps_recharge_max=temps_recharge_max;
    combattant->indice_portrait=indice_portrait;
    combattant->indice_sprite=indice_sprite;
    combattant->type=type;
    combattant->status=0;
    combattant->forme=forme;
}

/**
*
*\fn combattant_t *init_combattant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp,char * portrait,char * sprite,int type)
*\param nom prenom du combattant
*\param pv les pv du combattant
*\param vitesse vitesse du combattant
*\param camp camp du personnage (1=ennemi,0=allie)
*\param indice_portrait l'indice du portrait pour le lire dans le fichier
*\param indice_sprite l'indice du sprite pour le lire dans le fichier
*\param type type d'attaque special (0=attaque un ennemi,1=saute le tour d'un ennemi,2=soigne un ennemi)
*\param temps_recharge_max temps de recharge pour que le combattant est son attaque speciale
*\param puissance La force des attaques du combattant
*\param forme la forme des ennemis (0=slime,1=?,2=?,3=boss)
*\brief fonction qui creer le combattant 
*/
combattant_t *init_combattant(char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme,int pvMax){
    combattant_t * combattant=malloc(sizeof(combattant_t));
    combattant->nom=malloc(strlen(nom)+1);
    strcpy(combattant->nom,nom);
    combattant->pv=malloc(sizeof(int));
    *combattant->pv=pv;
    combattant->pvMax=pvMax;
    combattant->vitesse=vitesse;
    combattant->puissance=puissance;
    combattant->mort=0;
    combattant->camp=camp;
    combattant->temps_recharge=0;
    combattant->temps_recharge_max=temps_recharge_max;
    combattant->indice_portrait=indice_portrait;
    combattant->indice_sprite=indice_sprite;
    combattant->type=type;
    combattant->status=0;
    combattant->forme=forme;
    return combattant;
}

/**
*\fn void desctruction_combattant(combattant_t * combattant)
*\param combattant strcuture du combattant 
*\brief fonction qui detruit un combattant
*/
void desctruction_combattant(combattant_t * combattant){
    free(combattant->nom);
    free(combattant->pv);
    free(combattant);
}

/**
*\fn void desctruction_combat(combat_t * combat)
*\param combat strcuture du combat 
*\brief fonction qui detruit le combat
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
*\brief fonction qui affiche les points de la personne et le multiplicateur de degat
*/
//fonction qui affiche les points de la personne et le multiplicateur de degat
int affiche_point(int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, combat_t * combat,map_t * map )
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

	// Position du texte
	SDL_Rect r_mult = { 50, ((*he)-(r_basEcran.h/2))- textSurfacemult->h/2, textSurfacemult->w, textSurfacemult->h};

    int i ;
    for(i=0;i<combat->nb_point;i++){
        SDL_Rect r_point = {r_mult.x+((r_basEcran.w/3)/20)*i, r_mult.h+r_mult.y, (r_basEcran.w/3)/20, (r_basEcran.w/3)/20};
        SDL_RenderCopy(renderer, map -> tabTexture[195], NULL, & r_point);

    }
    

	// Afficher la texture sur le rendu
	SDL_RenderCopy(renderer, textTexturemult, NULL, &r_mult);
	SDL_FreeSurface(textSurfacemult);
	SDL_DestroyTexture(textTexturemult);

	free(textemult);
	textemult = NULL;
	TTF_CloseFont(font);
	return 0;

}



/**
*
*\fn int affiche_pv(int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_GEcran,SDL_Rect r_DEcran,combat_t *combat,map_t * map)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de la fenetre
*\param r_GEcran renctangle gauche de l'ecran
*\param r_DEcran renctangle droit de l'ecran
*\param combat structure combat
*\param map structure map
*\brief fonction qui affiche les allies et les ennemis sur les cotes
*/
//fonction qui affiche les allies et les ennemis sur les cotes
int affiche_pv(int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_GEcran,SDL_Rect r_DEcran,combat_t *combat,map_t * map){
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
        SDL_Rect textRect = {10+(*we*2/100), (r_GEcran.y+i*(r_GEcran.h/4))+(*he*4/100), textSurface->w, textSurface->h};
        if(strcmp(combat->ennemi[i]->nom,combat->combattant[combat->indice_combattant]->nom)==0 && combat->combattant[combat->indice_combattant]->mort==0 && combat->combattant[combat->indice_combattant]->status==0){
            textRect.x = (r_GEcran.x+(100)+(*we*4/100));
        }
        if(combat->ennemi[i]->status==1){
            SDL_Rect r_effet = {(textRect.x+textRect.w)+(*we)*2/100, textRect.y, (*we)*2/100, (*we)*2/100};
            SDL_RenderCopy(renderer, map -> tabTexture[169], NULL, & r_effet);
        }

        affVie(renderer,(r_GEcran.y+i*(r_GEcran.h/4))+textRect.h+(*he*4/100),10+(*we*2/100),combat->ennemi[i],map);
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
        SDL_Rect textRect = {r_DEcran.x+(*we*2/100), (r_DEcran.y+i*(r_GEcran.h/4))+(*he*4/100), textSurface->w, textSurface->h};
        if(strcmp(combat->allie[i]->nom,combat->combattant[combat->indice_combattant]->nom)==0 && combat->combattant[combat->indice_combattant]->mort==0 && combat->combattant[combat->indice_combattant]->status==0){
            textRect.x = (r_DEcran.x+(r_DEcran.w/50)+(*we*4/100));
        }
        if(combat->allie[i]->status==1){
            SDL_Rect r_effet = {(textRect.x+textRect.w)+(*we)*2/100, textRect.y, (*we)*2/100, (*we)*2/100};
            SDL_RenderCopy(renderer, map -> tabTexture[169], NULL, & r_effet);

        }
        affVie(renderer,(r_DEcran.y+i*(r_GEcran.h/4))+textRect.h+(*he*4/100),r_DEcran.x+(*we*2/100),combat->allie[i],map);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

    }

    TTF_CloseFont(font);
    return 0;

}

/**
*
*\fn attaque_ennemi(int nb_combattant,combat_t * combat)
*\param nb_combattant nombre de combattant 
*\param combat structure combat
*\brief fonction d'attaque de l'ennemi 
*/
//fonction d'attaque de l'ennemi 
int attaque_ennemi(int nb_combattant,combat_t * combat){

    int indice=0;
    //indice=forme_attaque(nb_combattant,combat);
    //combat->allie[indice]->pv-=100000;
  

    //attaque special des ennemis
    if(combat->combattant[combat->indice_combattant]->temps_recharge==combat->combattant[combat->indice_combattant]->temps_recharge_max){
        //Attaque puissante sur un allie
        if(combat->combattant[combat->indice_combattant]->type==0){
            indice=forme_attaque(nb_combattant,combat);
            *(combat->allie[indice]->pv)-=combat->combattant[combat->indice_combattant]->puissance*2;

        }
        //soigne un ennemi au hasard
        else if (combat->combattant[combat->indice_combattant]->type==2){
            //recupere l'indice d'un ennemi pour le soigner
            int i=0;
            int min=*(combat->ennemi[i]->pv);
            for(i=1;i<combat->nb_ennemi;i++){
                if((min>*(combat->ennemi[i]->pv) && *(combat->ennemi[i]->pv)>0) || min==0){
                    min=*(combat->ennemi[i]->pv);
                    indice=i;
                }
            }

            *(combat->ennemi[indice]->pv)+=combat->combattant[combat->indice_combattant]->pvMax*0.1;

        }
        //Fait passer le tour d'un allie
        else if (combat->combattant[combat->indice_combattant]->type==1){
            indice=forme_attaque(nb_combattant,combat);
            combat->allie[indice]->status=1;
        }
        //fait des degats a tous les allies
        else if(combat->combattant[combat->indice_combattant]->type==3){
            int i;
            for(i=0;i<combat->nb_allie;i++){
                *(combat->allie[i]->pv)-=combat->combattant[combat->indice_combattant]->puissance;
            }
        }
        combat->combattant[combat->indice_combattant]->temps_recharge=0;
    //attaque de base des ennemis
    }else{
        indice=forme_attaque(nb_combattant,combat);
        *(combat->allie[indice]->pv)-=combat->combattant[combat->indice_combattant]->puissance;
        combat->combattant[combat->indice_combattant]->temps_recharge++;
    }

    //passif de ennemi Finn, soigne un peu tout les ennemis a son tour
    if((combat->combattant[combat->indice_combattant]->type==2 && combat->combattant[combat->indice_combattant]->forme==3) || combat->combattant[combat->indice_combattant]->forme==4){
        int k=0;
        for(k=0;k<combat->nb_ennemi;k++){
            if(combat->ennemi[k]->mort==0)
                *(combat->ennemi[k]->pv)+=combat->combattant[combat->indice_combattant]->pvMax*5/100;
        }
    }
    
    
    return 0;
}
/**
*
*\fn int forme_attaque(int nb_combattant,combat_t * combat)
*\param nb_combattant nombre de combattant 
*\param combat structure combat
*\brief fonction qui donne l'indice de la personne attaque par rapport a la forme de l'ennemi
*/
//fonction qui donne l'indice de la personne attaque par rapport a la forme de l'ennemi
int forme_attaque(int nb_combattant,combat_t * combat){
    //ennemi de petite taille (slime) attaque l'allie qui a le moins de pv
        if(combat->combattant[combat->indice_combattant]->forme==0){
            //recupere l'allie qui a le moins de pv
            int i=0;
            int indice=0;
            int min=*(combat->allie[i]->pv);
            for(i=1;i<combat->nb_allie;i++){
                if((min>*(combat->allie[i]->pv) && *(combat->allie[i]->pv)>0) || min==0){
                    min=*(combat->allie[i]->pv);
                    indice=i;
                }
            }
            return indice;
        }

        //ennemi de moyenne taille (?) attaque l'allie qui a le moins de pv max
        if(combat->combattant[combat->indice_combattant]->forme==1){
            //recupere l'allie qui a le moins de pv max
            int i=0;
            int indice=0;
            int min=combat->allie[i]->pvMax;
            for(i=1;i<combat->nb_allie;i++){
                if((min>combat->allie[i]->pvMax && *(combat->allie[i]->pv)>0) || min==0){
                    min=combat->allie[i]->pvMax;
                    indice=i;
                }
            }
            return indice;
        }

        //ennemi de grande taille (?) attaque l'allie qui a le plus de PV
        if(combat->combattant[combat->indice_combattant]->forme==2){
            //recupere l'allie qui a le plus de pv 
            int i=0;
            int indice=0;
            int max=*(combat->allie[i]->pv);
            for(i=1;i<combat->nb_allie;i++){
                if(max<*(combat->allie[i]->pv) && *(combat->allie[i]->pv)>0){
                    max=*(combat->allie[i]->pv);
                    indice=i;
                }
            }
            return indice;
        }

        //ennemi de boss taille (?) attaque l'allie qui a le plus de pv max
        if(combat->combattant[combat->indice_combattant]->forme==3 || combat->combattant[combat->indice_combattant]->forme==4){
            //recupere l'allie qui a le plus de pv max
            int i=0;
            int indice=0;
            int max=combat->allie[i]->pvMax;
            for(i=1;i<combat->nb_allie;i++){
                if(max<combat->allie[i]->pvMax && *(combat->allie[i]->pv)>0){
                    max=combat->allie[i]->pvMax;
                    indice=i;
                }
            }
            return indice;
            
        }
        return 0;

}

/**
*
*\fn int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat,int etat,p_mv * personnage,map_t * map)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param renderer rendu de l'ecran
*\param combat structure de combat
*\param etat permet de savoir si c'est un alliee qui joue ou un ennemi pour afficher ce qu'il faut 
*\param personnage structure du personnage jouer 
*\brief fonction d'affichage du combat
*/

//fonction d'affichage du combat
int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat,int etat,p_mv * personnage,map_t * map){
    
    int j=0;
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
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
                SDL_Color textColorGris = {50, 50, 50};
                SDL_Color couleuractuel=textColor;

            if(combat->combattant[combat->indice_combattant]->temps_recharge<combat->combattant[combat->indice_combattant]->temps_recharge_max && combat->combattant[combat->indice_combattant]->camp==0){
                couleuractuel=textColorGris;
            }
            
            char * texte1;
            char * texte2;

            if(etat==0){
                texte1="Attaque";
                texte2="Attaque speciale";
            

            }
            else {
                texte1="Soigner";
                texte2=" ";
            }

                //creation du premier texte (Attaque)
                SDL_Surface * textSurfaceATQ1 = TTF_RenderText_Solid(font,texte1, textColor);
                if (!textSurfaceATQ1) {
                    erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
                    TTF_CloseFont(font);
                    return -1;
                }

                SDL_Texture *  textTextureATQ1= SDL_CreateTextureFromSurface(renderer, textSurfaceATQ1);
                SDL_Rect  r_ATQ1= {(r_basEcran.w*40/100),(r_basEcran.h*3)+r_basEcran.h/2,textSurfaceATQ1->w,textSurfaceATQ1->h};
                SDL_FreeSurface(textSurfaceATQ1);

                    if(SDL_QueryTexture(textTextureATQ1,NULL,NULL,&r_ATQ1.w,&r_ATQ1.h)!=0){
                        erreur_sdl("Impossible de charger le texte",NULL,renderer,textTextureATQ1,NULL);
                        return -1;          
                }



                //creation du troisieme texte (Attaque speciale)
                SDL_Surface * textSurfaceATQ3 = TTF_RenderText_Solid(font,texte2, couleuractuel);
                if (!textSurfaceATQ3) {
                    erreur_sdl("Erreur lors de la création de la surface de texte",NULL,renderer,textTextureATQ1,NULL);
                    TTF_CloseFont(font);
                    return -1;
                }
                
                SDL_Texture * textTextureATQ3 = SDL_CreateTextureFromSurface(renderer, textSurfaceATQ3);

                SDL_Rect r_ATQ3={(r_basEcran.w*40/100)+(r_basEcran.w*30/100),(r_basEcran.h*3)+r_basEcran.h/2,textSurfaceATQ3->w,textSurfaceATQ3->h};
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
            SDL_Rect r_hautEcran = {0,0,( * we),56};
            SDL_Rect r_hautEcran_cadre = {( * we) / 4,r_hautEcran.h-r_hautEcran.h*5/100,(( * we) - ( * we) / 4)-( * we) / 4,r_hautEcran.h*5/100};
            SDL_Surface * NomSurface;

            if(etat==0){
            //Nom du personnage selectionne
                NomSurface = TTF_RenderText_Blended(font,combat->ennemi[combat->indice_ennemi]->nom, textColor);
            }
            else{
                NomSurface = TTF_RenderText_Blended(font,combat->allie[combat->indice_allie]->nom, textColor);
            
            }

            if (!NomSurface) {
                erreur_sdl("Erreur lors de la création de la surface de texte\n",NULL,renderer,NULL,NULL);
                TTF_CloseFont(font);
            return -1;

            
            }
            SDL_Texture* NomTexture = SDL_CreateTextureFromSurface(renderer, NomSurface);
            SDL_Rect NomRect = {r_hautEcran.w/2-NomSurface->w/2, r_hautEcran.h/2-NomSurface->h/2, NomSurface->w, NomSurface->h};
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
    SDL_Rect r_ecran={0,0,( * we) ,( * he)};

    /*
     *
     *ECRAN GAUCHE
     *
     */

    SDL_Rect r_GEcran = {0,r_hautEcran.h,( * we) / 4,(r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};

    /*
     *
     *ECRAN DROIT
     *
     */
    SDL_Rect r_DEcran = {( * we) - ( * we) / 4,r_hautEcran.h,( * we)-((( * we) - ( * we) / 4)), (r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};

    /*
     *
     *ECRAN FOND
     *
     */
    SDL_Rect r_MEcran = {r_GEcran.w,r_hautEcran.h,r_DEcran.x - r_GEcran.w,(r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
    SDL_Rect r_Fleches_GEcran={r_GEcran.w,r_MEcran.h/2+r_hautEcran.h-(r_MEcran.h/6)/2,r_MEcran.h/6,r_MEcran.h/6};
    SDL_Rect r_Fleches_DEcran={r_DEcran.x-r_MEcran.h/6,r_MEcran.h/2+r_hautEcran.h-(r_MEcran.h/6)/2,r_MEcran.h/6,r_MEcran.h/6};
            


            /*
            *
            *AFFICHAGE ENNEMI
            *
            */



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
                    if(*(combat->combattant[j]->pv)<=0){
                        nbMort++;

                    }
                    
            }
            j=0;


            SDL_RenderClear(renderer);
         
            if(map->Nightmare==1){
                SDL_RenderCopy(renderer, map -> tabTexture[170], NULL, & r_ecran);
            }else{
                SDL_RenderCopy(renderer, map -> tabTexture[184], NULL, & r_ecran);
            }
            
            SDL_RenderCopy(renderer, map -> tabTexture[198], NULL, & r_MEcran);

            SDL_SetRenderDrawColor(renderer,50,50,50,255);
          

            if((nb_combattant-nbMort)%2==0){
                //affichage des combattant en haut pour savoir qui joue dans le cas paire
                for(i=0,j=0;i<nb_combattant-nbMort;i++,j++){


                    //passe au combattant suivant si il est mort
                    while(combat->combattant[j]->mort==1){
                        j++;
                    }
                    
                    SDL_Rect r1= {r_GEcran.w+((r_DEcran.x-r_GEcran.w)/8)*i+(((r_DEcran.x-r_GEcran.w)/8))*((8-(nb_combattant-nbMort))/2),r_hautEcran.h,(r_DEcran.x-r_GEcran.w)/8,100};
                    if(j==combat->indice_combattant){
                        if(combat->mult==1.0){
                            SDL_RenderCopy(renderer, map->tabTexture[159], NULL, &r1);
                        }
                        else if(combat->mult==1.5){
                            SDL_RenderCopy(renderer, map->tabTexture[158], NULL, &r1);
                        }
                        else if(combat->mult==2){
                            SDL_RenderCopy(renderer, map->tabTexture[157], NULL, &r1);
                        }
                        else if(combat->mult==2.5){
                            SDL_RenderCopy(renderer, map->tabTexture[156], NULL, &r1);
                        }
                        else if(combat->mult==3.0){
                            SDL_RenderCopy(renderer, map->tabTexture[155], NULL, &r1);
                        }

                    }
                    
                    if(map->Nightmare && combat->combattant[j]->forme!=3 && combat->combattant[j]->camp==1){
                         SDL_RenderCopy(renderer, map->tabTexture[combat->combattant[j]->indice_sprite+map->nbN], NULL, &r1);

                    }
                    else if(map->Nightmare && combat->combattant[j]->camp==0){
                         SDL_RenderCopy(renderer, map->tabTexture[combat->combattant[j]->indice_sprite+8], NULL, &r1);

                    }
                    else{
                         SDL_RenderCopy(renderer, map->tabTexture[combat->combattant[j]->indice_sprite], NULL, &r1);

                    }
                
                   

                }

            }else{
                //affichage des combattant en haut pour savoir qui joue dans le cas impaire
                for(i=0,j=0;i<nb_combattant-nbMort;i++,j++){
                    while(combat->combattant[j]->mort==1){
                        j++;
                    }
 

                    SDL_Rect r1= {r_GEcran.w+((r_DEcran.x-r_GEcran.w)/8)*i+(((r_DEcran.x-r_GEcran.w)/8))*((8-(nb_combattant-nbMort))/2)+(((r_DEcran.x-r_GEcran.w)/8)/2),r_hautEcran.h,(r_DEcran.x-r_GEcran.w)/8,100};
                    if(j==combat->indice_combattant){
                        if(combat->mult==1.0){
                            SDL_RenderCopy(renderer, map->tabTexture[159], NULL, &r1);
                        }
                        else if(combat->mult==1.5){
                            SDL_RenderCopy(renderer, map->tabTexture[158], NULL, &r1);
                        }
                        else if(combat->mult==2){
                            SDL_RenderCopy(renderer, map->tabTexture[157], NULL, &r1);
                        }
                        else if(combat->mult==2.5){
                            SDL_RenderCopy(renderer, map->tabTexture[156], NULL, &r1);
                        }
                        else if(combat->mult==3.0){
                            SDL_RenderCopy(renderer, map->tabTexture[155], NULL, &r1);
                        }
                        
                    }

                    if(map->Nightmare && combat->combattant[j]->forme!=3 && combat->combattant[j]->camp==1){
                         SDL_RenderCopy(renderer, map->tabTexture[combat->combattant[j]->indice_sprite+map->nbN], NULL, &r1);

                    }
                    else if(map->Nightmare && combat->combattant[j]->camp==0){
                         SDL_RenderCopy(renderer, map->tabTexture[combat->combattant[j]->indice_sprite+8], NULL, &r1);

                    }
                    else{
                         SDL_RenderCopy(renderer, map->tabTexture[combat->combattant[j]->indice_sprite], NULL, &r1);

                    }
                    


                    
                }

            }





    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    if(combat->mult==1){
        SDL_RenderCopy(renderer, map -> tabTexture[183], NULL, & r_GEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[183], NULL, & r_DEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[196], NULL, & r_basEcran);
    }
    else if(combat->mult==1.5){
        SDL_RenderCopy(renderer, map -> tabTexture[167], NULL, & r_GEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[167], NULL, & r_DEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[168], NULL, & r_basEcran);
    }
    else if(combat->mult==2){
        SDL_RenderCopy(renderer, map -> tabTexture[165], NULL, & r_GEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[165], NULL, & r_DEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[166], NULL, & r_basEcran);
    }
    else if(combat->mult==2.5){
        SDL_RenderCopy(renderer, map -> tabTexture[163], NULL, & r_GEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[163], NULL, & r_DEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[164], NULL, & r_basEcran);
    }
    else if(combat->mult==3){
        SDL_RenderCopy(renderer, map -> tabTexture[161], NULL, & r_GEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[161], NULL, & r_DEcran);
        SDL_RenderCopy(renderer, map -> tabTexture[162], NULL, & r_basEcran);
    }


    SDL_RenderCopy(renderer, map -> tabTexture[182], NULL, & r_Fleches_DEcran);
    SDL_RenderCopy(renderer, map -> tabTexture[181], NULL, & r_Fleches_GEcran);


    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, & r_hautEcran_cadre);

    SDL_RenderCopy(renderer, textTextureATQ1, NULL, &r_ATQ1);      
    SDL_RenderCopy(renderer, textTextureATQ3, NULL, &r_ATQ3);
                

    SDL_RenderCopy(renderer, NomTexture, NULL, &NomRect);
    SDL_RenderCopy(renderer, NumTourTexture, NULL, &NumTourRect);
            

    affiche_point(we,he,renderer,r_basEcran,combat,map);
    affiche_pv(we,he,renderer,r_GEcran,r_DEcran,combat,map);
    barreCauchemard(personnage,renderer,map);



            if(etat==0 && map->Nightmare==0){
                //creation texture de l'ennemi
                SDL_RenderCopy(renderer, map->tabTexture[combat->ennemi[combat->indice_ennemi]->indice_portrait], NULL, &r_ennemi);
            }
            else if(etat==0 && map->Nightmare==1){
                SDL_RenderCopy(renderer, map->tabTexture[combat->ennemi[combat->indice_ennemi]->indice_portrait+map->nbN], NULL, &r_ennemi);
            }
            else if (etat==1 && map->Nightmare==0){
                //creation texture de l'allie
                SDL_RenderCopy(renderer, map->tabTexture[combat->allie[combat->indice_allie]->indice_portrait], NULL, &r_ennemi);
            }
            else if(etat==1 && map->Nightmare==1){
                SDL_RenderCopy(renderer, map->tabTexture[combat->allie[combat->indice_allie]->indice_portrait+8], NULL, &r_ennemi);

            }
 

                
                SDL_RenderPresent(renderer);

                if(combat->combattant[combat->indice_combattant]->camp==1 && combat->combattant[combat->indice_combattant]->mort==0 ){
                    SDL_Delay(250);
                }
                else if(combat->combattant[combat->indice_combattant]->camp==0){
                    SDL_Delay(100);
                }
                
                                        
                                        
                //destruction des textures
                SDL_DestroyTexture(textTextureATQ1);
                SDL_DestroyTexture(textTextureATQ3);
                SDL_DestroyTexture(NomTexture);
                SDL_DestroyTexture(NumTourTexture);
                free(NumTour);
    return 0;
}


/**
*
*\fn int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int Nbennemi,combat_t * combat,int allie,p_mv * personnage,map_t * map)
*\param we Largeur de l'ecran
*\param he Hauteur de l'ecran
*\param event evenement
*\param renderer rendu de la fenetre
*\param Nbennemi nombre d'ennemie vivant
*\param combat struture de combat
*\param allie nombre d'allie encore en vie
*\param personnage struture du personnage jouer
*\param map struture de la map
*\brief fonction d'attaque d'un allie
*/
//fonction d'attaque d'un allie
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,ennemi_t * ennemi,combattant_t *combattant,int Nbennemi,combat_t * combat,int allie,p_mv * personnage,map_t * map){
        while (SDL_PollEvent(&event) != 0 );
        if(combattant->mort==0){
            SDL_Rect r_hautEcran = {0,0,( * we),56};
            SDL_Rect r_basEcran={0,(*he)-(*he)/4,(*we),(*he)/4};
            SDL_Rect r_GEcran = {0,r_hautEcran.h,( * we) / 4,(r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
            SDL_Rect r_DEcran = {( * we) - ( * we) / 4,r_hautEcran.h,( * we)-((( * we) - ( * we) / 4)), (r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
            SDL_Rect r_MEcran = {r_GEcran.w,r_hautEcran.h,r_DEcran.x - r_GEcran.w,(r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
            SDL_Rect r_Fleches_GEcran={r_GEcran.w,r_MEcran.h/2+r_hautEcran.h-(r_MEcran.h/6)/2,r_MEcran.h/6,r_MEcran.h/6};
            SDL_Rect r_Fleches_DEcran={r_DEcran.x-r_MEcran.h/6,r_MEcran.h/2+r_hautEcran.h-(r_MEcran.h/6)/2,r_MEcran.h/6,r_MEcran.h/6};
            SDL_Rect  r_ATQ1= {(r_basEcran.w*40/100),(r_basEcran.h*3)+r_basEcran.h/2,175,48};
            SDL_Rect  r_ATQ3= {(r_basEcran.w*40/100)+(r_basEcran.w*30/100),(r_basEcran.h*3)+r_basEcran.h/2,373,48};
            SDL_Rect r_mult = { 50, ((*he)-(r_basEcran.h/2))-47/2, 206, 47};
            int jouer=1;
            int nb_point_deb=combat->nb_point;
            int Nightmare_deb=*personnage->NightP;

             //passif de Finn, soigne un peu tout les allies a son tour
            if(map->Nightmare && combat->combattant[combat->indice_combattant]->type==2){
                int k=0;
                for(k=0;k<combat->nb_allie;k++){
                     if(combat->allie[k]->mort==0)
                        *(combat->allie[k]->pv)+=combat->combattant[combat->indice_combattant]->pvMax*5/100;
                }
            }


            while(jouer){
                

                while(ennemi->combattant[combat->indice_ennemi]->mort==1){
                    if(combat->indice_ennemi<combat->nb_ennemi){
                         combat->indice_ennemi++;
                    }
                    else{
                        combat->indice_ennemi=0;
                    }
                       
                }
                affichage_combat(we,he,renderer,combat,0,personnage,map);
                while (SDL_PollEvent(&event) != 0 ) {

                    //enleve des pv au monstre avec les attaques
                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        if((r_ATQ1.x<=event.button.x) && (r_ATQ1.x+r_ATQ1.w>=event.button.x) && ((r_ATQ1.y+r_ATQ1.h)>=event.button.y) && (r_ATQ1.y<=event.button.y)){
                            *(ennemi->combattant[combat->indice_ennemi]->pv)-=combat->combattant[combat->indice_combattant]->puissance*combat->mult;
                            jouer=0;
                        }
                        else if(((r_ATQ3.x<=event.button.x) && ((r_ATQ3.x+r_ATQ3.w)>=event.button.x) && ((r_ATQ3.y+r_ATQ3.h)>=event.button.y) && (r_ATQ3.y<=event.button.y)) && (combattant->temps_recharge>=combattant->temps_recharge_max)){
                            if(combattant->type==0){
                                *(ennemi->combattant[combat->indice_ennemi]->pv)-=combat->combattant[combat->indice_combattant]->puissance*combat->mult*2;
                            }
                            else if(combattant->type==1){
                                combat->ennemi[combat->indice_ennemi]->status=1;

                            }
                            else if(combattant->type==2){
                                
                                soin(combat,r_basEcran,renderer,we,he,allie,event,personnage,map);
                            }
                            else if(combattant->type==3){
                                int k=0;
                                for(k=0;k<combat->nb_ennemi;k++){
                                    *(ennemi->combattant[k]->pv)-=combat->combattant[combat->indice_combattant]->puissance*combat->mult;
                                }
                            }
                            
                            jouer=0;
                            combattant->temps_recharge=0;
                        }
                        else if((r_Fleches_GEcran.x<=event.button.x) && (r_Fleches_GEcran.x+r_Fleches_GEcran.w>=event.button.x) && ((r_Fleches_GEcran.y+r_Fleches_GEcran.h)>=event.button.y) && (r_Fleches_GEcran.y<=event.button.y)){
                            if(combat->indice_ennemi<=0){
                                 combat->indice_ennemi=combat->nb_ennemi-1;
                                
                            }
                            else{
                                combat->indice_ennemi--;
                               
                            }
                        }
                        else if((r_Fleches_DEcran.x<=event.button.x) && (r_Fleches_DEcran.x+r_Fleches_DEcran.w>=event.button.x) && ((r_Fleches_DEcran.y+r_Fleches_DEcran.h)>=event.button.y) && (r_Fleches_DEcran.y<=event.button.y)){
                            if(combat->indice_ennemi>=(combat->nb_ennemi-1)){
                                combat->indice_ennemi=0;
                                }
                            else{
                                combat->indice_ennemi++;
                            }
                        }
                        else if((r_mult.x<=event.button.x) && ((r_mult.x+r_mult.w)>=event.button.x) && ((r_mult.y+r_mult.h)>=event.button.y) && (r_mult.y<=event.button.y)){
                            if (combat -> mult < 2.5 && combat -> nb_point > 0) {
                                combat -> mult += 0.5;
                                //augmentation barre de cauchemar
                                if(combat->mult==1.5){
                                    *(personnage->NightP) = *(personnage->NightP) + 1;
                                    if(*personnage->NightP>personnage->NightMax){
                                        *personnage->NightP=personnage->NightMax;
                                    }
                                } else if (combat -> mult == 2.0) {
                                    //artefact qui diminu l'augmentation du cauchemar
                                    if(map->listeArtefact[6]->equipe==1){
                                        *personnage -> NightP += 2;
                                    }else{
                                        *personnage -> NightP += 3;
                                    }
                                    if (*personnage -> NightP > personnage -> NightMax) {
                                        *personnage -> NightP = personnage -> NightMax;
                                    }
                                } else if (combat -> mult == 2.5) {
                                    if(map->listeArtefact[6]->equipe==1){
                                        *personnage -> NightP += 5;
                                    }else{
                                        *personnage -> NightP += 6;
                                    }
                                    if (*personnage -> NightP > personnage -> NightMax) {
                                        *personnage -> NightP = personnage -> NightMax;
                                    }
                                }
                                (combat -> nb_point) --;

                            } 
                            //artefact qui ajoute la possibilite d'augmenter 1 de plus le multiplicateur
                            else if(combat -> mult < 3.0 && combat -> nb_point > 0 && map->listeArtefact[5]->equipe==1){
                               combat -> mult += 0.5;
                                //augmentation barre de cauchemar
                                if (combat -> mult == 3.0) {
                                    if(map->listeArtefact[6]->equipe==1){
                                        *personnage -> NightP += 9;
                                    }else{
                                        *personnage -> NightP += 10;
                                    }
                                    
                                    if (*personnage -> NightP > personnage -> NightMax) {
                                        *personnage -> NightP = personnage -> NightMax;
                                    }
                                (combat -> nb_point) --;
                                }
                            }
                            else{
                                *personnage -> NightP = Nightmare_deb;
                                combat -> nb_point = nb_point_deb;
                                combat -> mult = 1;
                            }
                            
                        }
                        
                    }
                    
                            

                }


            }
            //met le monde et alex en cauchemar
            if(*personnage->NightP>=personnage->NightMax){
                map->Nightmare=1;
                *personnage->Nightmare=1;
            }
            


        }
        //passe les ennemis si ils sont mort
        combat->indice_ennemi=0;
        while(combat->ennemi[combat->indice_ennemi]->mort==1){
            combat->indice_ennemi++;
        }
        
     return 0;
}
                
   


/**
*
*\fn int debut_combat(SDL_Event event,ennemi_t * ennemi,p_mv * pp,case_t * c)
*\param ennemi structure d'un pnj ennemi
*\param event evenement 
*\param pp structure du personnage jouer
*\param c structure de la case
*\brief fonction qui regarde si on a lancer un combat
*/

//fonction qui regarde si on a lancer un combat
int debut_combat(SDL_Event event,ennemi_t * ennemi,p_mv * pp,case_t * c){
    
    if( boolcol(c,pp) && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_p && *(ennemi->combattant[0]->pv)>0){
        ennemi->combat=1;
    } 
    return 0;
}


int boolMemeCase(case_t c1, case_t c2){
    if(c1.x == c2.x && c1.y == c2.y){
        return 1;
    }else{
        return 0;
    }
}

int boolDebutCombat(carte_t * cartec,p_mv * pp,obj_t * ennemi){
    int i,j;
    int xp = pp->c->x,yp = pp->c->y;
    int xe = ennemi->cas->x,ye = ennemi->cas->y;
    for(i=-1;i<2;i++){
        for(j=-1;j<2;j++){
            if(boolMemeCase(cartec->grille.tabGrille[xp][yp],cartec->grille.tabGrille[xe+i][ye+j])){
                return 1;
            }
        }
    }
    if(boolMemeCase(cartec->grille.tabGrille[xp][yp],cartec->grille.tabGrille[xe+2][ye])){
        return 1;
    }else if(boolMemeCase(cartec->grille.tabGrille[xp][yp],cartec->grille.tabGrille[xe-2][ye])){
        return 1;
    }else if(boolMemeCase(cartec->grille.tabGrille[xp][yp],cartec->grille.tabGrille[xe][ye+2])){
        return 1;
    }else if(boolMemeCase(cartec->grille.tabGrille[xp][yp],cartec->grille.tabGrille[xe+i][ye-2])){
        return 1;
    }

    return 0;
}

/**
*
*\fn void debut_combat_carte(carte_t * cartec,SDL_Event event,p_mv * pp)
*\param event evenement 
*\param pp structure du personnage jouer
*\param cartec structure de la carte ou le personnage se trouve
*\brief fonction qui appelle debut_combat avec tout les ennemis sur la map
*/
//fonction qui appelle debut_combat avec tout les ennemis sur la map
void debut_combat_carte(carte_t * cartec,SDL_Event event,p_mv * pp){
    int i;
    for(i=0;i<cartec->nbObj;i++){
        if(cartec->tabObj[i]->typeObj==2){
            Boss(cartec->tabObj[i],pp);
            if(boolDebutCombat(cartec,pp,cartec->tabObj[i])){
                ((ennemi_t *)cartec->tabObj[i]->tabObj[0])->combat=1;
            }
        }
    }
}

/**
*
*\fn int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2)
*\param combattant2 structure d'un combattant 
*\param combattant1 structure du combattant jouer
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

/**
*
*\fn int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2)
*\param combattant2 structure d'un combattant 
*\param combattant1 structure du pnj jouer
*\brief fonction d'encapsulation de la fonction compare_vitesse
*/

//encapsulation de la fonction compare_vitesse
int compare_vitesse_enc( const void * const combattant1 , const void * const combattant2 ) {
    const combattant_t *comb1e = *(const combattant_t**)combattant1;
  const combattant_t *comb2e = *(const combattant_t**)combattant2;
  return compare_vitesse(   comb1e ,comb2e );
}

/**
*
*\fn combat_t * init_combat()
*\brief fonction d'initialisation de la structure combat
*/

//fonction d'initialisation de la structure combat
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



int boolTousMort(ennemi_t * ennemi){
    int i;
    for(i=0;ennemi->combattant[i];i++){
        if(!ennemi->combattant[i]->mort)return 0;
    }
    return 1;
}

/**
*
*\fn void combat_carte(carte_t * cartec,int *we,int *he,SDL_Event event,SDL_Renderer * renderer,p_mv * pp,map_t * map,int * etat_boss)
*\param cartec structure de la carte ou le personnage se trouve
*\param we Largeur de la fenetre 
*\param he hauteur de la fenetre
*\param event evenement 
*\param renderer rendu de la fenetre
*\param pp structure du personnage jouer
*\param map structure de la map
*\param etat_boss pointeur sur l'etat du boss final
*\brief fonction qui appelle combat avec tout les ennemis sur la map
*/
//fonction qui appelle combat avec tout les ennemis sur la map
void combat_carte(carte_t * cartec,int *we,int *he,SDL_Event event,SDL_Renderer * renderer,p_mv * pp,map_t * map,int * etat_boss){
    int i;
    for(i=0;i<cartec->nbObj;i++){
        if(cartec->tabObj[i]->typeObj==2 ){
            combat(we,he,event,renderer,cartec->tabObj[i]->tabObj[0],pp,map,etat_boss);
            if(boolTousMort((ennemi_t *)cartec->tabObj[i]->tabObj[0])){
                if(((ennemi_t *)cartec->tabObj[i]->tabObj[0])->forme == 3){
                    switch (map->zoneChargee)
                    {
                    case 4 :
                        cartec->tabObj[cartec->nbObj]=init_obj(cartec->tabObj[i]->cas,50,5,2);
                        cartec->nbObj++; 
                        break;
                    case 2 :
                        cartec->tabObj[cartec->nbObj]=init_obj(cartec->tabObj[i]->cas,50,5,1);
                        cartec->nbObj++; 
                        break;
                    case 3 :
                        cartec->tabObj[cartec->nbObj]=init_obj(cartec->tabObj[i]->cas,50,5,3);
                        cartec->nbObj++; 
                        break;
                    default:
                        break;
                    }
                }
                save_ennemi(*cartec,*cartec->tabObj[i]);
                dest_obj(cartec,i);
            }
        }
    }
}

/**
*
*\fn int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,ennemi_t * ennemi,p_mv * pp,map_t * map,int * etat_boss)
*\param we Largeur de la fenetre 
*\param he hauteur de la fenetre
*\param event evenement 
*\param renderer rendu de la fenetre
*\param ennemi structure d'un ennemi
*\param pp structure du personnage jouer
*\param map structure de la map
*\param etat_boss pointeur sur l'etat du boss final
*\brief fonction qui s'occupe du combat avec un ennemi
*/

//fonction qui s'occupe du combat avec un ennemi
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,ennemi_t * ennemi,p_mv * pp,map_t * map,int * etat_boss){
    if(ennemi->combat){
         


        int i=0,allie=0;
        int nb_combattant=0;
        int j;
        int Nennemi=0;
        int alexMort=0;
        int attenteAda=0;
        int DejaNight=0;
        int alexMortEnnemi=0;
        int attenteAdaEnnemi=0;


        ennemi_t copieEnnemi;
        copieEnnemi=*ennemi;

        

        //compte le nombre d'allie dans l'equipe
        for (i=0;i<4;i++){
            if(pp->equipe[i]!=NULL){
                allie++;
            }
        }
        combattant_t *tabAllie[allie];
        combattant_t *copieAllie1;

        //copie des allies pour pouvoir changer ses statistiques pendant le combat
        for(i=0;i<allie;i++){
            copieAllie1=init_combattant(pp->equipe[i]->nom,*(pp->equipe[i]->pv),pp->equipe[i]->vitesse,pp->equipe[i]->camp,pp->equipe[i]->indice_portrait,pp->equipe[i]->indice_sprite,pp->equipe[i]->type,pp->equipe[i]->temps_recharge_max,pp->equipe[i]->puissance,pp->equipe[i]->forme,pp->equipe[i]->pvMax);
            tabAllie[i]=copieAllie1;
        }




        //dans le mode Nightmare
        if(map->Nightmare){
            i=0;
            while(ennemi->combattant[i]!=NULL && i<4){
                if(ennemi->combattant[i]->mort==0){
                    ennemi->combattant[i]->pvMax = ennemi->combattant[i]->pvMax*(map->nvZone+map->bonusZoneN);
                    ennemi->combattant[i]->puissance = ennemi->combattant[i]->puissance*(map->nvZone+map->bonusZoneN);
                    *(ennemi->combattant[i]->pv) = *(ennemi->combattant[i]->pv)*(map->nvZone+map->bonusZoneN);
                }
                i++;
            }
            i = 0;
            while (pp -> equipe[i] != NULL && i < 4) {
                if (pp -> equipe[i] -> mort == 0) {
                    //artefact qui augmente les pv max
                    if(map->listeArtefact[2]->equipe==1){
                        pp -> equipe[i] -> pvMax = pp -> equipe[i] -> pvMax * (map -> nvEquipe + map -> bonusEquipeN+1);
                        *pp -> equipe[i] -> pv = *pp -> equipe[i] -> pv * (map -> nvEquipe + map -> bonusEquipeN+1);
                    }
                    else{
                        pp -> equipe[i] -> pvMax = pp -> equipe[i] -> pvMax * (map -> nvEquipe + map -> bonusEquipeN);
                        *pp -> equipe[i] -> pv = *pp -> equipe[i] -> pv * (map -> nvEquipe + map -> bonusEquipeN);
                    }

                    //artefact qui augmente l'attaque
                    if(map->listeArtefact[0]->equipe==1){
                        pp -> equipe[i] -> puissance = pp -> equipe[i] -> puissance * (map -> nvEquipe + map -> bonusEquipeN+1);
                    }
                    else{
                        pp -> equipe[i] -> puissance = pp -> equipe[i] -> puissance * (map -> nvEquipe + map -> bonusEquipeN);
                    }
                    //artefact qui augmente la vitesse
                    if(map->listeArtefact[1]->equipe==1){
                        pp -> equipe[i] -> vitesse = pp -> equipe[i] -> vitesse * 1.5;
                    }
                    //artefact qui diminue le temps de recharge de l'attaque special
                    if(map->listeArtefact[7]->equipe==1){
                        pp -> equipe[i] -> temps_recharge_max =pp -> equipe[i] -> temps_recharge_max-1;
                    }
                    

                }
                i++;
            }
            DejaNight=1;
        }
        //dans le mode normal
        else{
            i=0;
            while(ennemi->combattant[i]!=NULL && i<4){
                *(ennemi->combattant[i]->pv) = *(ennemi->combattant[i]->pv)*map->nvZone;
                ennemi->combattant[i]->pvMax = ennemi->combattant[i]->pvMax*map->nvZone;
                ennemi->combattant[i]->puissance = ennemi->combattant[i]->puissance*map->nvZone;
                i++;
            }
            i = 0;
            while (pp -> equipe[i] != NULL && i < 4) {
                //artefact qui augmente les pv max
                if(map->listeArtefact[2]->equipe==1){
                    *pp -> equipe[i] -> pv = *pp -> equipe[i] -> pv *( map -> nvEquipe+1);
                    pp -> equipe[i] -> pvMax = pp -> equipe[i] -> pvMax * (map -> nvEquipe+1);
                }
                else{
                    *pp -> equipe[i] -> pv = *pp -> equipe[i] -> pv * map -> nvEquipe;
                    pp -> equipe[i] -> pvMax = pp -> equipe[i] -> pvMax * map -> nvEquipe;
                }

                //artefact qui augmente l'attaque
                if(map->listeArtefact[0]->equipe==1){
                    pp -> equipe[i] -> puissance = pp -> equipe[i] -> puissance * (map -> nvEquipe+1);
                }
                else{
                   pp -> equipe[i] -> puissance = pp -> equipe[i] -> puissance * map -> nvEquipe;
                }
                //artefact qui augmente la vitesse
                if(map->listeArtefact[1]->equipe==1){
                    pp -> equipe[i] -> vitesse = pp -> equipe[i] -> vitesse * 1.5;
                }
                //artefact qui diminue le temps de recharge de l'attaque special
                if(map->listeArtefact[7]->equipe==1){
                    pp -> equipe[i] -> temps_recharge_max =pp -> equipe[i] -> temps_recharge_max-1;

                }

                


                i++;
            }

        }
    


        combat_t * combat=init_combat();

        //compte le nombre d'allie dans l'equipe
        for (i=0;i<4;i++){
            if(pp->equipe[i]!=NULL){
                combat->nb_allie++;
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

        //artefact qui augmente le nombre de point au debut
        if(map->listeArtefact[4]->equipe==1){
            combat -> nb_point = 3;
        }
        else{
            combat -> nb_point = 2;
        }

        
        combat -> num_tour = 1;
        

        while(Nennemi>0 && allie>0){
            //trie vitesse

            qsort(combat->combattant,nb_combattant,sizeof(void *),compare_vitesse_enc);
            

            for(combat->indice_combattant=0;combat->indice_combattant<nb_combattant && Nennemi>0 && allie>0;combat->indice_combattant++){

                combat->mult=1;
                if(allie != 0){
                    affichage_combat(we,he,renderer,combat,0,pp,map);
                }
                SDL_Delay(500);

                if(combat->combattant[combat->indice_combattant]->camp==0 && combat->combattant[combat->indice_combattant]->mort==0){
                    //regarde si l'allie peut jouer
                    if(combat->combattant[combat->indice_combattant]->status==0){
                        attaque_allie(we,he,event,renderer,ennemi,combat->combattant[combat->indice_combattant],Nennemi,combat,allie,pp,map);

                        //passif Ada en mode cauchemar, elle peut jouer 2 fois de suite (attente de 2 tour)
                        if(map->Nightmare && combat->combattant[combat->indice_combattant]->type==3 && attenteAda==0){
                            attaque_allie(we,he,event,renderer,ennemi,combat->combattant[combat->indice_combattant],Nennemi,combat,allie,pp,map);
                            attenteAda=2;
                        }
                        else if(map->Nightmare && combat->combattant[combat->indice_combattant]->type==3){
                            attenteAda--;
                        }
                    }
                    else{
                        //passif de Lou ennemi,si l'allie doit passer son tour, il perd aussi des pv
                        for(i=0;i<combat->nb_ennemi;i++){
                            if((combat->ennemi[i]->forme==3 && combat->ennemi[i]->type==1) || (combat->combattant[combat->indice_combattant]->forme==4 && map->Nightmare==1) ){
                                *(combat->combattant[combat->indice_combattant]->pv)-=combat->ennemi[i]->puissance*1.5;
                            }
                        }
                        combat->combattant[combat->indice_combattant]->status=0;
                    }
                    combat->combattant[combat->indice_combattant]->temps_recharge++;
                }
                
                else if(combat->combattant[combat->indice_combattant]->camp==1 && combat->combattant[combat->indice_combattant]->mort==0){
                    if(combat->combattant[combat->indice_combattant]->status==0){
                        attaque_ennemi(nb_combattant,combat);

                        //passif Ada ennemi, elle peut jouer 2 fois de suite (attente de 2 tour)
                        if((combat->combattant[combat->indice_combattant]->type==3 && attenteAdaEnnemi==0 && combat->combattant[combat->indice_combattant]->forme==3) || (combat->combattant[combat->indice_combattant]->forme==4 && map->Nightmare==1 && attenteAda==0)){
                           attaque_ennemi(nb_combattant,combat);
                           attenteAdaEnnemi=2;
                        }
                        else if(combat->combattant[combat->indice_combattant]->type==3 && combat->combattant[combat->indice_combattant]->forme==3){
                            attenteAdaEnnemi--;
                        }
                    }
                    //passif Lou en mode cauchemar, si l'ennemi doit passer son tour, il perd aussi des pv
                    else{
                        if(map->Nightmare){
                            int k=0;
                            for(k=0;k<combat->nb_allie;k++){
                                if(combat->allie[k]->type==1 && combat->allie[k]->mort==0 ){
                                    *(combat->combattant[combat->indice_combattant]->pv)-=combat->allie[k]->puissance*1.5;
                                }
                            }
                        }
                        combat->combattant[combat->indice_combattant]->status=0;
                    }
                }
                for(j=0;j<nb_combattant;j++){
                    //passif d'Alex en mode cauchemar, si il meurt il peut ressuciter une fois
                    if(combat->combattant[j]->camp==0 && alexMort==0 && combat->combattant[j]->type==0 && *(combat->combattant[j]->pv)<=0  && combat->combattant[j]->mort==0 && map->Nightmare ){
                        *(combat->combattant[j]->pv)=combat->combattant[j]->pvMax;
                        alexMort=1;
                    }
                
                    //passif d'Alex ennemi, si il meurt il peut ressuciter une fois
                    if((combat->combattant[j]->camp==1 && alexMortEnnemi==0 && combat->combattant[j]->type==0 && *(combat->combattant[j]->pv)<=0 && combat->combattant[j]->forme==3) && (combat->combattant[combat->indice_combattant]->forme==4 && map->Nightmare==1 && alexMortEnnemi==0) ){
                        *(combat->combattant[j]->pv)=combat->combattant[j]->pvMax;
                        alexMortEnnemi=1;
                    }
                }
                //compte le nombre d'allie dans l'equipe
                for(j=0;j<nb_combattant;j++){
                    if(*(combat->combattant[j]->pv)<=0 && combat->combattant[j]->mort==0){
                        combat->combattant[j]->mort=1;
                        if(combat->combattant[j]->camp==0  ){
                            allie--;
                        }
                        else if(combat->combattant[j]->camp==1){
                            Nennemi--;
                        }

                        if(Nennemi==0 || allie==0){
                                SDL_RenderClear(renderer);
                                SDL_Rect rect={0,0,*we,*he};
                                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                                SDL_RenderFillRect(renderer,&rect);
                                SDL_RenderPresent(renderer);

                            }

                    }
                    
                }
                if(map->Nightmare && DejaNight==0){
                    DejaNight=1;
                    i=0;
                    while(ennemi->combattant[i]!=NULL && i<4){
                        if(ennemi->combattant[i]->mort==0){
                            ennemi->combattant[i]->pvMax = ennemi->combattant[i]->pvMax*(map->nvZone+map->bonusZoneN);
                            ennemi->combattant[i]->puissance = ennemi->combattant[i]->puissance*(map->nvZone+map->bonusZoneN);
                            *(ennemi->combattant[i]->pv) = *(ennemi->combattant[i]->pv)*(map->nvZone+map->bonusZoneN);
                        }
                        i++;
                    }
                    i=0;
                    while(pp->equipe[i]!=NULL && i<4){
                        if(pp->equipe[i]->mort==0){
                            pp->equipe[i]->pvMax = pp->equipe[i]->pvMax*(map->nvEquipe+map->bonusEquipeN);
                            *(pp->equipe[i]->pv) =pp->equipe[i]->pvMax ;
                            pp->equipe[i]->puissance = pp->equipe[i]->puissance*(map->nvEquipe+map->bonusEquipeN);

                        }
                        i++;
                    }
                }


                
            }
            combat->indice_combattant=0;
            combat->num_tour++;


            SDL_Delay(100);
            if(combat->nb_point<6){
                (combat->nb_point)++;
            }
            //artefact qui ressusite les allies
            if(allie==0 && map->listeArtefact[3]->equipe==1){
                int k;
                for(k=0;k<combat->nb_allie;k++){
                    *combat->allie[k]->pv=combat->allie[k]->pvMax/2;
                    combat->allie[k]->mort=0;
                    allie++;

                }
                map->listeArtefact[3]->equipe=0;
                map->listeArtefact[3]->possession=0;
            }
        }

            //Si les alliees on tuer tous les ennemis
            if(Nennemi==0){
                //cherche si dans les ennemis ils y avait un boss
                if(ennemi->forme==3 || ennemi->forme==4){
                    //si il y avait un boss et qu'on etait en mode nightmare, met la barre de cauchemar de moitier
                    if(map->Nightmare){
                        map->Nightmare=0;
                        *pp->Nightmare=0;
                        *pp->NightP=(pp->NightMax)/2;
                        map->argent+=10;
                    }
                    //vide la barre de cauchemar
                    else{
                        *pp->NightP=0;
                    
                    }
                //artefact qui augmente le nombre d'argent gagner
                if(map->listeArtefact[8]->equipe==1){
                        map -> argent += 15;
                }else{
                        map -> argent += 10;
                }
                //artefact qui augmente le nombre de niveau gagner
                if(map->listeArtefact[9]->equipe==1){
                        map -> nvEquipe += 2;
                }else{
                        map -> nvEquipe += 1;
                }

                
            }
            if(ennemi->forme==4){
                * etat_boss=1;
            }
            //si on est en cauchemar sans avoir attaquer de boss augmente les bonus d'equipe et de zone en mode cauchemar
            if (map -> Nightmare) {
                map -> bonusEquipeN += 0.5;
                map -> bonusZoneN += 1;
            }
        }

        //SDL_RenderPresent(renderer);
        *ennemi = copieEnnemi;

        for(i=0;i<combat->nb_allie;i++){


            copier_combattant(pp->equipe[i], tabAllie[i]);
            strcpy(pp->equipe[i]->nom,tabAllie[i]->nom);


        }
        ennemi->combat=0;
        for(i=0;i<combat->nb_allie;i++){
            desctruction_combattant(tabAllie[i]);
        }
        desctruction_combat(combat);

        if(ennemi->forme==3){
            newCompagnon(&pp,ennemi);
            switch(map->zoneChargee){
                case 2 : map->Zone2 = 2 ;map->cle = 1;break;
                case 3 : map->Zone3 = 2 ;map->talisman = 1;break;
                case 4 : map->Zone4 = 2 ;map->plongee = 1;break;
                case 5 : map->Zone5 = 2 ;break;
            default : return 1;
            }   
        }
    }
    return 0;
}
/**
*
*\fn void copier_combattant(combattant_t * combattant,combattant_t * combattantcopie)
*\param combattant structure combattant 
*\param combattantcopie structure combattant copier
*\brief fonction qui copie un combattant dans un autre
*/

//fonction qui copie un combattant dans un autre
void copier_combattant(combattant_t * combattant,combattant_t * combattantcopie){
    combattantcopie->mort=combattant->mort ;
    *(combattantcopie->pv)=*(combattant->pv) ;
    if(*(combattantcopie->pv)>combattantcopie->pvMax){
        *(combattantcopie->pv) = combattantcopie->pvMax;
    }
    strcpy(combattant->nom,combattantcopie->nom);
    combattant->pvMax=combattantcopie->pvMax;
    combattant->vitesse=combattantcopie->vitesse;
    combattant->mort=combattantcopie->mort;
    combattant->camp=combattantcopie->camp;
    combattant->temps_recharge=combattantcopie->temps_recharge;
    combattant->temps_recharge_max=combattantcopie->temps_recharge_max;
    combattant->indice_portrait=combattantcopie->indice_portrait;
    combattant->indice_sprite=combattantcopie->indice_sprite;
    combattant->type=combattantcopie->type;
    combattant->status=combattantcopie->status;
    combattant->puissance=combattantcopie->puissance;
    combattant->forme=combattantcopie->forme;
}
/**
*
*\fn void barreCauchemard(p_mv * pmv,SDL_Renderer * renderer,map_t * map)
*\param pmv structure du personnage jouer
*\param renderer rendu de la fenetre
*\param map structure de la map
*\brief fonction qui affiche la barre de cauchemar
*/

//fonction qui affiche la barre de cauchemar
void barreCauchemard(p_mv * pmv,SDL_Renderer * renderer,map_t * map){
        //Variable Night
    int xn = 10;
    int yn = -5;
    int pn = (144*(*pmv->NightP))/pmv->NightMax;

    SDL_Rect Night_bar= {xn,yn,256,64};
    SDL_Rect Night_barVide = {xn+81,yn+19,144,26};
    SDL_Rect Night_barPleine= {xn+81,yn+19,pn,26}; //144 = pleine



    //affichage bar de cauchemar
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &Night_barVide);

    SDL_SetRenderDrawColor(renderer, 43,27,85,255);
    SDL_RenderFillRect(renderer, &Night_barPleine);

    SDL_RenderCopy(renderer,  map->tabTexture[170], NULL, &Night_bar);


}

/**
*
*\fn void  affVie(SDL_Renderer * renderer,int  he,int we,combattant_t * combattant,map_t * map)
*\param we Largeur de la fenetre 
*\param he hauteur de la fenetre
*\param combattant structure du combattant
*\param renderer rendu de la fenetre
*\param map structure de la map
*\brief fonction qui affiche la barre de vie
*/

//fonction qui affiche la barre de vie
void affVie(SDL_Renderer * renderer,int  he,int we,combattant_t * combattant,map_t * map){
    //Variable PV

    if(*(combattant->pv)<0){
        *(combattant->pv)=0;
    }
    else if (*(combattant->pv)>combattant->pvMax){
        *(combattant->pv)=combattant->pvMax;
    }
    int p = (144*(*(combattant->pv)))/combattant->pvMax;

    //chargement de la police d'écriture
    TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 10);
    if (!font) {
        //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return ;
    }

    SDL_Color textColor = {255, 255, 255};
    char *texte = malloc(15);
    snprintf(texte, 15, "PV : %d/%d", *(combattant->pv),combattant->pvMax);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font,texte, textColor);
    if (!textSurface) {
        fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return ;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Position du texte



    SDL_Rect PV_bar= {we,he-5,256,64};
    SDL_Rect PV_barVide= {we+81,he-5+19,144,26};
    SDL_Rect PV_barPleine= {we+81,he-5+19,p,26}; //144 = pleine

    SDL_Rect textRect = {(PV_barVide.x)+(PV_barVide.w/2)-(textSurface->w/2), (PV_barVide.y)+(PV_barVide.h/2)-(textSurface->h/2), textSurface->w, textSurface->h};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //affichage bar de vie
    SDL_RenderFillRect(renderer, &PV_barVide);

    SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
    SDL_RenderFillRect(renderer, &PV_barPleine);

      // Afficher la texture sur le rendu
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(renderer, map->tabTexture[199], NULL, &PV_bar);


    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    free(texte);
    texte=NULL;
    TTF_CloseFont(font);

}

/**
*
*\fn void  soin(combat_t * combat,SDL_Rect r_basEcran,SDL_Renderer * renderer,int * we,int * he,int allie,SDL_Event event,p_mv * personnage,map_t * map)
*\param combat structure combat
*\param r_basEcran renctangle bas de l'ecran
*\param renderer rendu de la fenetre
*\param we Largeur de la fenetre 
*\param he hauteur de la fenetre
*\param allie nombre d'allie encore en vie 
*\param envent evenement
*\param personnage structure du personnage jouer
*\param map structure de la map
*\brief fonction qui s'accupe des soins des allies
*/

//fonction qui s'accupe des soins des allies
void soin(combat_t * combat,SDL_Rect r_basEcran,SDL_Renderer * renderer,int * we,int * he,int allie,SDL_Event event,p_mv * personnage,map_t * map){
    SDL_Rect r_hautEcran = {0,0,( * we),56};
    SDL_Rect r_GEcran = {0,r_hautEcran.h,( * we) / 4,(r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
    SDL_Rect r_DEcran = {( * we) - ( * we) / 4,r_hautEcran.h,( * we)-((( * we) - ( * we) / 4)), (r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
    SDL_Rect r_MEcran = {r_GEcran.w,r_hautEcran.h,r_DEcran.x - r_GEcran.w,(r_basEcran.y - r_hautEcran.y) - r_hautEcran.h};
    SDL_Rect r_Fleches_GEcran={r_GEcran.w,r_MEcran.h/2+r_hautEcran.h-(r_MEcran.h/6)/2,r_MEcran.h/6,r_MEcran.h/6};
    SDL_Rect r_Fleches_DEcran={r_DEcran.x-r_MEcran.h/6,r_MEcran.h/2+r_hautEcran.h-(r_MEcran.h/6)/2,r_MEcran.h/6,r_MEcran.h/6};
    int jouer=1;
    SDL_Rect  r_ATQ1= {(r_basEcran.w*40/100),(r_basEcran.h*3)+r_basEcran.h/2,175,48};
    combat->indice_allie=0;
    while(jouer){
        while(combat->allie[combat->indice_allie]->mort==1){
            if(combat->indice_allie<combat->nb_allie){
                combat->indice_allie++;
            }
            else{
                combat->indice_allie=0;
            }
                       
        }

        affichage_combat(we,he,renderer,combat,1,personnage,map);
        while (SDL_PollEvent(&event) != 0 ) {

            if(event.type == SDL_MOUSEBUTTONDOWN ){

                if((r_ATQ1.x<=event.button.x) && (r_ATQ1.x+r_ATQ1.w>=event.button.x) && ((r_ATQ1.y+r_ATQ1.h)>=event.button.y) && (r_ATQ1.y<=event.button.y)){
                    *(combat->allie[combat->indice_allie]->pv)+=10*combat->mult;
                    if(*(combat->allie[combat->indice_allie]->pv)>combat->allie[combat->indice_allie]->pvMax){
                        *(combat->allie[combat->indice_allie]->pv)=combat->allie[combat->indice_allie]->pvMax;
                    }
                    jouer=0;
                }
                if((r_Fleches_GEcran.x<=event.button.x) && (r_Fleches_GEcran.x+r_Fleches_GEcran.w>=event.button.x) && ((r_Fleches_GEcran.y+r_Fleches_GEcran.h)>=event.button.y) && (r_Fleches_GEcran.y<=event.button.y)){
                    if(combat->indice_allie>=(combat->nb_allie-1)){
                        combat->indice_allie--;
                    }
                    else{
                         combat->indice_allie=combat->nb_allie-1;
                    }
                }
                if((r_Fleches_DEcran.x<=event.button.x) && (r_Fleches_DEcran.x+r_Fleches_DEcran.w>=event.button.x) && ((r_Fleches_DEcran.y+r_Fleches_DEcran.h)>=event.button.y) && (r_Fleches_DEcran.y<=event.button.y)){
                    if(combat->indice_allie>=(combat->nb_allie-1)){
                        combat->indice_allie=0;
                        }
                    else{
                        combat->indice_allie++;
                    }
                }
            
            }
        }

    }
}

void newCompagnon(p_mv ** Leader,ennemi_t * Boss){
    if(Boss->forme == 3){
        int i;
        for(i=0;(*Leader)->equipe[i] && i < 4;i++);
        if((*Leader)->equipe[i])return;
        switch (Boss->type)
        {
        case 0://Alex
        (*Leader)->equipe[i]=init_combattant("Alex",100,50,0,136,135,0,2,15,0,100);
            break;

        case 1://Lou
        (*Leader)->equipe[i]=init_combattant("Lou",100,50,0,138,137,1,2,15,0,100);
            break;

        case 2://Finn
        (*Leader)->equipe[i]=init_combattant("Finn",100,50,0,140,139,2,2,15,0,100);
            break;

        case 3://Ada
        (*Leader)->equipe[i]=init_combattant("Ada",100,50,0,142,141,3,2,15,0,100);
            break;
        
        default:
            break;
        }
    }
}

