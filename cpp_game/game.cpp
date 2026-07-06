#include <iostream>
#include <conio.h>
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

using namespace std;

void wait(double n) {
    std::this_thread::sleep_for(std::chrono::duration<double>(n));
}

int ran(int n) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    return rand() % (n + 1);
}

void cls() {
    cout << "\033[2J\033[1;1H";
    cout.flush();
}

struct Game {
    bool is_game_over = false;
    vector<array<int, 2>> enemies;
    char key;
    int objs[2][2] = { {-1, -1}, {-1, -1} };
    int score = 0;
    short n = 0;
    int turn_counter = 0;
    const int size = 7;
    string map[7][7] = {
        {". ", ". ", ". ", ". ", ". ", ". ", ". "},
        {". ", ". ", ". ", ". ", ". ", ". ", ". "},
        {". ", ". ", ". ", ". ", ". ", ". ", ". "},
        {". ", ". ", ". ", ". ", ". ", ". ", ". "},
        {". ", ". ", ". ", ". ", ". ", ". ", ". "},
        {". ", ". ", ". ", ". ", ". ", ". ", ". "},
        {". ", ". ", ". ", ". ", ". ", ". ", ". "}
    };
    int ppos[2];
    int wpos[2] = { -1, -1 };
    bool has_weapon = false;
    bool is_weapon = false;

    Game() {
        cout<<"輸入敵人移動模式(0~5):";
        cin>>n;
        ppos[0] = ran(6);
        ppos[1] = ran(6);
        map[ppos[0]][ppos[1]] = "P ";
        add_rand_obj();
    }

    bool game_over() {
        cls();
        cout << "\t你被抓到了\n\tGAME OVER!\n\t你的分數:" << score
             << "\n\t你的存活回合數:" << turn_counter
             << "\n\t要重來一局嗎(y/n): ";
        char restart;
        cin >> restart;
        return restart == 'y';
    }

    bool is_nearby_player(int x, int y) {
        return abs(x - ppos[0]) <= 1 && abs(y - ppos[1]) <= 1;
    }

    bool is_valid_pos(int r, int c) {
        return r >= 0 && r < size && c >= 0 && c < size;
    }

