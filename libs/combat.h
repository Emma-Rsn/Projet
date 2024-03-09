#ifndef __COMBAT_H__
#define __COMBAT_H__



int debut_combat(SDL_Event event,pnj_t * ennemi,SDL_Rect * obj_r,p_mv * pp);
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,p_mv * pp);
int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer,p_eq * pp);
int attaque_ennemi(pnj_t * ennemi,p_mv * p,int nb_allie);
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,p_mv * pp,int nb_allie,int *nb_point);
int affiche_point(float mult,int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_basEcran,int *nb_point);
void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture);
#endif