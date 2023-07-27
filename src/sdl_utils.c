#include <linux/limits.h>
#include <string.h>
#include <libgen.h>

#include "sdl_utils.h"
#include "utilities.h"

const int SDL_START_SCREEN_WIDTH = 640;
const int SDL_START_SCREEN_HEIGHT = 480;

void sdl_init(SDL_Window** window, SDL_Renderer** rend, TTF_Font** font, char* srcdir, char* window_title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not be initialized!", SDL_GetError()); sdl_full_shutdown(window, -1); }

    *window = SDL_CreateWindow(
                window_title,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_START_SCREEN_WIDTH,
                SDL_START_SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        log_error("Window could not be created!", SDL_GetError()); sdl_full_shutdown(window, -1); }
    SDL_SetWindowResizable(*window, SDL_TRUE);

    *rend = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*rend == NULL) {
        log_error("Renderer could not be created!", SDL_GetError()); sdl_full_shutdown(window, -1); }
    SDL_SetRenderDrawColor(*rend, 0x00, 0xFF, 0x00, 0xFF);
    SDL_SetRenderDrawBlendMode(*rend, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(*rend);
    SDL_RenderPresent(*rend);

    if (TTF_Init() < 0) {
        log_error("TTF could not be initialized!", SDL_GetError()); sdl_full_shutdown(window, -1); }
    char fontdir[PATH_MAX];
    strncpy(fontdir, srcdir, sizeof(fontdir) - 1);
    strncat(fontdir, "/charybdis.ttf", sizeof(fontdir) - 1);
    *font = TTF_OpenFont(fontdir, 24);
    if (*font == NULL)  {
        log_error("Font could not be loaded!", SDL_GetError()); sdl_full_shutdown(window, -1); }
}

void sdl_full_shutdown(SDL_Window** window, int code) {
    SDL_DestroyWindow(*window);           
    SDL_Quit();                          
    exit(code);                          
}