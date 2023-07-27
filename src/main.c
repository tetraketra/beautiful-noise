#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <string.h>
#include <libgen.h>

#include "sdl_utils.h"
#include "utilities.h"

#define TEXT_OUTLINE_SIZE 2

int main(int argc, char *argv[]) {
    char srcdir[PATH_MAX];
    strncpy(srcdir, argv[0], sizeof(srcdir));
    dirname(srcdir);
    strncat(srcdir, "/../src", sizeof(srcdir) - 1);

    SDL_Window* window = NULL;
    SDL_Renderer* rend = NULL;
    TTF_Font*     font = NULL;
    sdl_init(&window, &rend, &font, srcdir, "Beautiful Noise");
    TTF_SetFontHinting(font, TTF_HINTING_MONO);

    
    SDL_Color       white = {0XFF, 0XFF, 0XFF, 0xFF};
    SDL_Color          bg = {0X00, 0X00, 0X00, 0xFF};
    SDL_Surface*   s_text = TTF_RenderText_Solid(font, "example text", white); 
    SDL_FillRect(s_text, 0, SDL_MapRGBA(s_text->format, 0, 0, 0, 0xFF));
    SDL_Texture*   t_text = SDL_CreateTextureFromSurface(rend, s_text);
    SDL_Rect         dest = {TEXT_OUTLINE_SIZE, TEXT_OUTLINE_SIZE, s_text->w, s_text->h};    

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

        SDL_RenderCopy(rend, t_text, NULL, &dest);

        SDL_RenderPresent(rend);
        // draw calls

        fps_sync();
    } // end program

    sdl_full_shutdown(&window, 0);
}