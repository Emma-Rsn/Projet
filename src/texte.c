#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

int affiche_texte(){
    if(TTF_Init() != 0){
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    return -1;
    }

    TTF_Font  *police = NULL;
    police= TTF_OpenFont("../fonts/alagard.ttf", 12); 

    if(police != 0){
        SDL_Color noir = {0, 0, 0}; //attention ce n'est pas un Uint32
        SDL_Surface* texte = TTF_RenderText_Blended(police, "Bonjour", noir) ;
        //affichage
        SDL_FreeSurface(texte); //On oublie toujours pas
        TTF_CloseFont(police);
    }
    else{
        TTF_CloseFont(police);
        printf("probleme a l'ouverture de la police");
        return -1;

    }

    TTF_Quit();
    return 0;
}

