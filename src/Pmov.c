//
//Pmov.c
//Created by Moreau Enzo
//

/**
*\file Pmov.c
*\brief programme pour afficher les personnages
*\author Moreau Enzo
*\date  Janvier 2024
*\version 1.0
*
*/



#include "../libs/commun.h"




/**
*
*\fn void pinput(p_mv * pmv,SDL_Event event)
*\param event permet de savoir si il y a un evenement
*\param pmv structure du personnage
*\brief fonction qui detecte si unetouche est presser et modifie ses coordonées
*/

//detection de touche presser et modification des coordonées
void pinput(p_mv * pmv,SDL_Event event,carte_t ** carte,map_t *map,SDL_Renderer * renderer){
    int temp = (*carte)->nZone;
    //si une touche est presser
    if(event.type == SDL_KEYDOWN){
        //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_z: 
            if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->y == 0){
                //cas des bords de grille valide
            }else{
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->y == 0){
                    *carte= &(map->tabMap[(*carte)->xcarte-1][(*carte)->ycarte]);
                    pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][LARG-1]);
                    pmv->r=pmv->c->Rectangle;
                    pmv->d=0;
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y-1].etat){
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y-1]);
                        pmv->r=pmv->c->Rectangle;
                        pmv->d=0;
                    }
                }
            }
            break;
            case SDLK_s: 
            if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->y == (LARG-1)){
            }else{
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->y == (LARG-1)){
                    *carte= &map->tabMap[(*carte)->xcarte+1][(*carte)->ycarte];
                    pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][0]);
                    pmv->r=pmv->c->Rectangle;
                    pmv->d=2;
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y+1].etat){
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y+1]);
                        pmv->r=pmv->c->Rectangle;
                        pmv->d=2;
                    }
                }
            }
            break;
            case SDLK_q: 
            if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->x == 0){
            }else{
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->x == 0){
                    *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte-1];
                    pmv->c=&((*carte)->grille.tabGrille[LONG-1][pmv->c->y]);
                    pmv->r=pmv->c->Rectangle;
                    pmv->d=3;
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x-1][pmv->c->y].etat){
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x-1][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        pmv->d=3;
                    }
                }
            }
            break;
            case SDLK_d: 
            if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->x == (LONG-1)){
            }else{
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->x == (LONG-1)){
                    *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte+1];
                    pmv->c=&((*carte)->grille.tabGrille[0][pmv->c->y]);
                    pmv->r=pmv->c->Rectangle;
                    pmv->d=1;
                }else if((*carte)->grille.tabGrille[pmv->c->x+1][pmv->c->y].etat){
                    pmv->c=&((*carte)->grille.tabGrille[pmv->c->x+1][pmv->c->y]);
                    pmv->r=pmv->c->Rectangle;
                    pmv->d=1;
                }
            }
            break;
            default: break;
        }
        if((*carte)->etat_brouillard == 1)(*carte)->etat_brouillard = 0;
        if(temp != (*carte)->nZone){
            chargement_Zone(map,renderer,(*carte)->nZone);
        }
    }
}


/**
*
*\fn int affp(p_mv * pmv,SDL_Renderer *renderer)
*\param pmv structure d'un personnage
*\param renderer rendu de la fenetre
*\brief fonction qui affiche le personnage
*/

