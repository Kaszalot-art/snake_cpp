#include <conio.h>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    
    

    int move_every_x_frames = 1;
    int start_frame = 1;
    bool run = true;
    bool stop_playing = false;
    while (!stop_playing){
    char direction = 'd';
    char key = 'd';
    int fps = 60;
    double frame_time = 1.0/fps;

    int width = 65;
    int height = 25;
    
    char board[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width;j++){
            board[i][j] = '_';
        }
    }

    int fruit[2] = {15,15};
    srand(time(0));

    // musze stworzyć zmienną z której będę usuwał koniec i dodawał nową wartość na początku
    vector<array<int,2>> player;

    array<int,2> head = {5,5};
    array<int,2> tail_one = {5,4};
    array<int,2> tail_two = {5,3};
    array<int,2> tail_three = {5,3};
    array<int,2> tail_four = {5,3};
    array<int,2> tail_five = {5,3};

    player.push_back(head);
    player.push_back(tail_one);
    player.push_back(tail_two);
    player.push_back(tail_three);
    player.push_back(tail_four);
    player.push_back(tail_five);


    int score = 0;
        
    while (run)
    {   
        
        
        auto start = chrono::high_resolution_clock::now();
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
                    int random_row = rand() % width;
                    int random_col = rand() % height;
                    fruit[0] = random_col;
                    fruit[1] = random_row;

                    for (array<int,2> x : player){
                        if (x[0] == fruit[0]){
                            if (x[1] = fruit[1]){
                                generate_random = false;
                            }
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

        cout << endl;
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
    std::cout << "\033[J";
    }
    
    
}