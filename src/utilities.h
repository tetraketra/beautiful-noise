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



typedef enum TC_CONFIG_KEYS {
    __CK_NONE,
    CK_IS_GROUP,     // groups represent a composite generative step, such as "rand noise on red, smooth noise on green, group_combine_mode is additive"
    CK_GROUP_BLEND_MODE,
    __END_CK_GROUP,
    CK_IS_MODIFIER,  // modifiers affect layers below them and at least as indented as them in the tree 
    CK_MODIFIER_TYPE,
    __END_CK_MODIFIER,
    CK_IS_GENERATOR, // generators produce as base noise texture 
    CK_GENERATOR_TYPE,
    __END_CONFIG_KEYS
} TC_CONFIG_KEYS;

enum TC_GROUP_BLEND_MODE {
    GBM_ADDITIVE,
    GBM_MULTIPLICATIVE,
    __END_GROUP_BLEND_MODE
} TC_GROUP_BLEND_MODE;

enum TC_MODIFIER_TYPE {
    MT_BLUR_SHARPEN,
    MT_CONTRAST,
    MT_SATURATION,
    MT_BRIGHTNESS,
    MT_INVERTION,
    MT_ROTATION,
    MT_TURBULENCE,
    __END_MODIFIER_TYPES
} TC_MODIFIER_TYPE;

enum TC_GENERATOR_TYPE {
    GT_RAND,
    GT_SMOOTH_RAND,
    GT_XOR,
    GT_SINE_DIAGONAL,   // sin(x + y)
    GT_SINE_HORIZONTAL, // sin(x)
    GT_SINE_CIRCLULAR,  // texture_side_length * sin(sqrt(x*x + y*y))
    GT_SINE_LATTICE,    // sin(x) + sin(y)
    GT_SIMPLEX,         // better perlin
    GT_VORONOI,
    __END_GENERATOR_TYPE
} TC_GENERATOR_TYPE;

typedef struct tree_config {
    TC_CONFIG_KEYS key;
    int value;
} key_value;


typedef struct dt_tree_node dt_tree_node;
typedef struct dt_tree_node {
    char                  title[DT_MAX_TITLE_LEN];
    key_value             config[DT_MAX_CONFIG_LEN];                   
    int                   num_children;
    struct dt_tree_node** children;
} dt_tree_node;

extern clock_t start_time, end_time;
extern int FPS, FRAME_TIME_MICROSECONDS;

void init_fps_sync(int fps);
void fps_sync(void);
void log_error(const char* message, const char* err);
uint32_t compose_pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
int dt_total_height(dt_tree_node* node);
int dt_max_width(dt_tree_node* node);
int dt_render_content(dt_tree_node* node, int line, int indent, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color);
void dt_render_background(dt_tree_node* node, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color);

#endif