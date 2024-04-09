#ifndef __MENU_H__
#define __MENU_H__

int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run);
void console_aff(SDL_Renderer * renderer,int we,int he,char * command);
int console_command(SDL_Event event,char * command);
int menu_option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run);
#endif