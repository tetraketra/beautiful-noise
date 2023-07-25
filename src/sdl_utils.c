#include "sdl_utils.h"
#include "utilities.h"

const int SDL_START_SCREEN_WIDTH = 640;
const int SDL_START_SCREEN_HEIGHT = 480;

void sdl_init(SDL_Surface** screen_surface, SDL_Window** window, char* window_title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not be initialized!", SDL_GetError()); sdl_full_shutdown(*window, -1); }

    *window = SDL_CreateWindow(
                window_title,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_START_SCREEN_WIDTH,
                SDL_START_SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
              SDL_SetWindowResizable(*window, SDL_TRUE);
    if (*window == NULL) {
        log_error("Window could not be created!", SDL_GetError()); sdl_full_shutdown(*window, -1); }

    *screen_surface = SDL_GetWindowSurface(*window);
    SDL_FillRect(*screen_surface, NULL, SDL_MapRGB((*screen_surface)->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(*window);
}

void sdl_resurface(SDL_Surface** screen_surface, SDL_Window** window) {
    SDL_FreeSurface(*screen_surface);
    *screen_surface = SDL_GetWindowSurface(*window);
}

