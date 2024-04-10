//
//menu.c
//Created by Moreau Enzo
//

/**
*\file menu.c
*\brief programme pour afficher le menu
*\author Moreau Enzo Pasquier Lina
*\date  Janvier 2024
*\version 
*
*/


#include "../libs/commun.h"


/**
*\fn int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run)
*\param we Largeur de l'ecran
*\param he Longueur de l'ecran
*\param event permet de savoir si il y a un evenement
*\param renderer rendu de la fenetre
*\param run pointeur pour continuer le programme
*\brief fonction qui affiche et gere les texte cliquable du menu 
*/

//fonction qui affiche et gere les texte cliquable du menu dans le jeu
int menu_option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,int * etatoption){

        

        SDL_RenderClear(renderer);
        SDL_Color textColor = {255, 255, 255};

        //chargement de la police d'écriture
        TTF_Font* fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
        if (!fontT) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColorT = {43, 27, 85};

        SDL_Surface* textSurfaceT = TTF_RenderText_Solid(fontT,"The Last Nightmare", textColorT);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(fontT);
            return -1;
        }

 
        SDL_Texture* textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

        SDL_Rect  r_text_T= {((*we)/2)-((textSurfaceT->w)/2),10,textSurfaceT->w,textSurfaceT->h};
        SDL_FreeSurface(textSurfaceT);

        if(SDL_QueryTexture(textTextureT,NULL,NULL,&r_text_T.w,&r_text_T.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }
        

        TTF_CloseFont(fontT);
        fontT=NULL;



        //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        
        
        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,"Quitter", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);
        

        SDL_Surface* textSurfaceC = TTF_RenderText_Solid(font,"Continuer", textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture* textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);
    

        SDL_Surface* textSurfaceO = TTF_RenderText_Solid(font,"Options", textColor);
        if (!textSurfaceO) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }
        
        SDL_Texture* textTextureO = SDL_CreateTextureFromSurface(renderer, textSurfaceO);
        

        TTF_CloseFont(font);
        font=NULL;


        //creation rectangle pour les textes
        SDL_Rect  r_text_C= {((*we)/2)-((textSurfaceC->w)/2),((*he)/3)*1-textSurfaceC->h,textSurfaceC->w,textSurfaceC->h};
        SDL_Rect  r_text_Q= {((*we)/2)-((textSurfaceQ->w)/2),((*he)/3)*2-textSurfaceQ->h,textSurfaceQ->w,textSurfaceQ->h};
        SDL_Rect  r_text_O= {((*we)/2)-((textSurfaceO->w)/2),((*he)/3)*3-textSurfaceO->h-50,textSurfaceO->w,textSurfaceO->h};
        
        
        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceO);


        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureC,NULL,NULL,&r_text_C.w,&r_text_C.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }

        if(SDL_QueryTexture(textTextureO,NULL,NULL,&r_text_O.w,&r_text_O.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }

        
        if((event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE) || (*etatoption==2)){
            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        //pour continuer le jeu
                        if((r_text_C.x<=event.button.x) && ((r_text_C.x+r_text_C.w)>=event.button.x) && ((r_text_C.y+r_text_C.h)>=event.button.y) && (r_text_C.y<=event.button.y)){
                            etat=0;
                            *etatoption=0;
                        }
                        //pour quitter le jeu
                        else if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+r_text_Q.w)>=event.button.x) && ((r_text_Q.y+r_text_Q.h)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            *etatoption=0;
                            *run=0;
                        }  

                        else if((r_text_O.x<=event.button.x) && ((r_text_O.x+r_text_O.w)>=event.button.x) && ((r_text_O.y+r_text_O.h)>=event.button.y) && (r_text_O.y<=event.button.y)){
                            etat=0;
                            *etatoption=1;
                        } 
                                            
                    }           
                }
        
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            
            SDL_RenderClear(renderer);

            
            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, &r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, &r_text_T);
            SDL_RenderCopy(renderer, textTextureO, NULL, &r_text_O);


            SDL_RenderPresent(renderer);
            SDL_Delay(100);
      
            }

        
        }
        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);
        SDL_DestroyTexture(textTextureO);


    return 0;
}

