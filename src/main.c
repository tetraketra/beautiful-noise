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

    // set up display tree
    dt_tree_node* root = calloc(1, sizeof(dt_tree_node));
    strcpy(root->data, "beautiful noise");
    root->num_children = 3;
    root->children = calloc(root->num_children, sizeof(dt_tree_node*));

        // ONLY FOR TESTING
        dt_tree_node* one_child = calloc(1, sizeof(dt_tree_node));
        strcpy(one_child->data, "one child");
        one_child->num_children = 1;
        one_child->children = calloc(one_child->num_children, sizeof(dt_tree_node*));

        dt_tree_node* zero_child = calloc(1, sizeof(dt_tree_node));
        strcpy(zero_child->data, "zero child");
        zero_child->num_children = 0;
        zero_child->children = calloc(zero_child->num_children, sizeof(dt_tree_node*));

        root->children[0] = zero_child;
        root->children[1] = one_child;
        root->children[2] = zero_child;
        one_child->children[0] = zero_child;
        // ONLY FOR TESTING
    
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

        dt_render_background(root, 5, 5, &rend, &font, &bg);
        dt_render_content(root, 0, 0, 10, 5, &rend, &font, &white);

        SDL_RenderPresent(rend);
        // draw calls

        fps_sync();
    } // end update loop

    sdl_full_shutdown(&window, 0);
} // end program