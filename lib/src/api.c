#include <errno.h>
#include "physics.h"

int pe_init(pe_loop_cb_t loop_cb)
{
    (void) loop_cb;
    return 0;
}

int pe_fini(void)
{
    return 0;
}

int pe_add_body(const struct pe_body *body)
{
    (void) body;
    return 0;
}

int pe_add_force(const struct pe_vector *force)
{
    (void) force;
    return 0;
}

int pe_loop(void)
{
    return 0;
}