/**
*\fn int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run)
*\param we Largeur de l'ecran
*\param he Longueur de l'ecran
*\param event permet de savoir si il y a un evenement
*\param renderer rendu de la fenetre
*\param run pointeur pour continuer le programme
*\brief fonction qui affiche et gere les textes cliquable de l'ecran titre
*/

//fonction qui affiche et gere les textes cliquable de l'ecran titre
int menu(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,int * etatoption,int * toucheDeplacement){
        SDL_RenderClear(renderer);
        SDL_Color textColor = {255, 255, 255};


        //chargement de la police d'écriture
        TTF_Font* fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
        if (!fontT) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColorT = {43, 27, 85};

        SDL_Surface* textSurfaceT = TTF_RenderText_Solid(fontT,"The Last Nightmare", textColorT);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(fontT);
            return -1;
        }

 
        SDL_Texture* textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

        SDL_Rect  r_text_T= {((*we)/2)-((textSurfaceT->w)/2),textSurfaceT->h,textSurfaceT->w,textSurfaceT->h};
        SDL_FreeSurface(textSurfaceT);

        if(SDL_QueryTexture(textTextureT,NULL,NULL,&r_text_T.w,&r_text_T.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }
        

        TTF_CloseFont(fontT);
        fontT=NULL;


                //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }


        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,"Quitter", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);
        

        SDL_Surface* textSurfaceC = TTF_RenderText_Solid(font,"Continuer", textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture* textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);
        

        SDL_Surface* textSurfaceO = TTF_RenderText_Solid(font,"Options", textColor);
        if (!textSurfaceO) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }
        
        SDL_Texture* textTextureO = SDL_CreateTextureFromSurface(renderer, textSurfaceO);
        


        SDL_Surface* textSurfaceN = TTF_RenderText_Solid(font,"Nouvelle partie", textColor);
        if (!textSurfaceN) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            SDL_FreeSurface(textSurfaceO);
            return -1;
        }
        
        SDL_Texture* textTextureN = SDL_CreateTextureFromSurface(renderer, textSurfaceN);

        TTF_CloseFont(font);
        font=NULL;


        //creation rectangle pour les textes
        SDL_Rect  r_text_C= {((*we)/2)-((textSurfaceC->w)/2),((*he)/4)*1-textSurfaceC->h+100,textSurfaceC->w,textSurfaceC->h};
        SDL_Rect  r_text_Q= {((*we)/2)-((textSurfaceQ->w)/2),(*he/4)*4-textSurfaceQ->h-100,textSurfaceQ->w,textSurfaceQ->h};
        SDL_Rect  r_text_O= {((*we)/2)-((textSurfaceO->w)/2),((*he)/4)*3-textSurfaceO->h-50,textSurfaceO->w,textSurfaceO->h};
        SDL_Rect  r_text_N= {((*we)/2)-((textSurfaceN->w)/2),(*he/4)*2-textSurfaceN->h+50,textSurfaceN->w,textSurfaceN->h};
        

        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceO);
        SDL_FreeSurface(textSurfaceN);


        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureC,NULL,NULL,&r_text_C.w,&r_text_C.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }

         if(SDL_QueryTexture(textTextureO,NULL,NULL,&r_text_O.w,&r_text_O.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }


        if(SDL_QueryTexture(textTextureN,NULL,NULL,&r_text_N.w,&r_text_N.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }

        

            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0 ) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        //pour continuer le jeu
                        if((r_text_C.x<=event.button.x) && ((r_text_C.x+r_text_C.w)>=event.button.x) && ((r_text_C.y+r_text_C.h)>=event.button.y) && (r_text_C.y<=event.button.y)){
                            etat=0;
                        }

                        //pour quitter le jeu
                        else if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+r_text_Q.w)>=event.button.x) && ((r_text_Q.y+r_text_Q.h)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            *run=0;
                        }
                        //Pour aller au menu option
                        else if((r_text_O.x<=event.button.x) && ((r_text_O.x+r_text_O.w)>=event.button.x) && ((r_text_O.y+r_text_O.h)>=event.button.y) && (r_text_O.y<=event.button.y)){
                            *etatoption=3;
                            option(we,he,event,renderer,etatoption,toucheDeplacement);
                        }  
                        //Pour creer une nouvelle partie
                        else if((r_text_N.x<=event.button.x) && ((r_text_N.x+r_text_N.w)>=event.button.x) && ((r_text_N.y+r_text_N.h)>=event.button.y) && (r_text_N.y<=event.button.y)){
                            etat=0;
                        }  
        
                                            
                    }           
                }
        
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            
            SDL_RenderClear(renderer);

            
            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, &r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, &r_text_T);
            SDL_RenderCopy(renderer, textTextureO, NULL, &r_text_O);
            SDL_RenderCopy(renderer, textTextureN, NULL, &r_text_N);


            SDL_RenderPresent(renderer);
            SDL_Delay(100);
      
            }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);
        SDL_DestroyTexture(textTextureO);
        SDL_DestroyTexture(textTextureN);

        SDL_RenderPresent(renderer);
        
        



    return 0;
}


