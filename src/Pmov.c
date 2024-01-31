#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

typedef struct personnage p_mv;
struct personnage{
    //coordonées du personnage et taille dans un rect
    SDL_Rect r;//{x,y,w,h}
    int d; //direction orienté{N,E,S,O}{0,1,2,3}
    int e; //etat du personnage
    char * nom;
};

//detection de touche presser et modification des coordonées
void pinput(p_mv * pmv,SDL_Event event){
    //si une touche est presser
    if(event.type == SDL_KEYDOWN){
        //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_z: pmv->r.y -= 1,pmv->d = 0; break;
            case SDLK_s: pmv->r.y += 1,pmv->d = 2; break;
            case SDLK_q: pmv->r.x -= 1,pmv->d = 3; break;
            case SDLK_d: pmv->r.x += 1,pmv->d = 1; break;
            default: break;
        }
        if(pmv->e == 0){
            pmv->e=1;
        }else if(pmv->e == 1){
            pmv->e=2;
        }else if(pmv->e == 2){
            pmv->e=1;
        }
    }else if(event.type == SDL_KEYUP && pmv->e != -1){
        pmv->e=0;
    }
}

//affiche le personnage
int affp(p_mv * pmv,SDL_Renderer *renderer){
    if(pmv->e == -1){
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
        SDL_RenderFillRect(renderer, &pmv->r);
        SDL_SetRenderDrawColor(renderer,0, 255, 0, 255);
        SDL_RenderDrawPoint(renderer,pmv->r.x+(pmv->r.w/2),pmv->r.y+(pmv->r.h/2));
    }
    else{
        SDL_Surface* perso;
        SDL_Texture * tperso;
        char * empSprit1 = malloc(sizeof(char)*30);
        char * empSprit2 = malloc(sizeof(char)*30);
        if(pmv->e == 0){
            //Nord
            if(pmv->d == 0){
                strcpy(empSprit1,"./sprite/");
                strcpy(empSprit2, "face2.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                strcpy(empSprit2, "face1.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                strcpy(empSprit2, "face3.png");
                strcat(empSprit1,pmv->nom);
                strcat(empSprit1, empSprit2);
                perso = IMG_Load(empSprit1);
                if (perso == NULL) {
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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
                    fprintf(stderr, "Erreur lors du chargement du sprite: %s\n", SDL_GetError());
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


//construit un point
p_mv initp(int x,int y){
    p_mv p;
    p.r.x=x;
    p.r.y=y;
    p.r.w=32;
    p.r.h=32;
    p.d=0;
    p.e=0;
    p.nom="alex";
    return p;
}