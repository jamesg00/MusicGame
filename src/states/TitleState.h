#pragma once
#include "utils/IState.h"
#include "core/Context.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class TitleState : public IState {
public:
    TitleState(Context* context);
    ~TitleState();

    void Enter() override;
    void Exit() override;
    void Update(double dt) override;
    void Render() override;
    void HandleEvent(const SDL_Event& event) override;

private:
    Context* mContext;
};
