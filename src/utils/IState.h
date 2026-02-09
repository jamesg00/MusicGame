#pragma once
#include <SDL3/SDL.h>

class IState {
public:
    virtual ~IState() = default;

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update(double dt) = 0;
    virtual void Render() = 0;
    virtual void HandleEvent(const SDL_Event& event) = 0;
};
