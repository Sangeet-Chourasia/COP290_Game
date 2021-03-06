#ifndef EXTERN
#define EXTERN extern


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720

// #define FONT "OpenSans-ExtraBoldItalic.ttf"
// #define FONT_SIZE 24

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <iostream>


using namespace std;

EXTERN SDL_Window* window=NULL;
EXTERN SDL_Renderer* renderer=NULL;

EXTERN SDL_Texture* welcome_background=NULL;
EXTERN SDL_Texture* menu_background=NULL;
EXTERN SDL_Texture* game_mode_background=NULL;
EXTERN SDL_Texture* spritesheet_boy=NULL;
EXTERN SDL_Event e;
EXTERN bool game_running=false;
EXTERN bool main_menu_on=false;
EXTERN bool settings_on=false;
EXTERN bool audio_onn=false;
EXTERN bool about_on=false;
EXTERN bool pause_on=false;
EXTERN bool game_mode_on=false;
EXTERN bool how_to_play_on=false;
EXTERN bool animation_on=false;

#endif