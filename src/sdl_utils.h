#include <SDL2/SDL.h>
#include <stdio.h>

#ifndef STD_UTILS_H
#define STD_UTILS_H

#define sdl_full_shutdown(window, code) {              \
    SDL_DestroyWindow(window);                         \
    SDL_Quit();                                        \
    exit(code);                                        \
    }

void sdl_init(SDL_Surface** screen_surface, SDL_Window** window, char* window_title);
void sdl_resurface(SDL_Surface** screen_surface, SDL_Window** window);

#endif