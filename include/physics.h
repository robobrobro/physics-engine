#ifndef PHYSICS_H
#define PHYSICS_H

#include <stddef.h>

/**
 * @brief A 2D vector
 */
struct pe_vector {
    float x;
    float y;
};

enum pe_shape {
    PE_SHAPE_ELLIPSE,
    PE_SHAPE_RECTANGLE,
};

/**
 * @brief A physics body
 */
struct pe_body {
    struct pe_vector position;  ///!< Initial position of the center of the body
    struct pe_vector size;
    enum pe_shape shape;
    float mass;                 ///!< Mass (in kg)
};

/**
 * @brief Callback function called each iteration of the physics engine loop
 * @param bodies List of bodies
 * @param body_count Count of bodies in the list
 * @param arg User argument
 */
typedef void (*pe_loop_cb_t)(const struct pe_body *bodies, size_t body_count, void *arg);

/**
 * @brief Initialize the physics engine
 * @param loop_cb Physics engine loop callback function
 * @returns 0 on success
 */
int pe_init(pe_loop_cb_t loop_cb);

/**
 * @brief Finalize the physics engine
 * @returns 0 on success
 */
int pe_fini(void);

/**
 * @brief Add a body to the physics engine
 * @param body The body to add
 * @returns 0 on success
 */
int pe_add_body(const struct pe_body *body);

/**
 * @brief Add a force to the physics engine
 * Add a constant force to the physics engine, for the lifetime of the engine
 * @param force Force to add
 * @returns 0 on success
 */
int pe_add_force(const struct pe_vector *force);

/**
 * @brief Run the physics engine
 * @returns 0 on success
 */
int pe_loop(void);

#endif  /* PHYSICS_H */
