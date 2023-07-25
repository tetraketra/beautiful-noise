#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "sdl_utils.h"
#include "utilities.h"

int main(void) {
    SDL_Window* window = NULL;
    SDL_Renderer* rend = NULL;
    sdl_init(&window, &rend, "Beautiful Noise");

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
                    if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        // not needed yet actually
                    }
                    break;
                }

                default: {
                    break;
                }
            }
        } // end polling

        // draw calls
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
        // draw calls

        fps_sync();
    } // end program

    sdl_full_shutdown(window, 0);
}