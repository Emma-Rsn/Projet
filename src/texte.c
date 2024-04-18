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


#include "../libs/commun.h"




//affiche une boite de dialogue en finction du msg de l'ec de la liste et d'un portrait
int aff_boite_dia(SDL_Renderer * rendu,int po,int *we,int* he,char * message,map_t * map){

    TTF_Font  * police = TTF_OpenFont("fonts/alagard.ttf", 20); 
    if (police == NULL){
            TTF_CloseFont(police);
            TTF_Quit();
            fprintf(stderr,"probleme a l'ouverture de la police\n");
            return -1;
    }
    SDL_Color blanc = {255, 255, 255};
    SDL_Rect r_po = {0,*he-TaillePo,TaillePo,TaillePo};
    SDL_Rect r_text = {TaillePo,*he-TaillePo,*we-TaillePo,TaillePo};

    //boite portrait
    SDL_RenderCopy(rendu,  map->tabTexture[po], NULL, &r_po);

    //boite texte
    SDL_SetRenderDrawColor(rendu,0,0,0,255);
    SDL_RenderFillRect(rendu, &r_text);
    SDL_Surface * texte = TTF_RenderText_Solid(police, message, blanc);
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
    TTF_CloseFont(police);
    SDL_FreeSurface(texte); 
    SDL_DestroyTexture(text_texture);

    return 0;
}



void debut_dialogue_carte(carte_t * cartec,SDL_Event event,p_mv * pp,int *etat_dialogue){
    int i;
    for(i=0;i<cartec->nbObj;i++){
        if(cartec->tabObj[i]->typeObj==3 || cartec->tabObj[i]->typeObj==4){
            debut_dialogue(event,pp,etat_dialogue,cartec->tabObj[i]->cas);
        }
    }
}


void debut_dialogue(SDL_Event event,p_mv * pp,int *etat_dialogue,case_t * c){
    if(boolcol(c,pp)  && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e){
        *etat_dialogue=1;
    } 
}


void dialogue_carte(carte_t * cartec,int *we,int *he,SDL_Event event,SDL_Renderer * renderer,map_t * map,int *etat_dialogue){
    int i;
    for(i=0;i<cartec->nbObj;i++){
        if(cartec->tabObj[i]->typeObj==3|| cartec->tabObj[i]->typeObj==4 || cartec->tabObj[i]->typeObj==5){
            if(cartec->tabObj[i]->typeObj==5 && *etat_dialogue == 1)dest_obj(cartec,i);
            pnj_dialogue(event,renderer,he,we,map,etat_dialogue,cartec->tabObj[i]->tabObj[0]);
        }
    }
}

void pnj_dialogue (SDL_Event event,SDL_Renderer * renderer,int * he,int * we,map_t * map,int *etat_dialogue,int num_dialogue){

    if(*etat_dialogue == 1){
        char * texte1="";
        texte1=" ";
        int portrait=0;

        //sauvegarde du fond
        SDL_Surface* surface = SDL_CreateRGBSurface(0, *we, *he, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        // Copie les pixels du rendu actuel dans la surface
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        // Créer une texture à partir de la surface
        SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Rect tecran = {0,0,*we,*he};
        int etat=1;
        while(etat){
            switch(num_dialogue){
                        case 1: 
                            texte1="Il me faut la clef du manoir pour rentrer dedans.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 2: 
                            texte1="Il me faudrait une combianaison de plonger pour aller sous l'eau.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 3: 
                            texte1="Une puissante force me repousse.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 4: 
                            texte1="Merci de m'avoir sauvee.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 5: 
                            texte1="Merci de m'avoir sauve.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 6: 
                            texte1="Merci de m'avoir sauvee.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 7: 
                            texte1="Merci de m'avoir sauve.";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        case 8: 
                            texte1="Oh non tu m'as tue !";
                            portrait=0;
                            num_dialogue=-1;
                            break;
                        default:
                            
                            break;
            }           
            SDL_RenderClear(renderer);
            while (SDL_PollEvent(&event) != 0) {
            	//si une touche est presser
                if(event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e){
                     switch(num_dialogue){
                        case -1: 
                            etat=0;
                            *etat_dialogue = 0;
                            break;
                        default:
                            *etat_dialogue =0;
                            etat=0;
                            break;
                    }           
                }
            }


            TTF_Font  * police = TTF_OpenFont("fonts/alagard.ttf", 40); 
            if (police == NULL){
                    TTF_CloseFont(police);
                    TTF_Quit();
                    fprintf(stderr,"probleme a l'ouverture de la police\n");
                    return ;
            }

            SDL_Color blanc = {255, 255, 255};
            SDL_Rect r_po = {0,*he-TaillePo,TaillePo,TaillePo};
            SDL_Rect r_text = {TaillePo,*he-TaillePo,*we-TaillePo,TaillePo};

            SDL_Surface * texte = TTF_RenderText_Solid(police, texte1, blanc);
            if (!texte){
                SDL_FreeSurface(texte);
                TTF_CloseFont(police);
                police = NULL;
                TTF_Quit();
                printf("probleme de texte\n");
                return ;
            }
            SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer,texte);

            SDL_Rect textRect = {(*we)-(r_text.w/2)-texte->w/2, (*he)-(r_text.h/2)-(texte->h/2), texte->w, texte->h};
            if(!text_texture){
                printf("Impossible de creeer la texture\n");
                TTF_CloseFont(police);
                police = NULL;
                TTF_Quit();
                return ;
            }
            
            SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,0,0,0,100);
            SDL_RenderFillRect(renderer, &tecran);

        

            //boite portrait
            SDL_RenderCopy(renderer,  map->tabTexture[portrait], NULL, &r_po);
            //boite texte
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderFillRect(renderer, &r_text);

            SDL_RenderCopy(renderer, text_texture, NULL, &textRect);
            

            TTF_CloseFont(police);
            SDL_FreeSurface(texte); 
            SDL_DestroyTexture(text_texture);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(targetTexture);
    }
}

