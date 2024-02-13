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
#include "../libs/commun.h"


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
int affiche_texte(SDL_Renderer * rendu,Liste *liste,int dim){

    if(liste->etat > 0){
        //initialisation des variables
        SDL_Surface * texte=NULL;
        SDL_Texture * texture=NULL;
        
        SDL_Rect r_text={10,10,0,0};

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
                TTF_Quit();
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

//affiche une boite de dialogue en finction du msg de l'ec de la liste et d'un portrait
int aff_boite_dia(SDL_Renderer * rendu,Liste *liste,SDL_Surface * po,int we,int he){
    TTF_Font  * police = TTF_OpenFont("fonts/alagard.ttf", 20); 
    if (police == NULL){
            TTF_CloseFont(police);
            TTF_Quit();
            fprintf(stderr,"probleme a l'ouverture de la police\n");
            return -1;
    }
    SDL_Color blanc = {255, 255, 255};
    SDL_Rect r_po = {0,he-TaillePo,TaillePo,TaillePo};
    SDL_Rect r_text = {TaillePo,he-TaillePo,we-TaillePo,TaillePo};

    //boite portrait
    SDL_Texture * po_texture = SDL_CreateTextureFromSurface(rendu, po);
    SDL_RenderCopy(rendu, po_texture, NULL, &r_po);
    SDL_DestroyTexture(po_texture);

    //boite texte
    int * w = malloc(sizeof(int));
    int * h = malloc(sizeof(int));
    *w= 10;
    *h= 10;
    SDL_SetRenderDrawColor(rendu,0,0,0,255);
    SDL_RenderFillRect(rendu, &r_text);
    SDL_Surface * texte = TTF_RenderText_Solid(police, liste->ec->message, blanc);
    if (!texte){
        SDL_FreeSurface(texte);
        TTF_CloseFont(police);
        police = NULL;
        TTF_Quit();
        printf("probleme de texte\n");
        return -1;
    }
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(rendu,texte);
    SDL_Rect textRect = {r_text.x+5, r_text.y+5, texte->w, texte->h};
    if(!text_texture){
        printf("Impossible de creeer la texture\n");
        TTF_CloseFont(police);
        police = NULL;
        TTF_Quit();
        return -1;
    }
    SDL_RenderCopy(rendu, text_texture, NULL, &textRect);
    free(w);
    free(h);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte); 
    SDL_DestroyTexture(text_texture);
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
void dialogue (SDL_Event event,Liste * liste){

	//si une touche est presser
    if(event.type == SDL_KEYDOWN ){
       //quelle touche est presser
        switch(event.key.keysym.sym){
            case SDLK_e:  
                    //dernier texte dans la structure
                    if(liste->ec->suivant==NULL){
                        liste->etat = 2;
                        liste_premier(liste);
                    }
                    else{
                        //premier element de la structure
                        if(liste->etat == 0){
                            liste->etat=1;
                        }
                        //suite des elments de la structure
                        else if (liste->etat == 1){
                            liste_suivant(liste);        
                        }
                    }
            	break;	
            default:break;
        }
        
    }

}

int liste_vide(Liste * liste){
    if(liste->premier == NULL){
        return 1;
    }else{
        return 0;
    }
}

void liste_premier(Liste * liste){
    if(liste != NULL){
        liste->ec = liste->premier;
    }
}


void liste_suivant(Liste * liste){
    if(liste->ec != NULL){
        liste->ec = liste->ec->suivant;
    }
}

/**
*
*\fn initialisation()
*\brief focntion pour initialiser la structure liste
*
*/

//focntion pour initialiser la structure liste
Liste * initialisation()
{
    Liste *liste = malloc(sizeof(*liste));

    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    liste->premier = NULL;
    liste_premier(liste);
    liste->etat=0;

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
    
    nouveau->message = malloc(strlen(nvMess)+1);
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
    liste_premier(liste);
}



//fonction pour supprimer le premier element de la liste
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
*\fn afficherListe(Liste *liste)
*\param liste liste chaine du texte a afficher
*\brief fonction qui detruit la structure liste 
*
*/


//fonction qui detruit la structure liste 
void liste_destruction(Liste * liste){
	liste_premier(liste);
	
	while(liste->ec != NULL){
        liste_suppression(liste);
        liste_premier(liste);
	}
    free(liste);
    liste = NULL;
}
