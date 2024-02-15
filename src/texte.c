//
//texte.c
//Created by Pasquier Lina 
//

/**
*\file texte.c
*\brief Programme qui affiche un texte sur la fenetre
*\author Pasquier Lina 
*\date 28 janvier 2024
*\version 0.3
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
*\fn int affiche_texte(SDL_Renderer * rendu,Liste* liste,int he,int * etat)
*\param liste structure du message a afficher
*\param he heension de la fenetre 
*\param rendu rendu de la fenetre
*\param etat etat du texte afficher
*\brief fonction qui affiche du texte 
*
*
*/




//fonction qui affiche du texte 
int affiche_texte(SDL_Renderer * rendu,Liste *liste,int he,int we,int * etat,SDL_Rect r_text){

    if(*etat==1){
        //initialisation des variables
        SDL_Surface * texte=NULL;
        SDL_Texture * texture=NULL;
        
        

        TTF_Font  * police = TTF_OpenFont("fonts/alagard.ttf", 20); 

        SDL_Color blanc = {255, 255, 255};

        if (!police){
            SDL_FreeSurface(texte);
            TTF_CloseFont(police);
            TTF_Quit();
            fprintf(stderr,"probleme a l'ouverture de la police\n");
            return -1;
        }

        else if(police){
            
            //recupere le texte a afficher
            texte = TTF_RenderText_Solid(police, liste->ec->message, blanc) ;

            if (!texte){
                SDL_FreeSurface(texte);
                TTF_CloseFont(police);
                police = NULL;
                printf("probleme de texte\n");
                return -1;
            }
            
            TTF_CloseFont(police);
            police = NULL;

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

            //r_text.y=(he-r_text.w)/2;
            //r_text.x=(we-r_text.w)/2;

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
*\fn void dialogue(SDL_Event event,int * etat,Liste * liste)
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
                        liste->test=0;
                        liste_premier(liste);
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
                            liste_suivant(liste);              
                        
                        }
                    }
            	break;	
            default:break;
        }
        
    }

}


/**
*
*\fn int liste_vide(Liste * liste)
*\param liste liste chainee du texte a afficher
*\brief fonction pour regarder si la liste chainee est vide 
*/

//fonction pour regarder si la liste chainee est vide 
int liste_vide(Liste * liste){
    if(liste->premier == NULL){
        return 1;
    }else{
        return 0;
    }
}

/**
*
*\fn void liste_premier(Liste * liste)
*\param liste liste chainee du texte a afficher
*\brief fonction pour aller au premier element de la liste chainee
*/

//fonction pour aller au premier element de la liste chainee
void liste_premier(Liste * liste){
    if(liste != NULL){
        liste->ec = liste->premier;
    }
}

/**
*
*\fn void liste_suivant(Liste * liste)
*\param liste liste chainee du texte a afficher
*\brief fonction pour aller a l'element suivant de la liste chainee
*/

//fonction pour aller a l'element suivant de la liste chainee
void liste_suivant(Liste * liste){
    if(liste->ec != NULL){
        liste->ec = liste->ec->suivant;
    }
}

/**
*
*\fn Liste * initialisation()
*\brief fonction pour initialiser la liste chainee
*
*/

//fonction pour initialiser la liste chainee
Liste * initialisation()
{
    Liste *liste = malloc(sizeof(*liste));

    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    liste->premier = NULL;
    liste_premier(liste);
    liste->test=0;

    return liste;
}
/**
*
*\fn void insertion(Liste *liste, char * nvMess)
*\param liste liste chainee du texte a afficher
*\param nvMess inserer un message dans la liste
*\brief fonction pour inserer un element a la liste chainee
*
*/


//fonction pour inserer un element a la liste chainee
void insertion(Liste *liste, char * nvMess)
{
    /* Création du nouvel élément */
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    mess_s *nouveau = malloc(sizeof(mess_s));

    if (nouveau == NULL)
    {
        printf("Probleme d'allocation de memoire\n");
        exit(EXIT_FAILURE);
    }
    
    nouveau->message = malloc(strlen(nvMess));
    strcpy(nouveau->message,nvMess);

    /* Insertion de l'élément au début de la liste */
    
    if(liste_vide(liste)){
        nouveau->suivant = NULL;
    }
    else{
        nouveau->suivant = liste->premier;  
    }
    liste->premier = nouveau;
    nouveau = NULL;
}

/**
*
*\fn void liste_suppression(Liste *liste)
*\param liste liste chainee du texte a afficher
*\brief fonction pour supprimer le premier element de la liste chainee
*
*/

//fonction pour supprimer le premier element de la liste chainee
void liste_suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

     liste_premier(liste);

    if (liste->ec != NULL)
    {
        mess_s *aSupprimer = liste->ec;
        if(liste->ec->suivant != NULL){
            liste_suivant(liste);
            liste->premier = liste->ec;
        }else{
            liste->premier = NULL;
        }
        free(aSupprimer->message);
        free(aSupprimer);
    }
} 

/**
*
*\fn void afficherListe(Liste *liste)
*\param liste liste chainee du texte a afficher
*\brief fonction qui affiche la liste chainee
*
*/

//fonction qui affiche la liste chainee
void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste_premier(liste);

    while (liste->ec != NULL)
    {
        printf("%s -> ", liste->ec->message);
        liste_suivant(liste);
    }
    liste_premier(liste);
    printf("NULL\n");
}
/**
*
*\fn void liste_destruction(Liste *liste)
*\param liste liste chainee du texte a afficher
*\brief fonction qui detruit la liste chainee
*
*/


//fonction qui detruit la liste chainee
void liste_destruction(Liste * liste){
	liste_premier(liste);
	
	while(liste->ec != NULL){
        liste_suppression(liste);
        liste_premier(liste);
	}
    free(liste);
    liste = NULL;
}
