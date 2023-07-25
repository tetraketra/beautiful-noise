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

    // testing
    SDL_Texture *texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 256, 256);
    uint32 pixels[256 * 256];
    for (int i = 0; i < 256 * 256; i++) {
        pixels[i] = compose_pixel(0xFF, 0xFF, 0xFF, rand() % 255);
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(texture, NULL, pixels, 256 * 4);
    // testing

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
        SDL_RenderCopy(rend, texture, NULL, NULL); // testing
        SDL_RenderPresent(rend);
        // draw calls

        fps_sync();
    } // end program

    sdl_full_shutdown(window, 0);
}