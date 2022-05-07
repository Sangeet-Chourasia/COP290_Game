
#include <vector>
#include<string>

#include "globals.h"
#include <fstream>
#define fps 20
#define PORT 8080
#include <string>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "animation.h"

bool button_pressed=false;
int frame = 0;
int direction=0;
void move(const Uint8* state,vector<vector<bool>> &allowed_pixel);

int player_x=25;
int player_y=40;

SDL_Rect player_frame{0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
SDL_Rect map_display{0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

SDL_Point player_point{player_x/2,player_y/2};
SDL_Rect player{209-player_x/2,420-player_y/2,player_x,player_y};
int sprite_boy_w,sprite_boy_h;


vector<vector<bool>> allowed_pixel;
int step=1;

int new_socket,valread;

void animation(bool multiplayer)
{
    float accum_anim_time = 0.0;
    Uint32 prev_time = 0;
    Uint32 curr_time = 0;

    // increase this number to make animation plays faster
    const int fAnim_fps = fps;
    // cache the calculation of animation speed
    const float kAnim_frame_delay = 0.0 / fAnim_fps;
    const int step =1;
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
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);
    if(multiplayer){make_socket();}

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
            //cout<<player.x<<" "<<allowed_pixel[player.x][player.y]<<" "<<player.y<<endl;
        }
        
        else{SDL_RenderCopy(renderer,spritesheet_boy,&Rect_movement[direction][0],&player);}
        // if(intersection)SDL_RenderCopy(renderer,menu_background,&current_src_pos,&current_dst_pos);
        SDL_RenderPresent(renderer);
        accum_anim_time += deltaTime;
        if (accum_anim_time >= kAnim_frame_delay)
        {
            frame = (frame + 1) % 8;
            accum_anim_time -= kAnim_frame_delay;
            if(button_pressed)
            {
                if(multiplayer){send_message(to_string(direction),new_socket,valread);}
            }
            else if(multiplayer){send_message(to_string(8),new_socket,valread);}
        }
        SDL_Delay(50);
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

cout<<"above_socket"<<endl;
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
//	char buffer[1024] = { 0 };

cout<<"above_socket1"<<endl;
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
cout<<"above_socket2"<<endl;
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
cout<<"above_socket4"<<endl;
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		cout<<"bind failed";
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		cout<<"listen";
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		cout<<"accept";
		exit(EXIT_FAILURE);
	}
// SOCKET END
cout<<"below_socket"<<endl;
}

void send_message(string str, int& new_socket ,int& valread)
{
    return;
    cout<<"inside_send"<<endl;
    char buffer[1024] = { 0 };
    char *hello = new char[str.length() + 1];
    strcpy(hello, str.c_str());
	valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent from server\n");
    cout<<"sock="<<new_socket<<"buffer="<<buffer;
    cout<<"outside_send"<<endl;
	return ;
}