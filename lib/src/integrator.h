struct state
{
    float x;    // position
    float v;    // velocity
};

void integrate(struct state *s, double t, float dt);
