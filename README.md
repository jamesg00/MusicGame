# Rhythm Game Port (SDL3)

This is a port of the Rhythm Game from Pygame to C++ using SDL3.

## Prerequisites

- C++17 compatible compiler
- CMake 3.14 or later
- Internet access (for fetching SDL3 and dependencies)

## Build Instructions

1.  Create a build directory:
    ```bash
    mkdir build
    cd build
    ```

2.  Configure the project:
    ```bash
    cmake ..
    ```

3.  Build:
    ```bash
    cmake --build .
    ```

4.  Run:
    ```bash
    ./RhythmGame
    ```

## Assets

Place assets in the `assets/` directory at the project root. They will be copied to the build directory.
