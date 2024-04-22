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



void lower(char *input, char *output){
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        output[i] = tolower(input[i]);
    }
    output[i] = '\0';
}


/**
*
*\fn void pinput(p_mv * pmv,SDL_Event event)
*\param event permet de savoir si il y a un evenement
*\param pmv structure du personnage
*\brief fonction qui detecte si unetouche est presser et modifie ses coordonées
*/

//detection de touche presser et modification des coordonées
void pinput(p_mv * pmv,SDL_Event event,carte_t ** carte,map_t *map,SDL_Renderer * renderer,int * transi,Mix_Music* gMusic,int * toucheDeplacement){
    if(*transi || pmv->lock){
        while (SDL_PollEvent(&event) != 0);
    }else{
        int temp = (*carte)->nZone;
        int xdep = pmv->c->x;
        int ydep = pmv->c->y;
        int ddep = *pmv->d;
        carte_t * dcartec = *carte;
        int Haut;
        int Bas;
        int Gauche;
        int Droite;
        int block = 0;
        

        switch(*toucheDeplacement){
            case 0:
                Haut=SDLK_z;
                Bas=SDLK_s;
                Gauche=SDLK_q;
                Droite=SDLK_d;
                break;
            case 1:
                Haut=SDLK_w;
                Bas=SDLK_s;
                Gauche=SDLK_a;
                Droite=SDLK_d;
                break;
            case 2:
                Haut=SDLK_UP;
                Bas=SDLK_DOWN;
                Gauche=SDLK_LEFT;
                Droite=SDLK_RIGHT;
                break;
            default:
            break;


        }
        //si une touche est presser
        if(event.type == SDL_KEYDOWN && ((event.key.keysym.sym == Haut) || (event.key.keysym.sym == Bas) || (event.key.keysym.sym == Gauche) || (event.key.keysym.sym == Droite))){
            //quelle touche est presser
            if(event.key.keysym.sym==Haut){

                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->y == 0){
                    if((*carte)->grille.tabGrille[pmv->c->x+1][pmv->c->y].etat == 2 || (*carte)->grille.tabGrille[pmv->c->x-1][pmv->c->y].etat == 2){
                        *carte= &(map->tabMap[(*carte)->xcarte-1][(*carte)->ycarte]);
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][LARG-1]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=0;
                        *transi = 1;
                    }else{
                        *pmv->d=0;
                        block = 1;
                    }
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->y == 0){
                        *carte= &(map->tabMap[(*carte)->xcarte-1][(*carte)->ycarte]);
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][LARG-1]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=0;
                        *transi = 1;
                    }else{
                        if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y-1].etat){
                            pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y-1]);
                            pmv->r=pmv->c->Rectangle;
                            *pmv->d=0;
                        }else{
                            *pmv->d=0;
                            block = 1;
                        }
                    }
                }
            }
            if(event.key.keysym.sym==Bas){
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->y == (LARG-1)){
                    if((*carte)->grille.tabGrille[pmv->c->x+1][pmv->c->y].etat == 2 || (*carte)->grille.tabGrille[pmv->c->x-1][pmv->c->y].etat == 2){
                        *carte= &map->tabMap[(*carte)->xcarte+1][(*carte)->ycarte];
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][0]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=2;
                        *transi = 1;
                    }else{
                        *pmv->d=2;
                        block = 1;
                    }
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->y == (LARG-1)){
                        *carte= &map->tabMap[(*carte)->xcarte+1][(*carte)->ycarte];
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][0]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=2;
                        *transi = 1;
                    }else{
                        if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y+1].etat){
                            pmv->c=&((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y+1]);
                            pmv->r=pmv->c->Rectangle;
                            *pmv->d=2;
                        }else{
                            *pmv->d=2;
                            block = 1;
                        }
                    }
                }
                }
            
                if(event.key.keysym.sym==Gauche){
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->x == 0){
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y-1].etat == 2 && pmv->c->y == LARG-1){
                        *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte-1];
                        pmv->c=&((*carte)->grille.tabGrille[LONG-1][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=3;
                        *transi = 1;
                    }else if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y+1].etat == 2 && pmv->c->y == 0){
                        *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte-1];
                        pmv->c=&((*carte)->grille.tabGrille[LONG-1][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=3;
                        *transi = 1;
                    }else{
                        *pmv->d=3;
                        block = 1;
                    }
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->x == 0){
                        *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte-1];
                        pmv->c=&((*carte)->grille.tabGrille[LONG-1][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=3;
                        *transi = 1;
                    }else{
                        if((*carte)->grille.tabGrille[pmv->c->x-1][pmv->c->y].etat){
                            pmv->c=&((*carte)->grille.tabGrille[pmv->c->x-1][pmv->c->y]);
                            pmv->r=pmv->c->Rectangle;
                            *pmv->d=3;
                        }else{
                            *pmv->d=3;
                            block = 1;
                        }
                    }
                }
                }
                if(event.key.keysym.sym==Droite){
                if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 3 && pmv->c->x == (LONG-1)){
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y-1].etat == 2 && pmv->c->y == LARG-1){
                        *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte+1];
                        pmv->c=&((*carte)->grille.tabGrille[0][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=1;
                        *transi = 1;
                    }else if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y+1].etat == 2 && pmv->c->y == 0){
                        *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte+1];
                        pmv->c=&((*carte)->grille.tabGrille[0][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=1;
                        *transi = 1;
                    }else{
                        *pmv->d=1;
                        block = 1;
                    }
                }else{
                    if((*carte)->grille.tabGrille[pmv->c->x][pmv->c->y].etat == 2 && pmv->c->x == (LONG-1)){
                        *carte= &map->tabMap[(*carte)->xcarte][(*carte)->ycarte+1];
                        pmv->c=&((*carte)->grille.tabGrille[0][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=1;
                        *transi = 1;
                    }else if((*carte)->grille.tabGrille[pmv->c->x+1][pmv->c->y].etat){
                        pmv->c=&((*carte)->grille.tabGrille[pmv->c->x+1][pmv->c->y]);
                        pmv->r=pmv->c->Rectangle;
                        *pmv->d=1;
                    }else{
                            *pmv->d=1;
                            block = 1;
                        }
                }
                }
            //deplacement statique
            if(((temp != (*carte)->nZone) && !zone_fini(*map))){
                *carte = dcartec;
                pmv->c = &((*carte)->grille.tabGrille[xdep][ydep]);
                pmv->r = pmv->c->Rectangle;
                pmv->e = 0;
                *transi = 0;
            }else{
                if(*pmv->d != ddep){
                    *carte = dcartec;
                    pmv->c = &((*carte)->grille.tabGrille[xdep][ydep]);
                    pmv->r = pmv->c->Rectangle;
                    pmv->e = 0;
                    *transi = 0;
                }else{
                    if(*(pmv->frame) != 0){
                        if(pmv->e == 1){
                            pmv->e = 2;
                        }else{
                            pmv->e = 1;
                        }
                    }else if(!block){
                        *(pmv->frame) = 1;
                        pmv->e = 1;
                    }
                }
            }

            if((*carte)->etat_brouillard == 1)(*carte)->etat_brouillard = 0;
            if(temp != (*carte)->nZone){
                chargement_Zone(map,renderer,(*carte)->nZone,gMusic);
            }
        }
    }
}

