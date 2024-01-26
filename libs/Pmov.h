#ifndef __PMOV_H__
#define __PMOV_H__

#include <SDL2/SDL.h>

// Déclaration de la variable globale
extern SDL_Event event;

// Structure du point
typedef struct point point_mv;
struct point{
    //coordonées du point
    int x;
    int y;
    //methode
    void (*ppinput)(point_mv*);
    point_mv (*pinipoint)(void);
    void (*pprintp)(point_mv*);
};

void pinput(point_mv * pmv);

void affp(point_mv * pmv,SDL_Renderer *renderer);

point_mv initpoint();

#endif