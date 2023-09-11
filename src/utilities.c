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

// DISPLAY TREE =============================================================

int _dth(texture_node* node) {
    if (!node)
        return 0;

    int total = 0;
    for (int i = 0; i < node->num_children; i++) {
        total += _dth(&node->children[i]) + 1;
    }

    return total;
}
int dt_total_height(texture_node* node) {
    return _dth(node) + 1;
}

int dt_max_width(texture_node* node) {
    if (!node)
        return 0;

    int max_width = 0;
    for (int i = 0, child_height; i < node->num_children; i++) {
        child_height = dt_max_width(&node->children[i]);
        max_width = max(child_height, max_width);
    }

    for (int i = 0; i < node->num_config; i++) 
        if (node->config[i].config_type == CT_title)
            return strlen(node->config[i].title) + 1;

    return 1;
}

int dt_render_content(texture_node* node, int line, int indent, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color) {
    if (!node)
        return 0;

    int title_index;
    for (int i = 0; i < node->num_config; i++) {
        if (node->config[i].config_type == CT_title) {
            title_index = i;
            break;
        }
    }

    SDL_Surface* text_surface = TTF_RenderText_Solid(*font, node->config[title_index].title, *color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(*rend, text_surface); SDL_FreeSurface(text_surface);
    SDL_Rect dest = {.x = startx + indent*DT_INDENT_PIX_WIDTH, .y = starty + line*text_surface->h,  .w = text_surface->w, .h = text_surface->h};  
    SDL_RenderCopy(*rend, text_texture, NULL, &dest); SDL_DestroyTexture(text_texture);

    for (int i = 0, child_line; i < node->num_children; i++) {
        child_line = dt_render_content(&node->children[i], ++line, indent + 1, startx, starty, rend, font, color);
        line = max(line, child_line);
    }

    return line;
}

void dt_render_background(texture_node* node, int startx, int starty, SDL_Renderer** rend, TTF_Font** font, SDL_Color* color) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(*font, " ", *color);
    int bg_width = dt_max_width(node)*text_surface->w;
    int bg_height = dt_total_height(node)*text_surface->h + 4;
    SDL_Rect dest = {.x = startx, .y = starty, .w = bg_width, .h = bg_height};

    SDL_Surface* background_surface = SDL_CreateRGBSurfaceWithFormat(SDL_SWSURFACE, bg_width, bg_height, 32, SDL_PIXELFORMAT_RGBA32); SDL_FreeSurface(text_surface);
    SDL_FillRect(background_surface, NULL, SDL_MapRGBA(background_surface->format, color->r, color->g, color->b, color->a)); 
    SDL_Texture* background_texture = SDL_CreateTextureFromSurface(*rend, background_surface); SDL_FreeSurface(background_surface);
    SDL_RenderCopy(*rend, background_texture, NULL, &dest); SDL_DestroyTexture(background_texture);
}

