#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

/*structure d'une carte
    toute les textured de fond (sous quelle forme ?)
    les zones de sortie (en rect sdl)
    pointeur sur carte adjc 1 a 4
    
*/
typedef struct carte_s carte_t;
struct carte_s{
    int test;
}
//matrice de carte