#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "cc.h"
#include "physics.h"

struct integrator_state {
    struct pe_vector *positions;
    struct pe_vector *velocities;
};

int integrator_init(const pe_loop_cb_t loop_cb, void *arg) HIDDEN;
int integrator_fini(void) HIDDEN;
int integrator_add_bodies(const struct pe_body *bodies, size_t body_count) HIDDEN;
int integrator_add_forces(const struct pe_vector *forces, size_t force_count) HIDDEN;
void integrate(struct integrator_state *s, float dt) HIDDEN;
int integrator_loop(void) HIDDEN;
int integrator_abort(void) HIDDEN;

#endif  /* INTEGRATOR_H */
