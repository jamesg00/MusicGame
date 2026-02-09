#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "assets/FontManager.h"
#include "utils/StateMachine.h"

struct Context {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::unique_ptr<FontManager> fontManager;
    StateMachine* stateMachine = nullptr;
};
