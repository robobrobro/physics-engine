/**
 * RK4 (4th order Runge-Kutta) integrator
 */

#include "integrator.h"

#include <assert.h>
#include <stddef.h>

struct derivative
{
    float dx;   // dx/dt = velocity
    float dv;   // dv/dt = acceleration
};

static float acceleration(const struct state *s, double t);
static void evaluate(const struct state *initial, double t, float dt, const struct derivative *d, struct derivative *out);

static float acceleration(const struct state *s, double t)
{
    /* TODO change from hard-coded spring damper */
    const float k = 15.f;
    const float b = 0.1f;

    assert(s != NULL);
    (void) t;

    return -k * s->x - b * s->v;
}

static void evaluate(const struct state *initial, double t, float dt, const struct derivative *d, struct derivative *out)
{
    struct state s;

    assert(initial != NULL);
    assert(d != NULL);
    assert(out != NULL);

    s = (typeof(s)) {
        .x = initial->x + d->dx * dt,
        .v = initial->v + d->dv * dt,
    };

    *out = (typeof(*out)) {
        .dx = s.v,
        .dv = acceleration(&s, t + dt),
    };
}

void integrate(struct state *s, double t, float dt)
{
    struct derivative d0 = { };
    struct derivative a, b, c, d;
    float dxdt, dvdt;

    assert(s != NULL);

    evaluate(s, t, 0.f, &d0, &a);
    evaluate(s, t, dt * 0.5f, &a, &b);
    evaluate(s, t, dt * 0.5f, &b, &c);
    evaluate(s, t, dt, &c, &d);

    dxdt = 1.f / 6.f * (a.dx + 2.f * (b.dv + c.dv) + d.dv);
    dvdt = 1.f / 6.f * (a.dv + 2.f * (b.dv + c.dv) + d.dv);

    s->x += dxdt * dt;
    s->v += dvdt * dt;
}
