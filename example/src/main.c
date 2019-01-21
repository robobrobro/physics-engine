/**
 * Silence OpenGL deprecation on macOS >= 10.14.
 * Apple wants us to use Metal, but I don't want to (yet).
 */
#if __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "physics.h"
#include <GLFW/glfw3.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define die(fmt, ...) { \
    if (errno != 0) \
        fprintf(stderr, "ERROR (" fmt "): %s\n", ##__VA_ARGS__, strerror(errno)); \
    else \
        fprintf(stderr, "ERROR (" fmt ")\n", ##__VA_ARGS__); \
    exit(1); \
}

static GLFWwindow *_window = NULL;

static void on_glfw_error(int error, const char *desc);
static void on_loop(const struct pe_body *bodies, size_t body_count, void *arg);
static void on_quit(void);
static void on_window_close(GLFWwindow *window);
static void quit(int sig);

static void on_glfw_error(int error, const char *desc)
{
    fprintf(stderr, "GLFW ERROR (%d): %s\n", error, desc);
    exit(2);
}

static void on_loop(const struct pe_body *bodies, size_t body_count, void *arg)
{
    (void) bodies;
    (void) body_count;
    (void) arg;

    glClear(GL_COLOR_BUFFER_BIT);

    /*
    size_t idx;
    for (idx = 0; idx < body_count; ++idx) {
        printf("%zu: p:(%.2f, %.2f) s:(%.2f, %.2f) m:%.2f\n", idx + 1,
            bodies[idx].position.x, bodies[idx].position.y,
            bodies[idx].size.x, bodies[idx].size.y,
            bodies[idx].mass
        );
    }
    */

    glfwSwapBuffers(_window);
    glfwPollEvents();
}

static void on_window_close(GLFWwindow *window)
{
    (void) window;
    quit(SIGINT);
}

static void on_quit(void)
{
    (void) pe_fini();
    glfwDestroyWindow(_window);
    (void) glfwTerminate();
}

static void quit(int sig)
{
    (void) sig;
    (void) pe_abort();
    glfwSetWindowShouldClose(_window, 1);
}

int main(void)
{
    struct pe_body body = {
        .size = { 5, 5 },
        .shape = PE_SHAPE_RECTANGLE,
        .mass = 1,
    };
    struct pe_vector gravity = { -10, 0 };
    int window_width, window_height;

    if (atexit(on_quit))
        die("adding exit handler");

    if (signal(SIGINT, quit))
        die("adding SIGINT handler");

    if (pe_init(on_loop, NULL))
        die("physics engine initialization");

    if (pe_add_force(&gravity))
        die("adding gravity to physics engine");

    if (pe_add_body(&body))
        die("adding body to physics engine");

    (void) glfwSetErrorCallback(on_glfw_error);

    printf("Initializing GLFW %s\n", glfwGetVersionString());

    if (!glfwInit())
        die("initializing GLFW");

    _window = glfwCreateWindow(640, 480, "physics-engine example", NULL, NULL);
    if (!_window)
        die("_window creation");

    (void) glfwSetWindowCloseCallback(_window, on_window_close);
    glfwMakeContextCurrent(_window);
    glfwGetFramebufferSize(_window, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);

    if (pe_loop())
        die("physics engine loop");

    return 0;
}
