#include "MenuState.h"
#include "TitleState.h"
#include "GameState.h"
#include "SettingsState.h"
#include <SDL3/SDL.h>

MenuState::MenuState(Context* context) : mContext(context) {
    mOptions = {"Play Level", "Settings", "Quit"};
}

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

    // Draw "Menu" Title
    TTF_Font* titleFont = mContext->fontManager->Load("title", "assets/upheavtt.ttf", 64);
    if (titleFont) {
        SDL_Surface* surface = TTF_RenderText_Solid(titleFont, "Menu", 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {120, 50, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }

    // Draw Options
    TTF_Font* optionFont = mContext->fontManager->Load("default", "assets/upheavtt.ttf", 36);
    if (optionFont) {
        float startY = 200;
        for (size_t i = 0; i < mOptions.size(); ++i) {
            SDL_Color color = (i == mSelectedOption) ? SDL_Color{255, 255, 0, 255} : SDL_Color{255, 255, 255, 255};
            SDL_Surface* surface = TTF_RenderText_Solid(optionFont, mOptions[i].c_str(), 0, color);
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
                if (texture) {
                    float x = 200 - surface->w / 2; // Center roughly
                    SDL_FRect dst = {x, startY + i * 50, (float)surface->w, (float)surface->h};
                    SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                    SDL_DestroyTexture(texture);
                }
                SDL_DestroySurface(surface);
            }
        }
    }

    // Placeholder for Trail Dropdown
    TTF_Font* smallFont = mContext->fontManager->Load("default", "assets/upheavtt.ttf", 20);
    if (smallFont) {
        SDL_Surface* surface = TTF_RenderText_Solid(smallFont, "Trail: [Default] v", 0, {200, 200, 200, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {10, 550, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }
}

void MenuState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
             mContext->stateMachine->ChangeState(std::make_unique<TitleState>(mContext));
        } else if (event.key.key == SDLK_UP) {
            mSelectedOption--;
            if (mSelectedOption < 0) mSelectedOption = mOptions.size() - 1;
        } else if (event.key.key == SDLK_DOWN) {
            mSelectedOption++;
            if (mSelectedOption >= mOptions.size()) mSelectedOption = 0;
        } else if (event.key.key == SDLK_RETURN) {
            if (mSelectedOption == 0) {
                mContext->stateMachine->ChangeState(std::make_unique<GameState>(mContext));
            } else if (mSelectedOption == 1) {
                mContext->stateMachine->ChangeState(std::make_unique<SettingsState>(mContext));
            } else if (mSelectedOption == 2) {
                mContext->shouldExit = true;
            }
        }
    }
    // Mouse Interaction
    else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        float mx = event.motion.x;
        float my = event.motion.y;
        float startY = 200;
        for (size_t i = 0; i < mOptions.size(); ++i) {
            // Very rough hit detection based on fixed layout
            if (my >= startY + i * 50 && my < startY + i * 50 + 40 && mx > 100 && mx < 300) {
                mSelectedOption = i;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
             float mx = event.button.x;
             float my = event.button.y;
             float startY = 200;
             for (size_t i = 0; i < mOptions.size(); ++i) {
                if (my >= startY + i * 50 && my < startY + i * 50 + 40 && mx > 100 && mx < 300) {
                    if (i == 0) {
                        mContext->stateMachine->ChangeState(std::make_unique<GameState>(mContext));
                        return; // State changed, this object is destroyed
                    } else if (i == 1) {
                        mContext->stateMachine->ChangeState(std::make_unique<SettingsState>(mContext));
                        return; // State changed, this object is destroyed
                    } else if (i == 2) {
                        mContext->shouldExit = true;
                    }
                }
             }
        }
    }
}
