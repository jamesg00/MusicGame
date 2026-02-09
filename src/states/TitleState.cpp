#include "TitleState.h"
#include "MenuState.h"

TitleState::TitleState(Context* context) : mContext(context) {}

TitleState::~TitleState() {}

void TitleState::Enter() {
    std::cout << "Entering Title State" << std::endl;
}

void TitleState::Exit() {
    std::cout << "Exiting Title State" << std::endl;
}

void TitleState::Update(double dt) {
    // Animation logic
}

void TitleState::Render() {
    if (!mContext || !mContext->renderer) return;

    TTF_Font* font = mContext->fontManager->Load("title", "assets/upheavtt.ttf", 64);
    if (font) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Rhythm Game", 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {50, 200, (float)surface->w, (float)surface->h}; // Simplified positioning
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }

    TTF_Font* smallFont = mContext->fontManager->Load("default", "assets/upheavtt.ttf", 24);
    if (smallFont) {
        SDL_Surface* surface = TTF_RenderText_Solid(smallFont, "Press Space", 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {100, 400, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }
}

void TitleState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_SPACE) {
            mContext->stateMachine->ChangeState(std::make_unique<MenuState>(mContext));
        }
    }
}
