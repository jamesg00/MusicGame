#include "SettingsState.h"
#include "MenuState.h"
#include <iostream>
#include <string>

SettingsState::SettingsState(Context* context) : mContext(context) {
    mMusicSliderRect = {50, 150, 300, 30};
    mSfxSliderRect = {50, 250, 300, 30};
    mBackButtonRect = {50, 350, 100, 40};
}

SettingsState::~SettingsState() {}

void SettingsState::Enter() {
    std::cout << "Entering Settings State" << std::endl;
}

void SettingsState::Exit() {
    std::cout << "Exiting Settings State" << std::endl;
}

void SettingsState::Update(double dt) {}

void SettingsState::Render() {
    if (!mContext || !mContext->renderer) return;

    // Title
    RenderText("Settings", 100, 50, 48, {255, 255, 255, 255});

    // Music Volume
    RenderText("Music Volume: " + std::to_string((int)(mContext->settings.musicVolume * 100)) + "%", 50, 120, 24, {255, 255, 255, 255});

    // Draw Slider Background
    SDL_SetRenderDrawColor(mContext->renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(mContext->renderer, &mMusicSliderRect);

    // Draw Slider Handle/Fill
    SDL_FRect musicFill = mMusicSliderRect;
    musicFill.w *= mContext->settings.musicVolume;
    SDL_SetRenderDrawColor(mContext->renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(mContext->renderer, &musicFill);


    // SFX Volume
    RenderText("SFX Volume: " + std::to_string((int)(mContext->settings.sfxVolume * 100)) + "%", 50, 220, 24, {255, 255, 255, 255});

    // Draw Slider Background
    SDL_SetRenderDrawColor(mContext->renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(mContext->renderer, &mSfxSliderRect);

    // Draw Slider Handle/Fill
    SDL_FRect sfxFill = mSfxSliderRect;
    sfxFill.w *= mContext->settings.sfxVolume;
    SDL_SetRenderDrawColor(mContext->renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(mContext->renderer, &sfxFill);

    // Back Button
    SDL_SetRenderDrawColor(mContext->renderer, 200, 50, 50, 255);
    SDL_RenderFillRect(mContext->renderer, &mBackButtonRect);
    RenderText("Back", 70, 355, 24, {255, 255, 255, 255});
}

void SettingsState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
             mContext->stateMachine->ChangeState(std::make_unique<MenuState>(mContext));
        }
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float x = event.button.x;
        float y = event.button.y;

        if (x >= mMusicSliderRect.x && x <= mMusicSliderRect.x + mMusicSliderRect.w &&
            y >= mMusicSliderRect.y && y <= mMusicSliderRect.y + mMusicSliderRect.h) {
            mDraggingMusic = true;
            mContext->settings.musicVolume = (x - mMusicSliderRect.x) / mMusicSliderRect.w;
        }
        else if (x >= mSfxSliderRect.x && x <= mSfxSliderRect.x + mSfxSliderRect.w &&
                 y >= mSfxSliderRect.y && y <= mSfxSliderRect.y + mSfxSliderRect.h) {
            mDraggingSfx = true;
            mContext->settings.sfxVolume = (x - mSfxSliderRect.x) / mSfxSliderRect.w;
        }
        else if (x >= mBackButtonRect.x && x <= mBackButtonRect.x + mBackButtonRect.w &&
                 y >= mBackButtonRect.y && y <= mBackButtonRect.y + mBackButtonRect.h) {
            mContext->stateMachine->ChangeState(std::make_unique<MenuState>(mContext));
        }

    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        mDraggingMusic = false;
        mDraggingSfx = false;
    } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        float x = event.motion.x;
        if (mDraggingMusic) {
             float vol = (x - mMusicSliderRect.x) / mMusicSliderRect.w;
             if (vol < 0.0f) vol = 0.0f;
             if (vol > 1.0f) vol = 1.0f;
             mContext->settings.musicVolume = vol;
        } else if (mDraggingSfx) {
             float vol = (x - mSfxSliderRect.x) / mSfxSliderRect.w;
             if (vol < 0.0f) vol = 0.0f;
             if (vol > 1.0f) vol = 1.0f;
             mContext->settings.sfxVolume = vol;
        }
    }
}

void SettingsState::RenderText(const std::string& text, float x, float y, int size, SDL_Color color) {
    TTF_Font* font = mContext->fontManager->Load("default", "assets/upheavtt.ttf", size);
    if (!font) return;

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), 0, color);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
        if (texture) {
            SDL_FRect dst = {x, y, (float)surface->w, (float)surface->h};
            SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
        }
        SDL_DestroySurface(surface);
    }
}
