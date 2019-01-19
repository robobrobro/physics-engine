#include "loop.h"

#include "debug.h"
#include <time.h>

#define dt 0.01

static double last_time = 0;
static double accumulator = 0;

static double hires_time_in_seconds(void);

void loop(struct state *current, struct state *previous, loop_cb_t cb, void *arg)
{
    struct state s;
    double frame_time;
    double now;
    double alpha;

    assert(current != NULL);
    assert(previous != NULL);
    assert(cb != NULL);

    if (last_time == 0)
        last_time = hires_time_in_seconds();

    now = hires_time_in_seconds();
    frame_time = now - last_time;

    if (frame_time > 0.25)
        frame_time = 0.25;

    last_time = now;

    accumulator += frame_time;

    while (accumulator >= dt) {
        *previous = *current;
        integrate(current, dt);
        accumulator -= dt;
    }

    alpha = accumulator / dt;

    s.x = current->x * alpha + previous->x * (1.0 - alpha);
    s.vx = current->vx * alpha + previous->vx * (1.0 - alpha);
    s.y = current->y * alpha + previous->y * (1.0 - alpha);
    s.vy = current->vy * alpha + previous->vy * (1.0 - alpha);

    cb(&s, arg);
}

static double hires_time_in_seconds(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec / 1000000000.0;
}
