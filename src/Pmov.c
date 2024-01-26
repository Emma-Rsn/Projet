#include <SDL2/SDL.h>
const int POINT_WIDTH = 20;
const int POINT_HEIGHT = 20;


SDL_Event event;
//structure du point
typedef struct point point_mv;
struct point{
    //coordonées du point
    int x;
    int y;
    //vitesse du point
    int xV;
    int yV;
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
            case SDLK_z: pmv->yV -= POINT_HEIGHT / 2; break;
            case SDLK_s: pmv->yV += POINT_HEIGHT / 2; break;
            case SDLK_q: pmv->xV -= POINT_WIDTH / 2; break;
            case SDLK_d: pmv->xV += POINT_WIDTH / 2; break;
            default: break;
        }
    }else if(event.type == SDL_KEYUP){
        //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_z: pmv->yV += POINT_HEIGHT / 2; break;
            case SDLK_s: pmv->yV -= POINT_HEIGHT / 2; break;
            case SDLK_q: pmv->xV += POINT_WIDTH / 2; break;
            case SDLK_d: pmv->xV -= POINT_WIDTH / 2; break;
            default: break;
        }
    }
}

//affiche le point
void affp(point_mv * pmv,SDL_Renderer *renderer){
    pmv->x += pmv->xV;
    pmv->y += pmv->yV;
    SDL_RenderDrawPoint(renderer,pmv->x,pmv->y);
}

//construit un point
point_mv initpoint(){
    point_mv p;
    p.x=0;
    p.y=0;
    p.xV=0;
    p.yV=0;
    p.ppinput=pinput;
    p.pinipoint=initpoint;
    p.pprintp=affp;
    return p;
}