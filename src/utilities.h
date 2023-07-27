#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef UTILITIES_H
#define UTILITIES_H

#define uint32 uint32_t
#define uint8  uint8_t
#define DT_MAX_DATA_LEN 32
#define DT_INDENT_PIX_WIDTH 10

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct dt_tree_node dt_tree_node;
typedef struct dt_tree_node {
    char                    data[DT_MAX_DATA_LEN];
    int                     num_children;
    struct dt_tree_node**   children;
} dt_tree_node;

extern clock_t start_time, end_time;
extern int FPS, FRAME_TIME_MICROSECONDS;

void init_fps_sync(int fps);
void fps_sync(void);
void log_error(const char* message, const char* err);
uint32 compose_pixel(uint8 red, uint8 green, uint8 blue, uint8 alpha);
int dt_total_height(dt_tree_node* node);
int dt_max_width(dt_tree_node* node);
int dt_render_content(dt_tree_node* node, int line, int indent, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color);
void dt_render_background(dt_tree_node* node, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color);

#endif