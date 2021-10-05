#ifndef SDL_UNITS_H
#define SDL_UNITS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Events.h"

void logSDLError(ostream& os,
                 const string &msg, bool fatal);

SDL_Texture* loadTexture(const string &file, SDL_Renderer* renderer);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
            int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void show_Text(SDL_Renderer* renderer, const string text, SDL_Surface* &surface,
               SDL_Texture* texture, TTF_Font* font, SDL_Color color, SDL_Rect& filled_rect);

string change_NumberToString(int number);

void refressScreen(SDL_Renderer * renderer, vvB &box, Game& game, SDL_Surface* &surface,
               SDL_Texture* texture, TTF_Font* font, SDL_Color color);

void screen_win_game(SDL_Renderer* renderer, SDL_Surface* &surface, SDL_Texture* texture, TTF_Font* font, SDL_Color color);

#endif
