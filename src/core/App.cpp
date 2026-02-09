#include "App.h"
#include "Config.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

// States
#include "states/TitleState.h"

App::App() : mContext(std::make_unique<Context>()), mIsRunning(false) {}

App::~App() {
    Cleanup();
}

bool App::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!TTF_Init()) {
        std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    mContext->window = SDL_CreateWindow("Rhythm Game", Config::ScreenWidth, Config::ScreenHeight, 0);
    if (!mContext->window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }

    mContext->renderer = SDL_CreateRenderer(mContext->window, NULL);
    if (!mContext->renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize Systems
    mContext->fontManager = std::make_unique<FontManager>();
    mContext->stateMachine = &mStateMachine;

    // Load Default Font
    // Using 24 as a base size, similar to Python code
    if (!mContext->fontManager->Load("default", "assets/upheavtt.ttf", 24)) {
        std::cerr << "Failed to load default font assets/upheavtt.ttf" << std::endl;
        // Proceeding might crash if states rely on it, but we log it.
    }
    // Load larger font for title
    if (!mContext->fontManager->Load("title", "assets/upheavtt.ttf", 64)) {
         std::cerr << "Failed to load title font assets/upheavtt.ttf" << std::endl;
    }


    // Push Initial State
    mStateMachine.ChangeState(std::make_unique<TitleState>(mContext.get()));

    mIsRunning = true;
    return true;
}

void App::Run() {
    if (!mIsRunning) return;

    double accumulator = 0.0;
    Uint64 lastTime = SDL_GetTicks();

    while (mIsRunning) {
        Uint64 currentTime = SDL_GetTicks();
        double frameTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        accumulator += frameTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                mIsRunning = false;
            }
            mStateMachine.HandleEvent(event);
        }

        // Fixed timestep update
        while (accumulator >= Config::FrameDuration) {
            mStateMachine.Update(Config::FrameDuration);
            accumulator -= Config::FrameDuration;
        }

        // Render
        SDL_SetRenderDrawColor(mContext->renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(mContext->renderer);

        mStateMachine.Render();

        SDL_RenderPresent(mContext->renderer);

        SDL_Delay(1);
    }
}

void App::Cleanup() {
    mContext->fontManager.reset(); // Destroy fonts before TTF_Quit

    if (mContext->renderer) {
        SDL_DestroyRenderer(mContext->renderer);
        mContext->renderer = nullptr;
    }
    if (mContext->window) {
        SDL_DestroyWindow(mContext->window);
        mContext->window = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
}
