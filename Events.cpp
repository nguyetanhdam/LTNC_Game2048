#include <bits/stdc++.h>

#include "Events.h"

using namespace std;

void solve(vector<int> &v){
     for(int i = 0 ; i < v.size(); ++ i){
        if(i < v.size() - 1 && v[i] == v[i + 1]){
            v[i] *= 2;
            v.erase(v.begin() + i + 1);
        }
     }
}

bool compare_Box(vvB &last_box, vvB& box, Game& game){
    for(int i = 0; i < game.level; ++ i) {
        for(int j = 0; j < game.level; ++ j) {
            if(box[i][j].value != last_box[i][j].value) return true;
        }
    }
    return false;
}

bool check_game_over (vvB& box, Game& game){
    return 0;
}

bool move_Left(vvB& box, Game& game, vvB& last_box){
    last_box = box;
    for(int i = 0; i < game.level; ++ i){
        vector<int> v;
        for(int j = 0; j < game.level; ++ j){
            if(!box[i][j].value) continue;
            v.push_back(box[i][j].value);
        }

        solve(v);
        if(v.size() == 0) continue;
        int pos = 0;
        for(int j = 0; j < game.level; ++ j){
            if(pos < v.size()) box[i][j].value = v[pos ++];
            else box[i][j].value = 0;
        }
    }
    return compare_Box(last_box, box, game);
}

bool move_Right(vvB& box, Game& game, vvB& last_box){
    last_box = box;
    for(int i = 0; i < game.level; ++ i){
        vector<int> v;
        for(int j = game.level - 1; j >= 0; -- j){
            if(!box[i][j].value) continue;
            v.push_back(box[i][j].value);
        }

        solve(v);
        if(v.empty()) continue;
        int pos = 0;
        for(int j = game.level - 1; j >= 0; -- j){
            if(pos < v.size()) box[i][j].value = v[pos ++];
            else box[i][j].value = 0;
        }
     }
    return compare_Box(last_box, box, game);
}

bool move_Down(vvB& box, Game& game, vvB& last_box){
    last_box = box;
    for(int j = 0; j < game.level; ++ j){
        vector<int> v;
        for(int i = game.level - 1; i >= 0; -- i){
            if(!box[i][j].value) continue;
            v.push_back(box[i][j].value);
        }

        solve(v);
        if(v.empty()) continue;
        int pos = 0;
        for(int i = game.level - 1; i >= 0; -- i){
            if(pos < v.size())
                box[i][j].value = v[pos ++];
            else box[i][j].value = 0;
        }
    }
    return compare_Box(last_box, box, game);
}

bool move_Up(vvB& box, Game& game, vvB& last_box){
    last_box = box;
    for(int j = 0; j < game.level; ++ j){
        vector<int> v;
        for(int i = 0; i < game.level; ++ i){
            if(!box[i][j].value) continue;
            v.push_back(box[i][j].value);
        }

        solve(v);
        if(v.empty()) continue;
        int pos = 0;
         for(int i = 0; i < game.level; ++ i){
            if(pos < v.size()) box[i][j].value = v[pos ++];
            else box[i][j].value = 0;
        }
     }
     return compare_Box(last_box, box, game);
}

void solve_Event(SDL_Event& e, Game& game, vvB& box, vvB& last_box) {
    if (check_game_over(box, game))
    {
        cout << "Thua rui nha hahaa";
    }
    else
    {
        while (true) {
            if (SDL_PollEvent(&e) == 0) continue;
            if (e.type == SDL_QUIT) {
                game.mode = OUT_GAME;
                break;
            }
            else if (e.type == SDL_KEYDOWN) {
                bool check=false;
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    game.mode = UNDO;
                    box = last_box;
                    break;
                }
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    game.mode = OUT_GAME;
                    break;
                }
                else if (e.key.keysym.sym == SDLK_LEFT) check = move_Left(box, game, last_box);
                else if (e.key.keysym.sym == SDLK_RIGHT) check = move_Right(box, game, last_box);
                else if (e.key.keysym.sym == SDLK_DOWN) check = move_Down(box, game, last_box);
                else if (e.key.keysym.sym == SDLK_UP) check = move_Up(box, game, last_box);
                game.mode = PLAY;
                if (!check) continue;
                break;
            }
        }
    }
}