int affp(p_mv * pmv,SDL_Renderer *renderer,SDL_Event event){
    SDL_Surface* perso=NULL;
    SDL_Texture * tperso=NULL;
    char * empSprit1 = malloc(sizeof(char)*30);
    int x = pmv->c->Rectangle.x;
    int y = pmv->c->Rectangle.y;
    char * name = malloc(sizeof(pmv->nom)+1);
    lower(pmv->nom,name);
    int nbMaxFrame = (FPS/10)*4;
    if(*(pmv->frame) != 0){
        pmv->lock = 1;
        if(pmv->e == 1){
            //Nord
            if(*pmv->d == 0){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "dos1");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                y = (y+TAILLE_CASE)-(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }
            //Est
            else if(*pmv->d == 1){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "prof1_1");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                x = (x-TAILLE_CASE)+(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }
            //Sud
            else if(*pmv->d == 2){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "face1");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                y = (y-TAILLE_CASE)+(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }
            //Ouest
            else if(*pmv->d == 3){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "prof2_1");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                x = (x+TAILLE_CASE)-(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }else{
                printf("Erreur : la direction n'existe pas\n");
                return -2;
            }
        }else if(pmv->e == 2){
            //Nord
            if(*pmv->d == 0){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "dos3");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                y = (y+TAILLE_CASE)-(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }
            //Est
            else if(*pmv->d == 1){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "prof1_3");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                x = (x-TAILLE_CASE)+(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
                SDL_FreeSurface(perso);
            }
            //Sud
            else if(*pmv->d == 2){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "face3");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                y = (y-TAILLE_CASE)+(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }
            //Ouest
            else if(*pmv->d == 3){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "prof2_3");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    //fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
                    return -1;
                }
                tperso = SDL_CreateTextureFromSurface(renderer, perso);
                SDL_FreeSurface(perso);
                x = (x+TAILLE_CASE)-(int)(TAILLE_CASE*((float)(*pmv->frame)/nbMaxFrame));
            }else{
                printf("Erreur : la direction n'existe pas\n");
                return -2;
            }
        }
        SDL_Rect aff = {x,y,TAILLE_CASE,TAILLE_CASE};
        SDL_RenderCopy(renderer, tperso, NULL, &aff);
        *(pmv->frame) = *(pmv->frame)+1;
        if(*(pmv->frame) > nbMaxFrame){
            *(pmv->frame) = 0;
            pmv->e=0;
            pmv->lock = 0;
        }else{
            if(*(pmv->frame) != 0){
                if(*(pmv->frame) < (nbMaxFrame/4)){
                    pmv->e = 2;
                }else if(*(pmv->frame) < (nbMaxFrame/4)*2){
                    pmv->e = 1;
                }else if(*(pmv->frame) < (nbMaxFrame/4)*3){
                    pmv->e = 2;
                }else{
                    pmv->e = 1;
                }
            }else{
                *(pmv->frame) = 1;
                pmv->e = 1;
            }
        }
        if(*(pmv->frame) != 0) while (SDL_PollEvent(&event) != 0);

    }else{//pas d'animation
        if(pmv->e == 0){
            //Nord
            if(*pmv->d == 0){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "dos2");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
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
            else if(*pmv->d == 1){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "prof1_2");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
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
            else if(*pmv->d == 2){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "face2");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
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
            else if(*pmv->d == 3){
                strcpy(empSprit1,"");
                strcat(empSprit1, "./sprite/");
                strcat(empSprit1,name);
                strcat(empSprit1, "prof2_2");
                if(*pmv->Nightmare)strcat(empSprit1, "corrup");
                strcat(empSprit1, ".png");
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
        }else{
            printf("Erreur d'etat\n");
            return -3;
        }
    }

    free(name);
    free(empSprit1);
    SDL_DestroyTexture(tperso);
    return 0;
}


