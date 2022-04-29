#include<SDL2/SDL.h>
#include <iostream>

int main(int argc,char *argv[])
{
    SDL_Window *window=nullptr;
    SDL_Surface *windowSurface=nullptr;
    SDL_Surface *image1=nullptr;
    SDL_Surface *image2=nullptr;
    SDL_Surface *image3=nullptr;
    SDL_Surface *current_image=nullptr;
    SDL_Init(SDL_INIT_VIDEO);

    window=SDL_CreateWindow("Mouse Event Test", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    windowSurface=SDL_GetWindowSurface(window);
    image1=SDL_LoadBMP("image1.bmp");
    image2=SDL_LoadBMP("image2.bmp");

    current_image=image1;
    bool isRunning=true;
    SDL_Event e;

    while(isRunning)
    {
        while(SDL_PollEvent(&e)!=0)
        {        
            if(e.type==SDL_QUIT)isRunning=false;
            else if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_LEFT)
                current_image=image1;
                if(e.button.button==SDL_BUTTON_RIGHT)
                current_image=image2;

            }
        }
        SDL_BlitSurface(current_image,NULL,windowSurface,NULL);
        SDL_UpdateWindowSurface(window);
    }
    SDL_Quit();

}