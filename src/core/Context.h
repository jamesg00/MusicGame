#pragma once
#include <SDL3/SDL.h>

struct Context {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
