#ifndef __TEXTE_H__
#define __TEXTE_H__

//#include "../libs/commun.h"



int aff_boite_dia(SDL_Renderer * rendu,int po,int *we,int* he,char * message,map_t * map);
void debut_dialogue(SDL_Event event,p_mv * pp,int *etat_dialogue,case_t * c);
void pnj_dialogue (SDL_Event event,SDL_Renderer * renderer,int * he,int * we,map_t * map,int *etat_dialogue,int num_dialogue,p_mv * pp);
void debut_dialogue_carte(carte_t * cartec,SDL_Event event,p_mv * pp,int *etat_dialogue);
void dialogue_carte(carte_t * cartec,int *we,int *he,SDL_Event event,SDL_Renderer * renderer,map_t * map,int *etat_dialogue,p_mv * pp);
void pnj_dialogue_enc(SDL_Event event,SDL_Renderer * renderer,int * he,int * we,map_t * map,int *etat_dialogue,void *num_dialogue,p_mv * pp);
#endif
