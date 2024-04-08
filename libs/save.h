#ifndef __SAVE_H__
#define __SAVE_H__
//#include "../libs/commun.h"

extern int save_settings(void);

extern int load_settings(int * lEcran,int * LEcran);

int save_pos(int xcarte,int ycarte,int xpos,int ypos);

int load_pos(int * xcarte,int * ycarte,int * xpos,int * ypos);

#endif