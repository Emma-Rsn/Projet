#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

#define LONG 16
#define LARG 9

#define ROW 3
#define COLUMN 3

/*structure d'une carte
    toute les textured de fond (sous quelle forme ?)
    les zones de sortie (en rect sdl)
    pointeur sur carte adjc 1 a 4
    
*/

typedef struct case_s case_t;
struct case_s{
    int etat;// si 0 alors pas d'obstacles dans la case
};

typedef struct carte_s carte_t;
struct carte_s{
    int etat_brouillard; // si 1 alors la carte est couverte de brouillard(pas encore explorée), si 0 alors la carte a été explorée
    SDL_Color bgColor;
    case_t grille[LONG][LARG]; //quadrillage des cases dans une seule carte
    carte_t * nord; // si NULL alors pas de lien avec la carte se trouvant au nord ou bordure de carte
    carte_t * sud; // si NULL alors pas de lien avec la carte se trouvant au sud ou bordure de carte
    carte_t * est; // si NULL alors pas de lien avec la carte se trouvant à l'est ou bordure de carte
    carte_t * ouest; // si NULL alors pas de lien avec la carte se trouvant à l'ouest ou bordure de carte
};

case_t * creation_case();
carte_t * creation_carte();
int color_carte(carte_t*c,SDL_Color Color);
int lien_carte(carte_t map[ROW][COLUMN]);
int creation_matrice(carte_t map[ROW][COLUMN]);
int destroy_case(case_t* c);
int destroy_carte(carte_t* carte);
int destroy_map(carte_t map[ROW][COLUMN]);