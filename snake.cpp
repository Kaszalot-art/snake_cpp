#include <conio.h>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <random>
#include <queue>
#include <utility>
#include <string>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);

char BFS(array<int, 2> head, char board[25][65],int fruit[2], int width,int height,char current_direction){
    array<int, 2> start = {head[0], head[1]};

    vector<bool> row(width, false);
    vector<vector<bool>> visited(height, row);

    // cout << height << '\n';
    // cout << width << '\n';

    vector<array<int,2>> int_row(width,{-1,-1});
    vector<vector<array<int,2>>> parents(height, int_row);

    parents[start[0]][start[1]] = {start[0],start[1]};

    // pair<int ,int> last_tile = {-1,-1};


    queue<pair<int,int>> q;

    int licznik = 0;
    visited[start[0]][start[1]] = true;
    q.push({start[0],start[1]});
    bool fruit_found = false;

    while(!q.empty()){
        pair<int, int> node = q.front();
        q.pop();
        licznik++;
        // cout<< licznik << '\n';
        // cout << "Odwiedzam: " << to_string(node.first) << to_string(node.second) << "\n";

        if (node.first == fruit[0] && node.second == fruit[1]){
            fruit_found = true;
            break;
            
        }
        if (node.first -1 >= 0 && (board[node.first - 1][node.second] == '_' || board[node.first - 1][node.second] == 'O') && board[node.first - 1][node.second] != 'x'){
            if (!visited[node.first - 1][node.second]){
                visited[node.first - 1][node.second] = true;
                parents[node.first - 1][node.second] = {node.first,node.second};
                q.push({node.first - 1,node.second});
            }
        }
        if (node.first + 1 < height && (board[node.first + 1][node.second] == '_' || board[node.first + 1][node.second] == 'O') && board[node.first + 1][node.second] != 'x'){
            if (!visited[node.first + 1][node.second]){
                visited[node.first + 1][node.second] = true;
                parents[node.first + 1][node.second] = {node.first,node.second};
                q.push({node.first + 1,node.second});
            }
        }
        if (node.second -1 >= 0 && (board[node.first][node.second - 1] == '_' || board[node.first][node.second - 1] == 'O') && board[node.first][node.second - 1] != 'x'){
            if (!visited[node.first][node.second-1]){
                visited[node.first][node.second-1] = true;
                parents[node.first][node.second -1] = {node.first,node.second};
                q.push({node.first,node.second-1});
            }
        }
        if (node.second + 1 < width &&  (board[node.first][node.second + 1] == '_' || board[node.first][node.second + 1] == 'O') && board[node.first][node.second + 1] != 'x'){
            if (!visited[node.first][node.second + 1]){
                visited[node.first][node.second + 1] = true;
                parents[node.first][node.second + 1] = {node.first,node.second};
                q.push({node.first,node.second + 1});
            }
        }
    }
    if (fruit_found){
        array<int, 2> current = {fruit[0], fruit[1]};
        array<int, 2> parent = parents[current[0]][current[1]];
        // int j =0;
        while (parent[0] != start[0] || parent[1] != start[1]){
            // j++;
            // cout << "parents path: " << to_string(j) << '\n'; 
            current = parent;
            parent = parents[current[0]][current[1]];
        }

        // cout << "start: " << to_string(start[0]) << " " << to_string(start[1]) << "   to path: " << to_string(current[0])<< " " << to_string(current[1]) << "    fruit: " << to_string(fruit[0])<< " " << to_string(fruit[1]) << " ";
        // std::cout << "\033[J";
        int dx =  start[0] - current[0];
        int dy =  start[1] - current[1];

        if(dx == 1) {return 'w';}
        if(dx == -1) { return 's';}

        if(dy == 1) {return 'a';}
        if(dy == -1) {return 'd';}

    }

    // cout << "zwraca current_pos" << '\n';
    return 'f';
}