int option(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * etatoption,int * toucheDeplacement){

    if(*etatoption==1 || *etatoption==3){


        SDL_Color textColor = {255, 255, 255};

                //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }


        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,"Retour", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);


        SDL_Surface* textSurfaceQwerty = TTF_RenderText_Solid(font,"Qwerty", textColor);
        if (!textSurfaceQwerty) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQwerty = SDL_CreateTextureFromSurface(renderer, textSurfaceQwerty);



        SDL_Surface* textSurfaceAzerty = TTF_RenderText_Solid(font,"Azerty", textColor);
        if (!textSurfaceAzerty) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureAzerty = SDL_CreateTextureFromSurface(renderer, textSurfaceAzerty);



        SDL_Surface* textSurfacefleches = TTF_RenderText_Solid(font,"fleches", textColor);
        if (!textSurfacefleches) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTexturefleches = SDL_CreateTextureFromSurface(renderer, textSurfacefleches);
        


        TTF_CloseFont(font);
        font=NULL;


        //creation rectangle pour les textes
        SDL_Rect  r_text_Q= {((*we)/2)-((textSurfaceQ->w)/2),(*he/4)*4-textSurfaceQ->h-100,textSurfaceQ->w,textSurfaceQ->h};
        SDL_Rect  r_text_Qwerty= {((*we)/4)*1-((textSurfaceQwerty->w)/2),(*he/2),textSurfaceQwerty->w,textSurfaceQwerty->h};
        SDL_Rect  r_text_Azerty= {((*we)/2)*1-((textSurfaceAzerty->w)/2),(*he/2),textSurfaceAzerty->w,textSurfaceAzerty->h};
        SDL_Rect  r_text_fleches= {((*we)/4)*3-((textSurfacefleches->w)/2),(*he/2),textSurfacefleches->w,textSurfacefleches->h};
 

        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceQwerty);
        SDL_FreeSurface(textSurfaceAzerty);
        SDL_FreeSurface(textSurfacefleches);

        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }
        if(SDL_QueryTexture(textTextureQwerty,NULL,NULL,&r_text_Qwerty.w,&r_text_Qwerty.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }
        if(SDL_QueryTexture(textTextureAzerty,NULL,NULL,&r_text_Azerty.w,&r_text_Azerty.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }
        if(SDL_QueryTexture(textTexturefleches,NULL,NULL,&r_text_fleches.w,&r_text_fleches.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

 

            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){


                        //pour quitter les options
                        if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+r_text_Q.w)>=event.button.x) && ((r_text_Q.y+r_text_Q.h)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            //retour au menu option
                            if(*etatoption==1){
                                *etatoption=2;
                            }
                            //retour a l'ecran titre
                            else{
                                *etatoption=0;
                            }
                        }

                        if((r_text_Qwerty.x<=event.button.x) && ((r_text_Qwerty.x+r_text_Qwerty.w)>=event.button.x) && ((r_text_Qwerty.y+r_text_Qwerty.h)>=event.button.y) && (r_text_Qwerty.y<=event.button.y)){
                            *toucheDeplacement=1;
                            
                        }

                        if((r_text_Azerty.x<=event.button.x) && ((r_text_Azerty.x+r_text_Azerty.w)>=event.button.x) && ((r_text_Azerty.y+r_text_Azerty.h)>=event.button.y) && (r_text_Azerty.y<=event.button.y)){
                            *toucheDeplacement=0;
                           
                        }

                        if((r_text_fleches.x<=event.button.x) && ((r_text_fleches.x+r_text_fleches.w)>=event.button.x) && ((r_text_fleches.y+r_text_fleches.h)>=event.button.y) && (r_text_fleches.y<=event.button.y)){
                            *toucheDeplacement=2;
                           
                        }
             
                    }   

                }

            
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer,100,100,100,255);
            SDL_RenderDrawRect(renderer,& r_text_Azerty);
            SDL_RenderDrawRect(renderer, &r_text_Qwerty);
            SDL_RenderDrawRect(renderer, &r_text_fleches);
            if(*toucheDeplacement==0){
                SDL_RenderFillRect(renderer, &r_text_Azerty);

            }
            if(*toucheDeplacement==1){
                SDL_RenderFillRect(renderer, &r_text_Qwerty);

            }
            if(*toucheDeplacement==2){
                SDL_RenderFillRect(renderer, &r_text_fleches);

            }

            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            
            SDL_RenderCopy(renderer, textTextureQwerty, NULL, &r_text_Qwerty);
            SDL_RenderCopy(renderer, textTextureAzerty, NULL, &r_text_Azerty);
            SDL_RenderCopy(renderer, textTexturefleches, NULL, &r_text_fleches);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);

        

      
            }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureQwerty);
        SDL_DestroyTexture(textTextureAzerty);
        SDL_DestroyTexture(textTexturefleches);


        
        }
    return 0;
        
    }



