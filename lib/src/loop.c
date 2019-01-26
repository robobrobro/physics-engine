#include "loop.h"

#include "debug.h"
#include <string.h>
#include <time.h>

#define dt 0.01

static double last_time = 0;
static double accumulator = 0;

static double hires_time_in_seconds(void);

void loop(struct integrator_state *current, struct integrator_state *previous, struct pe_body *bodies, size_t body_count)
{
    double frame_time;
    double now;
    double alpha;
    size_t idx;

    assert(current != NULL);
    assert(previous != NULL);
    assert(bodies != NULL);

    if (last_time == 0)
        last_time = hires_time_in_seconds();

    now = hires_time_in_seconds();
    frame_time = now - last_time;

    if (frame_time > 0.25)
        frame_time = 0.25;

    last_time = now;

    accumulator += frame_time;

    while (accumulator >= dt) {
        memcpy(previous->positions, current->positions, sizeof(*previous->positions) * body_count);
        memcpy(previous->velocities, current->velocities, sizeof(*previous->velocities) * body_count);
        integrate(current, dt);
        accumulator -= dt;
    }

    alpha = accumulator / dt;

    for (idx = 0; idx < body_count; ++idx) {
        struct pe_body *body = &bodies[idx];
        body->position.x = current->positions[idx].x * alpha + previous->positions[idx].x * (1.0 - alpha);
        body->position.y = current->positions[idx].y * alpha + previous->positions[idx].y * (1.0 - alpha);
    }
}

static double hires_time_in_seconds(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec / 1000000000.0;
}