//affiche le personnage
int affp(p_mv * pmv,SDL_Renderer *renderer){
    if(pmv->e == -1){
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
        SDL_RenderFillRect(renderer, &pmv->r);
        SDL_SetRenderDrawColor(renderer,0, 255, 0, 255);
        SDL_RenderDrawPoint(renderer,pmv->r.x+(pmv->r.w/2),pmv->r.y+(pmv->r.h/2));
    }
    else{
        SDL_Surface* perso=NULL;
        SDL_Texture * tperso=NULL;
        char * empSprit1 = malloc(sizeof(char)*30);
        char * empSprit2 = malloc(sizeof(char)*30);
        if(pmv->e == 0){
            //Nord
            if(pmv->d == 0){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "dos2.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Est
            else if(pmv->d == 1){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "prof1_2.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Sud
            else if(pmv->d == 2){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "face2.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Ouest
            else if(pmv->d == 3){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "prof2_2.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }else{
                printf("Erreur : la direction n'existe pas\n");
                return -2;
            }
        }else if(pmv->e == 1){
            //Nord
            if(pmv->d == 0){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "dos1.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Est
            else if(pmv->d == 1){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "prof1_1.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Sud
            else if(pmv->d == 2){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "face1.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Ouest
            else if(pmv->d == 3){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "prof2_1.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }else{
                printf("Erreur : la direction n'existe pas\n");
                return -2;
            }
        }else if(pmv->e == 2){
            //Nord
            if(pmv->d == 0){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "dos3.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Est
            else if(pmv->d == 1){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "prof1_3.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Sud
            else if(pmv->d == 2){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "face3.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }
            //Ouest
            else if(pmv->d == 3){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "prof2_3.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                SDL_RenderCopy(renderer, tperso, NULL, &(pmv->r));
            }else{
                printf("Erreur : la direction n'existe pas\n");
                return -2;
            }
        }
        free(empSprit1);
        free(empSprit2);
        SDL_DestroyTexture(tperso);
    }
    return 0;
}

/**
*
*\fn void col_p(SDL_Rect * obj_r,p_mv * pp)
*\param pp structure d'un personnage
*\param obj_r objet avec quoi il y a la collision
*\brief fonction qui s'occupe des collisions
*/

//fonction qui s'occupe des collisions
void col_p(SDL_Rect * obj_r,p_mv * pp){
        //Collision entre la partie haute du personnage et la partie haute de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= (obj_r->x+obj_r->w) && pp->r.y == obj_r->y) || ((pp->r.x+pp->r.w) >= obj_r->x && (pp->r.x+pp->r.w) <= (obj_r->x+obj_r->w) && pp->r.y == obj_r->y)){
            pp->r.y += 1;
        }
        //Collision entre la partie haute du personnage et la partie basse de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= (obj_r->x+obj_r->w) && pp->r.y == (obj_r->y+obj_r->h)) || ((pp->r.x+pp->r.w) >= obj_r->x && (pp->r.x+pp->r.w) <= (obj_r->x+obj_r->w) && pp->r.y == (obj_r->y+obj_r->h))){
            pp->r.y += 1;
        }

        //Collision entre la partie droite du personnage et la partie droite de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= (obj_r->y+obj_r->h) && (pp->r.x+pp->r.w) == (obj_r->x+obj_r->w)) || ((pp->r.y+pp->r.h) >= obj_r->y && (pp->r.y+pp->r.h) <= (obj_r->y+obj_r->h) && (pp->r.x+pp->r.w) == (obj_r->x+obj_r->w))){
            pp->r.x -= 1;
        }
        //Collision entre la partie droite du personnage et la partie gauche de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= (obj_r->y+obj_r->h) && (pp->r.x+pp->r.w) == obj_r->x) || ((pp->r.y+pp->r.h) >= obj_r->y && (pp->r.y+pp->r.h) <= (obj_r->y+obj_r->h) && (pp->r.x+pp->r.w) == obj_r->x)){
            pp->r.x -= 1;
        }
        //Collision entre la partie basse du personnage et la partie basse de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= (obj_r->x+obj_r->w) && (pp->r.y+pp->r.h) == (obj_r->y+obj_r->h)) || ((pp->r.x+pp->r.w) >= obj_r->x && (pp->r.x+pp->r.w) <= (obj_r->x+obj_r->w) && (pp->r.y+pp->r.h) == (obj_r->y+obj_r->h))){
            pp->r.y -= 1;
        }
        //Collision entre la partie basse du personnage et la partie haute de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= (obj_r->x+obj_r->w) && (pp->r.y+pp->r.h) == obj_r->y) || ((pp->r.x+pp->r.w) >= obj_r->x && (pp->r.x+pp->r.w) <= (obj_r->x+obj_r->w) && (pp->r.y+pp->r.h) == obj_r->y)){
            pp->r.y -= 1;
        }

        //Collision entre la partie gauche du personnage et la partie droite de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= (obj_r->y+obj_r->h) && pp->r.x == (obj_r->x+obj_r->w)) || ((pp->r.y+pp->r.h) >= obj_r->y && (pp->r.y+pp->r.h) <= (obj_r->y+obj_r->h) && pp->r.x == (obj_r->x+obj_r->w))){
            pp->r.x += 1;
        }
        //Collision entre la partie gauche du personnage et la partie gauche de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= (obj_r->y+obj_r->h) && pp->r.x == obj_r->x) || ((pp->r.y+pp->r.h) >= obj_r->y && (pp->r.y+pp->r.h) <= (obj_r->y+obj_r->h) && pp->r.x == obj_r->x)){
            pp->r.x += 1;
        }
}


/**
*
*\fn p_eq *initp_eq(char* nom,int pv,char * nomATQ1,char * nomATQ2,char * nomATQspe)
*\param nom prenom du personnage
*\param pv les pv du personnage
*\param nomATQ1 nom de l'attaque de base du personnage
*\param nomATQ2 nom de l'attaque particuliere de personnage
*\param nomATQspe nom de l'attaque special du personnage dans le cauchemar
*\brief fonction qui creer le personnage de l'equipe avec les parametres
*/
p_eq *initp_eq(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp){
    p_eq * pe=malloc(sizeof(p_eq));
    pe->nom=nom;
    pe->pv=pv;
    pe->nomATQ1=nomATQ1;
    pe->nomATQspe=nomATQspe;
    pe->vitesse=vitesse;
    pe->combatant=init_combatant(nom,pv,nomATQ1,nomATQspe,vitesse,camp);

    return pe;
}

/**
*
*\fn void desctruction_p_eq(p_mv * p)
*\param p strcuture du personnage 
*\brief fonction qui detruit les personnages de l'equipe
*/
void desctruction_p_eq(p_mv * p){
    int i;
    int nb_allie=0;
        for (i=0;i<4;i++){
            if(p->equipe[i]!=NULL){
                nb_allie++;
            }
        }
    for(i=0;i<nb_allie;i++){
        desctruction_combatant(p->equipe[i]->combatant,nb_allie);
        free(p->equipe[i]);
    }
    
}

//construit un point
p_mv initp(carte_t * carte,case_t * c){
    p_mv p;
    p.carte = carte;
    p.c = c;
    p.r = p.c->Rectangle;
    p.d=0;
    p.e=0;
    p.nom="alex";
    int i ;
    for (i=0;i<4;i++){
        p.equipe[i]=NULL;
    }
    p.equipe[0]=initp_eq("alex",100,"Attaque 1","Attaque spe",50,0);
    return p;
}

