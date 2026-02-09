#include "GameState.h"
#include "MenuState.h"
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

GameState::GameState(Context* context) : mContext(context) {}

GameState::~GameState() {}

void GameState::Enter() {
    std::cout << "Entering Game State" << std::endl;
}

void GameState::Exit() {
    std::cout << "Exiting Game State" << std::endl;
}

void GameState::Update(double dt) {}

void GameState::Render() {
    if (!mContext || !mContext->renderer) return;

    TTF_Font* font = mContext->fontManager->Load("title", "assets/upheavtt.ttf", 64);
    if (font) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Start", 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {50, 250, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }
}

void GameState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
             mContext->stateMachine->ChangeState(std::make_unique<MenuState>(mContext));
        }
    }
}
