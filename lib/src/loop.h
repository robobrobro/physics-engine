#ifndef LOOP_H
#define LOOP_H

#include "integrator.h"

typedef void (*loop_cb_t)(const struct state *s, void *arg);

void loop(struct state *current, struct state *previous, loop_cb_t cb, void *arg);

#endif  /* LOOP_H */
