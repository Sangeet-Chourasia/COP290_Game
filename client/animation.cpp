
#include <vector>
#include<string>

#include "globals.h"
#include <fstream>
#define fps 20
#define PORT 8080
#include <string>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "animation.h"
void Reset();
void Main_Menu();
void add_time_score();
SDL_Rect target{806,292,839-806,393-303};
void print(int );
void handle_other_event();
char buffer[1024] = { 0 };
bool button_pressed=false;
int frame = 0;
int direction=0;
void move(const Uint8* state,vector<vector<bool>> &allowed_pixel);
void set();
int pos_counter=0;
int neg_counter=0;
int player_x=25;
int player_y=40;
int score=0;

SDL_Rect player_frame2{0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
SDL_Rect map_display{0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

SDL_Point player_point2{239,81};
SDL_Rect player2{239-player_x/2,81-player_y/2,player_x,player_y};
int sprite_boy_w,sprite_boy_h;

SDL_Rect player_frame{0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
SDL_Point player_point{207,423};
SDL_Rect player{207-player_x/2,423-player_y/2,player_x,player_y};

SDL_Surface* map_surface;
SDL_Surface* player_surface;
SDL_Rect *currentFrame;
SDL_Rect Rect_movement[8][8];

int sock= 0,valread;


vector<vector<bool>> allowed_pixel;
float accum_anim_time = 0.0;
Uint32 prev_time = 0;
Uint32 curr_time = 0;

// increase this number to make animation plays faster
int fAnim_fps = fps;
// cache the calculation of animation speed
const float kAnim_frame_delay = 0.0 / fAnim_fps;
const int step =1;

int time_started=0;
int time_taken=0;

void animation(bool multiplayer)
{
    set();
      /*if (TTF_Init() == -1){cout<<"hey"<<endl;
    cout<<"SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError();
    return ;}
    cout<<"hey";
    print(score);*/
    if(!load_matrix()){cout<<"load matrix failed"<<endl;return;}
    int sprite_boy_w,sprite_boy_h;
    SDL_QueryTexture(spritesheet_boy, NULL, NULL, &sprite_boy_w,&sprite_boy_h);
    Rect_movement[8][8];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            Rect_movement[i][j]=SDL_Rect{j*sprite_boy_w/8,i*sprite_boy_h/8,sprite_boy_w/8,sprite_boy_h/8};
        }
    }
    frame = 0;
    direction=0;

    SDL_RenderPresent(renderer);

    SDL_Delay(2000);
    if(multiplayer)


        {

            cout<<"multiplayer_ _pressed"<<endl;    
            make_socket();

            cout<<"socket successfull"<<endl;

}

    IMG_Init(IMG_INIT_JPG);
    IMG_Init(IMG_INIT_PNG);
    player_surface=IMG_Load("Images/sprite_boy.png");
    time_started=SDL_GetTicks();
    while(game_running)
    {
        button_pressed=false;
        Uint8* arrow_keys;
        while (SDL_PollEvent(&e) != 0)
        {
        // user requests quit
            if (e.type == SDL_QUIT)
            {
                game_running= false;
            }
            else if(e.type==SDL_KEYDOWN)
            {
                button_pressed=true;
                const Uint8* state = SDL_GetKeyboardState(NULL);
                move(state,allowed_pixel); 
            }
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(time_started==0){time_started=SDL_GetTicks();}
                else{time_taken+=SDL_GetTicks()-time_started;time_started=0;}
            }
        }

        prev_time = curr_time;
        curr_time = SDL_GetTicks();
        float deltaTime = (curr_time - prev_time) / 1000.0f;            
        currentFrame = &Rect_movement[direction][frame];        
        accum_anim_time += deltaTime;
        if (accum_anim_time >= kAnim_frame_delay)
        {
            if(pos_counter!=0){pos_counter--;}
            if(neg_counter!=0){neg_counter--;}
            if(pos_counter>0){fAnim_fps=50;}
            else if(neg_counter>0){fAnim_fps=5;}
            else{fAnim_fps=20;}

            frame = (frame + 1) % 8;
            accum_anim_time -= kAnim_frame_delay;
            if(multiplayer)
            {
                string str=to_string(player.x)+" "+to_string(player.y);
                send_message(str,sock,valread);
                //cout<<buffer<<" buffer"<<endl;
                /*if(button_pressed)
                {
                if(multiplayer){send_message(to_string(direction),sock,valread);}
                }
                else if(multiplayer){send_message(to_string(8),sock,valread);}
                */
                int size = sizeof(buffer) / sizeof(char);
                cout<<"size="<<size<<endl;
                int p2_x,p2_y;
                string p2x="";
                string p2y="";
                bool change=false;
                for(int i=0;i<size;i++)
                {
                if(buffer[i]==' '){change=true;continue;}
                if(!change){p2x+=buffer[i];}
                else{p2y+=buffer[i];}
                }
                cout<<"for loop finished "<<p2x<<" "<<p2y<<endl;
                player2.x=stoi(p2x);
                player2.y=stoi(p2y);
            }
            //move2(buffer,allowed_pixel);
        }
        SDL_RenderClear(renderer);
        if(multiplayer){SDL_RenderCopy(renderer,spritesheet_boy,&Rect_movement[direction][frame],&player2);}

        SDL_RenderCopy(renderer,map2,NULL,NULL);
        // SDL_RenderCopy(renderer,game_mode_background,NULL,&player_frame);
        if(button_pressed)
        {
        SDL_RenderCopy(renderer,spritesheet_boy,currentFrame,&player);
        //cout<<player.x<<" "<<allowed_pixel[player.x][player.y]<<" "<<player.y<<endl;
        }

        else{SDL_RenderCopy(renderer,spritesheet_boy,&Rect_movement[direction][0],&player);}

        // if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
        SDL_RenderCopy(renderer,spritesheet_boy,&Rect_movement[direction][frame],&player2);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        handle_other_event();
        if(SDL_HasIntersection(&player,&target))
        {
            time_taken+=(SDL_GetTicks()-time_started);
            time_taken/=1000;
            score+=(180-time_taken);
            ofstream record;
            record.open ("record.txt");
            record << "Score of server is :"<<score<<"total time taken in seconds:"<<time_taken<<endl;
            record.close();
            if(!multiplayer){Reset();Main_Menu();}
        }
        if(multiplayer && SDL_HasIntersection(&player2,&target))
        {
            Reset();
            Main_Menu();
        }
    }
}

