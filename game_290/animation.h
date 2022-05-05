#include "globals.h"
using namespace std;

int player_x=25;
int player_y=40;
SDL_Rect player{0,0,player_x,player_y};
SDL_Rect player_frame{0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
SDL_Rect map_display{500,500,SCREEN_WIDTH,SCREEN_HEIGHT};

SDL_Point player_point{player_x/2,player_y/2};

int sprite_boy_w,sprite_boy_h;
int map_h;
int map_w;

vector<vector<bool>> allowed_pixel;
float accum_anim_time = 0.0;
Uint32 prev_time = 0;
Uint32 curr_time = 0;

// increase this number to make animation plays faster
const int fAnim_fps = 20;
// cache the calculation of animation speed
const float kAnim_frame_delay = 0.0 / fAnim_fps;
const int step =1;

SDL_Event e;


void move(const Uint8* state,vector<vector<bool>> &allowed_pixel);
void up();
void down();
void left();
void right();
void update_center();
bool feasible(char,vector<vector<bool>> &allowed_pixel);
//void set_player_at_center();
bool button_pressed;
int frame = 0;
int direction=0;
bool load_matrix();
void animation()
{
    if(!load_matrix()){cout<<"load matrix failed"<<endl;return;}
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
    frame = 0;
    direction=0;
    while(game_running)
    {
        button_pressed=false;
        

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
                move(state,allowed_pixel); 
                update_center();    
            }
        }
        prev_time = curr_time;
        curr_time = SDL_GetTicks();
        float deltaTime = (curr_time - prev_time) / 1000.0f;            
        SDL_Rect* currentFrame = &Rect_movement[direction][frame];
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,map,&map_display,NULL);
        // SDL_RenderCopy(renderer,game_mode_background,NULL,&player_frame);
        if(button_pressed)
        {
            SDL_RenderCopy(renderer,spritesheet_boy,currentFrame,&player);
        }
        else{SDL_RenderCopy(renderer,spritesheet_boy,&Rect_movement[direction][0],&player);}
        // if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
        accum_anim_time += deltaTime;
        if (accum_anim_time >= kAnim_frame_delay)
        {
            frame = (frame + 1) % 8;
            accum_anim_time -= kAnim_frame_delay;
        }
        SDL_Delay(50);
    }   
}

void move(const Uint8* state,vector<vector<bool>> &allowed_pixel)
{
    if((state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN]) || (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT])){button_pressed=false;}
    else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]){direction=5;if(!feasible('U',allowed_pixel)&& feasible('L',allowed_pixel)){return;}up();left();}
    else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]){direction=7;if(!feasible('U',allowed_pixel)&& feasible('R',allowed_pixel)){return;}up();right();}
    else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]){direction=4;if(!feasible('D',allowed_pixel)&& feasible('L',allowed_pixel)){return;}down();left();}
    else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]){direction=6;if(!feasible('D',allowed_pixel)&& feasible('R',allowed_pixel)){return;}down();right();}
    else if(state[SDL_SCANCODE_UP]){direction=3;if(!feasible('U',allowed_pixel)){return;}up();}
    else if(state[SDL_SCANCODE_DOWN]){direction=0;if(!feasible('D',allowed_pixel)){return;}down();;}
    else if(state[SDL_SCANCODE_LEFT]){direction=1;if(!feasible('L',allowed_pixel)){return;}left();}
    else if(state[SDL_SCANCODE_RIGHT]){direction=2;if(!feasible('R',allowed_pixel)){return;}right();}
    else{button_pressed=false;}
}

void up()
{
    if(player_frame.y-step>=0)
    {
        player_frame.y-=step;
        player.y-=step;
    }
    else
    {
        if(player_frame.y!=0)
        {       
            player.y-=player_frame.y;
            player_frame.y=0;
        }
        else if(map_display.y-step>=0)
        {
            map_display.y-=step;
        }
        else if(map_display.y!=0)
        {
            map_display.y=0;
        }
        else if(player.y-step>=player_frame.y){player.y-=step;}
        else{player.y=0;}
    }
}

