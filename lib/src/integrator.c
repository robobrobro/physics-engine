/**
 * RK4 (4th order Runge-Kutta) integrator
 */

#include "integrator.h"

#include <assert.h>
#include <stddef.h>

void integrate(struct state *s, double t, float dt)
{
    assert(s != NULL);

    (void) t; // TODO needed?

    s->v += (s->F / s->m) * dt;
    s->x += s->v * dt;
}
