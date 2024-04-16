#ifndef __SAVE_H__
#define __SAVE_H__
//#include "../libs/commun.h"

extern int save_settings(void);

extern int load_settings(int * lEcran,int * LEcran);

int save_pos(int xcarte,int ycarte,p_mv pmv,map_t map);

int load_pos(int * xcarte,int * ycarte,int * xpos,int * ypos,map_t * map,int * pv,p_mv * pmv,int ** tabparam);

#endif