void down()
{
    if(player_frame.y+player_frame.h+step<=SCREEN_HEIGHT)
    {
        player_frame.y+=step;
        player.y+=step;
    }
    else
    {
        if(player_frame.y+player_frame.h!=SCREEN_HEIGHT)
        {       
            player.y+=SCREEN_HEIGHT-player_frame.y-player_frame.h;
            player_frame.y=SCREEN_HEIGHT-player_frame.h;
        }
        else if(map_display.y+map_display.h+step<=map_h)
        {
            map_display.y+=step;
        }
        else if(map_display.y+map_display.h!=map_h)
        {
            map_display.y=map_h-map_display.h;
        }
        else
        {
            if(player.y+player.h+step<=player_frame.y+player_frame.y){player.y+=step;}
            else{player.y=SCREEN_HEIGHT-player.h;}
        }
    }
    return;
}

void left()
{
    if(player_frame.x-step>=0)
    {
        player_frame.x-=step;
        player.x-=step;
    }
    else
    {
        if(player_frame.x!=0)
        {       
            player.x-=player_frame.x;
            player_frame.x=0;
        }
        else if(map_display.x-step>=0)
        {
            map_display.x-=step;
        }
        else if(map_display.x!=0)
        {
            map_display.x=0;
        }
        else
        {
            if(player.x-step>=player_frame.x){player.x-=step;}
            else{player.x=0;}
        }
    }
    return;
}

void right()
{
    if(player_frame.x+player_frame.w+step<=SCREEN_WIDTH)
    {
        player_frame.x+=step;
        player.x+=step;
    }
    else
    {
        if(player_frame.x+player_frame.w!=SCREEN_WIDTH)
        {       
            player.x+=SCREEN_WIDTH-player_frame.x-player_frame.w;
            player_frame.x=SCREEN_WIDTH-player_frame.w;
        }
        else if(map_display.x+map_display.w+step<=map_w)
        {
            map_display.x+=step;
        }
        else if(map_display.x+map_display.w!=map_w)
        {
            map_display.x=map_w-map_display.w;
        }
        else
        {
            if(player.x+player.w+step<=player_frame.x+player_frame.x){player.x+=step;}
            else{player.x=SCREEN_WIDTH-player.w;}
        }
    }
    return;
}

bool feasible(char c,vector<vector<bool>> &allowed_pixel)
{
    if(c=='U' && player_point.y!=player_y/2){if(allowed_pixel[player_point.x][player_point.y-1]){cout<<allowed_pixel[player_point.x][player_point.y-1];return true;}}
    if(c=='D' && player_point.y!=map_h-player_y/2){if(allowed_pixel[player_point.x][player_point.y+1]){return true;}}
    if(c=='L' && player_point.y!=player_x/2){if(allowed_pixel[player_point.x-1][player_point.y]){return true;}}
    if(c=='R' && player_point.y!=map_h-player_x/2){if(allowed_pixel[player_point.x+1][player_point.y]){return true;}}
    return false;
}

void update_center()
{
    player_point.x=player.x+player.w/2;
    player_point.y=player.y+player.h/2;
}

bool load_matrix()
{
    SDL_QueryTexture(map, NULL, NULL, &map_w,&map_h);
    ifstream file("matrix.txt");
    if(!file.is_open())
    {
        cout<<"cannot load matrix file"<<endl;
        return false;
    }
    for(int i=0;i<map_h;i++)
    {
        vector<bool> temp;
        for(int j=0;j<map_w;j++)
        {
            int k;
            file>>k;
            if(k==255){temp.push_back(false);}
            else{temp.push_back(true);}
        }
        allowed_pixel.push_back(temp);
    }
    cout<<allowed_pixel.size()<<" "<<allowed_pixel[0].size()<<" "<<map_w<<" "<<map_h;
    return true;
}