#include "globals.h"
#include "Main_Menu.h"
#include "game_mode.h"
SDL_Point Mouse_point;
SDL_Rect play_game;
SDL_Rect how_to_play;
SDL_Rect settings;
SDL_Rect audio_on;
SDL_Rect audio_off;
SDL_Rect quit;
SDL_Rect about;

void setting();
void about_m();
void htp();

void Main_Menu()
{
    SDL_Event e;
    int menu_w,menu_h;
    SDL_QueryTexture(menu_background, NULL, NULL, &menu_w, &menu_h);

    play_game=SDL_Rect{650, 320, 570, 200};
    how_to_play=SDL_Rect{650, 523, 570, 200};
    settings=SDL_Rect{650, 727, 570, 200};

    audio_on=SDL_Rect{104,881,137,137};
    audio_off=SDL_Rect{274,881,137,137};

    quit=SDL_Rect{103,77,123,129};
    about=SDL_Rect{1761,879,137,127};

    SDL_Rect rect[]= {play_game,how_to_play,settings,audio_on,audio_off,quit,about};
    SDL_Rect current_src_pos;
    SDL_Rect current_dst_pos;

    double sf_x=SCREEN_WIDTH/(menu_w*1.0)  ;    // scaling factor in x
    double sf_y=SCREEN_HEIGHT/(menu_h*1.0)  ;    // scaling factor in y
    game_mode_on=true;
    //Mix_PlayMusic(gMusic,-1);
    while(game_running==true)
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
                        game_mode_on=true;
                        game_mode();
                    }
                    if(i==1)
                    {
                        htp();
                    }
                    if(i==2)
                    {
                        setting();
                    }
                    if(i==3)
                    {
                        audio_onn=true;
                    }
                    if(i==4)
                    {
                        audio_onn=false;
                    }
                    if(i==5)
                    {
                        game_running= false;
                    }
                    if(i=6)
                    {
                        about_m();
                    }
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,menu_background,NULL,NULL);
        if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
    }
}

void about_m()
{
    SDL_Event e;
    int menu_w,menu_h;
    SDL_QueryTexture(about_menu, NULL, NULL, &menu_w, &menu_h);

    audio_on=SDL_Rect{104,881,137,137};
    audio_off=SDL_Rect{274,881,137,137};

    quit=SDL_Rect{103,77,123,129};
    about=SDL_Rect{1761,879,137,127};

    SDL_Rect rect[]= {audio_on,audio_off,quit,about};
    SDL_Rect current_src_pos;
    SDL_Rect current_dst_pos;

    double sf_x=SCREEN_WIDTH/(menu_w*1.0)  ;    // scaling factor in x
    double sf_y=SCREEN_HEIGHT/(menu_h*1.0)  ;    // scaling factor in y
    game_mode_on=true;
    //Mix_PlayMusic(gMusic,-1);
    while(game_running==true)
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
                        audio_onn=true;
                    }
                    if(i==1)
                    {
                        audio_onn=false;
                    }
                    if(i==2)
                    {
                        Main_Menu();
                    }
                    if(i=3)
                    {
                        about_m();
                    }
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,how_toplay,NULL,NULL);
        if(intersection)SDL_RenderCopy(renderer,how_toplay,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
    }
}

void htp()
{
    SDL_Event e;
    int menu_w,menu_h;
    SDL_QueryTexture(how_toplay, NULL, NULL, &menu_w, &menu_h);

    audio_on=SDL_Rect{104,881,137,137};
    audio_off=SDL_Rect{274,881,137,137};

    quit=SDL_Rect{103,77,123,129};
    about=SDL_Rect{1761,879,137,127};

    SDL_Rect rect[]= {audio_on,audio_off,quit,about};
    SDL_Rect current_src_pos;
    SDL_Rect current_dst_pos;

    double sf_x=SCREEN_WIDTH/(menu_w*1.0)  ;    // scaling factor in x
    double sf_y=SCREEN_HEIGHT/(menu_h*1.0)  ;    // scaling factor in y
    game_mode_on=true;
    //Mix_PlayMusic(gMusic,-1);
    while(game_running==true)
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
                        audio_onn=true;
                    }
                    if(i==1)
                    {
                        audio_onn=false;
                    }
                    if(i==2)
                    {
                        Main_Menu();
                    }
                    if(i=3)
                    {
                        about_m();
                    }
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,how_toplay,NULL,NULL);
        if(intersection)SDL_RenderCopy(renderer,how_toplay,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
    }
}


void setting()
{
    SDL_Event e;
    int menu_w,menu_h;
    SDL_QueryTexture(menu_background, NULL, NULL, &menu_w, &menu_h);

    play_game=SDL_Rect{650, 320, 570, 200};
    how_to_play=SDL_Rect{650, 523, 570, 200};
    settings=SDL_Rect{650, 727, 570, 200};

    audio_on=SDL_Rect{104,881,137,137};
    audio_off=SDL_Rect{274,881,137,137};

    quit=SDL_Rect{103,77,123,129};
    about=SDL_Rect{1761,879,137,127};

    SDL_Rect rect[]= {play_game,how_to_play,settings,audio_on,audio_off,quit,about};
    SDL_Rect current_src_pos;
    SDL_Rect current_dst_pos;

    double sf_x=SCREEN_WIDTH/(menu_w*1.0)  ;    // scaling factor in x
    double sf_y=SCREEN_HEIGHT/(menu_h*1.0)  ;    // scaling factor in y
    game_mode_on=true;
    //Mix_PlayMusic(gMusic,-1);
    while(game_running==true)
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
                        audio_onn=true;
                    }
                    if(i==1)
                    {
                        audio_onn=false;
                    }
                    if(i==2)
                    {
                        Main_Menu();
                    }
                    if(i==3)
                    {
                        audio_onn=true;
                    }
                    if(i==4)
                    {
                        audio_onn=false;
                    }
                    if(i==5)
                    {
                        Main_Menu();
                    }
                    if(i=6)
                    {
                        about_m();
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,settings_menu,NULL,NULL);
        if(intersection)SDL_RenderCopy(renderer,settings_menu,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
    }
}
