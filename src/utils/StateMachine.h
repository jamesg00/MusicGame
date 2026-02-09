#pragma once
#include "IState.h"
#include <memory>
#include <SDL3/SDL.h>

class StateMachine {
public:
    void ChangeState(std::unique_ptr<IState> newState);
    void Update(double dt);
    void Render();
    void HandleEvent(const SDL_Event& event);

private:
    std::unique_ptr<IState> mCurrentState;
};
