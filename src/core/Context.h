#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "assets/FontManager.h"
#include "assets/TextureManager.h"
#include "utils/StateMachine.h"

struct Settings {
    float musicVolume = 0.5f;
    float sfxVolume = 0.5f;
};

struct Context {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<TextureManager> textureManager;
    StateMachine* stateMachine = nullptr;
    Settings settings;
    bool shouldExit = false;
};
