#include <time.h>
#include <unistd.h>

#ifndef UTILITIES_H
#define UTILITIES_H

#define uint32 uint32_t
#define uint8  uint8_t

extern clock_t start_time, end_time;
extern int FPS, FRAME_TIME_MICROSECONDS;

void init_fps_sync(int fps);
void fps_sync(void);
void log_error(const char* message, const char* err);
uint32 compose_pixel(uint8 red, uint8 green, uint8 blue, uint8 alpha);

#endif