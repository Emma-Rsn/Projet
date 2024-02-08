//
//texte.c
//Created by Pasquier Lina 
//

/**
*\file texte.c
*\brief Programme qui affiche un texte sur la fenetre
*\author Pasquier Lina
*\date 28 janvier 2024
*\version 0.2
*
*
*
*/


#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>


/**
*
*\fn affiche_texte(SDL_Renderer * rendu,char *mess,int dim)
*\param mess message a afficher
*\param dim dimension de la fenetre 
*\param rendu rendu de la fenetre
*
*
*
*/





int affiche_texte(SDL_Renderer * rendu,char *mess,int dim,SDL_Color color){


    //initialisation des variables
    SDL_Surface * texte=NULL;
    SDL_Texture * texture=NULL;
    
    SDL_Rect r_text={10,10,0,0};

    TTF_Font  *police = TTF_OpenFont("fonts/alagard.ttf", 20); 

    //SDL_Color blanc = {255, 255, 255};

    
    if (!police){
    	SDL_FreeSurface(texte);
    	TTF_CloseFont(police);
    	TTF_Quit();
    	fprintf(stderr,"probleme a l'ouverture de la police");
        return -1;
    }

    if(police){
        
    	//recupere le texte a afficher
        texte = TTF_RenderText_Solid(police, mess, color) ;

        if (!texte){
        	SDL_FreeSurface(texte);
    		TTF_CloseFont(police);
        	TTF_Quit();
        	printf("probleme de texte");
        	return -1;
        }
        TTF_CloseFont(police);

        //afiche le texte 
        texture =SDL_CreateTextureFromSurface(rendu,texte);
        SDL_FreeSurface(texte); 
        
        if(!texture){
        	printf("Impossible de creeer la texture");
        	TTF_Quit();
        	return -1;
        }
        if(SDL_QueryTexture(texture,NULL,NULL,&r_text.w,&r_text.h)!=0){
        	printf("Impossible de charger le texte");
        	TTF_Quit();
        	return -1;
        
        }
        
        //changer la position du texte 
        r_text.y=(dim-r_text.w)/2;
        r_text.x=(dim-r_text.w)/2;
        SDL_RenderCopy(rendu,texture,NULL,&r_text);
        /*if(test!=0){
        	printf("Impossible d'afficher le texte");
        	TTF_Quit();
        	return -1;
        }*/
        SDL_DestroyTexture(texture);
        

        
    }

    return 0;
}







int i=0;

/**
*
*\fn dialogue(SDL_Renderer * rendu,char *mess,int dim)
*\param mess message a afficher
*\param dim dimension de la fenetre 
*\param rendu rendu de la fenetre
*
*
*
*/
char *mess[2]={"The Last Nightmare","Bonjour"};

int dialogue (SDL_Event event,int * etat){
	SDL_Color blanc = {255, 255, 255};
	SDL_Color noir = {0, 0,0};
	//si une touche est presser
    if(event.type == SDL_KEYDOWN ){
       //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_f:  
            	i++;
            	break;	
            default:break;
        }
        
    }
    return i;
}


struct mess {
    char * mess;
    char * suivant;
}







