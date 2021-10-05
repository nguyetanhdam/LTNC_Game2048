#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

#include "SDL_units.h"
#include "Events.h"

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

const char WINDOW_TITLE[] = "GAME 2048";
const char Title_win_game[] = "Congratulation";

void create_Random(vvB& box, Game& game);

int main(int argc, char* argv[]) {
    cout << "Chao mung ban da choi game 2048!" << endl << "Chuc ban co nhung trai nghiem vui ve!" << endl << endl;
    srand((unsigned int )time(NULL));
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture = NULL;
    SDL_Color color;

    Game game = Game(PLAY, 4);
    SCREEN_WIDTH = BOX_WIDTH * game.level;
    SCREEN_HEIGHT = BOX_HEIGHT * game.level;

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // khởi tạo TTF
    if(TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    font = TTF_OpenFont("VeraMoBd.ttf", 60);
    if (font == NULL) logSDLError(cout, "TTF OpenFont", true);
    color = { 200, 250, 100 };


    vvB box, last_box;
    for (int i = 0; i < game.level; ++i) {
        vector<Box> v;
        for (int j = 0; j < game.level; ++j) {
            v.push_back(Box{ j * BOX_HEIGHT, i * BOX_WIDTH, 0 });
        }
        box.push_back(v);
    }
    box[0][0].value = 2;
    create_Random(box, game);
    refressScreen(renderer, box, game, surface, texture, font, color);
    while (true) {
        solve_Event(e, game, box, last_box);

        for (int i = 0; i < game.level; ++i){
            for (int j = 0; j < game.level; ++j){
                if(box[i][j].value == 8)
                {
                    return 0;
                }
            }
        }

        if (game.mode == OUT_GAME) break;
        if (game.mode != UNDO) create_Random(box, game);
        refressScreen(renderer, box, game, surface, texture, font, color);
    }

    SDL_Delay(100);
    quitSDL(window, renderer);
    cout << "Cam on ban da choi game!" << endl;
    return 0;
}

void create_Random(vvB& box, Game& game){
    while(true){
        int i = rand() % game.level;
        int j = rand() % game.level;
        if(box[i][j].value) continue;
        box[i][j].value = 2;
        break;
    }
}
