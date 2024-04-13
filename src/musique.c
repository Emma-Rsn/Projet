#include "../libs/commun.h"

void pause(SDL_Event event,Mix_Music* gMusic){
    if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_9)){
        if( Mix_PlayingMusic() == 0 ){
             Mix_PlayMusic( gMusic, -1 );
        }else{
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
}
void newMusic(int nZone, Mix_Music * gMusic){
    // Libérer la mémoire si une musique est déjà chargée
    if (gMusic != NULL) {
        Mix_FreeMusic(gMusic);
        gMusic = NULL;
    }

    // Charger la nouvelle musique
    switch (nZone) {
        case 0:
            gMusic = Mix_LoadMUS("musique/Game-Over.mp3");
            break;
        case 1:
            gMusic = Mix_LoadMUS("musique/creepy-devil-dance.mp3");
            break;
        case 2:
            gMusic = Mix_LoadMUS("musique/18-Prairie4.mp3");
            break;
        case 3:
            gMusic = Mix_LoadMUS("musique/16-Havoc.mp3");
            break;
        case 4:
            gMusic = Mix_LoadMUS("musique/1-BattleField.mp3");
            break;
        case 5:
            gMusic = Mix_LoadMUS("musique/Game-Over.mp3");
            break;
        case 6:
            gMusic = Mix_LoadMUS("musique/9-EpicBattle.mp3");
            break;
        default:
            gMusic = Mix_LoadMUS("musique/creepy-devil-dance.mp3");
            break;
    }

    // Vérifier si le chargement a réussi
    if (gMusic == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        // Jouer la musique en boucle (-1 indique la lecture en boucle)
        Mix_PlayMusic(gMusic, -1);
    }
}