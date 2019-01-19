#ifndef INTEGRATOR_H
#define INTEGRATOR_H

struct state
{
    float x, y;     // position
    float vx, vy;   // velocity
    float Fx, Fy;   // force
    float m;        // mass
};

void integrate(struct state *s, float dt) __attribute((visibility("hidden")));

#endif  /* INTEGRATOR_H */
