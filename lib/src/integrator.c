/**
 * Semi-implicit Euler integrator
 */

#include "integrator.h"

#include <assert.h>
#include <stddef.h>

void integrate(struct state *s, float dt)
{
    assert(s != NULL);

    s->vx += (s->Fx / s->m) * dt;
    s->vy += (s->Fy / s->m) * dt;
    s->x += s->vx * dt;
    s->y += s->vy * dt;
}
