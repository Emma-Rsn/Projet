#ifndef __COMMUN_H__
#define __COMMUN_H__

#define TaillePo 300

#define LONG 30 //grille 
#define LARG 16 //grille

#define ROWS 6 //map
#define COLUMNS 6 //map
#define NB_ZONE 5

#define MIN_ZONE2 8
#define MAX_ZONE2 10

#define TAILLE_ZONE3 6

#define MIN_ZONE4 8
#define MAX_ZONE4 10

#define MIN_ZONE5 6
#define MAX_ZONE5 7

typedef struct obj_s obj_t;
typedef struct combat_s combat_t;
typedef struct combattant_s combattant_t;
typedef struct ennemi_s ennemi_t;
typedef struct pnj_s pnj_t;
typedef struct personnage p_mv;

typedef struct case_s case_t;
typedef struct grille_s grille_t;
typedef struct carte_s carte_t;
typedef struct map_s map_t;

typedef struct mess_t mess_s;
typedef struct Liste Liste;

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../libs/save.h"
#include "../libs/printImg.h"

#include "../libs/texte.h"
#include "../libs/map2.h"
#include "../libs/printImg.h"
#include "../libs/save.h"
#include "../libs/menu.h"
#include "../libs/OBJ.h"
#include "../libs/combat.h"
#include "../libs/musique.h"

#include "../libs/Pmov.h"
#endif