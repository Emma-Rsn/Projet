#ifndef __SAVE_H__
#define __SAVE_H__
//#include "../libs/commun.h"

extern int save_settings(void);

extern int load_settings(int * lEcran,int * LEcran);

int save_pos(int xcarte,int ycarte,p_mv pmv,map_t map,int touche,int leader);

int load_pos(int * xcarte,int * ycarte,int * xpos,int * ypos,map_t * map,int * pv,p_mv * pmv,int ** tabparam,int * touche,int * leader);

void nouvelle_partie(int param);

void effacer_sauvg();

void save_ennemi(carte_t cartec,obj_t ennemi);

void load_ennemi(map_t * map);

#endif