# physics-engine

A 2D physics engine implemented in C.

## Prerequisites

- [Doxygen](http://www.doxygen.nl/) - documentation generation tool
- [SCons](https://scons.org/) - software construction tool (e.g. GNU Make)

The example program has additional prerequisites:

- [GLFW](https://www.glfw.org/) - OpenGL library

### Environment

To build the example program, the following environment variables must be defined.

- `GLFW_PATH` - Directory containing GLFW source

## Building

This project is built with [scons](https://scons.org/). To build everything, run `scons`. The library and example program can be built separately by running `scons lib` and `scons example`, respectively.