/**
*
*\fn void desctruction_p_eq(p_mv * p)
*\param p strcuture du personnage 
*\brief fonction qui detruit les personnages de l'equipe et le pointeur sur frame
*/

void desctruction_p_eq(p_mv * p){
    free(p->frame);
    free(p->d);
    free(p->Nightmare);
    free(p->NightP);
    int i;
    int nb_allie=0;
        for (i=0;i<4;i++){
            if(p->equipe[i]!=NULL){
                nb_allie++;
            }
        }
    for(i=0;i<nb_allie;i++){
        desctruction_combattant(p->equipe[i]);
    }
    free(p);
    
}

/**
*
*\fn p_mv * initp()
*\brief fonction qui creer le personnage joue
*/
p_mv * initp(){
    p_mv * p = malloc(sizeof(p_mv));
    p->d=malloc(sizeof(int));
    p->frame = malloc(sizeof(int));
    p->Nightmare = malloc(sizeof(int));
    p->NightP = malloc(sizeof(int));
    *p->d=0;
    p->e=0;
    *p->Nightmare = 0;
    p->NightMax = 100;
    *p->NightP = 0;
    *(p->frame) = 0;
    p->lock = 0;
    return p;
}

/**
*
*\fn void remplirp(p_mv * p,case_t * c,int leader)
*\param p structure personnage joue
*\param c case du joueur
*\param leader numero du personnage jouer (son type)
*\brief fonction qui remplie le personnage joue
*/
void remplirp(p_mv * p,case_t * c,int leader){
    p->c = c;
    p->r = c->Rectangle;
    if(*p->NightP == p->NightMax){
        *p->Nightmare = 1;
    }else{
        *p->Nightmare = 0;
    }
    int i ;
    for (i=0;i<4;i++){
        p->equipe[i]=NULL;
    }
    //leader
    switch (leader)
    {
    case 0://Alex
    p->nom="Alex";
    p->equipe[0]=init_combattant(p->nom,190,60,0,136,135,0,2,27,0,190);
        break;

    case 1://Lou
    p->nom="Lou";
    p->equipe[0]=init_combattant(p->nom,180,75,0,138,137,1,3,23,0,180);
        break;

    case 2://Finn
    p->nom="Finn";
    p->equipe[0]=init_combattant(p->nom,230,70,0,140,139,2,3,15,0,230);
        break;

    case 3://Ada
    p->nom="Ada";
    p->equipe[0]=init_combattant(p->nom,135,65,0,142,141,3,2,36,0,135);
        break;
    
    default:
    p->nom="Default";
    p->equipe[0]=init_combattant(p->nom,200,50,0,136,135,0,2,20,0,200);
        break;
    }
}
     

void transition(SDL_Renderer * renderer,int * transi,int we,int he){
    if(*transi){
        SDL_Surface* surface = SDL_CreateRGBSurface(0, we, he, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        // Copie les pixels du rendu actuel dans la surface
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        // Créer une texture à partir de la surface
        SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_Rect ecran  = {0,0,we,he};
        int i;
        SDL_Event event;
        for(i=255;i>0;i = i-4){
            SDL_PollEvent(&event);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,0,0,0,i);
            SDL_RenderFillRect(renderer, &ecran);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        *transi = 0;
    }
}