void move(const Uint8* state,vector<vector<bool>> &allowed_pixel)
{
    if((state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN]) || (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT])){button_pressed=false;}
    else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
    {
        direction=5;
        if(allowed_pixel[player_point.y-1][player_point.x-1])
        {
            up();left();
        }
    }
    else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
    {
        direction=7;
        if(allowed_pixel[player_point.y-1][player_point.x+1])
        {
            up();right();
        }
    }
    else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT])
    {
        direction=4;
        if(allowed_pixel[player_point.y+1][player_point.x-1])
        {
            down();left();
        }
    }
    else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT])
    {
        direction=6;
        if(allowed_pixel[player_point.y+1][player_point.x+1])
        {
            down();right();
        }
    }
/*    else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]){direction=6;if(!feasible('D',allowed_pixel)&& feasible('R',allowed_pixel)){button_pressed=false;return;}down();right();}
    else if(state[SDL_SCANCODE_UP]){direction=3;if(!feasible('U',allowed_pixel)){return;button_pressed=false;}up();}
    else if(state[SDL_SCANCODE_DOWN]){direction=0;if(!feasible('D',allowed_pixel)){return;button_pressed=false;}down();;}
    else if(state[SDL_SCANCODE_LEFT]){direction=1;if(!feasible('L',allowed_pixel)){return;button_pressed=false;}left();}
    else if(state[SDL_SCANCODE_RIGHT]){direction=2;if(!feasible('R',allowed_pixel)){return;button_pressed=false;}right();}*/
    

    else if(state[SDL_SCANCODE_UP])
    {
        direction=3;
        if(allowed_pixel[player_point.y-1][player_point.x])
        {
            up();
        }
    }
    else if(state[SDL_SCANCODE_DOWN])
    {
        direction=0;
        if(allowed_pixel[player_point.y+1][player_point.x])
        {
            down();
        }
    }
    else if(state[SDL_SCANCODE_LEFT])
    {
        direction=1;
        if(allowed_pixel[player_point.y][player_point.x-1])
        {
            left();
        }
    }
    else if(state[SDL_SCANCODE_RIGHT])
    {
        direction=2;
        if(allowed_pixel[player_point.y][player_point.x+1])
        {
            right();
        }
    }
    else{button_pressed=false;}
    update_center();
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
/*
void up()
{
    if(player.y==0){return;}
    player.y-=1;
}

void down()
{
    if(player.y+player.h==map_h){return;}
    player.y+=1;
}

void left()
{
    if(player.x==0){return;}
    player.x-=1;
}
void right()
{
    if(player.x+player.w==map_w){return;}
    player.x+=1;
}*/

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
            else{temp.push_back(true);}//SDL_RenderDrawPoint(renderer,j, i);cout<<"i:"<<i<<" j:"<<j<<endl;}
        }
        allowed_pixel.push_back(temp);
    }
    //cout<<allowed_pixel.size()<<" "<<allowed_pixel[0].size()<<" "<<map_w<<" "<<map_h;
    return true;
}

