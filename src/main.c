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

    // TESTING ONLY
    int tex_w = 256, tex_h = 256;
    int tex_sub_w = 256, tex_sub_h = 256;
    SDL_Texture *texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, tex_w, tex_h);
    uint32 pixels[tex_w * tex_h];
    for (int i = 0; i < tex_w * tex_h; i++) {
        pixels[i] = compose_pixel(rand()%255, rand()%255, rand()%255, 0xFF);
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(texture, NULL, pixels, tex_w * 4);
    // TESTING ONLY

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

                // TESTING ONLY 
                case SDL_KEYDOWN: {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP: {
                            tex_sub_h = (tex_sub_h == 1) ? tex_sub_h : tex_sub_h / 2;
                            tex_sub_w = (tex_sub_w == 1) ? tex_sub_w : tex_sub_w / 2;
                            break;
                        }
                        case SDLK_DOWN: {
                            tex_sub_h = (tex_sub_h == tex_h) ? tex_sub_h : tex_sub_h * 2;
                            tex_sub_w = (tex_sub_w == tex_w) ? tex_sub_w : tex_sub_w * 2;
                            break;
                        }
                    }
                }
                // TESTING ONLY 

                default: {
                    break;
                }
            }
        } // end polling

        // draw calls
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, texture, &(SDL_Rect){.y = 0, .x = 0, .w = tex_sub_w, .h = tex_sub_h} , NULL); // testing
        SDL_RenderPresent(rend);
        // draw calls

        fps_sync();
    } // end program

    sdl_full_shutdown(window, 0);
}