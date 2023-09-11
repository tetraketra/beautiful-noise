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

int main(int argc, char *argv[]) {
    // set up directory handling
    char srcdir[PATH_MAX];
    strncpy(srcdir, argv[0], sizeof(srcdir));
    dirname(srcdir);
    strncat(srcdir, "/../src", sizeof(srcdir) - 1);

    // set up sdl
    SDL_Window* window = NULL;
    SDL_Renderer* rend = NULL;
    TTF_Font*     font = NULL;
    sdl_init(&window, &rend, &font, srcdir, "Beautiful Noise");
    TTF_SetFontHinting(font, TTF_HINTING_MONO);
    
    // BASE STATE TESTING
        texture_node testing_node_info = {
            .node_type = NT_B_additive, 
            .num_children = 1, .num_config = 3,
        };
        config_pair testing_node_config[3] = {
            (config_pair) {.type = CT_alpha, .value = (config_value) {.alpha = 2} },
            (config_pair) {.type = CT_blue, .value = (config_value) {.blue = 10} },
            (config_pair) {.type = CT_title, .value = (config_value) {.title = "testing"} },
        };
        texture_node* testing_root_node = tn_init(&testing_node_info, testing_node_config);
        
        texture_node testing_noise = {
            .node_type = NT_G_rand,
            .num_children = 2, .num_config = 1,
        };
        config_pair testing_noise_config[2] = {
            (config_pair) {.type = CT_seed, .value = (config_value) {.seed = 123} },
        };
        texture_node* testing_noise_node = tn_init(&testing_noise, testing_noise_config);

        texture_node testing_solid = {
            .node_type = NT_G_solid,
            .num_children = 0, .num_config = 1,
        };
        config_pair testing_solid_config[1] = {
            (config_pair) {.type = CT_title, .value = (config_value) {.title = "beeeeeeeeeeeeeg"} },
        };
        texture_node* testing_solid_node = tn_init(&testing_solid, testing_solid_config);

        testing_root_node->children[0] = testing_noise_node;
        testing_noise_node->children[0] = testing_solid_node;
        testing_noise_node->children[1] = testing_solid_node;

    // BASE STATE TESTING
    
    SDL_Color       white = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
    SDL_Color          bg = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0x7F};

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

        tt_render_background(testing_root_node, 5, 5, &rend, &font, &bg);
        tt_render_content(testing_root_node, 0, 0, 10, 5, &rend, &font, &white);

        SDL_RenderPresent(rend);
        // draw calls

        fps_sync();
    } // end update loop

    sdl_full_shutdown(&window, 0);
} // end program