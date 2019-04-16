/**
 * Semi-implicit Euler integrator
 */

#include "integrator.h"

#include "debug.h"
#include "loop.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool _looping = false;

static pe_loop_cb_t _loop_cb = NULL;
static void *_loop_cb_arg = NULL;

static struct integrator_state _current_state = {};
static struct integrator_state _previous_state = {};

static struct pe_body *_bodies = NULL;
static size_t _body_count = 0;

static struct pe_vector _force = {};

int integrator_init(const pe_loop_cb_t loop_cb, void *arg)
{
    if (!loop_cb)
        return (errno = EINVAL);

    _loop_cb = loop_cb;
    _loop_cb_arg = arg;

    return 0;
}

int integrator_fini(void)
{
    _looping = false;

    _loop_cb = NULL;
    _loop_cb_arg = NULL;

    free(_current_state.positions);
    free(_current_state.velocities);
    _current_state = (typeof(_current_state)) {};

    free(_previous_state.positions);
    free(_previous_state.velocities);
    _previous_state = (typeof(_previous_state)) {};

    free(_bodies);
    _bodies = NULL;
    _body_count = 0;

    _force = (typeof(_force)) {};

    return 0;
}

int integrator_add_bodies(const struct pe_body *bodies, size_t body_count)
{
    size_t new_body_count = _body_count + body_count;
    size_t idx;

    if (!bodies)
        return (errno = EINVAL);

    _bodies = realloc(_bodies, sizeof(*_bodies) * new_body_count);
    if (!_bodies)
        return errno;

    _current_state.positions = realloc(_current_state.positions, sizeof(*_current_state.positions) * new_body_count);
    if (!_current_state.positions)
        return errno;

    _current_state.velocities = realloc(_current_state.velocities, sizeof(*_current_state.velocities) * new_body_count);
    if (!_current_state.velocities)
        return errno;

    _previous_state.positions = realloc(_previous_state.positions, sizeof(*_previous_state.positions) * new_body_count);
    if (!_previous_state.positions)
        return errno;

    _previous_state.velocities = realloc(_previous_state.velocities, sizeof(*_previous_state.velocities) * new_body_count);
    if (!_previous_state.velocities)
        return errno;

    memcpy(&_bodies[_body_count], bodies, sizeof(*bodies) * body_count);

    for (idx = _body_count; idx < new_body_count; ++idx) {
        _current_state.positions[idx] = _bodies[idx].position;
        _previous_state.positions[idx] = _bodies[idx].position;
        _current_state.velocities[idx] = (typeof(*_current_state.velocities)) {};
        _previous_state.velocities[idx] = (typeof(*_previous_state.velocities)) {};
    }

    _body_count = new_body_count;

    return 0;
}

int integrator_add_forces(const struct pe_vector *forces, size_t force_count)
{
    size_t idx;

    if (!forces)
        return (errno = EINVAL);

    for (idx = 0; idx < force_count; ++idx) {
        _force.x += forces[idx].x;
        _force.y += forces[idx].y;
    }

    return 0;
}

void integrate(struct integrator_state *s, float dt)
{
    size_t idx;

    assert(s != NULL);

    for (idx = 0; idx < _body_count; ++idx) {
        s->velocities[idx].x += (_force.x / _bodies[idx].mass) * dt;
        s->velocities[idx].y += (_force.y / _bodies[idx].mass) * dt;
        s->positions[idx].x += s->velocities[idx].x * dt;
        s->positions[idx].y += s->velocities[idx].y * dt;
    }
}

int integrator_loop(void)
{
    _looping = true;

    if (!_loop_cb)
        return (errno = EINVAL);

    while (_looping) {
        loop(&_current_state, &_previous_state, _bodies, _body_count);
        _loop_cb(_bodies, _body_count, _loop_cb_arg);
    }

    return 0;
}

int integrator_abort(void)
{
    _looping = false;
    return 0;
}
