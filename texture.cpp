#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* image=NULL;
SDL_Texture* button_sprite=NULL;

int main(void)
{
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Point Mouse_point;
    srcrect.x = 60;
    srcrect.y = 45;
    
    dstrect.x = 640/2;
    dstrect.y = 480/2;
    dstrect.w = 100;
    dstrect.h = 50;
    printf("hey1");
    if(SDL_Init(SDL_INIT_VIDEO) >= 0)
    {
        printf("hey2");
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_Event e;
        bool running=true;
        
        window=SDL_CreateWindow("texture_demo",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        image=IMG_LoadTexture(renderer,"menu_background.png");
        button_sprite=IMG_LoadTexture(renderer,"buttons.png");
int w,h;
SDL_QueryTexture(image, NULL, NULL, &w, &h);
        srcrect.w =80;
    srcrect.h = 45;
cout<<w<<" "<<h<<endl;
        while(running==true)
        {
            while (SDL_PollEvent(&e) != 0)
            {
            // user requests quit
                if (e.type == SDL_QUIT)
                {
                    running= false;
                }
            }
            int x,y;
            SDL_GetMouseState(&Mouse_point.x, &Mouse_point.y);
            if(SDL_PointInRect(&Mouse_point,&dstrect))
            {
                cout<<"hurray";

                SDL_RenderCopy(renderer,image,&srcrect,&dstrect);
                SDL_RenderPresent(renderer);

            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, image, NULL,NULL);
            SDL_RenderCopy(renderer,button_sprite,&srcrect,&dstrect);
            SDL_RenderPresent(renderer);
        }
    }
    return 0;
}





 /**
 * 07 - Hardware rendering (new in SDL2) with texture
 *
 */
/*
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool init();
bool loadMedia();
void close();

// load individual image
SDL_Texture* loadTexture(const char* path);

// the window we'll be rendering to
SDL_Window* gWindow = NULL;

// the window's renderer
SDL_Renderer* gRenderer = NULL;

// texture image
SDL_Texture* gImage = NULL;

bool init() {
  // initialize sdl
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // create window
  gWindow = SDL_CreateWindow("07 - Texture Loading and Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // create renderer for window
  // as we use SDL_Texture, now we need to use renderer to render stuff
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL)
  {
    printf("SDL could not create renderer! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // set initial render color
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // initialize png loading
  // see https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC8
  // returned from IMG_Init is all flags initted, so we could check for all possible
  // flags we aim for
  int imgFlags = IMG_INIT_PNG;
  int inittedFlags = IMG_Init(imgFlags);
  if ( (inittedFlags & imgFlags) != imgFlags)
  {
    // from document, not always that error string from IMG_GetError() will be set
    // so don't depend on it, just for pure information
    printf("SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    return false;
  }

  return true;
}

SDL_Texture* loadTexture(const char* path)
{
  // load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL)
  {
    printf("Unable to load image %s! SDL error: %s\n", path, IMG_GetError());
    return NULL;
  }

  // create texture from surface pixels
  // SDL_Texture* newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  SDL_Texture* newTexture=IMG_LoadTexture(gRenderer,"hello_world.bmp");
  if (newTexture == NULL)
  {
    printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
  }
  // now free original loaded surface
  // if success, we have a new copy of optimized surface
  // if fail, we still don't need it as we failed to convert to optimized surface
  SDL_FreeSurface(loadedSurface);

  return newTexture;
}

bool loadMedia()
{
  // load stretching image
  gImage = loadTexture("hello_world.bmp");
  if (gImage == NULL)
  {
    printf("Failed to load stretching image!\n");
    return false;
  }

  return true;
}

void close()
{
  // deallocate surface
  SDL_DestroyTexture(gImage);
  gImage = NULL;

  // destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // quit SDL_image
  IMG_Quit();

  // quit sdl subsystem
  SDL_Quit();
}

int main(int argc, char* args[])
{
  // start up SDL and create window
  if (!init())
  {
    printf("Failed to initialize\n");
  }	
  else
  {
    // load media
    if (!loadMedia())
    {
      printf("Failed to load media!\n");
    }
    else
    {
      // main loop flag
      bool quit = false;

      // event handler
      SDL_Event e;

      // while application is running
      while (!quit)
      {
        // handle events on queue
        // if it's 0, then it has no pending event
        // we keep polling all event in each game loop until there is no more pending one left
        while (SDL_PollEvent(&e) != 0)
        {
          // user requests quit
          if (e.type == SDL_QUIT)
          {
            quit = true;
          }
          // user presses a key
          else if (e.type == SDL_KEYDOWN)
          {
            switch (e.key.keysym.sym)
            {
              case SDLK_ESCAPE:
                quit = true;
                break;
            }
          }
        }

        // clear screen
        SDL_RenderClear(gRenderer);

        // render texture to screen
        // the texture's resolution and the target resolution is the same so should be no stretching here
        SDL_RenderCopy(gRenderer, gImage, NULL, NULL);

        // update screen from any rendering performed since this previous call
        // as we don't use SDL_Surface now, we can't use SDL_UpdateWindowSurface
        SDL_RenderPresent(gRenderer);
      }
    }
  }

  // free resource and close SDL
  close();

  return 0;
}
*/