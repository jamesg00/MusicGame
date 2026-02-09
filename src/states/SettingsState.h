#pragma once
#include "utils/IState.h"
#include "core/Context.h"
#include <SDL3_ttf/SDL_ttf.h>

class SettingsState : public IState {
public:
    SettingsState(Context* context);
    ~SettingsState();

    void Enter() override;
    void Exit() override;
    void Update(double dt) override;
    void Render() override;
    void HandleEvent(const SDL_Event& event) override;

private:
    Context* mContext;
    SDL_FRect mMusicSliderRect;
    SDL_FRect mSfxSliderRect;
    SDL_FRect mBackButtonRect;
    bool mDraggingMusic = false;
    bool mDraggingSfx = false;

    void RenderText(const std::string& text, float x, float y, int size, SDL_Color color);
};