void make_socket()
{
    // SOCKET

// Server side C/C++ program to demonstrate Socket
// programming

    cout<<"inside_socket"<<endl;
	// int server_fd;
	struct sockaddr_in serv_addr;
	// int opt = 1;
	// int addrlen = sizeof(address);
//	char buffer[1024] = { 0 };

// cout<<"above_socket1"<<endl;
	// Creating socket file descriptor
	 if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return ;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return ;
    }
 
    if (connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr))
        < 0) {
        printf("\nConnection Failed \n");
        return ;
    }
// SOCKET END
cout<<sock<<endl;
cout<<"connection done"<<endl;


}

void send_message(string str, int& new_socket ,int& valread)
{
    // return;
    cout<<str<<endl;
   
  //  char buffer[1024] = { 0 };
    char *hello = new char[str.length() + 1];
    strcpy(hello, str.c_str());

     cout<<"inside_send"<<endl;
    send(sock, hello, strlen(hello), 0);
	printf("Hello message sent from client\n");

    valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);
	
	
    cout<<"sock="<<sock<<"buffer="<<buffer<<endl;
    // cout<<"outside_send"<<endl;
	return ;
}

void draw()
{}/*


void draw()
{
    map_surface=IMG_Load("Images/map.jpg");
    if(button_pressed)
    {
        SDL_BlitSurface(player_surface,currentFrame,map_surface,&player);
        //cout<<player.x<<" "<<allowed_pixel[player.x][player.y]<<" "<<player.y<<endl;
    }
    else{SDL_BlitSurface(player_surface,&Rect_movement[direction][0],map_surface,&player);}
    SDL_BlitSurface(player_surface,currentFrame,map_surface,&player2);
    SDL_Texture* temp= SDL_CreateTextureFromSurface(renderer, map_surface);
    if(player.x+player.w>map_display.w)
    {
        map_display.x=player.x+player.w-map_display.w;
    }
    if(player.y+player.h>map_display.h)
    {
        map_display.y=player.y+player.h-map_display.h;
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,temp,&map_display,NULL);
    // SDL_RenderCopy(renderer,game_mode_background,NULL,&player_frame);

    // if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(map_surface);
}


*/


SDL_Rect cycle1{680,1410,128,57};
SDL_Rect cycle2{1398,487,50,28};
SDL_Rect cycle3{1787,1001,47,55};
SDL_Rect cycle4{1437,487,41,66};
SDL_Rect cycle5{2936,1021,70,30};
SDL_Rect cycle6{2904,1017,75,30};


SDL_Rect array_cycle[]={cycle1,cycle2,cycle3,cycle4,cycle5,cycle6};

