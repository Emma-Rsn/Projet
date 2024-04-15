#ifndef __TEXTE_H__
#define __TEXTE_H__

//#include "../libs/commun.h"


struct mess_t
{
    char * message;
    mess_s *suivant;
};


struct Liste
{
    mess_s * premier;
    mess_s * ec;
    int etat; //0 = pas d'affichage debut liste 1 == affichage premier 2 == affichage element 3 == affichage dernier
};

extern SDL_Event event;

int aff_boite_dia(SDL_Renderer * rendu,int po,int *we,int* he,char * message,map_t * map);
void debut_dialogue(SDL_Event event,p_mv * pp,int *etat_dialogue,case_t * c);
void pnj_dialogue (SDL_Event event,SDL_Renderer * renderer,int * he,int * we,map_t * map,int *etat_dialogue,int num_dialogue);
void debut_dialogue_carte(carte_t * cartec,SDL_Event event,p_mv * pp,int *etat_dialogue);
void dialogue_carte(carte_t * cartec,int *we,int *he,SDL_Event event,SDL_Renderer * renderer,map_t * map,int *etat_dialogue);
#endif
