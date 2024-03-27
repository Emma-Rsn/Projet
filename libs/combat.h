#ifndef __COMBAT_H__
#define __COMBAT_H__

//#include "../libs/commun.h"
/**
*
*\struct combattant_s
*\param nom prenom du combattant
*\param pv les pv du combattant
*\param vitesse vitesse du combattant
*\param nomATQ1 nom de l'attaque de base du combattant
*\param nomATQspe nom de l'attaque special du combattant dans le cauchemar
*\brief structure de combattant 
*/


struct combattant_s{
    char * nom;
    int pv;
    int vitesse;
    char * nomATQ1;
    char * nomATQspe;
    int mort;
    int camp; //0 alliee, 1 ennemi
    SDL_Surface * po;
};

struct combat_s{
    combattant_t * combattant[8];
    combattant_t * ennemi[4];
    combattant_t * allie[4];
    int nb_point;
    float mult;
    int indice_combattant;
    int indice_ennemi;
    int nb_ennemi;
    int nb_allie;
    int num_tour;
    //barre de cauchemard
};

int compare_vitesse_enc( const void * const combattant1 , const void * const combattant2 ) ;
int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2);
int debut_combat(SDL_Event event,pnj_t * ennemi,p_mv * pp);
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,p_mv * pp);
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,pnj_t * ennemi,combattant_t *combattant,int Nbennemi,combat_t * combat);
int attaque_ennemi(combattant_t *combattantAt,int nb_combattant,combattant_t *combattant[]);
int affiche_pv(int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_GEcran,SDL_Rect r_DEcran,combat_t *combat);
int affiche_point(int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, combat_t * combat);
void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture,SDL_Texture *Texture2);
void desctruction_combattant(combattant_t * combattant);
combattant_t *init_combattant(char* nom,int pv,char * nomATQ1,char * nomATQspe,int vitesse,int camp,char * portrait);
void aff(combattant_t * combattant);
int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat);
combat_t * init_combat();
#endif