char generate_move(vector<array<int,2>> player,char board[25][65], int fruit[2],int height,int width,char current_direction){
    bool clear_path = true;
    array<int,2> head = player[0];
    bool left = true;
    bool right = true;
    bool up = true;
    bool down = true;
    int skip_first = 0;
    
    char bfs = BFS(player[0],board,fruit,height,width,current_direction);
    if (bfs != 'f'){
        return bfs;
    }

    for (array<int,2> x : player){
        if (skip_first == 0){skip_first++;continue;}
        if ((x[1] == head[1]+1 && x[0] == head[0]) || head[1]+1 > height){
            right = false;
        }
        if ((x[1] == head[1]-1 && x[0] == head[0]) || head[1]-1 < 0){
            left = false;
        }
        if ((x[0] == head[0]-1 && x[1] == head[1]) || head[0]-1 < 0){
            up = false;
        }
        if ((x[0] == head[0]+1 && x[1] == head[1]) || head[0]+1 > width){
            down = false;
        }
        skip_first++;
    }
    
    // góra/dół
    if (player[0][0] < fruit[0]){
        if (down){
            return 's';
        }
        else if (left){
            return 'a';
        }else if (right){
            return 'd';
        }
    }
    else if(player[0][0] > fruit[0]){
        if (up){
            return 'w';
        }else if (right){
            return 'd';
        }
        else if (left){
            return 'a';
        }
    }
    // lewo/prawo
    else if (player[0][1] > fruit[1]){
        if (left){return 'a';}
        else if (down) {return 's';}
        else if (up){return'w';}
        

    }else if(player[0][1] < fruit[1]){
        if (right){return 'd';}
        else if (up){return'w';}
        else if (down) {return 's';}
    }
    // else if (player[0][0] == fruit[0]){
    //     if (current_direction == 'w'){return 's';}
    //     else if (current_direction == 's'){return 'w';}
    // }
    if(up){return 'w';}
    if(down){return 's';}
    if(left){return 'a';}
    if(right){return 'd';}

    return 'f';

}



