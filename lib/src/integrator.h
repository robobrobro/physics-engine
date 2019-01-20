#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "physics.h"

struct integrator_state {
    struct pe_vector *positions;
    struct pe_vector *velocities;
};

int integrator_init(const pe_loop_cb_t loop_cb, void *arg) __attribute((visibility("hidden")));
int integrator_fini(void) __attribute((visibility("hidden")));
int integrator_add_bodies(const struct pe_body *bodies, size_t body_count) __attribute((visibility("hidden")));
int integrator_add_forces(const struct pe_vector *forces, size_t force_count) __attribute((visibility("hidden")));
void integrate(struct integrator_state *s, float dt) __attribute((visibility("hidden")));
int integrator_loop(void) __attribute((visibility("hidden")));
int integrator_abort(void) __attribute((visibility("hidden")));

#endif  /* INTEGRATOR_H */
