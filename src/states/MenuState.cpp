#include "MenuState.h"
#include "TitleState.h"

MenuState::MenuState(Context* context) : mContext(context) {}

MenuState::~MenuState() {}

void MenuState::Enter() {
    std::cout << "Entering Menu State" << std::endl;
}

void MenuState::Exit() {
    std::cout << "Exiting Menu State" << std::endl;
}

void MenuState::Update(double dt) {}

void MenuState::Render() {
    if (!mContext || !mContext->renderer) return;

    TTF_Font* font = mContext->fontManager->Load("title", "assets/upheavtt.ttf", 64);
    if (font) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Menu", 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {100, 100, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }
}

void MenuState::HandleEvent(const SDL_Event& event) {
    // Basic navigation logic for next milestone
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
             mContext->stateMachine->ChangeState(std::make_unique<TitleState>(mContext));
        }
    }
}
