#include "App.h"
#include "Config.h"
#include <SDL3/SDL.h>
#include <iostream>

App::App() : mContext(std::make_unique<Context>()), mIsRunning(false) {}

App::~App() {
    Cleanup();
}

bool App::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
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
        }

        // Fixed timestep update
        while (accumulator >= Config::FrameDuration) {
            // Update(Config::FrameDuration);
            accumulator -= Config::FrameDuration;
        }

        // Render
        SDL_SetRenderDrawColor(mContext->renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(mContext->renderer);

        // Draw a simple rect to show it's working
        SDL_SetRenderDrawColor(mContext->renderer, 255, 0, 0, 255); // Red rect
        SDL_FRect rect = {100.0f, 100.0f, 50.0f, 50.0f};
        SDL_RenderFillRect(mContext->renderer, &rect);

        SDL_RenderPresent(mContext->renderer);

        // Simple delay to prevent 100% CPU usage if vsync is off or fast
        SDL_Delay(1);
    }
}

void App::Cleanup() {
    if (mContext->renderer) {
        SDL_DestroyRenderer(mContext->renderer);
        mContext->renderer = nullptr;
    }
    if (mContext->window) {
        SDL_DestroyWindow(mContext->window);
        mContext->window = nullptr;
    }
    SDL_Quit();
}
