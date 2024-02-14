#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

#define LONG 16
#define LARG 9

#define ROWS 3
#define COLUMNS 3

/*structure d'une carte
    toute les textured de fond (sous quelle forme ?)
    les zones de sortie (en rect sdl)
    pointeur sur carte adjc 1 a 4
    
*/

typedef struct case_s case_t;
struct case_s{
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
    //grille_t grille; //quadrillage des cases dans une seule carte
    //carte_t * nord; // si NULL alors pas de lien avec la carte se trouvant au nord ou bordure de carte
    //carte_t * sud; // si NULL alors pas de lien avec la carte se trouvant au sud ou bordure de carte
    //carte_t * est; // si NULL alors pas de lien avec la carte se trouvant à l'est ou bordure de carte
    //carte_t * ouest; // si NULL alors pas de lien avec la carte se trouvant à l'ouest ou bordure de carte
};

typedef struct map_s map_t;
struct map_s{
    carte_t tabMap[LONG][LARG];
};

case_t creation_case(void);
grille_t creation_grille(void);
carte_t creation_carte(void);
carte_t color_carte(carte_t c, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
map_t creation_map (void);