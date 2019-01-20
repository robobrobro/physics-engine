#include "physics.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define die(fmt, ...) { \
    fprintf(stderr, "ERROR (" fmt "): %s\n", ##__VA_ARGS__, strerror(errno)); \
    exit(1); \
}

static void on_loop(const struct pe_body *bodies, size_t body_count, void *arg)
{
    size_t idx;

    (void) arg;

    for (idx = 0; idx < body_count; ++idx) {
        printf("%zu: p:(%.2f, %.2f) s:(%.2f, %.2f) m:%.2f\n", idx + 1,
            bodies[idx].position.x, bodies[idx].position.y,
            bodies[idx].size.x, bodies[idx].size.y,
            bodies[idx].mass
        );
    }
}

static void on_exit(void)
{
    (void) pe_fini();
}

static void quit(int sig)
{
    (void) sig;
    (void) pe_abort();
}

int main(void)
{
    struct pe_body body = {
        .size = { 5, 5 },
        .shape = PE_SHAPE_RECTANGLE,
        .mass = 1,
    };

    struct pe_vector gravity = { -10, 0 };

    if (atexit(on_exit))
        die("adding exit handler");

    if (signal(SIGINT, quit))
        die("adding SIGINT handler");

    if (signal(SIGALRM, quit))
        die("adding SIGALRM handler");

    if (pe_init(on_loop, NULL))
        die("physics engine initialization");

    if (pe_add_force(&gravity))
        die("adding gravity to physics engine");

    if (pe_add_body(&body))
        die("adding body to physics engine");

    (void) alarm(10);

    if (pe_loop())
        die("physics engine loop");

    return 0;
}
