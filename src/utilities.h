#include <time.h>
#include <unistd.h>

#ifndef UTILITIES_H
#define UTILITIES_H

extern clock_t start_time, end_time;
extern int FPS, FRAME_TIME_MICROSECONDS;

void init_fps_sync(int fps);
void fps_sync(void);
void log_error(const char* message, const char* err);

#endif