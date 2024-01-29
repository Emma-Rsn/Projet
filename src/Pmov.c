#include <SDL2/SDL.h>

typedef struct personnage p_mv;
struct personnage{
    //coordonées du personnage et taille dans un rect
    SDL_Rect r;//{x,y,w,h}
    int d; //direction orienté{N,E,S,W}{0,1,2,3}
    int e; //etat du personnage
};

//detection de touche presser et modification des coordonées
void pinput(p_mv * pmv,SDL_Event event){
    //si une touche est presser
    if(event.type == SDL_KEYDOWN){
        //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_z: pmv->r.y -= 1; break;
            case SDLK_s: pmv->r.y += 1; break;
            case SDLK_q: pmv->r.x -= 1; break;
            case SDLK_d: pmv->r.x += 1; break;
            default: break;
        }
    }
}

//affiche le personnage
void affp(p_mv * pmv,SDL_Renderer *renderer){
    if(pmv->e == -1){
        SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
        SDL_RenderFillRect(renderer, &pmv->r);
        SDL_SetRenderDrawColor(renderer,0, 255, 0, 255);
        SDL_RenderDrawPoint(renderer,pmv->r.x+(pmv->r.w/2),pmv->r.y+(pmv->r.h/2));
    }
}


void col_p(SDL_Rect * obj_r,p_mv * pp){
        //Collision entre la partie haute du personnage et la partie haute de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= obj_r->w && pp->r.y == obj_r->y) || (pp->r.w >= obj_r->x && pp->r.w <= obj_r->w && pp->r.y == obj_r->y)){
            pp->r.y += 1;
        }
        //Collision entre la partie haute du personnage et la partie basse de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= obj_r->w && pp->r.y == obj_r->h) || (pp->r.w >= obj_r->x && pp->r.w <= obj_r->w && pp->r.y == obj_r->h)){
            pp->r.y += 1;
        }
        //Collision entre la partie droite du personnage et la partie droite de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= obj_r->h && pp->r.w == obj_r->w) || (pp->r.h >= obj_r->y && pp->r.h <= obj_r->h && pp->r.w == obj_r->w)){
            pp->r.x -= 1;
        }
        //Collision entre la partie droite du personnage et la partie gauche de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= obj_r->h && pp->r.w == obj_r->x) || (pp->r.h >= obj_r->y && pp->r.h <= obj_r->h && pp->r.w == obj_r->x)){
            pp->r.x -= 1;
        }
        //Collision entre la partie basse du personnage et la partie basse de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= obj_r->w && pp->r.h == obj_r->h) || (pp->r.w >= obj_r->x && pp->r.w <= obj_r->w && pp->r.h == obj_r->h)){
            pp->r.y -= 1;
        }
        //Collision entre la partie basse du personnage et la partie haute de l'obj
        if((pp->r.x >= obj_r->x && pp->r.x <= obj_r->w && pp->r.h == obj_r->y) || (pp->r.w >= obj_r->x && pp->r.w <= obj_r->w && pp->r.h == obj_r->y)){
            pp->r.y -= 1;
        }
        //Collision entre la partie gauche du personnage et la partie droite de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= obj_r->h && pp->r.x == obj_r->w) || (pp->r.h >= obj_r->y && pp->r.h <= obj_r->h && pp->r.x == obj_r->w)){
            pp->r.x -= 1;
        }
        //Collision entre la partie gauche du personnage et la partie gauche de l'obj
        if((pp->r.y >= obj_r->y && pp->r.y <= obj_r->h && pp->r.x == obj_r->x) || (pp->r.h >= obj_r->y && pp->r.h <= obj_r->h && pp->r.x == obj_r->x)){
            pp->r.x -= 1;
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
    p.e=-1;
    return p;
}