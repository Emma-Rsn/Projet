#ifndef __COMBAT_H__
#define __COMBAT_H__


int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp);
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi);
int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer);
#endif