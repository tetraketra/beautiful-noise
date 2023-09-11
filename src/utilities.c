#include "utilities.h"

int FPS;
int FRAME_TIME_MICROSECONDS;
clock_t start_time, end_time;

// FPS SYNC ==================================================================

void init_fps_sync(int fps) {
    FPS = fps;
    FRAME_TIME_MICROSECONDS = 1000000 / FPS;
}

void fps_sync(void) {
    end_time = clock();
    long sleep_time_microseconds = FRAME_TIME_MICROSECONDS - (end_time - start_time);
    if (sleep_time_microseconds > 0)
        nanosleep((struct timespec[]){{0, 300L}},NULL);
}

// ERROR HANDLING ===========================================================

void log_error(const char* message, const char* err) {
    printf("%s Error: %s\n", message, err);
}

// TEXTURE NODE =============================================================

texture_node* tn_init(texture_node* info_node, config_pair config_list[]) {
    texture_node* malloced_node = malloc(sizeof(texture_node));
    
    malloced_node->node_type    = info_node->node_type;
    malloced_node->num_children = info_node->num_children;
    malloced_node->num_config   = info_node->num_config;
    malloced_node->children     = calloc(info_node->num_children, sizeof(texture_node));
    malloced_node->config       = calloc(info_node->num_config,   sizeof(config_pair) );
    
    if (config_list)
        memcpy(malloced_node->config, config_list, info_node->num_config * sizeof(config_pair));
    
    return malloced_node;
}

int tn_get_config_index(texture_node* node, int config_type) {
    for (int i = 0; i < node->num_config; i++)
        if (node->config[i].type == config_type) 
            return i;

    return TN_NO_CONFIG_INDEX_FOUND;
}

char* tn_get_title_safe(texture_node* node) {
    for (int i = 0; i < node->num_config; i++)
        if (node->config[i].type == CT_title) 
            return node->config[i].value.title;
    
    switch (node->node_type) {
        case NT_G_rand:                     return "g: random noise";
        case NT_G_smooth:                   return "g: smooth noise";
        case NT_G_solid:                    return "g: solid color";
        case NT_G_xor:                      return "g: xor pattern";
        case NT_B_additive:                 return "g: add blend";
        case NT_B_multiplicative:           return "g: mult blend";
        case NT_M_invert:                   return "m: invert";
        case NT_M_turbulate:                return "m: turbulate";
        default:                            return "DEFAULT TITLE";
    }
}

// TEXTURE TREE =============================================================

int tt_total_height(texture_node* node) { return _th(node) + 1; }
int _th(texture_node* node) {
    if (!node)
        return 0;

    int total = 0;
    for (int i = 0; i < node->num_children; i++) {
        total += _th(node->children[i]) + 1;
    }

    return total;
}


int tt_max_width(texture_node* node) {
    if (!node)
        return 0;

    int max_width = strlen(tn_get_title_safe(node));
    for (int i = 0; i < node->num_children; i++) {
        max_width = max(tt_max_width(node->children[i]) + 1, max_width);
    }

    return max_width;
}

int tt_render_content(texture_node* node, int line, int indent, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color) {
    if (!node)
        return 0;

    SDL_Surface* text_surface = TTF_RenderText_Solid(
        *font, 
        tn_get_title_safe(node),
        *color
    );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(
        *rend,
        text_surface
    ); 
    SDL_Rect dest = {
        .x = startx + indent*DT_INDENT_PIX_WIDTH, 
        .y = starty + line*text_surface->h,  
        .w = text_surface->w, 
        .h = text_surface->h
    };  

    SDL_RenderCopy(*rend, text_texture, NULL, &dest); 
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    for (int i = 0; i < node->num_children; i++) {
        line = max(line, tt_render_content(node->children[i], ++line, indent + 1, startx, starty, rend, font, color));
    }

    return line;
}

void tt_render_background(texture_node* node, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(*font, " ", *color);
    int bg_width  = (tt_max_width(node) + 1) * text_surface->w;
    int bg_height = tt_total_height(node) * text_surface->h + 5;
    SDL_Rect dest = {.x = startx, .y = starty, .w = bg_width, .h = bg_height};

    SDL_Surface* background_surface = SDL_CreateRGBSurfaceWithFormat(SDL_SWSURFACE, bg_width, bg_height, 32, SDL_PIXELFORMAT_RGBA32); SDL_FreeSurface(text_surface);
    SDL_FillRect(background_surface, NULL, SDL_MapRGBA(background_surface->format, color->r, color->g, color->b, color->a)); 
    SDL_Texture* background_texture = SDL_CreateTextureFromSurface(*rend, background_surface); SDL_FreeSurface(background_surface);
    SDL_RenderCopy(*rend, background_texture, NULL, &dest); SDL_DestroyTexture(background_texture);
}

