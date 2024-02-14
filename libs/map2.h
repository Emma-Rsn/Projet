#ifndef __MAP2_H__
#define __MAP2_H__


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

#define LONG 30
#define LARG 16

#define ROWS 3
#define COLUMNS 3

typedef struct case_s case_t;
struct case_s{
    SDL_Rect Rectangle;
    int etat;// si 0 alors pas d'obstacles dans la case
};

typedef struct grille_s grille_t;
struct grille_s{
    case_t tabGrille[LONG][LARG];
};

typedef struct carte_s carte_t;
struct carte_s{
    int etat_brouillard; // si 1 alors la carte est couverte de brouillard(pas encore explorée), si 0 alors la carte a été explorée
    Uint8 r;
    Uint8 g; 
    Uint8 b;
    Uint8 a;
    grille_t grille; //quadrillage des cases dans une seule carte
    //carte_t * nord; // si NULL alors pas de lien avec la carte se trouvant au nord ou bordure de carte
    //carte_t * sud; // si NULL alors pas de lien avec la carte se trouvant au sud ou bordure de carte
    //carte_t * est; // si NULL alors pas de lien avec la carte se trouvant à l'est ou bordure de carte
    //carte_t * ouest; // si NULL alors pas de lien avec la carte se trouvant à l'ouest ou bordure de carte
};

typedef struct map_s map_t;
struct map_s{
    carte_t tabMap[ROWS][COLUMNS];
};

case_t creation_case(int w, int h);
grille_t creation_grille(int w, int h);
carte_t creation_carte(int w, int h);
map_t creation_map (int w, int h);
int afficher_grille(grille_t grille, SDL_Renderer *renderer);

#endif