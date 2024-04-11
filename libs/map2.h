#ifndef __MAP2_H__
#define __MAP2_H__


//#include "../libs/commun.h"
#include "../libs/OBJ.h"


struct case_s{
    SDL_Rect Rectangle;
    int x;
    int y;
    int etat;// si 0 alors obstacles dans la case 1 case libre 2 case libre mais en bordure 3 case libre mais en bordure finale
    int ntexture;
};


struct grille_s{
    case_t tabGrille[LONG][LARG];
};


struct carte_s{
    int xcarte;
    int ycarte;
    int etat_brouillard; // si 1 alors la carte est couverte de brouillard(pas encore explorée), si 0 alors la carte a été explorée
    Uint8 r;// couleurs du background de chaque carte
    Uint8 g; 
    Uint8 b;
    Uint8 a;
    int nZone;
    int nbObj;
    obj_t tabObj[20];
    grille_t grille; //quadrillage des cases dans une seule carte
};


struct map_s{
    carte_t tabMap[ROWS][COLUMNS];
    char *** tabPath;
    int nbTexture[10];
    SDL_Texture ** tabTexture;
    int zoneChargee;
    int Nightmare;
    int nbN;
    int nvZone;
    int nvEquipe;
    float bonusEquipeN;
    int bonusZoneN;
    int argent;
};

case_t creation_case();
grille_t creation_grille(int w, int h, int bord);
carte_t creation_carte(int w, int h,int x,int y);
map_t creation_map (int w, int h);
int afficher_grille(grille_t grille, SDL_Renderer *renderer);
int betaAfficherMap(SDL_Renderer *renderer,map_t * map,carte_t * cartec);
int creer_map(map_t * map);
int remplir_map(map_t *map);
int afficher_zone (map_t m);
float min(float a, float b);
int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec);
int chargement_Zone(map_t * map,SDL_Renderer *renderer,int nZone,Mix_Music* gMusic);
void lumiere(SDL_Renderer *renderer,carte_t *cartec,case_t *c);
int load_layout(carte_t * c,char * namefile);
int detruire_tab_path(map_t *map);
int nb_texture_chargement(map_t *map, char* namefile);
int creation_tab_path(map_t *map,char * namefile);
int creation_tab_texture(map_t *map,SDL_Renderer *renderer,int nbZone,int free);
#endif