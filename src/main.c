#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "sdl_utils.h"
#include "utilities.h"

int main(void) {
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;
    sdl_init(&screen_surface, &window, "Beautiful Noise");

    init_fps_sync(60);
    bool quit = false; SDL_Event e;
    while (start_time = clock(), !quit) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) { // handle events
                case SDL_QUIT: {
                    quit = true;
                    break;
                }

                case SDL_WINDOWEVENT: {
                    if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                        sdl_resurface(&screen_surface, &window);
                    break;
                }

                default: {
                    break;
                }
            }
        } // end polling

        // draw calls
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
        SDL_UpdateWindowSurface(window);
        // draw calls

        fps_sync();
    } // end program

    sdl_full_shutdown(window, 0);
}