SDL_Rect Dog1{807,513,90,62};
SDL_Rect Dog2{808,491,60,80};
SDL_Rect Dog3{821,1116,66,90};
SDL_Rect Dog4{1392,576,75,55};
SDL_Rect Dog5{1371,563,62,60};
SDL_Rect Dog6{2240,1032,84,73};
SDL_Rect Dog7{3144,586,83,62};
SDL_Rect Dog8{4025,685,75,78};
SDL_Rect Dog9{3786,1328,60,80};
SDL_Rect Dog10{3744,1327,100,50};

SDL_Rect array_Dog[]={Dog1,Dog2,Dog3,Dog4,Dog5,Dog6,Dog7,Dog8,Dog9,Dog10};

SDL_Rect friend1{860,665,73,44};
SDL_Rect friend2{888,664,45,122};
SDL_Rect friend3{1219,1125,88,44};
SDL_Rect friend4{3062,814,74,44};
SDL_Rect friend5{3091,816,104,54};
SDL_Rect friend6{3865,734,59,69};

SDL_Rect array_friend[]={friend1,friend2,friend3,friend4,friend5,friend6};

SDL_Rect prof1{2219,926,90,134};
SDL_Rect prof2{2963,1088,120,54};
SDL_Rect prof3{2935,472,110,72};
SDL_Rect prof4{2935,472,62,102};

SDL_Rect array_prof[]={prof1,prof2,prof3,prof4};

void set()
{

for(int i=0;i<6;i++)
{
    SDL_Rect r=array_friend[i];
    r.x/=4800;
    r.w/=4800;
    r.y/=2782;
    r.h/=2782;
}

for(int i=0;i<10;i++)
{
    SDL_Rect r=array_friend[i];
    r.x/=4800;
    r.w/=4800;
    r.y/=2782;
    r.h/=2782;
}
for(int i=0;i<6;i++)
{
    SDL_Rect r=array_friend[i];
    r.x/=4800;
    r.w/=4800;
    r.y/=2782;
    r.h/=2782;
}
for(int i=0;i<4;i++)
{
    SDL_Rect r=array_friend[i];
    r.x/=4800;
    r.w/=4800;
    r.y/=2782;
    r.h/=2782;
}

}

void handle_other_event()
{
    bool b=false;
    for(int i=0;i<6;i++)
    {
        SDL_Rect r=array_cycle[i];
        if(SDL_HasIntersection(&r,&player))
        {
            pos_counter=1000;
            b=true;
            score+=10;
        }
    }
    for(int i=0;i<10;i++)
    {
        SDL_Rect r=array_Dog[i];
        if(SDL_HasIntersection(&r,&player))
        {
            neg_counter=400;
            b=true;
            score-=10;
        }
    }
    for(int i=0;i<6;i++)
    {
        SDL_Rect r=array_friend[i];
        if(SDL_HasIntersection(&r,&player))
        {
            neg_counter=700;
            b=true;
            score-=10;
        }
    }
    for(int i=0;i<4;i++)
    {
        SDL_Rect r=array_prof[i];
        if(SDL_HasIntersection(&r,&player))
        {
            neg_counter=500;
            b=true;
            score-=10;
        }
    }    
}

/*
void print(int score)
{
TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
SDL_Color Black = {0, 0, 0};
string str=to_string(score);
char* char_arr = &str[0];
SDL_Surface* surfaceMessage =TTF_RenderText_Solid(Sans,char_arr, Black);
SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
SDL_Rect rect{0,0,50,10};
SDL_RenderCopy(renderer,Message,NULL,&rect);
}*/




void Reset()
{
    SDL_Rect player_frame_r{0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
    SDL_Rect map_display_r{0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    SDL_Point player_point_r{239,81};
    SDL_Rect player_r{239-player_x/2,81-player_y/2,player_x,player_y};

    SDL_Rect player_frame2_r{0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
    SDL_Point player_point2_r{207,423};
    SDL_Rect player2_r{207-player_x/2,423-player_y/2,player_x,player_y};
}