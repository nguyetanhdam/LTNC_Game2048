#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Events.h"

using namespace std;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer* renderer){
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr)
			logSDLError(cout, "CreateTextureFromSurface", true);
	}
	else  logSDLError(cout, "LoadBMP", true);
	return texture;
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

void waitUntilKeyPressed(){
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void show_Text(SDL_Renderer* renderer, const string text, SDL_Surface* &surface,
               SDL_Texture* texture, TTF_Font* font, SDL_Color color, SDL_Rect& filled_rect){
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect srcRest;
	srcRest.x = 0;
	srcRest.y = 0;
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

    SDL_RenderCopy(renderer, texture, &srcRest, &filled_rect);

}

string change_NumberToString(int number){
    number = max(number, 0);
    string res;
    while(number > 0){
        res = char(number % 10 + 48) + res;
        number /= 10;
    }
    if(!res.size()) res = "0";
    return res;
}

void refressScreen(SDL_Renderer * renderer, vvB &box, Game& game, SDL_Surface* &surface,
               SDL_Texture* texture, TTF_Font* font, SDL_Color color){

    SDL_SetRenderDrawColor(renderer, 50, 20, 100, 255);   //black
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i < game.level; ++ i)
        for(int j = 0; j < game.level; ++ j){
            SDL_Rect range_box;
            range_box.x = box[i][j].x;
            range_box.y = box[i][j].y;
            range_box.w = BOX_WIDTH;
            range_box.h = BOX_HEIGHT;
            SDL_RenderDrawRect(renderer, &range_box);
            if(box[i][j].value){
                string text = change_NumberToString(box[i][j].value);
                show_Text(renderer, text, surface, texture, font, color, range_box);
            }
        }
    SDL_RenderPresent(renderer);
}