//fonction qui affiche et gere les textes cliquable de l'ecran titre
int menu_gameOver(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,p_mv* personnage){
    if(personnage->equipe[0]->pv<=0){

        SDL_RenderClear(renderer);
        SDL_Color textColor = {255, 255, 255};


        //chargement de la police d'écriture
        TTF_Font* fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
        if (!fontT) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColorT = {150, 0, 0};

        SDL_Surface* textSurfaceT = TTF_RenderText_Solid(fontT,"Game Over", textColorT);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(fontT);
            return -1;
        }

 
        SDL_Texture* textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

        SDL_Rect  r_text_T= {((*we)/2)-((textSurfaceT->w)/2),((*he)/3),textSurfaceT->w,textSurfaceT->h};
        SDL_FreeSurface(textSurfaceT);

        if(SDL_QueryTexture(textTextureT,NULL,NULL,&r_text_T.w,&r_text_T.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }
        

        TTF_CloseFont(fontT);
        fontT=NULL;


                //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }


        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,"Quitter", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);
        

        SDL_Surface* textSurfaceC = TTF_RenderText_Solid(font,"Rejouer", textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture* textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);
        

        


        SDL_Surface* textSurfaceN = TTF_RenderText_Solid(font,"Magasin", textColor);
        if (!textSurfaceN) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }
        
        SDL_Texture* textTextureN = SDL_CreateTextureFromSurface(renderer, textSurfaceN);

        TTF_CloseFont(font);
        font=NULL;


        //creation rectangle pour les textes

        SDL_Rect  r_text_Q= {((*we)/2)-((textSurfaceQ->w)/2),(*he/4)*4-textSurfaceQ->h-100,textSurfaceQ->w,textSurfaceQ->h};
        SDL_Rect  r_text_N= {((*we)/2)-((textSurfaceN->w)/2),(*he/4)*2-textSurfaceN->h+50,textSurfaceN->w,textSurfaceN->h};
        SDL_Rect  r_text_C= {((*we)/2)-((textSurfaceC->w)/2),(*he/4)*3-textSurfaceC->h,textSurfaceC->w,textSurfaceC->h};
        

        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceN);


        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureC,NULL,NULL,&r_text_C.w,&r_text_C.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }



        if(SDL_QueryTexture(textTextureN,NULL,NULL,&r_text_N.w,&r_text_N.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }

        

            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0 ) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        //pour continuer le jeu
                        if((r_text_C.x<=event.button.x) && ((r_text_C.x+r_text_C.w)>=event.button.x) && ((r_text_C.y+r_text_C.h)>=event.button.y) && (r_text_C.y<=event.button.y)){
                            etat=0;
                        }

                        //pour quitter le jeu
                        else if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+r_text_Q.w)>=event.button.x) && ((r_text_Q.y+r_text_Q.h)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            *run=0;
                        }
                        //Pour aller au magasin
                        else if((r_text_N.x<=event.button.x) && ((r_text_N.x+r_text_N.w)>=event.button.x) && ((r_text_N.y+r_text_N.h)>=event.button.y) && (r_text_N.y<=event.button.y)){
                            etat=0;
                            magasin(we,he,event,renderer,run,personnage);
                        }  
        
                                            
                    }           
                }
        
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            
            SDL_RenderClear(renderer);

            
            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, &r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, &r_text_T);
            SDL_RenderCopy(renderer, textTextureN, NULL, &r_text_N);


            SDL_RenderPresent(renderer);
            SDL_Delay(100);
      
            }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);
        SDL_DestroyTexture(textTextureN);

        SDL_RenderPresent(renderer);
        
        


    }
    return 0;
}

