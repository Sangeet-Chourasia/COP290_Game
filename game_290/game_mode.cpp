#include "globals.h"
#include "game_mode.h"
#include "animation.h"
//#include "animation.h"
using namespace std;

void game_mode()
{
    SDL_Point Mouse_point;
    SDL_Texture* game_mode_background=IMG_LoadTexture(renderer,"Images/game_mode.png");
    int menu_w,menu_h;
    SDL_QueryTexture(game_mode_background, NULL, NULL, &menu_w, &menu_h);

    SDL_Rect single_player=SDL_Rect{559, 308, 1276-559, 555-308};
    SDL_Rect multiplayer=SDL_Rect{558, 603, 1275-558,852- 603};

    SDL_Rect audio_on=SDL_Rect{107,881,137,137};
    SDL_Rect audio_off=SDL_Rect{274,881,137,137};

    SDL_Rect home=SDL_Rect{100,77,139,142};
    SDL_Rect about=SDL_Rect{1761,879,137,127};

    SDL_Rect rect[]= {single_player,multiplayer,audio_on,audio_off,home,about};
    SDL_Rect current_src_pos;
    SDL_Rect current_dst_pos;

    SDL_RenderPresent(renderer);
    double sf_x=SCREEN_WIDTH/(menu_w*1.0)  ;    // scaling factor in x
    double sf_y=SCREEN_HEIGHT/(menu_h*1.0)  ;    // scaling factor in y
    game_mode_on=true;
    //Mix_PlayMusic(gMusic,-1);
    while(game_mode_on && game_running) 
    {
        SDL_Event e;
        bool button_pressed=false;
        while (SDL_PollEvent(&e) != 0)
        {
        // user requests quit
            if (e.type == SDL_QUIT)
            {
                game_mode_on= false;
                main_menu_on=false;
                game_running=false;
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
        bool intersection=false;
        for(int i=0;i<7;i++)
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

                        cout<<"open single player game mode"<<endl;
                        animation_on=true;
                        animation(false);
                    }
                    if(i==1)
                    {
                        cout<<"open multiplayer player game mode"<<endl;
                        animation_on=true;
                        animation(true);
                    }
                    if(i==2)
                    {
                        cout<<"audio_on";
                    }
                    if(i==3)
                    {
                        cout<<"audio_off";
                    }
                    if(i==4)
                    {
                        game_mode_on=false;
                        main_menu_on=true;
                    }
                    if(i==5)
                    {
                        cout<<"audio_on";
                    }
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,game_mode_background,NULL,NULL);
        if(intersection)SDL_RenderCopy(renderer,game_mode_background,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
    }
}