int main(int argc, char* argv[]){
    system("cls");
    bool auto_play = false;
    int fps = 60;
    
    for(int i = 0; i < argc; i++){
        string arg = argv[i];
        if (arg == "-a" || arg =="--auto") auto_play = true;
        if ((arg.find("--fps=",0))==0){

            fps = stoi(arg.substr(6));
        }
    }
    
    
    int move_every_x_frames = 1;
    int start_frame = 1;
    bool run = true;
    bool stop_playing = false;
    while (!stop_playing){
    char direction = 'a';
    char key = 's';
    
    double frame_time = 1.0/fps;

    const int width = 65;
    const int height = 25;

    uniform_int_distribution<> width_gen(0, width-1);
    uniform_int_distribution<> height_gen(0, height-1);
    
    char board[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width;j++){
            board[i][j] = '_';
        }
    }

    int fruit[2] = {5,15};
    srand(time(0));

    vector<array<int,2>> player;

    array<int,2> head = {5,5};
    array<int,2> tail_one = {4,5};
    array<int,2> tail_two = {4,6};
    array<int,2> tail_three = {5,6};
    array<int,2> tail_four = {6,6};
    array<int,2> tail_five = {6,7};
    array<int,2> tail_six = {6,7};

    player.push_back(head);
    player.push_back(tail_one);
    player.push_back(tail_two);
    player.push_back(tail_three);
    player.push_back(tail_four);
    player.push_back(tail_five);
    player.push_back(tail_six);

    for (array<int,2> x : player){
        board[x[0]][x[1]] = 'x';
    }

    int score = 0;
        
    while (run)
    {   
        
        
        auto start = chrono::high_resolution_clock::now();
        if (!auto_play)
        {
            if (_kbhit()){
            char key_pressed = _getch();
            if (key_pressed == 'w' || key_pressed == 'a' || key_pressed == 's' || key_pressed == 'd'){
                if (key_pressed == 'w' && key != 's'){
                    key = key_pressed;
                }
                else if (key_pressed == 's' && key != 'w'){
                    key = key_pressed;
                }
                else if (key_pressed == 'a' && key != 'd'){
                    key = key_pressed;
                }
                else if (key_pressed == 'd' && key != 'a'){
                    key = key_pressed;
                }
                
            }
            
            
            // cout << key << endl;
        }
        }else{
            key = generate_move(player, board,fruit,width, height, key);
        }
        if (start_frame%move_every_x_frames ==0){

            board[player.back()[0]][player.back()[1]] = '_';
            // if(direction == 's'){
            //     if (player_location[0] < height && player_location[0] > 0) {player_location[0]++;}
            // }
            // else if(direction == 'w'){
            //     if (player_location[0] < height && player_location[0] > 0) {player_location[0]--;}
            // }
            // else if (direction == 'a'){
            //     if (player_location[1] < width && player_location[1] > 0) {player_location[1]--;}
            // }
            // else if(direction == 'd'){
            //     if (player_location[1] < width && player_location[1] > 0) {player_location[1]++;}
            // }
            // board[player_location[0]][player_location[1]] = 'x';

            if(key == 's'){
                if (player[0][0] < height ) {player.insert(player.begin(),{player[0][0]+1,player[0][1]});}
            }
            else if(key == 'w'){
                if (player[0][0] < height) {player.insert(player.begin(),{player[0][0]-1,player[0][1]});}
            }
            else if (key == 'a'){
                if (player[0][1] < width) {player.insert(player.begin(),{player[0][0],player[0][1]-1});}
            }
            else if(key == 'd'){
                if (player[0][1] < width) {player.insert(player.begin(),{player[0][0],player[0][1]+1});}
            }
            if(player[0][0] >= height || player[0][0] < 0 || player[0][1] >= width || player[0][1] < 0){
                break;
            }
            
            if (player[0][0] == fruit[0] && player[0][1] == fruit[1]){
                board[fruit[0]][fruit[1]] = '_';
                score++;
                bool generate_random = true;
                while (generate_random){
                    generate_random = false;
                    int random_row = width_gen(gen);
                    int random_col = height_gen(gen);
                    fruit[0] = random_col;
                    fruit[1] = random_row;

                    for (array<int,2> x : player){
                        if (x[0] == fruit[0] && x[1] == fruit[1]){
                            generate_random = true;
                            break;
                        }
                    }
                    
                }
                board[fruit[0]][fruit[1]] = 'O';
                
            }
            else{
                player.pop_back();
            }

            for (array<int,2> x : player){
                board[x[0]][x[1]] = 'x';
            }
            board[player[0][0]][player[0][1]] = 'x';
            start_frame = 1;
        }
        board[fruit[0]][fruit[1]] = 'O';
        string board_string;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width;j++){
                board_string += board[i][j];
            }
            board_string += '\n';
        }
        // system("cls");
        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        board_string += "score: "+ to_string(score);
        cout << board_string;

        // kolizje
        int i = 0;
        for (array<int,2> x : player){
            if (i==0){
                i++;
                continue;
            }
            if (x == player[0]){
                run = false;
            }
            i++;
        }
        


        start_frame++;
        auto end = chrono::high_resolution_clock::now();

        cout << '\n';
        chrono::duration<double> frame_duration =  end - start;
        // cout << frame_duration.count() << endl;
        double sleep_time = frame_time - frame_duration.count();
        if (sleep_time >0) {
            // cout << sleep_time;
            
            Sleep(sleep_time*1000);
        }
            
    }
    COORD coord;
    coord.X = 0;
    coord.Y = height+2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    std::cout << "\033[J";
    char continue_game;
    cout << "play again? [y/n]";
    cin >> continue_game;
    if (continue_game == 'n'){
        stop_playing = true;
    }
    if (continue_game == 'y'){
        run = true;
        stop_playing = false;
    }
    coord.Y = height;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    system("cls");
    std::cout << "\033[J";
    }
    
    
}