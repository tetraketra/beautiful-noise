#include <SDL2/SDL.h>
#include <stdio.h>

#ifndef STD_UTILS_H
#define STD_UTILS_H

#define sdl_full_shutdown(window, code) {              \
    SDL_DestroyWindow(window);                         \
    SDL_Quit();                                        \
    exit(code);                                        \
    }

void sdl_init(SDL_Window** window, SDL_Renderer** rend, char* window_title);

#endif