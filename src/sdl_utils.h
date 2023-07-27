#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#ifndef STD_UTILS_H
#define STD_UTILS_H

void sdl_full_shutdown(SDL_Window** window, int code);
void sdl_init(SDL_Window** window, SDL_Renderer** rend, TTF_Font** font, char* srcdir, char* window_title);

#endif