struct state
{
    float x;    // position
    float v;    // velocity
    float F;    // force
    float m;    // mass
};

void integrate(struct state *s, double t, float dt);