//fonction qui affiche et gere les textes cliquable de l'ecran titre
int magasin(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int * run,p_mv* personnage){


        SDL_RenderClear(renderer);
        SDL_Color textColor = {255, 255, 255};




        //chargement de la police d'écriture
        TTF_Font* fontT = TTF_OpenFont("fonts/alagard.ttf", 75);
        if (!fontT) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }

        SDL_Color textColorT = {43, 27, 85};

        SDL_Surface* textSurfaceT = TTF_RenderText_Solid(fontT,"Magasin", textColorT);
        if (!textSurfaceT) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(fontT);
            return -1;
        }

 
        SDL_Texture* textTextureT = SDL_CreateTextureFromSurface(renderer, textSurfaceT);

        SDL_Rect  r_text_T= {((*we)/2)-((textSurfaceT->w)/2),textSurfaceT->h,textSurfaceT->w,textSurfaceT->h};
        SDL_FreeSurface(textSurfaceT);

        if(SDL_QueryTexture(textTextureT,NULL,NULL,&r_text_T.w,&r_text_T.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }
        

        TTF_CloseFont(fontT);
        fontT=NULL;


                //chargement de la police d'écriture
        TTF_Font* font = TTF_OpenFont("fonts/alagard.ttf", 50);
        if (!font) {
            //fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return -1;
        }


        SDL_Surface* textSurfaceQ = TTF_RenderText_Solid(font,"Quitter", textColor);
        if (!textSurfaceQ) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return -1;
        }

        SDL_Texture* textTextureQ = SDL_CreateTextureFromSurface(renderer, textSurfaceQ);
        

        SDL_Surface* textSurfaceC = TTF_RenderText_Solid(font,"Rejouer", textColor);
        if (!textSurfaceC) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            return -1;
        }

        SDL_Texture* textTextureC = SDL_CreateTextureFromSurface(renderer, textSurfaceC);
        

        


        SDL_Surface* textSurfaceN = TTF_RenderText_Solid(font,"Magasin", textColor);
        if (!textSurfaceN) {
            fprintf(stderr, "Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            SDL_FreeSurface(textSurfaceQ);
            SDL_FreeSurface(textSurfaceC);
            return -1;
        }
        
        SDL_Texture* textTextureN = SDL_CreateTextureFromSurface(renderer, textSurfaceN);

        TTF_CloseFont(font);
        font=NULL;


        //creation rectangle pour les textes

        SDL_Rect  r_text_Q= {((*we)/2)-((textSurfaceQ->w)/2),(*he/4)*4-textSurfaceQ->h-100,textSurfaceQ->w,textSurfaceQ->h};
        SDL_Rect  r_text_N= {((*we)/2)-((textSurfaceN->w)/2),(*he/4)*2-textSurfaceN->h+50,textSurfaceN->w,textSurfaceN->h};
        SDL_Rect  r_text_C= {((*we)/2)-((textSurfaceC->w)/2),(*he/4)*3-textSurfaceC->h,textSurfaceC->w,textSurfaceC->h};
        

        SDL_FreeSurface(textSurfaceC);
        SDL_FreeSurface(textSurfaceQ);
        SDL_FreeSurface(textSurfaceN);


        if(SDL_QueryTexture(textTextureQ,NULL,NULL,&r_text_Q.w,&r_text_Q.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;          
        }

        if(SDL_QueryTexture(textTextureC,NULL,NULL,&r_text_C.w,&r_text_C.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
        }



        if(SDL_QueryTexture(textTextureN,NULL,NULL,&r_text_N.w,&r_text_N.h)!=0){
                printf("Impossible de charger le texte\n");
                return -1;
            
        }

        

            int etat=1;
            while(etat){

                while (SDL_PollEvent(&event) != 0 ) {

                    if(event.type == SDL_MOUSEBUTTONDOWN ){

                        //pour continuer le jeu
                        if((r_text_C.x<=event.button.x) && ((r_text_C.x+r_text_C.w)>=event.button.x) && ((r_text_C.y+r_text_C.h)>=event.button.y) && (r_text_C.y<=event.button.y)){
                            etat=0;
                        }

                        //pour quitter le jeu
                        else if((r_text_Q.x<=event.button.x) && ((r_text_Q.x+r_text_Q.w)>=event.button.x) && ((r_text_Q.y+r_text_Q.h)>=event.button.y) && (r_text_Q.y<=event.button.y)){
                            etat=0;
                            *run=0;
                        }
                        //Pour aller au magasin
                        else if((r_text_N.x<=event.button.x) && ((r_text_N.x+r_text_N.w)>=event.button.x) && ((r_text_N.y+r_text_N.h)>=event.button.y) && (r_text_N.y<=event.button.y)){
                            etat=0;
                        }  
        
                                            
                    }           
                }
        
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            
            SDL_RenderClear(renderer);

            
            SDL_RenderCopy(renderer, textTextureQ, NULL, &r_text_Q);
            SDL_RenderCopy(renderer, textTextureC, NULL, &r_text_C);
            SDL_RenderCopy(renderer, textTextureT, NULL, &r_text_T);
            SDL_RenderCopy(renderer, textTextureN, NULL, &r_text_N);


            SDL_RenderPresent(renderer);
            SDL_Delay(100);
      
            }

        SDL_DestroyTexture(textTextureQ);
        SDL_DestroyTexture(textTextureC);
        SDL_DestroyTexture(textTextureT);
        SDL_DestroyTexture(textTextureN);

        SDL_RenderPresent(renderer);
        
        


    
    return 0;
}








/*int console_command(SDL_Event event,char * command){
    if(command == NULL){
        command = malloc(80);
    }
    if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_j)){
        scanf("%s",command);
    }
    return 0;
}

int console_aff(SDL_Renderer * renderer,int we,int he,char * command){
    TTF_Font  * police = TTF_OpenFont("fonts/alagard.ttf", 20); 
    SDL_Color blanc = {255, 255, 255};
    if (police == NULL){
        TTF_CloseFont(police);
        TTF_Quit();
        fprintf(stderr,"probleme a l'ouverture de la police\n");
        return -1;
    }
    SDL_Rect r = {0,we-32,he,32};
    SDL_SetRenderDrawColor(renderer, 0,0,0,120);
    SDL_RenderFillRect(renderer, &r);
    SDL_Surface * texte = TTF_RenderText_Solid(police, command, blanc);
    if (!texte){
        SDL_FreeSurface(texte);
        TTF_CloseFont(police);
        police = NULL;
        TTF_Quit();
        printf("probleme de texte\n");
        return -1;
    }
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer,texte);
    SDL_Rect textRect = {r.x+5, r.y+5, texte->w, texte->h};
    if(!text_texture){
        printf("Impossible de creeer la texture\n");
        TTF_CloseFont(police);
        police = NULL;
        TTF_Quit();
        return -1;
    }
    SDL_RenderCopy(renderer, text_texture, NULL, &textRect);
    return 0;
}*/

