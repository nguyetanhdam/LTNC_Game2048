#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>

using namespace std;

const int BOX_WIDTH = 100;
const int BOX_HEIGHT = 100;

struct Box {
    int x, y;
    int value;
};

#define vvB vector<vector<Box>>

enum Mode {
    UNDO,
    PLAY,
    END_GAME,
    OUT_GAME,
    WIN_GAME
};

struct Game {
    Mode mode;
    int level;
    Game(Mode mode, int level){
        this -> mode = mode;
        this -> level = level;
    }
};

void solve (vector<int> &v);

bool compare_Box (vvB &last_box, vvB& box, Game& game);

bool check_game_over (vvB& box, Game& game);

bool move_Left (vvB& box, Game& game, vvB& last_box);

bool move_Right (vvB& box, Game& game, vvB& last_box);

bool move_Down (vvB& box, Game& game, vvB& last_box);

bool move_Up (vvB& box, Game& game, vvB& last_box);

void solve_Event (SDL_Event& e, Game& game, vvB& box, vvB& last_box);

#endif // EVENTS_H
