#define EXTERN
#include "game.h"

int main(void)
{
    if((initialize() && load_all_media())==false)
    {
        cout<<"game is unable to run";
        return 0;
    }
    game_running=true;
    Mix_PlayChannel(-1, gHigh, 0);
    SDL_RenderCopy(renderer,welcome_background,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_Event e;
    while(game_running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                game_running=false;
            }
        }
    Main_Menu();
    }
}

bool initialize()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO )<0)
    {
        cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout<<"SDL_mixer could not initialize! Error:"<<Mix_GetError()<<endl;
        return false;
    }
    window=SDL_CreateWindow("Welcome_to_the Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(window==NULL)
    {
        cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
    cout<<"SDL could not create renderer! SDL_Error: "<<SDL_GetError()<<" \n";
    return false;
    }
    return true;
}

bool load_all_media()
{
    welcome_background=IMG_LoadTexture(renderer,"Images/welcome.png");
    if(welcome_background==NULL)
    {
        cout<<"SDL could not load welcome background texture! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;       
    }
    menu_background=IMG_LoadTexture(renderer,"Images/Main_Menu.png");
    if(menu_background==NULL)
    {
        cout<<"SDL could not load menu background texture! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;       
    }
    game_mode_background=IMG_LoadTexture(renderer,"Images/game_mode.png");
    if(game_mode_background==NULL)
    {
        cout<<"SDL could not load game_mode background texture! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;       
    }
    spritesheet_boy=IMG_LoadTexture(renderer,"Images/sprite_boy.png");
    if(spritesheet_boy==NULL)
    {
        cout<<"SDL could not load spritesheet_boy texture! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;       
    }
    map=IMG_LoadTexture(renderer,"Images/map.jpeg");
    if(map==NULL)
    {
        cout<<"SDL could not load map! SDL_Error: "<<SDL_GetError()<<" \n";
        return false;
    }
    SDL_QueryTexture(map, NULL, NULL, &map_w,&map_h);
    //ifstream file("matrix.txt");
    /*if(!load_matrix())
    {
        cout<<"could not load matrix"<<endl;
        return false;
    }*/
    if(!load_sound())
    {
        cout<<"could not load sound"<<endl;
        return false;
    }
    return true;
}

bool load_sound()
{
    gMusic = Mix_LoadMUS("bensound-ukulele.mp3");
    if (gMusic == NULL)
    {
        SDL_Log("Failed to load music [bensound-ukulele.mp3]. Error: %s", Mix_GetError());
        return false;
    }

  // load sfx, scratch.wav
    gScratch = Mix_LoadWAV("scratch.wav");
    if (gScratch == NULL)
    {
        SDL_Log("Failed to load sfx [scratch.wav]. Error: %s", Mix_GetError());
        return false;
    }

  // load sfx, high.wav
    gHigh = Mix_LoadWAV("high.wav");
    if (gHigh == NULL)
    {
        SDL_Log("Failed to load sfx [high.wav]. Error %s", Mix_GetError());
        return false;
    }

    // load sfx, medium.wav
    gMedium = Mix_LoadWAV("medium.wav");
    if (gMedium == NULL)
    {
        SDL_Log("Failed to load sfx [medium.wav]. Error %s", Mix_GetError());
        return false;
    }

    // load sfx, low.wav
    gLow = Mix_LoadWAV("low.wav");
    if (gLow == NULL)
    {
        SDL_Log("Failed to laod sfx [low.wav]. Error %s", Mix_GetError());
        return false;
    }
    return true;   

}