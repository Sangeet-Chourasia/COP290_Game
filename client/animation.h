void up();
void down();
void left();
void right();
void update_center();
bool feasible(char,vector<vector<bool>> &allowed_pixel);

bool load_matrix();
void send_message(string,int&, int&);
void make_socket();
void animation(bool multiplayer);
void draw();
void move(const Uint8* state,vector<vector<bool>> &allowed_pixel);
