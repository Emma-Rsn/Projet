//
//TLN.c
//Created by Moreau Enzo Rasson Emma Pasquier Lina 
//

/**
*\file TLN.c
*\brief programme principale
*\author Moreau Enzo Rasson Emma Pasquier Lina 
*\date  janvier 2024
*\version 0.0
*
*/

#include "../libs/commun.h"

//nombre de frame par secondes voulu
#define FPS 30

int main(){
    srand(time(NULL));

    //initialisation variable menu

    int * etat_menu=malloc(sizeof(int));
    int * run=malloc(sizeof(int));
    *run=1;

     
    //resolution de l'ecran
    save_settings();
    int * hEcran = malloc(sizeof(int));
    int * wEcran = malloc(sizeof(int));
    load_settings(wEcran,hEcran);

     // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    // Initialisation de TTF
    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur d'initialisation de TTF : %s\n", SDL_GetError());
        return -1;
    }
    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *wEcran, *hEcran, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    // Création du rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur de création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    //mode de transparence
    SDL_BlendMode blend = SDL_BLENDMODE_BLEND;
    SDL_SetRenderDrawBlendMode(renderer, blend);

    //IMG de fond
    //SDL_Texture* backgroundTexture = NULL;
    
    
    // Initialiser la map
    map_t map=creation_map((*wEcran),(*hEcran));
    int *etat_map=malloc(sizeof(int));
    (*etat_map)=0;
    int ouigrille = 0;
    int ouilumiere = 0;

    remplir_map(&map);
    nb_texture_chargement(&map, "save/texture.txt");
    creation_tab_path(&map, "save/texture.txt");
    afficher_zone(map);
    //def spawn
    int q,s,xp,yp;
    if(!load_pos(&q,&s,&xp,&yp)){
        for(q = 0;q<ROWS;q++){
            for(s = 0;s<COLUMNS;s++){
                if(map.tabMap[q][s].nZone == 1){
                    break;
                }
            }
            if(map.tabMap[q][s].nZone == 1){
                    break;
            }
        }
        xp = 12,yp=5;
    }
    carte_t * cartec = &(map.tabMap[q][s]);
    cartec->etat_brouillard = 0;
    map.zoneChargee=cartec->nZone;
    chargement_Zone(&map,renderer,map.zoneChargee);
    //load_layout(&(map.tabMap[0][5]),"save/layout3_1.txt");
    load_layout(&(map.tabMap[5][5]),"save/layoutbeach.txt");


    //variable FPS
    int cmpfps = 0;
    int dfps = FPS;
    Uint32 * t0 = malloc(sizeof(Uint32));
    Uint32 * t1 = malloc(sizeof(Uint32));
    int * nfps = malloc(sizeof(int));
    *t0 = -1;

    //creation personnage
	p_mv Alex;
	Alex = initp(cartec,&(cartec->grille.tabGrille[xp][yp]));
    Alex.equipe[1]=init_combattant("Lou",100,"ATQ1","ATspe",60,0,"");
    Alex.equipe[2]=init_combattant("Max",100,"ATQ num 1","ATK spe",45,0,"");
	p_mv * pAlex = &Alex;

    

    //creation d'un pnj
    pnj_t Alex2;
    Alex2 = init_pnj("Alex2","sprite/alexdial.png", "sprite/alexface2.png",&(map.tabMap[0][0].grille.tabGrille[14][9]),&map.tabMap[0][0]);
    pnj_t * pAlex2 = &Alex2;
    insertion(Alex2.dial, "Bonjour");
    insertion(Alex2.dial, "Test");

    //creation ennemi 
    pnj_t Alex3;
    Alex3 = init_pnj("Alex3","sprite/slimebluedial.png", "sprite/slimeblue.png",&(map.tabMap[0][0].grille.tabGrille[1][2]),&map.tabMap[0][0]);
    Alex3.combattant[1]=init_combattant("Lute",100,"ATQ11","ATspe1",10,1,"sprite/alexdial.png");
    pnj_t * pAlex3 = &Alex3;

    ennemi_t Slime = init_ennemi("Slime","Sprite/slimebluedial.png");
    Slime.combattant[1] = init_combattant("Lute",100,"ATQ11","ATspe1",10,1,"sprite/alexdial.png");
    ennemi_t * PSlime = &Slime;
    obj_t ObjSlime = init_obj(&map.tabMap[3][3].grille.tabGrille[4][5],9,2,PSlime);
    map.tabMap[3][3].tabObj[0] = ObjSlime;
    map.tabMap[3][3].nbObj = 1;
    

    //variable indique l'etat du prog
    int i;//brouillard
    int j;//brouillard

    int * transi = malloc(sizeof(int));
    *transi = 0;

    SDL_Event event;
    //char * command = NULL;

    //zone declaration objet
    SDL_Rect HUD  = {0,0,*wEcran,56};

    Mix_Music* gMusic = NULL;

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    gMusic = Mix_LoadMUS( "Game-Over.mp3" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    Mix_PlayMusic( gMusic, -1 );

    //boucle du programme
    while (*run) {
        //zone d'evenement
        while (SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_h)){
                if(ouigrille == 0){
                    ouigrille = 1;
                }else{
                    ouigrille = 0;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_l)){
                if(ouilumiere == 0){
                    ouilumiere = 1;
                }else{
                    ouilumiere = 0;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_m)){
                for(i = 0;i < ROWS;i++){
                    for(j = 0; j < COLUMNS; j++){
                        map.tabMap[i][j].etat_brouillard = 0;
                    }
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_x)){                
                (*etat_map)=1;
                /*if(ind_map==1){
                    ind_map=2;
                }
                if(ind_map==2){
                    ind_map=3;
                }
                if(ind_map==3){
                    ind_map=0;
                }*/
            }if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_9)){
                if( Mix_PlayingMusic() == 0 )
                {
                    //Play the music
                    Mix_PlayMusic( gMusic, -1 );
                }
                //If music is being played
                else
                {
                    //If the music is paused
                    if( Mix_PausedMusic() == 1 )
                    {
                        //Resume the music
                        Mix_ResumeMusic();
                    }
                    //If the music is playing
                    else
                    {
                        //Pause the music
                        Mix_PauseMusic();
                    }
                }
            }
            
            pinput(pAlex,event,&cartec,&map,renderer,transi);

            //menu
            //console_command(event,command);
            menu(wEcran,hEcran,event,renderer,run);
            debut_dialogue(event,pAlex2,pAlex);
            debut_combat(event,ObjSlime.tabObj[0],pAlex,ObjSlime.cas);
            
        }
        //zone d'affichage
        //ajustement de dfps
        if(NB_Fps(nfps,t0,t1)){
            cmpfps = *nfps;
            if(*nfps < FPS){
                dfps++;
            }else if(*nfps >= FPS){
                dfps--;
            }
        }
        //efface le rendu
        switch(cartec->nZone){
            case 1: SDL_SetRenderDrawColor(renderer, 206,206,206,255);break;
            case 2: SDL_SetRenderDrawColor(renderer, 86,115,154,255);break;
            case 3: SDL_SetRenderDrawColor(renderer, 153,81,43,255);break;
            case 4: SDL_SetRenderDrawColor(renderer, 104,157,113,255);break;
            case 5: SDL_SetRenderDrawColor(renderer, 115,8,0,255);break;
            default: SDL_SetRenderDrawColor(renderer, 0,0,0,255);break;
        }
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 245, 255);
        SDL_RenderFillRect(renderer, &HUD);

        //affiche la grille
        betaAfficherMap(renderer,&map,cartec);
        if(ouigrille)afficher_grille(cartec->grille,renderer);

        //Affichage pnj
        aff_pnj(Alex2,renderer,cartec);
        aff_pnj(Alex3,renderer,cartec);

        //affiche les fps
        aff_Fps(cmpfps,renderer);
        //transition(renderer,transi,*wEcran,*hEcran);

        //Affiche un personnage
        affp(pAlex,renderer);
        affTabObj(renderer,map,cartec);

        if(ouilumiere)lumiere(renderer,cartec,pAlex->c);
        //console_aff(renderer,*hqEcran,*wEcran,command);


        //afficher dialogue
        pnj_dialogue (event,pAlex2,renderer,hEcran,wEcran);

        //afficher map
        afficher_map(event,map,renderer,wEcran,hEcran,etat_map,cartec);
        
        //Commence une combat
        combat(wEcran,hEcran,event,renderer,ObjSlime.tabObj[0],pAlex);

    
        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/dfps);
    }

    // Libérer les ressources
    //combattant(pAlex);

    save_pos(cartec->xcarte,cartec->ycarte,pAlex->c->x,pAlex->c->y);

    free(etat_map);
    free(nfps);
    free(t0);
    free(t1);
    free(etat_menu);
    free(run);
    free(transi);

    Mix_FreeMusic( gMusic );

    

    //SDL_DestroyTexture(backgroundTexture);
    creation_tab_texture(&map,renderer,1,1);
    detruire_tab_path(&map);

    dest_pnj(pAlex2);
    dest_pnj(pAlex3);
    desctruction_p_eq(pAlex);
    free(wEcran);
    free(hEcran);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
