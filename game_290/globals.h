#ifndef GLOBALS
#define GLOBALS


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#include <stdio.h>
#include <stdbool.h>
#include <iostream>

#include <vector>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 741



#ifndef EXTERN
#define EXTERN extern
#endif






// #define FONT "OpenSans-ExtraBoldItalic.ttf"
// #define FONT_SIZE 24



EXTERN SDL_Window* window;
EXTERN SDL_Renderer* renderer;

EXTERN SDL_Texture* welcome_background;
EXTERN SDL_Texture* menu_background;
EXTERN SDL_Texture* game_mode_background;
EXTERN SDL_Texture* spritesheet_boy;
EXTERN SDL_Texture* map;

EXTERN SDL_Event e;
EXTERN bool game_running;
EXTERN bool main_menu_on;
EXTERN bool settings_on;
EXTERN bool audio_onn;
EXTERN bool about_on;
EXTERN bool pause_on;
EXTERN bool game_mode_on;
EXTERN bool how_to_play_on;
EXTERN bool animation_on;

//EXTERN bool button_pressed;

EXTERN int map_w;
EXTERN int map_h;


EXTERN Mix_Chunk *gScratch ;
EXTERN Mix_Chunk *gHigh ;
EXTERN Mix_Chunk *gMedium ;
EXTERN Mix_Chunk *gLow ;
EXTERN Mix_Music *gMusic ;


#endif