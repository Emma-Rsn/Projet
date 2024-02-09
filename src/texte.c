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
#include "../libs/texte.h"


/**
*
*\fn affiche_texte(SDL_Renderer * rendu,Liste* liste,int dim,int * etat)
*\param liste structure du message a afficher
*\param dim dimension de la fenetre 
*\param rendu rendu de la fenetre
*\param etat etat du texte afficher
*
*
*
*/




//fonction qui affiche du texte 
int affiche_texte(SDL_Renderer * rendu,Liste *liste,int dim,int * etat){
    printf("%d\n",*etat);


    if(*etat==1){
        //initialisation des variables
        SDL_Surface * texte=NULL;
        SDL_Texture * texture=NULL;
        
        SDL_Rect r_text={10,10,0,0};

        TTF_Font  *police = TTF_OpenFont("fonts/alagard.ttf", 20); 

        SDL_Color blanc = {255, 255, 255};


        
        if (!police){
            SDL_FreeSurface(texte);
            TTF_CloseFont(police);
            TTF_Quit();
            fprintf(stderr,"probleme a l'ouverture de la police\n");
            return -1;
        }


        if(police){
            
            //recupere le texte a afficher
            texte = TTF_RenderText_Solid(police, liste->ec->message, blanc) ;

            if (!texte){
                SDL_FreeSurface(texte);
                TTF_CloseFont(police);
                TTF_Quit();
                printf("probleme de texte\n");
                return -1;
            }
            TTF_CloseFont(police);

            //afiche le texte 
            texture =SDL_CreateTextureFromSurface(rendu,texte);
            SDL_FreeSurface(texte); 
            
            if(!texture){
                printf("Impossible de creeer la texture\n");
                TTF_Quit();
                return -1;
            }
            if(SDL_QueryTexture(texture,NULL,NULL,&r_text.w,&r_text.h)!=0){
                printf("Impossible de charger le texte\n");
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

    }

    return 0;
}






/**
*
*\fn dialogue(SDL_Event event,int * etat,Liste * liste)
*\param event permet de savoir si il y a un evenement
*\param etat etat du texte afficher
*\param liste liste chaine du texte a afficher
*
*
*
*/

//fonction pour afficher le texte ou non par rapport a son etat
void dialogue (SDL_Event event,int * etat,Liste * liste){

	//si une touche est presser
    if(event.type == SDL_KEYDOWN ){
       //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_e:  
                    //dernier texte dans la structure
                    if(liste->ec->suivant==NULL){
                        printf("%s","test");
                        liste->test=2;
                        *etat=0;
                    }
                    else{
                        *etat=1;
                        //premier element de la structure
                        if(liste->test == 0){
                            liste->test=1;

                        }
                        //suite des elments de la structure
                        else if (liste->test==1){
                            printf("%p",liste->ec->suivant);
                            liste->ec=liste->ec->suivant;               
                        
                        }

                    }

                    
                    
            	break;	
            default:break;
        }
        
    }

}

/**
*
*\fn initialisation()
*\brief focntion pour initialiser la structure liste
*
*/


//focntion pour initialiser la structure liste
Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));

    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->premier = NULL;
    liste->ec=liste->premier;
    liste->test=0;

    return liste;
}
/**
*
*\fn insertion(Liste *liste, char * nvMess)
*\param liste liste chaine du texte a afficher
*\param nvMess inserer un message dans la liste
*\brief fonction pour inserer un element a la structure liste
*
*/


//fonction pour inserer un element a la structure liste
void insertion(Liste *liste, char * nvMess)
{
    /* Création du nouvel élément */
    mess_s *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    nouveau->message = nvMess;

    /* Insertion de l'élément au début de la liste */
    
    if(liste->premier==NULL){
        nouveau->suivant = NULL;

    }
    else{
        nouveau->suivant = liste->premier;  
    }
    liste->premier = nouveau;
    
}



//fonction pour supprimer un element de la liste
void suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        mess_s *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
} 

/**
*
*\fn afficherListe(Liste *liste)
*\param liste liste chaine du texte a afficher
*\brief fonction qui affiche la structure liste
*
*/

//fonction qui affiche la structure liste
void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    mess_s *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%s -> ", actuel->message);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}
/**
*
*\fn afficherListe(Liste *liste)
*\param liste liste chaine du texte a afficher
*\brief fonction qui detruit la structure liste 
*
*/


//fonction qui detruit la structure liste 
void destruction(Liste * liste){
	liste->ec=liste->premier;
    
	
	while(liste->ec->suivant!=NULL){
        mess_s * sup=liste->ec;
        liste->ec=liste->ec->suivant;
        sup->suivant=NULL;
        free(sup);
		
	}
    free(liste->ec);
    free(liste);

}
