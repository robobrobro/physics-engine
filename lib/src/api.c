#include <errno.h>
#include "integrator.h"
#include "physics.h"

int pe_init(const pe_loop_cb_t loop_cb, void *arg)
{
    return integrator_init(loop_cb, arg);
}

int pe_fini(void)
{
    return integrator_fini();
}

int pe_add_body(const struct pe_body *body)
{
    return integrator_add_bodies(body, 1);
}

int pe_add_force(const struct pe_vector *force)
{
    return integrator_add_forces(force, 1);
}

int pe_loop(void)
{
    return integrator_loop();
}

int pe_abort(void)
{
    return integrator_abort();
}
