#ifndef __TEXTE_H__
#define __TEXTE_H__

extern SDL_Event event;
int affiche_texte(SDL_Renderer * rendu,char *mess,int dim,SDL_Color color);
void dialogue (SDL_Renderer * rendu,int dim);


#endif
