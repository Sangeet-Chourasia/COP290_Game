#include <SDL2/SDL.h>

#include "globals.h"
using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


SDL_Rect dst_Rect{0,0,50,80};

float accum_anim_time = 0.0;
Uint32 prev_time = 0;
Uint32 curr_time = 0;

// increase this number to make animation plays faster
const int fAnim_fps = 10;
// cache the calculation of animation speed
const float kAnim_frame_delay = 0.0 / fAnim_fps;

SDL_Event e;
void animation()
{
    int sprite_boy_w,sprite_boy_h;
    SDL_QueryTexture(spritesheet_boy, NULL, NULL, &sprite_boy_w,&sprite_boy_h);
    SDL_Rect Rect_movement[8][8];

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            Rect_movement[i][j]=SDL_Rect{j*sprite_boy_w/8,i*sprite_boy_h/8,sprite_boy_w/8,sprite_boy_h/8};
        }
    }
    int frame = 0;
    int direction=0;
    while(game_running)
    {
        bool button_pressed=false;
        

        Uint8* arrow_keys;
        while (SDL_PollEvent(&e) != 0)
        {
        // user requests quit*/
            if (e.type == SDL_QUIT)
            {
                game_running= false;
            }
            else if(e.type==SDL_KEYDOWN)
            {
                button_pressed=true;
                const Uint8* state = SDL_GetKeyboardState(NULL);
                /*cout<<state[SDL_SCANCODE_UP];
                cout<<"burraaaahhhhh";
                cout << typeid(state[SDLK_UP]).name() << endl;*/
                /*Uint8* arrow_key={state[SDL_SCANCODE_UP],state[SDL_SCANCODE_DOWN],state[SDL_SCANCODE_LEFT],state[SDL_SCANCODE_RIGHT]};
                arrow_keys=arrow_key;*/
                if((state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN]) || (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT])){button_pressed=false;}
                else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]){direction=5;dst_Rect.x=max(0,dst_Rect.x-5);dst_Rect.y=max(0,dst_Rect.y-5);}
                else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]){direction=7;dst_Rect.x=min(SCREEN_WIDTH-sprite_boy_w/8,dst_Rect.x+5);dst_Rect.y=max(0,dst_Rect.y-5);}
                else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]){direction=4;dst_Rect.x=max(0,dst_Rect.x-5);dst_Rect.y=min(SCREEN_HEIGHT-sprite_boy_h/8,dst_Rect.y+5);}
                else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]){direction=6;dst_Rect.x=min(SCREEN_WIDTH-sprite_boy_w/8,dst_Rect.x+5);dst_Rect.y=min(SCREEN_HEIGHT-sprite_boy_h/8,dst_Rect.y+5);}
                else if(state[SDL_SCANCODE_UP]){direction=3;dst_Rect.y=max(0,dst_Rect.y-5);}
                else if(state[SDL_SCANCODE_DOWN]){direction=0;dst_Rect.y=min(SCREEN_HEIGHT-sprite_boy_h/8,dst_Rect.y+5);}
                else if(state[SDL_SCANCODE_LEFT]){direction=1;dst_Rect.x=max(0,dst_Rect.x-5);}
                else if(state[SDL_SCANCODE_RIGHT]){direction=2;dst_Rect.x=min(SCREEN_WIDTH-sprite_boy_w/8,dst_Rect.x+5);}
                else{button_pressed=false;} 
                
            }
        }
        
        prev_time = curr_time;
        curr_time = SDL_GetTicks();
        float deltaTime = (curr_time - prev_time) / 1000.0f;            
        SDL_Rect* currentFrame = &Rect_movement[direction][frame];
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if(button_pressed)
        {
            SDL_RenderCopy(renderer,spritesheet_boy,currentFrame,&dst_Rect);
        }
        else{SDL_RenderCopy(renderer,spritesheet_boy,&Rect_movement[direction][0],&dst_Rect);}
        // if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
        accum_anim_time += deltaTime;
        // SDL_Log("accum %f", accum_anim_time);
        if (accum_anim_time >= kAnim_frame_delay)
        {
            frame = (frame + 1) % 8;
            // SDL_Log("increased frame to %d", frame);
            accum_anim_time -= kAnim_frame_delay;
        }
        SDL_Delay(50);
    }   
}
/*
int main(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) >= 0)
    {
        TTF_Init(); 
        SDL_Event e;
        bool game_running=true;
        window=SDL_CreateWindow("texture_demo",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Texture * spritesheet_boy=IMG_LoadTexture(renderer,"Images/sprite_boy.png");

        int sprite_boy_w,sprite_boy_h;
        SDL_QueryTexture(spritesheet_boy, NULL, NULL, &sprite_boy_w,&sprite_boy_h);

        SDL_Rect Rect_movement[8][8];

        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                Rect_movement[i][j]=SDL_Rect{j*sprite_boy_w/8,i*sprite_boy_h/8,sprite_boy_w/8,sprite_boy_h/8};
            }
        }
        int frame = 0;
        while(game_running)
        {
            bool button_pressed=false;
            while (SDL_PollEvent(&e) != 0)
            {
            // user requests quit
                if (e.type == SDL_QUIT)
                {
                    game_running= false;
                }
                else if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&Mouse_point.x, &Mouse_point.y);
                    button_pressed=true;
                }
            }
            SDL_GetMouseState(&Mouse_point.x, &Mouse_point.y);
            Mouse_point.x/=sf_x;
            Mouse_point.y/=sf_y;
            bool intersection=false;*/
            /*for(int i=0;i<7;i++)
            {
                SDL_Rect src_rect=rect[i];
                if(SDL_PointInRect(&Mouse_point,&src_rect))
                {
                    current_src_pos=src_rect;
                    current_dst_pos=SDL_Rect{sf_x*src_rect.x-20,sf_y*src_rect.y-10,sf_x*src_rect.w+40,sf_y*src_rect.h+20};
                    intersection=true;
                    if(button_pressed)
                    {
                        if(i==0)
                        {
                            game_mode_on=true;
                            game_mode(window,renderer);
                        }
                    }
                    break;
                }
            }
            prev_time = curr_time;
            curr_time = SDL_GetTicks();
            float deltaTime = (curr_time - prev_time) / 1000.0f;            
            SDL_Rect* currentFrame = &Rect_movement[direction][frame];
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderCopy(renderer,spritesheet_boy,currentFrame,NULL);
            // if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
            SDL_RenderPresent(renderer);
            accum_anim_time += deltaTime;
            SDL_Log("accum %f", accum_anim_time);
            if (accum_anim_time >= kAnim_frame_delay)
            {
                frame = (frame + 1) % 8;
                SDL_Log("increased frame to %d", frame);
                accum_anim_time -= kAnim_frame_delay;
            }
        }
    }
    return 0;

}*/