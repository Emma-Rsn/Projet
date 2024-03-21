#ifndef __COMBAT_H__
#define __COMBAT_H__

//#include "../libs/commun.h"
/**
*
*\struct combatant_s
*\param nom prenom du combatant
*\param pv les pv du combatant
*\param vitesse vitesse du combatant
*\param nomATQ1 nom de l'attaque de base du combatant
*\param nomATQspe nom de l'attaque special du combatant dans le cauchemar
*\brief structure de combatant 
*/


struct combatant_s{
    char * nom;
    int pv;
    int vitesse;
    char * nomATQ1;
    char * nomATQspe;
    int mort;
    int camp; //0 alliee, 1 ennemi
};

int compare_vitesse_enc( const void * const combatant1 , const void * const combatant2 ) ;
int compare_vitesse(const combatant_t * const combatant1,const combatant_t * const combatant2);
int debut_combat(SDL_Event event,pnj_t * ennemi,p_mv * pp);
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,p_mv * pp);
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,int *nb_point,combatant_t *combatant,int Nbennemi);
int attaque_ennemi(combatant_t *combatantAt,int nb_combatant,int allie,combatant_t *combatant[]);
int affiche_pv(pnj_t * ennemi,int *we,int *he,SDL_Renderer * renderer,combatant_t * combatant);
int affiche_point(float mult, int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, int *nb_point);
void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture,SDL_Texture *Texture2);
void desctruction_combatant(combatant_t * combatant,int nb_combatant);
combatant_t *init_combatant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp);
void aff(combatant_t * combatant);
#endif