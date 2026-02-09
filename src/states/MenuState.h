#pragma once
#include "utils/IState.h"
#include "core/Context.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class MenuState : public IState {
public:
    MenuState(Context* context);
    ~MenuState();

    void Enter() override;
    void Exit() override;
    void Update(double dt) override;
    void Render() override;
    void HandleEvent(const SDL_Event& event) override;

private:
    Context* mContext;
};
