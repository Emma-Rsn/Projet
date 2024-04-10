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
void newMusic(int nZone,Mix_Music* gMusic){
            if(nZone == 0){
                gMusic = Mix_LoadMUS( "musique/Game-Over.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else if(nZone == 1){
                gMusic = Mix_LoadMUS( "musique/creepy-devil-dance.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else if(nZone == 2){
                gMusic = Mix_LoadMUS( "musique/18-Prairie4.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else if(nZone == 3){
                gMusic = Mix_LoadMUS( "musique/16-Havoc.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else if(nZone == 4){
                gMusic = Mix_LoadMUS( "musique/1-BattleField.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else if(nZone == 5){
                gMusic = Mix_LoadMUS( "musique/Game-Over.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else if(nZone == 6){
                gMusic = Mix_LoadMUS( "musique/9-EpicBattle.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }else{
                gMusic = Mix_LoadMUS( "musique/creepy-devil-dance.mp3" );
                if( gMusic == NULL )
                {
                    printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                Mix_PlayMusic( gMusic, -1 );
            }
}