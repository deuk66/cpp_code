#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cmath>
#include <array>
#include <set>
#include <ctime>
#include <utility>
#include <unistd.h>
#include <stdio.h>
#include <deque>
#include <windows.h>


using namespace std;


int ran(int n){   //random(0~n)
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    return rand() % (n + 1);
}
void cls(){   //清除
    cout << "\033[2J\033[1;1H";
    cout.flush();
}

struct Game{
    array <int,2> new_pos(){
        array<int ,2> pos;
        while(true){
            pos={ran(14),ran(14)};
            if(map[pos[0]][pos[1]]==" . "){
                break;
            }
        }
        return pos;
    }
    string map[15][15];
    int head[2]={7,7};
    deque <array<int,2>> body ; 
    bool game_over = false;
    char side = 'w'; // 初始方向
    double speed = 0.2; // 每次移動的間隔（秒）
    void set_pea(){
        
    }
    Game(){
        for(auto &i:map){
            for(auto &j:i){
                j=" . ";
            }
        }
        
    }
    void set_map(){
        for(auto &i:map){
            for(auto &j:i){
                cout<<j;
            }
            cout<<endl;
        }
    }
    void move(char c){
        
    }
    void play() {
        while (!game_over) {
            cls(); // 清除畫面
            set_map(); // 顯示地圖
            
            // 檢查是否有按鍵
            if (kbhit()) {
                char input = getch();
                // 處理方向變更
                if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                    side = input;
                } else if (input == 'q') {
                    game_over = true; // 按 q 離開
                    continue;
                }
            }
    
            //  根據目前方向移動蛇頭
            body.push_front();
            switch (side) {
                case 'w': head[0]--; break;
                case 's': head[0]++; break;
                case 'a': head[1]--; break;
                case 'd': head[1]++; break;
            }
            
            
            map[head[0]][head[1]] = " @ ";
    
            sleep(speed/1000.0);
        }
    cout << "Game Over!\n";
}
};


int main() {
    system("chcp 65001");
    
    Game game;
    game.play();
    return 0;
}