    void display_map() {
        cls();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << map[i][j];
            }
            cout << "\n";
        }
        if (has_weapon) {
            cout << "你擁有武器(按E使用)\n";
        }
        cout << "分數:" << score << endl;
        cout << "第" << turn_counter << "回合\n";
    }

    bool play() {
        while (!is_game_over) {
            display_map();
            wait(0.5);
            if (_kbhit()) {
                key = _getch();
                move_player();
                if ((key != 'w' && key != 's') && (key != 'a' && key != 'd')) {
                    continue;
                }
                turn_counter++;
                if (n == 5) {
                    if (turn_counter % 3 > 0) move_enemies();
                } else if (n == 4) {
                    if (ran(9) > 3) move_enemies();
                } else if (n == 3) {
                    if (ran(7) > 3) move_enemies();
                } else if (n == 2) {
                    if (ran(6) > 3) move_enemies();
                } else if (n == 1) {
                    if (turn_counter % 2) move_enemies();
                } else if (n == 0) {
                    if (turn_counter % 3 == 0) move_enemies();
                }
            }
        }
        return game_over();
    }

    void move_player() {
        int r = ppos[0];
        int c = ppos[1];
        if (key == 27) {
            cout << "\n你按下 ESC，遊戲結束。\n";
            exit(0);
        } else if (key == 'w' && r > 0) {
            map[r][c] = ". ";
            r--;
        } else if (key == 's' && r < 6) {
            map[r][c] = ". ";
            r++;
        } else if (key == 'a' && c > 0) {
            map[r][c] = ". ";
            c--;
        } else if (key == 'd' && c < 6) {
            map[r][c] = ". ";
            c++;
        } else if (key == 'e') {
            use_weapon();
            return;
        }

        ppos[0] = r;
        ppos[1] = c;

        if (map[r][c] == "O ") {
            score++;
            for (auto& opos : objs) {
                if (opos[0] == r && opos[1] == c) {
                    opos[0] = -1;
                    opos[1] = -1;
                    if (ran(15) < static_cast<int>(enemies.size()) && !has_weapon) {
                        add_weapon();
                    }
                }
            }
            add_rand_obj();
            if (score % 2 == 1) {
                add_enemy();
            }
        } else if (map[r][c] == "E ") {
            is_game_over = true;
            return;
        } else if (map[r][c] == "W ") {
            has_weapon = true;
            wpos[0] = -1;
            wpos[1] = -1;
        }

        map[r][c] = "P ";
    }

    bool ninm(int pos[2]) {
        return map[pos[0]][pos[1]] == ". ";
    }

    void add_rand_obj() {
        for (auto& opos : objs) {
            if (opos[0] == -1 && opos[1] == -1) {
                while (true) {
                    int pos[2] = { ran(6), ran(6) };
                    if (ninm(pos) && (!is_nearby_player(pos[0], pos[1]))) {
                        map[pos[0]][pos[1]] = "O ";
                        opos[0] = pos[0];
                        opos[1] = pos[1];
                        break;
                    }
                }
            }
        }
    }

    void add_enemy() {
        while (true) {
            int pos[2] = { ran(6), ran(6) };
            if (ninm(pos) && (!is_nearby_player(pos[0], pos[1]))) {
                enemies.push_back({ pos[0], pos[1] });
                map[pos[0]][pos[1]] = "E ";
                break;
            }
        }
    }

    void move_enemies() {
        set<pair<int, int>> new_positions;
        for (auto& enemy : enemies) {
            int old_r = enemy[0];
            int old_c = enemy[1];

            bool on_obj = false, on_weapon = false;
            for (auto& opos : objs) {
                if (opos[0] == old_r && opos[1] == old_c) {
                    map[old_r][old_c] = "O ";
                    on_obj = true;
                    break;
                } else if (wpos[0] == old_r && wpos[1] == old_c) {
                    map[old_r][old_c] = "W ";
                    on_weapon = true;
                    break;
                }
            }
            if (!on_obj && !on_weapon) map[old_r][old_c] = ". ";

            int new_r = old_r, new_c = old_c;
            if (abs(old_r - ppos[0]) > abs(old_c - ppos[1])) {
                if (ppos[0] < old_r && is_valid_pos(old_r - 1, old_c)) new_r--;
                else if (ppos[0] > old_r && is_valid_pos(old_r + 1, old_c)) new_r++;
            } else {
                if (ppos[1] < old_c && is_valid_pos(old_r, old_c - 1)) new_c--;
                else if (ppos[1] > old_c && is_valid_pos(old_r, old_c + 1)) new_c++;
            }

            if (new_positions.count({ new_r, new_c }) > 0 || map[new_r][new_c] == "E ") {
                new_r = old_r;
                new_c = old_c;
            }

            enemy[0] = new_r;
            enemy[1] = new_c;
            new_positions.insert({ new_r, new_c });

            if (new_r == ppos[0] && new_c == ppos[1]) {
                is_game_over = true;
                return;
            }

            map[new_r][new_c] = "E ";
        }
    }

    void add_weapon() {
        is_weapon = true;
        while (true) {
            int pos[2] = { ran(6), ran(6) };
            if ((!has_weapon)&&ninm(pos) && (!is_nearby_player(pos[0], pos[1]))) {
                wpos[0] = pos[0];
                wpos[1] = pos[1];
                map[pos[0]][pos[1]] = "W ";
                break;
            }
        }
    }

    void use_weapon() {
        if (!has_weapon) return;

        vector<array<int, 2>> new_enemies;
        for (auto& enemy : enemies) {
            int er = enemy[0];
            int ec = enemy[1];
            if (abs(er - ppos[0]) <= 1 && abs(ec - ppos[1]) <= 1) {
                if (ran(1) == 0) {
                    map[er][ec] = ". ";
                    continue;
                }
            }
            new_enemies.push_back(enemy);
        }
        enemies = new_enemies;
        has_weapon = false;
        is_weapon = false;
    }
};

int main() {
    system("chcp 65001");
    while (true) {
        Game game;
        if (!game.play()) break;
    }
    return 0;
}
