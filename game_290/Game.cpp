#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include<iostream>
#include "globals.h"
#include "Main_Menu.h"

using namespace std;
#define EXTERN

bool initialize();
bool load_all_media();
void close();

int main(void)
{
    if((initialize() && load_all_media())==false)
    {
        cout<<"game is unable to run";
        return 0;
    }
    game_running=true;
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
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<" \n";
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
    return true;
}