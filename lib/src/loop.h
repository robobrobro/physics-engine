#ifndef LOOP_H
#define LOOP_H

#include "integrator.h"

void loop(struct integrator_state *current, struct integrator_state *previous, struct pe_body *bodies, size_t body_count) __attribute((visibility("hidden")));

#endif  /* LOOP_H */
