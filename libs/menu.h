#ifndef __MENU_H__
#define __MENU_H__

int menu(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * run, int * etatoption, int * toucheDeplacement,map_t * map,int * leader) ;
void console_aff(SDL_Renderer * renderer,int we,int he,char * command);
int console_command(SDL_Event event,char * command);
int menu_option(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * run, int * etatoption,map_t * map);
int option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * etatoption,int * toucheDeplacement,map_t * map);
int menu_gameOver(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,p_mv* personnage,map_t * map,int * leader);
int magasin(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,p_mv* personnage,map_t * map);
int inventaire(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, map_t * map);
int menu_FinPartie(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, int * run, p_mv * personnage, map_t * map,int * etat_boss) ;
int choix_perso(int * we, int * he, SDL_Event event, SDL_Renderer * renderer, map_t * map,int * leader) ;
#endif