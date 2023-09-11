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

#define nullptr (void*)0

#define DT_MAX_TITLE_LEN 32
#define DT_MAX_CONFIG_LEN 32
#define DT_INDENT_PIX_WIDTH 10

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

enum special_values {
    __OFFSET = 1000,
    TN_NO_CONFIG_INDEX_FOUND,
};

typedef enum config_type {
    CT_title,
    CT_seed,
    CT_red,
    CT_green,
    CT_blue,
    CT_alpha,
    CT_turbulate_factor,
    CT_turbulate_alphafalloff,
} config_type;
typedef union config_value {
    char title[20];
    int seed;
    int red;
    int green;
    int blue;
    int alpha;
    int turbulate_factor;
    double turbulate_alphafalloff;
} config_value;
typedef struct config_pair {
    int type;
    config_value value;
} config_pair;

typedef enum node_type {
    _NT_NONE,
    NT_B_additive,
    NT_B_multiplicative,
    _NT_END_BLENDERS,
    NT_M_turbulate,
    NT_M_invert,
    _NT_END_MODIFIERS,
    NT_G_solid,
    NT_G_rand,
    NT_G_smooth,
    NT_G_xor,
    _NT_END_GENERATORSS,
} node_type;
typedef struct texture_node texture_node;
typedef struct texture_node {
    node_type node_type;
    int num_config;
    int num_children;
    texture_node** children;    
    config_pair* config;
} texture_node;

extern clock_t start_time, end_time;
extern int FPS, FRAME_TIME_MICROSECONDS;

void init_fps_sync(int fps);
void fps_sync(void);
void log_error(const char* message, const char* err);
uint32_t compose_pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
int tt_total_height(texture_node* node);
int tt_max_width(texture_node* node);
int tt_render_content(texture_node* node, int line, int indent, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color);
void tt_render_background(texture_node* node, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color);
int _th(texture_node* node);
texture_node* tn_init(texture_node* info_node, config_pair config_list[]);
int tn_get_config_index(texture_node* node, int config_type);

#endif