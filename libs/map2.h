#ifndef __MAP2_H__
#define __MAP2_H__


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include "../libs/commun.h"

typedef struct case_s case_t;
struct case_s{
    SDL_Rect Rectangle;
    int x;
    int y;
    int etat;// si 0 alors obstacles dans la case 1 case libre 2 case libre mais en bordure 3 case libre mais en bordure finale
    int ntexture;
};

typedef struct grille_s grille_t;
struct grille_s{
    case_t tabGrille[LONG][LARG];
};

typedef struct carte_s carte_t;
struct carte_s{
    int xcarte;
    int ycarte;
    int etat_brouillard; // si 1 alors la carte est couverte de brouillard(pas encore explorée), si 0 alors la carte a été explorée
    Uint8 r;// couleurs du background de chaque carte
    Uint8 g; 
    Uint8 b;
    Uint8 a;
    int nZone;
    grille_t grille; //quadrillage des cases dans une seule carte
    //carte_t * nord; // si NULL alors pas de lien avec la carte se trouvant au nord ou bordure de carte
    //carte_t * sud; // si NULL alors pas de lien avec la carte se trouvant au sud ou bordure de carte
    //carte_t * est; // si NULL alors pas de lien avec la carte se trouvant à l'est ou bordure de carte
    //carte_t * ouest; // si NULL alors pas de lien avec la carte se trouvant à l'ouest ou bordure de carte
};

typedef struct map_s map_t;
struct map_s{
    carte_t tabMap[ROWS][COLUMNS];
    int nbtextur;
    SDL_Texture ** tabTexture;
};

case_t creation_case();
grille_t creation_grille(int w, int h, int bord);
carte_t creation_carte(int w, int h,int x,int y);
map_t creation_map (int w, int h);
int afficher_grille(grille_t grille, SDL_Renderer *renderer);
int betaAfficherMap(SDL_Renderer *renderer,map_t * map,carte_t * cartec);
int remplir_map(map_t *map);
int afficher_zone (map_t m);
float min(float a, float b);
int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec);
int chargement_Zone(map_t * map,SDL_Renderer *renderer,int nZone);
#endif