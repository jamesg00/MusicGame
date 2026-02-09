#pragma once
#include "utils/IState.h"
#include "core/Context.h"

class GameState : public IState {
public:
    GameState(Context* context);
    ~GameState();

    void Enter() override;
    void Exit() override;
    void Update(double dt) override;
    void Render() override;
    void HandleEvent(const SDL_Event& event) override;

private:
    Context* mContext;
};
