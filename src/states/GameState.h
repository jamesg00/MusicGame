#pragma once
#include "utils/IState.h"
#include "core/Context.h"
#include "game/Chart.h"
#include "game/NoteSystem.h"
#include "game/Scoring.h"

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
    Chart mChart;
    NoteSystem mNoteSystem;
    Scoring mScoring;
    double mSongTime;
    size_t mNextNoteIndex;
};
