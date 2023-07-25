#include <stdio.h>

#include "utilities.h"
#include <time.h>

int FPS;
int FRAME_TIME_MICROSECONDS;
clock_t start_time, end_time;

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

void log_error(const char* message, const char* err) {
    printf("%s Error: %s\n", message, err);
}