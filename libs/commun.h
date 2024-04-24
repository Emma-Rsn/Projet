#ifndef __COMMUN_H__
#define __COMMUN_H__

#define TaillePo 300

#define LONG 30 //grille 
#define LARG 16 //grille

#define ROWS 6 //map
#define COLUMNS 6 //map
#define NB_ZONE 5

#define TAILLE_CASE 64

//nombre de frame par secondes voulu
#define FPS 60
#define BONUS_EQUIPE_N 3
#define BONUS_ZONE_N 1
#define PLUS_BONUS_EQUIPE 0.5
#define PLUS_BONUS_ZONE 1

#define NB_PARAM 38


typedef struct obj_s obj_t;
typedef struct combat_s combat_t;
typedef struct combattant_s combattant_t;
typedef struct ennemi_s ennemi_t;
typedef struct pnj_s pnj_t;
typedef struct personnage p_mv;

typedef struct artefact_s artefact_t;
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
#include <unistd.h>

#include "../libs/save.h"
#include "../libs/printImg.h"

#include "../libs/texte.h"
#include "../libs/map.h"
#include "../libs/printImg.h"
#include "../libs/save.h"
#include "../libs/menu.h"
#include "../libs/OBJ.h"
#include "../libs/combat.h"
#include "../libs/musique.h"

#include "../libs/Pmov.h"
#endif