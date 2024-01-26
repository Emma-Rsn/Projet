#include <SDL2/SDL.h>

SDL_Event event;
//structure du point
typedef struct point point_mv;
struct point{
    //coordonées du point
    int x;
    int y;
    //methode
    void (*ppinput)(point_mv*);
    point_mv (*pinipoint)(void);
    void (*pprintp)(point_mv*,SDL_Renderer*);
};

//detection de touche presser et modification de la vitesse
void pinput(point_mv * pmv){
    //si une touche est presser
    if(event.type == SDL_KEYDOWN){
        //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_z: pmv->y -= 1; break;
            case SDLK_s: pmv->y += 1; break;
            case SDLK_q: pmv->x -= 1; break;
            case SDLK_d: pmv->x += 1; break;
            default: break;
        }
        printf("%d",pmv->x);
    }
}

//affiche le point
void affp(point_mv * pmv,SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,0, 255, 0, 255);
    SDL_RenderDrawPoint(renderer,pmv->x,pmv->y);
}

//construit un point
point_mv initpoint(){
    point_mv p;
    p.x=200;
    p.y=200;
    p.ppinput=pinput;
    p.pinipoint=initpoint;
    p.pprintp=affp;
    return p;
}