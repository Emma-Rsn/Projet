#ifndef __MENU_H__
#define __MENU_H__

int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,int * etatoption,int * toucheDeplacement,map_t * map);
void console_aff(SDL_Renderer * renderer,int we,int he,char * command);
int console_command(SDL_Event event,char * command);
int menu_option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,int * etatoption);
int option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * etatoption,int * toucheDeplacement);
int menu_gameOver(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,p_mv* personnage,map_t * map);
int magasin(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,p_mv* personnage,map_t * map);
int inventaire(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, map_t * map);
#endif