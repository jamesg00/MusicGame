#include "StateMachine.h"

void StateMachine::ChangeState(std::unique_ptr<IState> newState) {
    if (mCurrentState) {
        mCurrentState->Exit();
    }
    mCurrentState = std::move(newState);
    if (mCurrentState) {
        mCurrentState->Enter();
    }
}

void StateMachine::Update(double dt) {
    if (mCurrentState) {
        mCurrentState->Update(dt);
    }
}

void StateMachine::Render() {
    if (mCurrentState) {
        mCurrentState->Render();
    }
}

void StateMachine::HandleEvent(const SDL_Event& event) {
    if (mCurrentState) {
        mCurrentState->HandleEvent(event);
    }
}
